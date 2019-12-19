#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int interpret_intcode(int data_len, int *data) {
    int i;

    for (i = 0; i < data_len; i += 4) {
        if (data[i] == 99) {
            break;
        }
        else if (data[i] < 1 || data[i] > 2 || i + 3 >= data_len) {
            fprintf(stderr, "bad command at position %d\n", i);
            exit(1);
        }
        else if (data[i] == 1) {
            data[data[i+3]] = data[data[i+1]] + data[data[i+2]];
        }
        else if (data[i] == 2) {
            data[data[i+3]] = data[data[i+1]] * data[data[i+2]];
        }
    }

    return data_len ? data[0] : -1;
}

int main() {
    int i, j;
    FILE *fp;
    char *line = NULL;
    ssize_t read;
    size_t len = 0;
    int data_len = 0;
    int data_capacity = 8;
    int *data = malloc(sizeof(*data) * data_capacity);
    int *copy;

    if (!(fp = fopen("2.txt", "r"))) {
        perror("couldn't open '2.txt'");
        return 1;
    }

    for (; (read = getdelim(&line, &len, ',', fp)) != -1; free(line), (line = NULL)) {
        while (read + data_len >= data_capacity) {
            if (!(data = realloc(data, (data_capacity *= 2) * sizeof(*data)))) {
                perror("realloc failed");
                return 1;
            }
        }
        
        data[data_len++] = atoi(line);
    }

    free(line);
    fclose(fp);

    copy = malloc(sizeof(*data) * data_len);
    memcpy(copy, data, sizeof(*data) * data_len);
    copy[1] = 12;
    copy[2] = 2;
    printf("2.1 => %d\n", interpret_intcode(data_len, copy));

    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
            memcpy(copy, data, sizeof(*data) * data_len);
            copy[1] = i;
            copy[2] = j;

            if (interpret_intcode(data_len, copy) == 19690720) {
                printf("2.2 => %d\n", 100 * i + j);
                break;
            }
        }
    }
    
    free(data);
    free(copy);
    return 0;
}


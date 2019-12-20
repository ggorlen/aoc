#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "intcode.h"

int main() {
    FILE *fp;
    char *line = NULL;
    ssize_t read;
    size_t len = 0;
    int data_len = 0;
    int data_capacity = 8;
    int *data = malloc(sizeof(*data) * data_capacity);
    //int *copy;

    if (!(fp = fopen("5.txt", "r"))) {
        perror("couldn't open '5.txt'");
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

    //copy = malloc(sizeof(*data) * data_len);
    //memcpy(copy, data, sizeof(*data) * data_len);
    interpret_intcode(data_len, data);
    //printf("5.1 => %d\n", );
    
    free(data);
    //free(copy);
    return 0;
}


#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_longs(const char *s, long **res) {
    int len = strlen(s);
    int res_len = 0;
    *res = malloc(sizeof(**res));

    if (!res) {
        perror("failed to malloc");
        exit(1);
    }

    char current[50];
    int current_len = 0;

    for (int i = 0; i < len; i++) {
        if (isdigit(s[i]) && i < len - 1) {
            current[current_len++] = s[i];
        }
        else if (current_len) {
            res_len++;
            *res = realloc(*res, sizeof(**res) * res_len);

            if (!(*res)) {
                perror("failed to realloc");
                exit(1);
            }

            current[current_len] = '\0';
            (*res)[res_len-1] = atol(current);
            current_len = 0;
        }
    }

    return res_len;
}

int main() {
    const int max_width = 300;
    char line[max_width];
    FILE *fp;

    if (!(fp = fopen("5.txt", "r"))) {
        perror("couldn't open '5.txt'");
        return 1;
    }

    fgets(line, max_width, fp);
    long *seeds;
    int seeds_len = parse_longs(line, &seeds);
    assert(seeds_len > 0);
    bool seeds_processed[seeds_len];
    memset(seeds_processed, false, seeds_len);

    while (fgets(line, max_width, fp)) {
        const int len = strlen(line);

        if (len < 2 || !isdigit(line[0])) {
            memset(seeds_processed, false, seeds_len);
            continue;
        }

        long *digits;
        int digits_len = parse_longs(line, &digits);
        assert(digits_len == 3);
        long dst = digits[0];
        long src = digits[1];
        long length = digits[2];

        for (int i = 0; i < seeds_len; i++) {
            if (
                !seeds_processed[i] &&
                seeds[i] >= src && seeds[i] <= src + length
            ) {
                seeds_processed[i] = true;
                seeds[i] = seeds[i] - src + dst;
            }
        }

        free(digits);
    }

    long lowest = seeds[0];

    for (int i = 0; i < seeds_len; i++) {
        lowest = seeds[i] < lowest ? seeds[i] : lowest;
    }

    printf("%ld\n", lowest);
    fclose(fp);
    free(seeds);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/utils.h"

int main() {
    FILE *f = fopen("3.txt", "r");
    char *lp;
    char line[32];
    unsigned int id, i, j, row, col, width, height;
    size_t side_len = 1100;
    char overlaps[1500] = {0};
    short *matrix = malloc(sizeof(*matrix) * 1210000);
    memset(matrix, -1, sizeof(*matrix) * 1210000);
    
    for (id = 1; fgets(line, 32, f); id++) {
        lp = line;
        parse_number(&lp);
        row = parse_number(&lp);
        col = parse_number(&lp);
        width = parse_number(&lp);
        height = parse_number(&lp);
        overlaps[id] = 1;
        
        for (i = row; i < row + width; i++) {
            for (j = col; j < col + height; j++) {
                if (matrix[i*side_len+j] < 0) {
                    matrix[i*side_len+j] = id;
                }
                else if (matrix[i*side_len+j] > 0) {
                    overlaps[matrix[i*side_len+j]] = 0;
                    overlaps[id] = 0;
                }
            }
        }
    }

    for (i = 0; i < 1500; i++) {
        if (overlaps[i] == 1) {
            printf("%d\n", i);
        }
    }

    fclose(f);
    free(matrix);
    return 0;
}

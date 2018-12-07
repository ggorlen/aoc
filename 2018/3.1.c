#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_number(char **line) {
    char res[16];
    int i;

    for ((*line)++; **line && !isdigit(**line); (*line)++);

    for (i = 0; **line && isdigit(**line); (*line)++) {
        res[i++] = **line;
    }

    res[i] = '\0';
    return atoi(res);
}

int main() {
    FILE *f = fopen("3.txt", "r");
    char *lp;
    char line[32];
    unsigned int i, j, row, col, width, height;
    unsigned int total_overlap = 0;
    char *matrix = malloc(sizeof(*matrix) * 1210000);
    size_t matrix_side_len = 1100;
    
    while (fgets(line, 32, f)) {
        lp = line;
        parse_number(&lp);
        row = parse_number(&lp);
        col = parse_number(&lp);
        width = parse_number(&lp);
        height = parse_number(&lp);
        
        for (i = row; i < row + width; i++) {
            for (j = col; j < col + height; j++) {
                if (matrix[i*matrix_side_len+j] == 0) {
                    matrix[i*matrix_side_len+j] = 1;
                }
                else if (matrix[i*matrix_side_len+j] == 1) {
                    matrix[i*matrix_side_len+j] = 2;
                    total_overlap++;
                }
            }
        }
    }

    printf("%d\n", total_overlap);
    fclose(f);
    free(matrix);
    return 0;
}

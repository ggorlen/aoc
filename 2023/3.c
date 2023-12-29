#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int max_width = 150;
    int width = max_width;
    char line[width];
    int lines_len = 0;
    FILE *fp;
    char **lines = malloc(sizeof(*lines));

    if (!(fp = fopen("3.txt", "r"))) {
        perror("couldn't open '3.txt'");
        return 1;
    }

    while (fgets(line, max_width, fp)) {
        int len = strlen(line);
        line[len-1] = '\0';
        width = len - 1;
        lines_len++;
        lines = realloc(lines, lines_len * sizeof(*lines));
        lines[lines_len-1] = malloc(width + 1);
        strcpy(lines[lines_len-1], line);
    }

    int total = 0;
    int gearTotal = 0;

    for (int i = 0; i < lines_len; i++) {
        for (int j = 0; j < width; j++) {
            if (isdigit(lines[i][j]) || lines[i][j] == '.') {
                continue;
            }

            int adjacent = 0;
            int gears = 1;

            for (int dx = -1; dx < 2; dx++) {
                for (int dy = -1; dy < 2; dy++) {
                    int x = dx + j;
                    int y = dy + i;

                    if (
                        y >= 0 && y < lines_len &&
                        x >= 0 && x < width &&
                        isdigit(lines[y][x])
                    ) {
                        char num[32] = {};
                        int num_len = 0;

                        while (x >= 0 && isdigit(lines[y][x])) {
                            x--;
                        }

                        if (x < 0 || !isdigit(lines[y][x])) {
                            x++;
                        }

                        while (x < width && isdigit(lines[y][x])) {
                            num[num_len++] = lines[y][x];
                            lines[y][x] = '.';
                            x++;
                        }

                        adjacent++;
                        total += atoi(num);
                        gears *= atoi(num);
                    }
                }
            }

            if (lines[i][j] == '*' && adjacent == 2) {
                gearTotal += gears;
            }
        }
    }

    printf("%d\n", total);
    printf("%d\n", gearTotal);

    for (int i = 0; i < lines_len; i++) {
        free(lines[i]);
    }

    free(lines);
    fclose(fp);
    return 0;
}

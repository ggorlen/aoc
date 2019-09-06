#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct cell {
    int x;
    int y;
    bool visited;
};

int main() {
    int x, y, i;
    int total = 0;
    int threshold = 10000;
    int grid_len = 0;
    int points_len = 0;
    struct cell *points = malloc(sizeof(*points));
    struct cell **grid;
    FILE *f = fopen("6.txt", "r");
    
    while (fscanf(f, "%d, %d\n", &x, &y) != EOF) {
        points = realloc(points, (points_len + 1) * sizeof(*points));
        points[points_len].x = x;
        points[points_len++].y = y;
        grid_len = x > grid_len ? x : grid_len;
        grid_len = y > grid_len ? y : grid_len;
    }

    fclose(f);

    if (!grid_len) { 
        return 1; 
    }

    grid = malloc(sizeof(*grid) * grid_len);

    for (y = 0; y < grid_len; y++) {
        grid[y] = malloc(sizeof(*grid[y]) * grid_len);

        for (x = 0; x < grid_len; x++) {
            int dist_sum = 0;

            for (i = 0; i < points_len; i++) {
                dist_sum += abs(points[i].x - x) + abs(points[i].y - y);
            }

            grid[y][x].visited = dist_sum >= threshold;
        }
    }

    for (y = 0; y < grid_len; y++) {
        for (x = 0; x < grid_len; x++) {
            total += !grid[y][x].visited;
        }

        free(grid[y]);
    }

    free(grid);
    free(points);
    printf("%d\n", total);
    return 0;
}


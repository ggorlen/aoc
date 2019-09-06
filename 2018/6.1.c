#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct cell {
    int x;
    int y;
    bool visited;
};

int get_size(int width, int height, int x, int y, struct cell **grid) {
    struct cell dirs[4] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    int i, size = 1;

    if (x <= 0 || x >= width - 1 || y >= height - 1 || y <= 0) {
        return -1;
    }
    else if (grid[y][x].visited) {
        return 0;
    }

    grid[y][x].visited = true;

    for (i = 0; i < 4; i++) {
        int new_x = x + dirs[i].x;
        int new_y = y + dirs[i].y;

        if (grid[new_y][new_x].x == grid[y][x].x && 
            grid[new_y][new_x].y == grid[y][x].y) {
            int new_size = get_size(width, height, new_x, new_y, grid);

            if (new_size < 0) {
                return new_size;
            }
            
            size += new_size;
        }
    }
    
    return size;
}

int main() {
    int x, y, i;
    int grid_len = 0;
    int points_len = 0;
    int largest = 0;
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
            int closest = grid_len * 2;

            for (i = 0; i < points_len; i++) {
                int dist = abs(points[i].x - x) + abs(points[i].y - y);
    
                if (dist == closest) {
                    grid[y][x].visited = true;
                }
                else if (dist < closest) {
                    closest = dist;
                    grid[y][x].visited = false;
                    grid[y][x].x = points[i].x;
                    grid[y][x].y = points[i].y;
                }
            }
        }
    }

    for (y = 0; y < grid_len; y++) {
        for (x = 0; x < grid_len; x++) {
            int size = get_size(grid_len, grid_len, x, y, grid);
         
            if (size > largest) {
                largest = size;
            }
        }
    }

    for (i = 0; i < grid_len; i++) {
        free(grid[i]);
    }

    free(grid);
    free(points);
    printf("%d\n", largest);
    return 0;
}

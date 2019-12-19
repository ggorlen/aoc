#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
    int x;
    int y;
    int steps;
};

struct line {
    struct point *src;
    struct point *dst;
};

struct list {
    void **data;
    int len;
    int capacity;
};

int list_resize(struct list *L) {
    if (L->len >= L->capacity - 1 &&
        (!(L->data = realloc(L->data, (L->capacity *= 2) * sizeof(*(L->data)))))) {
        perror("realloc failed");
        return -1;
    }

    return 0;
}

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

struct point *lines_intersection(struct line *a, struct line *b) {
    if (a->src->y != a->dst->y && b->src->y == b->dst->y) {
        struct line *tmp = a;
        a = b;
        b = tmp;
    }

    if (a->src->x != a->dst->x && b->src->x == b->dst->x) {
        int aLeftX = min(a->src->x, a->dst->x);
        int aRightX = max(a->src->x, a->dst->x);
        int bTopY = max(b->src->y, b->dst->y);
        int bBotY = min(b->src->y, b->dst->y);

        if (a->src->y <= bTopY && a->src->y >= bBotY && 
            aLeftX <= b->src->x && aRightX >= b->src->x) {
            struct point *res = malloc(sizeof(*res));
            res->x = b->src->x;
            res->y = a->src->y;
            return res;
        }
    }

    return NULL;
}

int get_steps(struct line *L, struct point *intersection) {
    if (L->src->x == L->dst->x) {
        return L->src->steps + abs(L->src->y - intersection->y);
    }

    return L->src->steps + abs(L->src->x - intersection->x);
}

int main() {
    int i, j;
    FILE *fp;
    char *line = NULL;
    ssize_t read;
    size_t len = 0;
    int dirs_len = 0;
    struct list **dirs = malloc(sizeof(*dirs));
    struct list **lines;

    if (!(fp = fopen("3.txt", "r"))) {
        perror("couldn't open '3.txt'");
        return 1;
    }

    for (; (read = getdelim(&line, &len, ',', fp)) != -1; free(line), (line = NULL)) {
        if (dirs_len <= 0 || (strchr(line, '\n') && strchr(line, ','))) {
            if (!(dirs = realloc(dirs, sizeof(*dirs) * (dirs_len + 1)))) {
                perror("realloc failed");
                return 1;
            }

            struct list *d = malloc(sizeof(*dirs[dirs_len]));
            dirs[dirs_len++] = d;
            d->capacity = 8;
            d->len = 0;
            d->data = malloc(sizeof(*(d->data)) * d->capacity);
        }
        
        struct list *d = dirs[dirs_len-1];
        list_resize(d);

        if (strchr(line, '\n') && strchr(line, ',')) {
            char *second = strchr(line, '\n') + 1;
            d->data[d->len] = malloc(sizeof(*(d->data[d->len])) * read);
            *strchr(second, ',') = '\0';
            strcpy(d->data[d->len++], second);
            *(strchr(line, '\n') + 1) = '\0';
            read = strlen(line);
            d = dirs[dirs_len-2];
        }

        d->data[d->len] = malloc(sizeof(*(d->data[d->len])) * read);
        line[read-1] = '\0';
        strcpy(d->data[d->len++], line);
    }

    free(line);
    fclose(fp);
    lines = malloc(sizeof(*lines) * dirs_len);

    for (i = 0; i < dirs_len; i++) {
        int x = 0;
        int y = 0;
        int steps = 0;
        struct list *line = malloc(sizeof(*lines[i]));
        lines[i] = line;
        line->capacity = 8;
        line->len = 0;
        line->data = malloc(sizeof(struct line *) * line->capacity);
    
        for (j = 0; j < dirs[i]->len; j++) {
            int prevX = x;
            int prevY = y;
            char *dir = dirs[i]->data[j];

            if (dir[0] == 'U') {
                y += atoi(dir + 1);
            }
            else if (dir[0] == 'D') {
                y += -atoi(dir + 1);
            }
            else if (dir[0] == 'L') {
                x += -atoi(dir + 1);
            }
            else if (dir[0] == 'R') {
                x += atoi(dir + 1);
            }

            struct line *L = malloc(sizeof(struct line));
            L->src = malloc(sizeof(struct point));
            L->dst = malloc(sizeof(struct point));
            L->src->x = prevX;
            L->src->y = prevY;
            L->dst->x = x;
            L->dst->y = y;
            L->src->steps = steps;
            steps += atoi(dir + 1);
            L->dst->steps = steps;
            list_resize(line);
            line->data[line->len++] = L;
        }
    }

    int best_dist_manhattan = 2147483647;
    int best_dist_steps = 2147483647;

    for (i = 0; i < lines[0]->len; i++) {
        struct line *a = (struct line *)lines[0]->data[i];

        for (j = 0; j < lines[1]->len; j++) {
            struct line *b = (struct line *)lines[1]->data[j];
            struct point *intersect = lines_intersection(a, b);

            if (intersect) {
                int manhattan_dist = abs(intersect->x) + abs(intersect->y);

                if (manhattan_dist && manhattan_dist < best_dist_manhattan) {
                    best_dist_manhattan = manhattan_dist;
                }

                int steps = get_steps(a, intersect) + get_steps(b, intersect);

                if (steps && steps < best_dist_steps) {
                    best_dist_steps = steps;
                }
            }

            free(intersect);
        }
    }
    
    for (i = 0; i < dirs_len; i++) {
        for (j = 0; j < dirs[i]->len; j++) {
            free(dirs[i]->data[j]);
        }

        for (j = 0; j < dirs[i]->len; j++) {
            struct line *L = (struct line *)lines[i]->data[j];
            free(L->src);
            free(L->dst);
            free(lines[i]->data[j]);
        }

        free(dirs[i]->data);
        free(dirs[i]);
        free(lines[i]->data);
        free(lines[i]);
    }

    free(dirs);
    free(lines);

    printf("part 1: %d\npart 2: %d\n", best_dist_manhattan, best_dist_steps);
    return 0;
}


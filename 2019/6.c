#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *name;
    int orbits;
    int back_len;
    int *back;
};

int index_of(int len, struct node **nodes, char *target) {
    int i;

    for (i = 0; i < len; i++) {
        if (!strcmp(nodes[i]->name, target)) {
            return i;
        }
    }

    return -1;
}

void resize(int len, int *capacity, struct node ***L) {
    if (len >= (*capacity) - 1 &&
        !(*L = realloc(*L, sizeof(**L) * (*capacity *= 2)))) {
        fprintf(stderr, "realloc failed\n");
        exit(1);
    }
}

int add(int *nodes_len, int *nodes_capacity, 
        struct node ***nodes, char *name) {
    resize(*nodes_len, nodes_capacity, nodes);
    int len = *nodes_len;
    (*nodes)[len] = malloc(sizeof((**nodes)[len]));
    (*nodes)[len]->name = strdup(name);
    (*nodes)[len]->back_len = 0;
    (*nodes)[len]->back = malloc(sizeof((*nodes)[len]->back));
    (*nodes)[len]->orbits = -1;
    return (*nodes_len)++;
}

int minimum_xfers(int len, struct node **nodes, int start, int end) {
    int i;
    int front = 0;
    int back = 1;
    int q[len][2];
    bool visited[len];
    memset(visited, false, len * sizeof(*visited));
    q[front][0] = start;
    q[front][1] = 0;

    while (back != front) {
        int node = q[front][0];
        int steps = q[front][1];
        front = (front + 1) % len;

        if (node == end) {
            return steps - 2;
        }
        else if (node >= 0 && !visited[node]) {
            visited[node] = true;
            q[back][0] = nodes[node]->orbits;
            q[back][1] = steps + 1;
            back = (back + 1) % len;

            for (i = 0; i < nodes[node]->back_len; i++) {
                q[back][0] = nodes[node]->back[i];
                q[back][1] = steps + 1;
                back = (back + 1) % len;
            }
        }
    }
    
    return -1;
}

int main() {
    int i, j;
    FILE *fp;
    int line_len = 9;
    char line[line_len];
    int nodes_len = 0;
    int nodes_capacity = 8;
    struct node **nodes = malloc(sizeof(*nodes) * nodes_capacity);
    int total = 0;

    if (!(fp = fopen("6.txt", "r"))) {
        perror("couldn't open '6.txt'");
        return 1;
    }

    while (fgets(line, line_len, fp)) {
        line[strlen(line)-1] = '\0';
        char *src = strchr(line, ')');
        char *dst = line;
        *src = '\0';
        src++;

        if ((i = index_of(nodes_len, nodes, src)) < 0) {
            i = add(&nodes_len, &nodes_capacity, &nodes, src);
        }

        if ((j = index_of(nodes_len, nodes, dst)) < 0) {
            j = add(&nodes_len, &nodes_capacity, &nodes, dst);
        }

        nodes[i]->orbits = j;
        struct node *nj = nodes[j];
        nj->back = realloc(nj->back, ++(nj->back_len) * 
                                     sizeof(*nj->back));
        nj->back[nj->back_len-1] = i;
    }

    for (i = 0; i < nodes_len; i++) {
        struct node *n = nodes[i];

        for (; n->orbits >= 0; total++, n = nodes[n->orbits]);
    }

    int you_idx = index_of(nodes_len, nodes, "YOU");
    int santa_idx = index_of(nodes_len, nodes, "SAN");
    printf("part 1 => %d\npart 2 => %d\n", total, 
           minimum_xfers(nodes_len, nodes, you_idx, santa_idx));

    for (i = 0; i < nodes_len; i++) {
        free(nodes[i]->name);
        free(nodes[i]->back);
        free(nodes[i]);
    }

    free(nodes);
    fclose(fp);
    return 0;
}


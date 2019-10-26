#include <stdio.h>
#include <stdlib.h>

struct node {
    int metadata_len;
    int children_len;
    int *metadata;
    struct node **children;
};

static struct node *build_tree_r(int *i, int data_len, int *data) {
    int j;
    struct node *new_node = malloc(sizeof(*new_node));
    new_node->children_len = data[(*i)++];
    new_node->metadata_len = data[(*i)++];

    if (new_node->children_len) {
        int children_size = sizeof(*(new_node->children)) * new_node->children_len;
        new_node->children = malloc(children_size);
    }

    if (new_node->metadata_len) {
        int metadata_size = sizeof(*(new_node->metadata)) * new_node->metadata_len;
        new_node->metadata = malloc(metadata_size);
    }

    for (j = 0; j < new_node->children_len; j++) {
        new_node->children[j] = build_tree_r(i, data_len, data);
    }

    for (j = 0; j < new_node->metadata_len; j++) {
        new_node->metadata[j] = data[(*i)++];
    }

    return new_node;
}

struct node *build_tree(int data_len, int *data) {
    int i = 0;
    return build_tree_r(&i, data_len, data);
}

void free_tree(struct node *root) {
    if (root) {
        int i;

        for (i = 0; i < root->children_len; i++) {
            free_tree(root->children[i]);
        }

        free(root);
    }
}

int sum_tree_metadata(struct node *root) {
    if (!root) return 0;

    int i;
    int sum = 0;
        
    for (i = 0; i < root->children_len; i++) {
        sum += sum_tree_metadata(root->children[i]);
    }

    for (i = 0; i < root->metadata_len; i++) {
        sum += root->metadata[i];
    }

    return sum;
}

int root_val_from_child_refs(struct node *root) {
    if (!root) return 0;

    int i;
    int sum = 0;
        
    if (root->children_len) {
        for (i = 0; i < root->metadata_len; i++) {
            if (root->metadata[i] <= root->children_len) {
                sum += root_val_from_child_refs(root->children[root->metadata[i]-1]);
            }
        }
    }
    else {
        for (i = 0; i < root->metadata_len; i++) {
            sum += root->metadata[i];
        }
    }

    return sum;
}

int main() {
    FILE *fp;
    char *line = NULL;
    ssize_t read;
    size_t len = 0;
    int data_len = 0;
    int data_capacity = 8;
    int *data = malloc(sizeof(*data) * data_capacity);

    if (!(fp = fopen("8.txt", "r"))) {
        perror("couldn't open '8.txt'");
        return 1;
    }

    for (; (read = getdelim(&line, &len, ' ', fp)) != -1; free(line), (line = NULL)) {
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
    struct node *root = build_tree(data_len, data);
    free(data);
    printf("%d\n%d\n", sum_tree_metadata(root), root_val_from_child_refs(root));
    free_tree(root);
    return 0;
}


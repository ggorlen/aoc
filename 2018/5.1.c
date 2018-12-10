#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    struct node *next;
    char data;
} node;

node *node_create() {
    node *head = malloc(sizeof(*head));
    memset(head, 0, sizeof(*head));
    return head;
}

void list_add(node **head, char data) {
    node *new_head = node_create();
    new_head->data = data;
    new_head->next = *head;
    *head = new_head;
}

void list_destroy(node *head) {
    while (head) {
        node *temp = head;
        head = head->next;
        free(temp);
    }
}

node *list_remove(node *prev, node *curr, node **head) {
    node *next = curr->next;

    if (prev) {
        prev->next = curr->next;
    }
    else {
        *head = curr->next;
    }

    free(curr);
    return next;
}

int react(int polymer_len, node *head) {
    node *prev, *curr;
    int reacted = 1;

    while (reacted) {
        reacted = 0;

        for (curr = head, prev = NULL; curr && curr->next;
             prev = curr, curr = curr->next) {

            if ((isupper(curr->data) && 
                 tolower(curr->data) == curr->next->data) || 
                (isupper(curr->next->data) && 
                 tolower(curr->next->data) == curr->data)) {
                curr = list_remove(prev, curr, &head);
                curr = list_remove(prev, curr, &head);
                polymer_len -= 2;
                reacted = 1;
            }
        }
    }

    return polymer_len;
}

int main() {
    int i;
    int polymer_len = 50000;
    char polymer[polymer_len];
    FILE *f = fopen("5.txt", "r");
    fgets(polymer, polymer_len + 1, f);

    node *head = node_create();
    head->data = polymer[polymer_len-1];

    for (i = polymer_len - 2; i >= 0; i--) {
        list_add(&head, polymer[i]);
    }

    printf("%d\n", react(polymer_len, head));
    fclose(f);
    list_destroy(head);
    return 0;
}

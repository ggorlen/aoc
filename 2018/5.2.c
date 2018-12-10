#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct node {
    struct node *next;
    char data;
} node;

typedef struct task {
    char letter;
    node *head;  
    int *results;
} task;

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
        free(curr);
    }
    else {
        *head = curr->next;
        // free(curr)
    }

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

int remove_all_ignore_case(char needle, node **head) {
    node *prev = NULL;
    node *curr = *head;
    int len = 0;
    
    while (curr) {
        if (tolower(curr->data) == needle || 
            toupper(curr->data) == needle) {
            curr = list_remove(prev, curr, head);
        }
        else {
            prev = curr;
            curr = curr->next;
            len++;
        }
    }

    return len - 1;
}

node *list_copy(node *head) {
    node *new_head = node_create();
    node *curr = new_head;

    while (head) {
        curr->data = head->data;
        curr->next = node_create();
        curr = curr->next;
        head = head->next;
    }

    return new_head;
}

void *work(void *arg) { 
    task *t = (task *)arg;
    node *head = list_copy(t->head);
    int len = remove_all_ignore_case(t->letter, &head);
    t->results[t->letter-65] = react(len, head);
    list_destroy(head);
    free(t);
    return NULL;
}

int main() {
    int i;
    int polymer_len = 50000;
    int best = polymer_len;
    char polymer[polymer_len];
    char alpha[26];
    int results[26];
    pthread_t threads[26];
    FILE *f = fopen("5.txt", "r");
    fgets(polymer, polymer_len + 1, f);
    fclose(f);

    node *head = node_create();
    head->data = polymer[polymer_len-1];

    for (i = polymer_len - 2; i >= 0; i--) {
        list_add(&head, polymer[i]);
    }

    for (i = 0; i < 26; i++) {
        pthread_t thread;
        alpha[i] = i + 65;
        task *t = malloc(sizeof(*t));
        t->letter = alpha[i];
        t->head = head;
        t->results = results;
        pthread_create(&thread, NULL, work, t);
        threads[i] = thread;
    }

    for (i = 0; i < 26; i++) {
        pthread_join(threads[i], NULL);
        best = best < results[i] ? best : results[i];
        printf("%c %d\n", i + 65, results[i]);
    }

    printf("\nbest: %d\n", best);
    list_destroy(head);
    return 0;
}

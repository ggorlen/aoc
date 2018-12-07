#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int i, digit, current;
    int freq_len = 0;
    int freq[1000];
    int len = 100000;
    char *seen = malloc(len * sizeof(*seen));
    char *neg_seen = malloc(len * sizeof(*neg_seen));
    FILE *f = fopen("1.txt", "r");

    if (!seen || !neg_seen) { 
        puts("malloc failed"); 
        exit(1);
    }

    memset(seen, 0, len * sizeof(*seen));
    memset(neg_seen, 0, len * sizeof(*neg_seen));

    while (fscanf(f, "%d\n", &digit) != EOF) {
        freq[freq_len++] = digit;
    }

    for (i = 0, current = 0;; i = (1 + i) % freq_len) {
        current += freq[i];

        if ((current < 0 && neg_seen[0-current] == 1) || 
            (current >= 0 && seen[current] == 1)) {
            break;
        }
        else if (current < 0) {
            neg_seen[0-current] = 1;
        }
        else {
            seen[current] = 1;
        }
    }

    printf("%d\n", current);
    fclose(f);
    free(seen);
    free(neg_seen);
    return 0;
}

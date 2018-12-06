#include <stdio.h>

int main() {
    int i, digit, current;
    unsigned short seen[100000] = {0};
    unsigned short neg_seen[100000] = {0};
    int freq[100000];
    int freq_len = 0;
    FILE *fd = fopen("1.txt", "r");

    while (fscanf(fd, "%d\n", &digit) != EOF) {
        freq[freq_len++] = digit;
    }

    for (i = 0, current = 0;; i = ++i % freq_len) {
        current += freq[i];

        if (current < 0 && neg_seen[current]++ > 0 || seen[current]++ > 0) {
            break;
        }
    }

    printf("%d\n", current);
    return 0;
}

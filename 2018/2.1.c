#include <stdio.h>
#include <string.h>

int main() {
    int i;
    int twos = 0;
    int threes = 0;
    FILE *f = fopen("2.txt", "r");
    unsigned short counts[128];
    char line[32];

    while (fgets(line, 32, f)) {
        memset(counts, 0, 128 * sizeof(unsigned short));

        for (i = strlen(line) - 1; i >= 0; i--) { 
            counts[line[i]-'0']++;
        }

        for (i = 0; i < 128; i++) {
            if (counts[i] == 2) {
                twos++;
                break;
            }
        }

        for (i = 0; i < 128; i++) {
            if (counts[i] == 3) {
                threes++;
                break;
            }
        }
    }

    printf("%d\n", twos * threes);
    fclose(f);
    return 0;
}

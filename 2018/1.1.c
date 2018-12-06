#include <stdio.h>

int main() {
    FILE *f = fopen("1.txt", "r");
    int digit, current = 0;

    while (fscanf(f, "%d\n", &digit) != EOF) {
        current += digit;
    }

    printf("%d\n", current);
    fclose(f);
    return 0;
}

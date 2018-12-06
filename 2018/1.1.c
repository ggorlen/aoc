#include <stdio.h>

int main() {
    FILE *fd = fopen("1.txt", "r");
    int digit, current = 0;

    while (fscanf(fd, "%d\n", &digit) != EOF) {
        current += digit;
    }

    printf("%d\n", current);
    return 0;
}

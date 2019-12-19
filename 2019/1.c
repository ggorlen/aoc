#include <stdio.h>

int main() {
    FILE *f = fopen("1.txt", "r");
    int mass; 
    int regular_total = 0;
    int recursive_total = 0;

    while (fscanf(f, "%d\n", &mass) != EOF) {
        regular_total += mass / 3 - 2;

        while ((mass = mass / 3 - 2) > 0) {
            recursive_total += mass;
        }
    }

    printf("regular: %d, recursive: %d\n", regular_total, recursive_total);
    fclose(f);
    return 0;
}


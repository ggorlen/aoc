#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("2.txt", "r");
    char ids[250][32];
    int ids_len = 0;
    char line[32];
    int i, j, k, id_len, errors;

    while (fgets(line, 32, f)) {
        strcpy(ids[ids_len++], line);
    }

    for (i = 0; i < ids_len; i++) {
        id_len = strlen(ids[i]);

        for (j = i + 1; j < ids_len; j++) {
            errors = 0;

            for (k = 0; k < id_len && errors < 2; k++) {
                if (ids[i][k] != ids[j][k]) {
                    errors++;
                }
            }

            if (errors < 2) {
                for (k = 0; k < id_len; k++) {
                    if (ids[i][k] == ids[j][k]) {
                        putchar(ids[i][k]);
                    }
                }
            }
        }
    }

    fclose(f);
    return 0;
}

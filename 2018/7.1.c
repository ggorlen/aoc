#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main() {
    int i, j;
    bool keep_going;
    char line[50];
    bool deps[26][26];
    int seq[26];
    int seq_len = 0;
    FILE *f = fopen("7.txt", "r");
    memset(deps, false, sizeof(deps));

    while (fgets(line, 50, f)) {
        deps[line[36]-65][line[5]-65] = true;
    }

    fclose(f);

    for (keep_going = true; keep_going;) {
        for (keep_going = false, i = 0; i < 26; i++) {
            bool has_deps = false;

            for (j = 0; j < 26 && !has_deps; j++) {
                if (deps[i][j]) {
                    has_deps = true;
                }
            }

            if (!has_deps) {
                for (j = 0; j < 26; j++) {
                    deps[j][i] = false;
                    deps[i][j] = true;
                }

                seq[seq_len++] = i;
                keep_going = true;
                break;
            }
        }
    }

    for (i = 0; i < 26; i++) {
        printf("%c", seq[i] + 65);
    }

    puts("");
    return 0;
}


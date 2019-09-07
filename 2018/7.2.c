#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct worker {
    int task_id;
    int seconds_remaining;
};

int main() {
    int i, j;
    int workers_len = 5;
    int work_time = 61;
    int tasks = 26;
    int remaining = tasks;
    int seconds = 0;
    struct worker workers[workers_len];
    bool deps[tasks][tasks];
    bool done[tasks];
    char line[50];
    FILE *fp = fopen("7.txt", "r");
    memset(deps, false, sizeof(deps));
    memset(done, false, sizeof(done));
    memset(workers, 0, sizeof(workers));

    while (fgets(line, 50, fp)) {
        deps[line[36]-65][line[5]-65] = true;
    }

    fclose(fp);

    for (; remaining; seconds++) {
        for (i = 0; i < tasks; i++) {
            if (done[i]) continue;

            bool has_deps = false;

            for (j = 0; !has_deps && j < tasks; j++) {
                if (deps[i][j]) {
                    has_deps = true;
                }
            }

            if (!has_deps) {
                for (j = 0; j < workers_len; j++) {
                    if (!workers[j].seconds_remaining) {
                        done[i] = true;
                        workers[j].seconds_remaining = i + work_time;
                        workers[j].task_id = i;
                        break;
                    }
                }
            }
        }

        for (i = 0; i < workers_len; i++) {
            if (workers[i].seconds_remaining &&
                !--workers[i].seconds_remaining) {

                for (j = 0; j < tasks; j++) {
                    deps[j][workers[i].task_id] = false;
                }

                remaining--;
            }
        }
    }

    printf("%d\n", seconds);
    return 0;
}


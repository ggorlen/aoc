#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/utils.h"

enum state { ON_DUTY, ASLEEP, AWAKE };

typedef struct event_t {
    int month;
    int day;
    int hour;
    int minute;
    int id;
    int state;
} event_t;

int cmp(const void *x, const void *y) {
    event_t *a = *(event_t **)x;
    event_t *b = *(event_t **)y;
   
    if (a->month != b->month) {
        return a->month - b->month;
    }
    else if (a->day != b->day) {
        return a->day - b->day;
    }
    else if (a->hour != b->hour) {
        return a->hour - b->hour;
    }
    else if (a->minute != b->minute) {
        return a->minute - b->minute;
    }

    return 0;
}

int main() {
    event_t *event;
    char line[64];
    char *lp;
    int i, j, on_duty, fell_asleep, max_id, max_minute, best, max_asleep;
    int minutes_asleep[4000][60];
    int sleep_time[4000] = {0};
    FILE *f = fopen("4.txt", "r");
    size_t events_len = 0;
    event_t *events[1100];
    
    for (i = 0; i < 4000; i++) {
        for (j = 0; j < 60; j++) {
            minutes_asleep[i][j] = 0;
        }
    }
    
    while (fgets(line, 64, f)) {
        event = malloc(sizeof(*event));
        memset(event, -1, sizeof(*event));
        events[events_len++] = event;
        lp = line;
        parse_number(&lp);
        event->month = parse_number(&lp);
        event->day = parse_number(&lp);
        event->hour = parse_number(&lp);
        event->minute = parse_number(&lp);

        if (strstr(line, "begins shift")) {
            event->id = parse_number(&lp);
            event->state = ON_DUTY;
        }
        else if (strstr(line, "falls asleep")) {
            event->state = ASLEEP;
        }
        else if (strstr(line, "wakes up")) {
            event->state = AWAKE;
        }
    }

    qsort(&events, events_len, sizeof(event_t *), cmp);
    
    for (i = 0; i < events_len; i++) {
        switch (events[i]->state) {
        case ON_DUTY:
            on_duty = events[i]->id;
            break;
        case ASLEEP:
            fell_asleep = events[i]->minute;
            break;
        case AWAKE:
            sleep_time[on_duty] += events[i]->minute - fell_asleep;

            for (j = fell_asleep; j < events[i]->minute; j++) {
                minutes_asleep[on_duty][j]++;
            }

            break;
        }
    }

    for (max_asleep = 0, i = 0; i < 4000; i++) {
        if (sleep_time[i] > max_asleep) {
            max_asleep = sleep_time[i];
            max_id = i;
            best = 0;

            for (j = 0; j < 60; j++) {
                if (best < minutes_asleep[i][j]) {
                    best = minutes_asleep[i][j];
                    max_minute = j;
                }
            }
        }
    }

    printf("4.1: %d\n", max_id * max_minute);

    for (max_asleep = 0, i = 0; i < 4000; i++) {
        for (j = 0; j < 60; j++) {
            if (minutes_asleep[i][j] > max_asleep) {
                max_asleep = minutes_asleep[i][j];
                max_id = i;
                max_minute = j;
            }
        }
    }

    printf("4.2: %d\n", max_id * max_minute);

    for (i = 0; i < events_len; i++) {
        free(events[i]);
    }
    
    fclose(f);
    return 0;
}

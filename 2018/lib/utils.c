#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int parse_number(char **line) {
    char res[16];
    int i;

    for ((*line)++; **line && !isdigit(**line); (*line)++);

    for (i = 0; **line && isdigit(**line); (*line)++) {
        res[i++] = **line;
    }

    res[i] = '\0';
    return atoi(res);
}

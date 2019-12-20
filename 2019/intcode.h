#ifndef __INTCODDE_H__

#include <math.h>
#include <stdio.h>

int mode(int *data, int idx, int offset) {
    if (data[idx] / (int)pow(10, offset + 1) % 10) {
        return data[idx+offset];
    }

    return data[data[idx+offset]];
}

typedef void (*op)(int *data, int *ip);

void add(int *data, int *ip) {
    data[data[(*ip)+3]] = mode(data, *ip, 1) + mode(data, *ip, 2);
    *ip += 4;
}

void mul(int *data, int *ip) {
    data[data[(*ip)+3]] = mode(data, *ip, 1) * mode(data, *ip, 2);
    *ip += 4;
}

void input(int *data, int *ip) {
    int digit;
    printf("> ");
    scanf("%d", &digit);
    data[data[(*ip)+1]] = digit;
    *ip += 2;
}

void output(int *data, int *ip) {
    printf("%d\n", mode(data, *ip, 1));
    *ip += 2;
}

void jz(int *data, int *ip) {
    if (mode(data, *ip, 1)) {
        *ip = mode(data, *ip, 2);
    }
    else {
        *ip += 3;
    }
}

void jnz(int *data, int *ip) {
    if (!mode(data, *ip, 1)) {
        *ip = mode(data, *ip, 2);
    }
    else {
        *ip += 3;
    }
}

void lt(int *data, int *ip) {
    data[data[(*ip)+3]] = mode(data, *ip, 1) < mode(data, *ip, 2) ? 1 : 0;
    *ip += 4;
}

void eq(int *data, int *ip) {
    data[data[(*ip)+3]] = mode(data, *ip, 1) == mode(data, *ip, 2) ? 1 : 0;
    *ip += 4;
}

int interpret_intcode(int data_len, int *data) {
    static op ops[10] = {
        NULL, &add, &mul, &input, &output,
        &jz, &jnz, &lt, &eq
    };
    int ip = 0;

    while (ip < data_len) {
        int opcode = data[ip] % 100;

        if (opcode == 99) {
            break;
        }

        ops[opcode](data, &ip);
    }

    return data_len ? data[0] : -1;
}

#endif

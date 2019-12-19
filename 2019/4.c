#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool ascending_digits(int n) {
    if (n < 10) return true;
    if (n % 10 < n / 10 % 10) return false;
    return ascending_digits(n / 10);
}

bool repeating_digit(int n) {
    for (n = abs(n); n > 9; n /= 10) {
        if (n % 10 == n / 10 % 10) return true;
    }

    return false;
}

bool repeating_digit_pair(int n) {
    char digits[16];
    sprintf(digits, "%d", abs(n));

    for (int i = 0, len = strlen(digits); i < len; i++) {
        if (digits[i] == digits[i+1] && 
            (i > len - 3 || digits[i] != digits[i+2]) && 
            (!i || digits[i-1] != digits[i])) {
            return true;
        }
    }
    
    return false;
}

int main() {
    int from = 240920;
    int to = 789857;
    int total_pt1 = 0;
    int total_pt2 = 0;
    
    for (int i = from; i < to; i++) {
        if (ascending_digits(i)) {
            if (repeating_digit(i)) {
                total_pt1++;
            }
            
            if (repeating_digit_pair(i)) {
                total_pt2++;
            }
        }
    }

    printf("part 1: %d\npart 2: %d\n", total_pt1, total_pt2);
    return 0;
}

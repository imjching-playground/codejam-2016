#include <stdio.h>

int valid(flag) {
    unsigned int mask = (1 << 10) - 1;
    return (flag & mask) == mask ? 1 : 0;
}

int main(void) {
    int t; // number of test cases
    scanf("%d", &t);

    int n; // number that Bleatrix has chosen
    for (int i = 1; i <= t; i++) {
        scanf("%d", &n);

        unsigned int last_number = n;
        unsigned int flag = 0; // 0x0000000000
        for (int d = 2;; d++) {
            if (last_number == 0) {
                last_number = -1;
                break;
            }
            // record all the digits
            while (last_number > 0) {
                flag |= (1 << last_number % 10);
                last_number /= 10;
            }
            // check if all digits are seen
            if (valid(flag) > 0) {
                last_number =  n * (d - 1);
                break;
            }
            last_number =  n * d; // next number
        }

        if (last_number == -1) {
            printf("Case #%d: INSOMNIA\n", i);
        } else {
            printf("Case #%d: %d\n", i, last_number);
        }
    }

    return 0;
}
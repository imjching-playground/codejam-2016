#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int is_prime(unsigned long number) {
    if (number < 2) return 0; // not a prime number
    if (number == 2 || number == 3) return 1; // 2 and 3 are prime
    if (number % 2 == 0 || number % 3 == 0) return 0; // not a prime number if divisible by 2/3
    unsigned long i;
    for (i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

unsigned long dec2bin(unsigned long num) {
    long int bin = 0, k = 1;

    while (num) {
        bin += (num % 2) * k;
        k *= 10;
        num /= 2;
    }

    return bin;
}

int main(void) {
    int t; // number of test cases
    scanf("%d", &t); // will only be 1

    int n = 0, j = 0; // n = length, j = count
    for (int i = 1; i <= t; i++) {
        // read N and J
        scanf("%d", &n);
        scanf("%d", &j);

        printf("Case #%d:\n", i);
        if (n == 0 || j == 0) { // nothing
            break;
        }

        // form the base string
        // 32 chars base
        char str_base[33] = "10000000000000000000000000000001"; // omg, it's 4 am already
        // for (int x = 0; x < n; x++) {
        //     str_base[x] = (x == 0 || x == n - 1) ? '1' : '0';
        // }

        // printf("%s\n", str_base);

        int generated_count = 0;
        // long limit = pow(10, n / 2); // let's not count large numbers

        unsigned long num_base_2 = strtoul(str_base, NULL, 2);
        printf("%lu\n", num_base_2);
        while (generated_count < j) {
            long divisors[9];
            int is_jamcoin = 0;

            for (int base = 2; base <= 10; base++) {
                long num_base = strtoul(str_base, NULL, base);
                // printf("%lu\n", num_base);
                if (is_prime(num_base)) {
                    break;
                }
                if (base == 10) {
                    is_jamcoin = 1;
                    generated_count++; // we found one
                }

                // now we'll form the divisors
                for (long i = 2; i <= num_base / 2; i++) {
                    divisors[base - 2] = i;
                    break;
                }
            }

            // is a jamcoin
            if (is_jamcoin == 1) {
                printf("%s ", str_base);
                for (int d = 0; d < 9; d++) {
                    printf("%lu ", divisors[d]);
                }
                printf("\n");
                // if (generated_count == j) {
                //     break;
                // }
            }

            num_base_2 += 2;
            sprintf(str_base, "%lu", dec2bin(num_base_2));
        }
    }

    return 0;
}

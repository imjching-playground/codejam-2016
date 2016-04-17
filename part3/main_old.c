#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 10
#define INT_SIZE 1 // 4 bytes * 8 bits = 32 bits, more than enough

// Set the kth bit in array A
void set_bit(int A[], int k) {
    A[k / 32] |= (1 << (k % 32));
}

// Clear the kth bit in array A
void clear_bit(int A[], int k) {
    A[k / 32] &= ~(1 << (k % 32));
}

// Check if the kth bit in array A is present
int check_bit(int A[], int k) {
    return (A[k / 32] & (1 << (k % 32))) != 0;
}

// Flip the kth bit in array A
void flip_bit(int A[], int k) {
    A[k / 32] ^= (1 << (k % 32));
}

// Reverse and flip the bits from i = 0 to i = end
void reverse_and_flip_bits(int A[], int end) {
    for (int i = 0; i < (end / 2); i++) {
        int temp = check_bit(A, i);
        if (check_bit(A, end - i - 1)) {
            set_bit(A, i);
        } else {
            clear_bit(A, i);
        }
        if (temp) {
            set_bit(A, end - i - 1);
        } else {
            clear_bit(A, end - i - 1);
        }
    }
    for (int i = 0; i < end; i++) {
        flip_bit(A, i);
    }
}

int main(void) {
    int t; // number of test cases
    scanf("%d", &t);

    char s[MAX_LENGTH]; // string S, maximum length of 10
    int bits[INT_SIZE]; // we need 10 bits, hence 1 int will do
    for (int i = 1; i <= t; i++) {
        scanf("%s", s);

        // printf("%lu\n", strlen(s));
        if (strlen(s) == 0) { // No pancakes, no flipping
            printf("Case #%d: 0\n", i);
            continue;
        }

        // Clear the bit array
        for (int x = 0; x < INT_SIZE; x++) {
            bits[x] = 0;
        }

        // Translate + to 1 and - to 0 in the bits array
        int len = strlen(s);
        for (int pos = 0; pos < len; pos++) {
            if (s[pos] == '+') {
                set_bit(bits, pos);
            } // else it's still 0
        }
        // Now set the remaining bits after len to 1 (happy)
        for (int pos = len; pos < (INT_SIZE * 4 * 8); pos++) {
            set_bit(bits, pos);
        }

        // for (int pos = 0; pos < (INT_SIZE * 4 * 8); pos++) {
        //     printf("%d", check_bit(bits, pos));
        // }

        int flipped_count = 0;
        while (1) {
            if (check_bit(bits, 0) == 1) { // start with a +, flip first
                int l = 0;
                while (check_bit(bits, l) == 1 && l < MAX_LENGTH) l++;

                if (l == MAX_LENGTH) { // all done, break loop
                    break;
                }

                reverse_and_flip_bits(bits, l);
                flipped_count++;
            }

            // should start with a - here, look for differences now
            int l = 0;
            while (check_bit(bits, l) == 0) l++;

            reverse_and_flip_bits(bits, l);
            flipped_count++;
        }

        printf("Case #%d: %d\n", i, flipped_count);
    }

    return 0;
}

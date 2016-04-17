#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void reverse_and_flip_array(char array[], int end) {
    // reverse array from i = 0 to i = end - 1
    for (int i = 0; i < end / 2; i++) {
        char temp = array[i];
        array[i] = array[end - i - 1];
        array[end - i - 1] = temp;
    }

    // flip the signs
    for (int i = 0; i < end; i++) {
        array[i] = (array[i] == '+' ? '-' : '+');
    }
}

int main(void) {
    int t; // number of test cases
    scanf("%d", &t);

    char s[MAX_LENGTH + 1]; // string S
    for (int i = 1; i <= t; i++) {
        scanf("%s", s);

        if (strlen(s) == 0) { // No pancakes, no flipping
            printf("Case #%d: 0\n", i);
            continue;
        }

        int flip_count = 0;
        int len = strlen(s);
        while (1) {
            if (s[0] == '+') { // ensure that the array starts with -
                int plus_count = 0;
                while (s[plus_count] == '+' && plus_count < len) plus_count++;

                if (plus_count == len) {
                    break;
                }

                reverse_and_flip_array(s, plus_count);
                flip_count++;
            }

            // should start with a - here, look for differences now
            int minus_count = 0;
            while (s[minus_count] == '-' && minus_count < len) minus_count++;

            reverse_and_flip_array(s, minus_count);
            flip_count++;
        }

        printf("Case #%d: %d\n", i, flip_count);

        memset(&s[0], 0, sizeof(s)); // reset the array
    }

    return 0;
}

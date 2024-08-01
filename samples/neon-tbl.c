#include <arm_neon.h>
#include <stdio.h>

int main() {
    int8_t table_array[32] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    };

    // table[0] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30}
    // table[1] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31}
    int8x16x2_t table = vld2q_s8(table_array);

    uint8x16_t indices = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30};
    int8x16_t result = vqtbl2q_s8(table, indices);
    // output: 0 4 8 12 16 20 24 28 1 5 9 13 17 21 25 29
    for (int i = 0; i < 16; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}

#include <stdio.h>
#include <arm_neon.h>

void print_int32x4(int32x4_t vec) {
    int32_t array[4];
    vst1q_s32(array, vec);
    printf("[%d, %d, %d, %d]\n", array[0], array[1], array[2], array[3]);
}

int main() {
    // Original vectors:
    // [1, 2, 3, 4]
    // [5, 6, 7, 8]
    int32x4_t vec_a = {1, 2, 3, 4};
    int32x4_t vec_b = {5, 6, 7, 8};
    printf("Original vectors:\n");
    print_int32x4(vec_a);
    print_int32x4(vec_b);

    // After zip:
    // [1, 5, 2, 6]
    // [3, 7, 4, 8]
    int32x4_t zip1_result = vzip1q_s32(vec_a, vec_b);
    int32x4_t zip2_result = vzip2q_s32(vec_a, vec_b);
    printf("\nAfter zip:\n");
    print_int32x4(zip1_result);
    print_int32x4(zip2_result);

    // Recovered vectors using unzip:
    // [1, 2, 3, 4]
    // [5, 6, 7, 8]
    int32x4_t unzip_a = vuzp1q_s32(zip1_result, zip2_result);
    int32x4_t unzip_b = vuzp2q_s32(zip1_result, zip2_result);
    printf("\nRecovered vectors using unzip:\n");
    print_int32x4(unzip_a);
    print_int32x4(unzip_b);

    return 0;
}

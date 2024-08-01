#include <stdio.h>
#include <arm_neon.h>

void print_int32x4(const char* label, int32x4_t vec) {
    int32_t arr[4];
    vst1q_s32(arr, vec);
    printf("%s: {%d, %d, %d, %d}\n", label, arr[0], arr[1], arr[2], arr[3]);
}

int main() {
    int32x4_t a = {1, 2, 3, 4};
    int32x4_t b = {5, 6, 7, 8};

    // Vector a: {1, 2, 3, 4}
    // Vector b: {5, 6, 7, 8}
    print_int32x4("Vector a", a);
    print_int32x4("Vector b", b);

    // Result1: {1, 5, 3, 7}
    int32x4_t result1 = vtrn1q_s32(a, b);
    print_int32x4("Result1", result1);

    // Result2: {2, 6, 4, 8}
    int32x4_t result2 = vtrn2q_s32(a, b);
    print_int32x4("Result2", result2);

    return 0;
}

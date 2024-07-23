#include <stdio.h>
#include <arm_neon.h>

int main() {
    int8_t src1[8] = { 127, -128, -50, -100,  0,   30, -1, 60};
    int8_t src2[8] = {-128,  127, -60,  100, -20, -30, -2, 70};

    int8x8_t v1 = vld1_s8(src1);
    int8x8_t v2 = vld1_s8(src2);

    int8x8_t abs_diff = vabd_s8(v1, v2);

    int8_t result[8];
    vst1_s8(result, abs_diff);

    printf("Absolute differences:\n");
    for (int i = 0; i < 8; i++) {
        printf("Abs diff of %d and %d is %d\n", src1[i], src2[i], result[i]);
    }

    return 0;
}

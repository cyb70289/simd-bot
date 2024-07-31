#include <stdio.h>
#include <arm_neon.h>

void print_int32x4(int32x4_t v) {
    printf("%d, %d, %d, %d\n", vgetq_lane_s32(v, 0), vgetq_lane_s32(v, 1),
                               vgetq_lane_s32(v, 2), vgetq_lane_s32(v, 3));
}

int main() {
    int32_t values[] = {42, 43, 44};

    int32x4x3_t result = vld3q_dup_s32(values);

    // Vector 1: 42, 42, 42, 42
    // Vector 2: 43, 43, 43, 43
    // Vector 3: 44, 44, 44, 44
    printf("Vector 1: ");
    print_int32x4(result.val[0]);
    printf("Vector 2: ");
    print_int32x4(result.val[1]);
    printf("Vector 3: ");
    print_int32x4(result.val[2]);

    return 0;
}

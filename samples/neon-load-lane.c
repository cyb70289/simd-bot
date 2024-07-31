#include <stdio.h>
#include <arm_neon.h>

int main() {
    int32x4_t vec = vdupq_n_s32(0);

    const int32_t a = 10;
    const int32_t b = 20;
    const int32_t c = 30;
    const int32_t d = 40;

    vec = vld1q_lane_s32(&a, vec, 0);
    vec = vld1q_lane_s32(&b, vec, 1);
    vec = vld1q_lane_s32(&c, vec, 2);
    vec = vld1q_lane_s32(&d, vec, 3);

    // Vector elements: 10, 20, 30, 40
    printf("Vector elements: %d, %d, %d, %d\n", 
           vgetq_lane_s32(vec, 0), 
           vgetq_lane_s32(vec, 1), 
           vgetq_lane_s32(vec, 2), 
           vgetq_lane_s32(vec, 3));

    return 0;
}

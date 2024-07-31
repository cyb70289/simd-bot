#include <stdio.h>
#include <arm_neon.h>

void print_int32x4(const char* name, int32x4_t vec) {
    printf("%s: [%d, %d, %d, %d]\n", name, 
           vgetq_lane_s32(vec, 0), vgetq_lane_s32(vec, 1),
           vgetq_lane_s32(vec, 2), vgetq_lane_s32(vec, 3));
}

int main() {
    int32x4_t vec1 = {1, 2, 3, 4};
    int32x4_t vec2 = {5, 6, 7, 8};
    
    printf("Input vectors:\n");
    print_int32x4("vec1", vec1);
    print_int32x4("vec2", vec2);
    
    printf("\nTesting vextq_s32:\n");
    
    for (int i = 0; i <= 3; i++) {
        int32x4_t result;
        switch (i) {
            // [1, 2, 3, 4]
            case 0: result = vextq_s32(vec1, vec2, 0); break;
            // [2, 3, 4, 5]
            case 1: result = vextq_s32(vec1, vec2, 1); break;
            // [3, 4, 5, 6]
            case 2: result = vextq_s32(vec1, vec2, 2); break;
            // [4, 5, 6, 7]
            case 3: result = vextq_s32(vec1, vec2, 3); break;
        }
        
        printf("vextq_s32(vec1, vec2, %d):\n", i);
        print_int32x4("result", result);
        printf("\n");
    }

    return 0;
}

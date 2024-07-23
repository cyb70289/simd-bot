#include <arm_neon.h>
#include <stdio.h>

int main() {
    uint64_t r0 = vtstd_s64(1LL, 2LL);
    uint64_t r1 = vtstd_s64(1LL, 3LL);
    // r0 = 0, r1 = ffffffffffffffff
    printf("r0 = %llx, r1 = %llx\n", r0, r1);
    return 0;
}

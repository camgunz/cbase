#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

bool checked_mul_u8_2(uint8_t a, uint8_t b, uint8_t *rp) {
    *rp = a * b;
    return ((a > 1) && (b > 1) && ((UINT8_MAX / a) < b));
}

bool checked_mul_u16_2(uint16_t a, uint16_t b, uint16_t *rp) {
    *rp = a * b;
    return ((a > 1) && (b > 1) && ((UINT16_MAX / a) < b));
}

bool checked_mul_u32_2(uint32_t a, uint32_t b, uint32_t *rp) {
    *rp = a * b;
    return ((a > 1) && (b > 1) && ((UINT32_MAX / a) < b));
}

bool checked_mul_u64_2(uint64_t a, uint64_t b, uint64_t *rp) {
    *rp = a * b;
    return ((a > 1) && (b > 1) && ((UINT64_MAX / a) < b));
}

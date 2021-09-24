#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool checked_mul_s8_2(int8_t a, int8_t b, int8_t *rp) {
    int16_t lr = (int16_t)a * (int16_t)b;
    *rp = (int8_t)lr;

    return lr > INT8_MAX || lr < INT8_MIN;
}

bool checked_mul_s16_2(int16_t a, int16_t b, int16_t *rp) {
    int32_t lr = (int32_t)a * (int32_t)b;
    *rp = (int16_t)lr;

    return lr > INT16_MAX || lr < INT16_MIN;
}

bool checked_mul_s32_2(int32_t a, int32_t b, int32_t *rp) {
    int64_t lr = (int64_t)a * (int64_t)b;
    *rp = (int32_t)lr;

    return lr > INT32_MAX || lr < INT32_MIN;
}

bool checked_mul_s64_2(int64_t a, int64_t b, int64_t *rp) {
    __int128 lr = (__int128)a * (__int128)b;
    *rp = (int64_t)lr;

    return lr > INT64_MAX || lr < INT64_MIN;
}

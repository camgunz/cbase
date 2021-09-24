#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

#define define_tests(op_name,                                                 \
                     op,                                                      \
                     int_t,                                                   \
                     bint_t,                                                  \
                     uint_t,                                                  \
                     signed,                                                  \
                     bits,                                                    \
                     max,                                                     \
                     min)                                                     \
    bool checked_##op_name##_##signed##bits##_2(int_t a,                      \
                                                int_t b,                      \
                                                int_t *rp) {                  \
        bint_t lr = (bint_t)a op (bint_t) b;                                  \
        *rp = (int_t)lr;                                                      \
        return lr > max || lr < min;                                          \
    }                                                                         \
                                                                              \
    bool checked_##op_name##_##signed##bits##_3(int_t a,                      \
                                                int_t b,                      \
                                                int_t *rp) {                  \
        int_t r = (uint_t)a op (uint_t) b;                                    \
        *rp = r;                                                              \
        return (a < 0 && b < 0 && r >= 0) || (a >= 0 && b >= 0 && r < 0);     \
    }                                                                         \
                                                                              \
    bool checked_##op_name##_##signed##bits##_4(int_t a,                      \
                                                int_t b,                      \
                                                int_t *rp) {                  \
        uint_t ur = (uint_t)a op (uint_t) b;                                  \
        uint_t sr = ur >> (bits - 1);                                         \
        uint_t sa = (uint_t)a >> (bits - 1);                                  \
        uint_t sb = (uint_t)b >> (bits - 1);                                  \
        *rp = ur;                                                             \
        return (sa && sb && !sr) || (!sa && !sb && sr);                       \
    }                                                                         \
                                                                              \
    bool checked_##op_name##_##signed##bits##_5(int_t a,                      \
                                                int_t b,                      \
                                                int_t *rp) {                  \
        static const uint_t mask = (uint_t)1 << (bits - 1);                   \
        *rp = (uint_t)a op (uint_t) b;                                        \
        return ((uint_t)a & mask) == ((uint_t)b & mask) &&                    \
               ((uint_t)a & mask) != ((uint_t)*rp & mask);                    \
    }                                                                         \
                                                                              \
    bool checked_##op_name##_##signed##bits##_6(int_t a,                      \
                                                int_t b,                      \
                                                int_t *rp) {                  \
        uint_t r = (uint_t)a op (uint_t) b;                                   \
        *rp = r;                                                              \
        return (((uint_t)a ^ r) & ((uint_t)b ^ r)) >> (bits - 1);             \
    }                                                                         \
                                                                              \
    bool checked_##op_name##_##signed##bits##_7(int_t a,                      \
                                                int_t b,                      \
                                                int_t *rp) {                  \
        if (b > 0 && a > max - b) {                                           \
            *rp = (a + min) op (b + min);                                     \
            return 1;                                                         \
        }                                                                     \
        if (b < 0 && a < min - b) {                                           \
            *rp = (a - min) op (b - min);                                     \
            return 1;                                                         \
        }                                                                     \
        *rp = a op b;                                                         \
        return 0;                                                             \
    }

define_tests(sub, -, int8_t, int16_t, uint8_t, s, 8, INT8_MAX, INT8_MIN)
define_tests(sub, -, int16_t, int32_t, uint16_t, s, 16, INT16_MAX, INT16_MIN)
define_tests(sub, -, int32_t, int64_t, uint32_t, s, 32, INT32_MAX, INT32_MIN)
define_tests(sub, -, int64_t, __int128, uint64_t, s, 64, INT64_MAX, INT64_MIN)

#include <inttypes.h>
#include <stdio.h>

#include "checked_signed_add.h"
#include "timing.h"

#ifdef _MAKE_OVERFLOW
#define _EXTRA 2
#else
#define _EXTRA -2
#endif

#define define_run_checked(op_name, int_t, signed, bits, max, num)          \
    static void run_checked_##op_name##_##signed##bits##_##num(void) {      \
        int_t r;                                                            \
        bool o =                                                            \
            checked_##op_name##_##signed##bits##_##num((max >> 1) + _EXTRA, \
                                                       (max >> 1) + _EXTRA, \
                                                       &r);                 \
        (void)o;                                                            \
    }

define_run_checked(add, int8_t, s, 8, INT8_MAX, 1)
define_run_checked(add, int8_t, s, 8, INT8_MAX, 2)
define_run_checked(add, int8_t, s, 8, INT8_MAX, 3)
define_run_checked(add, int8_t, s, 8, INT8_MAX, 4)
define_run_checked(add, int8_t, s, 8, INT8_MAX, 5)
define_run_checked(add, int8_t, s, 8, INT8_MAX, 6)
define_run_checked(add, int8_t, s, 8, INT8_MAX, 7)

define_run_checked(add, int16_t, s, 16, INT16_MAX, 1)
define_run_checked(add, int16_t, s, 16, INT16_MAX, 2)
define_run_checked(add, int16_t, s, 16, INT16_MAX, 3)
define_run_checked(add, int16_t, s, 16, INT16_MAX, 4)
define_run_checked(add, int16_t, s, 16, INT16_MAX, 5)
define_run_checked(add, int16_t, s, 16, INT16_MAX, 6)
define_run_checked(add, int16_t, s, 16, INT16_MAX, 7)

define_run_checked(add, int32_t, s, 32, INT32_MAX, 1)
define_run_checked(add, int32_t, s, 32, INT32_MAX, 2)
define_run_checked(add, int32_t, s, 32, INT32_MAX, 3)
define_run_checked(add, int32_t, s, 32, INT32_MAX, 4)
define_run_checked(add, int32_t, s, 32, INT32_MAX, 5)
define_run_checked(add, int32_t, s, 32, INT32_MAX, 6)
define_run_checked(add, int32_t, s, 32, INT32_MAX, 7)

define_run_checked(add, int64_t, s, 64, INT64_MAX, 1)
define_run_checked(add, int64_t, s, 64, INT64_MAX, 2)
define_run_checked(add, int64_t, s, 64, INT64_MAX, 3)
define_run_checked(add, int64_t, s, 64, INT64_MAX, 4)
define_run_checked(add, int64_t, s, 64, INT64_MAX, 5)
define_run_checked(add, int64_t, s, 64, INT64_MAX, 6)
define_run_checked(add, int64_t, s, 64, INT64_MAX, 7)

void run_add_s8_benchmarks(unsigned int run_count) {
    double ns1 = time_func(run_checked_add_s8_1, run_count);
    double ns2 = time_func(run_checked_add_s8_2, run_count);
    double ns3 = time_func(run_checked_add_s8_3, run_count);
    double ns4 = time_func(run_checked_add_s8_4, run_count);
    double ns5 = time_func(run_checked_add_s8_5, run_count);
    double ns6 = time_func(run_checked_add_s8_6, run_count);
    double ns7 = time_func(run_checked_add_s8_7, run_count);

    printf("checked_add_s8_1: %g\n", ns1);
    printf("checked_add_s8_2: %g\n", ns2);
    printf("checked_add_s8_3: %g\n", ns3);
    printf("checked_add_s8_4: %g\n", ns4);
    printf("checked_add_s8_5: %g\n", ns5);
    printf("checked_add_s8_6: %g\n", ns6);
    printf("checked_add_s8_7: %g\n", ns7);
}

void run_add_s16_benchmarks(unsigned int run_count) {
    double ns1 = time_func(run_checked_add_s16_1, run_count);
    double ns2 = time_func(run_checked_add_s16_2, run_count);
    double ns3 = time_func(run_checked_add_s16_3, run_count);
    double ns4 = time_func(run_checked_add_s16_4, run_count);
    double ns5 = time_func(run_checked_add_s16_5, run_count);
    double ns6 = time_func(run_checked_add_s16_6, run_count);
    double ns7 = time_func(run_checked_add_s16_7, run_count);

    printf("checked_add_s16_1: %g\n", ns1);
    printf("checked_add_s16_2: %g\n", ns2);
    printf("checked_add_s16_3: %g\n", ns3);
    printf("checked_add_s16_4: %g\n", ns4);
    printf("checked_add_s16_5: %g\n", ns5);
    printf("checked_add_s16_6: %g\n", ns6);
    printf("checked_add_s16_7: %g\n", ns7);
}

void run_add_s32_benchmarks(unsigned int run_count) {
    double ns1 = time_func(run_checked_add_s32_1, run_count);
    double ns2 = time_func(run_checked_add_s32_2, run_count);
    double ns3 = time_func(run_checked_add_s32_3, run_count);
    double ns4 = time_func(run_checked_add_s32_4, run_count);
    double ns5 = time_func(run_checked_add_s32_5, run_count);
    double ns6 = time_func(run_checked_add_s32_6, run_count);
    double ns7 = time_func(run_checked_add_s32_7, run_count);

    printf("checked_add_s32_1: %g\n", ns1);
    printf("checked_add_s32_2: %g\n", ns2);
    printf("checked_add_s32_3: %g\n", ns3);
    printf("checked_add_s32_4: %g\n", ns4);
    printf("checked_add_s32_5: %g\n", ns5);
    printf("checked_add_s32_6: %g\n", ns6);
    printf("checked_add_s32_7: %g\n", ns7);
}

void run_add_s64_benchmarks(unsigned int run_count) {
    double ns1 = time_func(run_checked_add_s64_1, run_count);
    double ns2 = time_func(run_checked_add_s64_2, run_count);
    double ns3 = time_func(run_checked_add_s64_3, run_count);
    double ns4 = time_func(run_checked_add_s64_4, run_count);
    double ns5 = time_func(run_checked_add_s64_5, run_count);
    double ns6 = time_func(run_checked_add_s64_6, run_count);
    double ns7 = time_func(run_checked_add_s64_7, run_count);

    printf("checked_add_s64_1: %g\n", ns1);
    printf("checked_add_s64_2: %g\n", ns2);
    printf("checked_add_s64_3: %g\n", ns3);
    printf("checked_add_s64_4: %g\n", ns4);
    printf("checked_add_s64_5: %g\n", ns5);
    printf("checked_add_s64_6: %g\n", ns6);
    printf("checked_add_s64_7: %g\n", ns7);
}

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "checked_signed_mul.h"
#include "rand.h"
#include "testing.h"
#include "timing.h"

compare_func_2(mul, int8_t, s, 8)
compare_func_2(mul, int16_t, s, 16)
compare_func_2(mul, int32_t, s, 32)
compare_func_2(mul, int64_t, s, 64)

all_test_func(mul, int8_t, s, 8, INT8_MIN, INT8_MAX)

rand_test_func(mul, s, 16)
rand_test_func(mul, s, 32)
rand_test_func(mul, s, 64)

edge_test_func(mul, int16_t, s, 16, INT16_MAX)
edge_test_func(mul, int32_t, s, 32, INT32_MAX)
edge_test_func(mul, int64_t, s, 64, INT64_MAX)

void run_mul_s8_tests(void) {
    puts("Testing 8-bit signed muls");
    all_test_mul_s8();
}

void run_mul_s16_tests(unsigned int test_count) {
    puts("Testing 16-bit signed muls");
    edge_test_mul_s16();
    rand_test_mul_s16(test_count);
}

void run_mul_s32_tests(unsigned int test_count) {
    puts("Testing 32-bit signed muls");
    edge_test_mul_s32();
    rand_test_mul_s32(test_count);
}

void run_mul_s64_tests(unsigned int test_count) {
    puts("Testing 64-bit signed muls");
    edge_test_mul_s64();
    rand_test_mul_s64(test_count);
}

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "checked_unsigned_mul.h"
#include "rand.h"
#include "testing.h"

compare_func_2(mul, uint8_t, u, 8)
compare_func_2(mul, uint16_t, u, 16)
compare_func_2(mul, uint32_t, u, 32)
compare_func_2(mul, uint64_t, u, 64)

all_test_func(mul, uint8_t, u, 8, 0, UINT8_MAX)

rand_test_func(mul, u, 16)
rand_test_func(mul, u, 32)
rand_test_func(mul, u, 64)

edge_test_func(mul, uint16_t, u, 16, UINT16_MAX)
edge_test_func(mul, uint32_t, u, 32, UINT32_MAX)
edge_test_func(mul, uint64_t, u, 64, UINT64_MAX)

void run_mul_u8_tests(void) {
    puts("Testing 8-bit unsigned muls");
    all_test_mul_u8();
}

void run_mul_u16_tests(unsigned int test_count) {
    puts("Testing 16-bit unsigned muls");
    edge_test_mul_u16();
    rand_test_mul_u16(test_count);
}

void run_mul_u32_tests(unsigned int test_count) {
    puts("Testing 32-bit unsigned muls");
    edge_test_mul_u32();
    rand_test_mul_u32(test_count);
}

void run_mul_u64_tests(unsigned int test_count) {
    puts("Testing 64-bit unsigned muls");
    edge_test_mul_u64();
    rand_test_mul_u64(test_count);
}

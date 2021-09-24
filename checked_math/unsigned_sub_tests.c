#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "checked_unsigned_sub.h"
#include "rand.h"
#include "testing.h"

compare_func_2(sub, uint8_t, u, 8)
compare_func_2(sub, uint16_t, u, 16)
compare_func_2(sub, uint32_t, u, 32)
compare_func_2(sub, uint64_t, u, 64)

all_test_func(sub, uint8_t, u, 8, 0, UINT8_MAX)

rand_test_func(sub, u, 16)
rand_test_func(sub, u, 32)
rand_test_func(sub, u, 64)

edge_test_func(sub, uint16_t, u, 16, UINT16_MAX)
edge_test_func(sub, uint32_t, u, 32, UINT32_MAX)
edge_test_func(sub, uint64_t, u, 64, UINT64_MAX)

void run_sub_u8_tests(void) {
    puts("Testing 8-bit unsigned subs");
    all_test_sub_u8();
}

void run_sub_u16_tests(unsigned int test_count) {
    puts("Testing 16-bit unsigned subs");
    edge_test_sub_u16();
    rand_test_sub_u16(test_count);
}

void run_sub_u32_tests(unsigned int test_count) {
    puts("Testing 32-bit unsigned subs");
    edge_test_sub_u32();
    rand_test_sub_u32(test_count);
}

void run_sub_u64_tests(unsigned int test_count) {
    puts("Testing 64-bit unsigned subs");
    edge_test_sub_u64();
    rand_test_sub_u64(test_count);
}

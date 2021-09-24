#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "checked_unsigned_add.h"
#include "rand.h"
#include "testing.h"
#include "timing.h"

compare_func_3(add, uint8_t, u, 8)
compare_func_3(add, uint16_t, u, 16)
compare_func_3(add, uint32_t, u, 32)
compare_func_3(add, uint64_t, u, 64)

all_test_func(add, uint8_t, u, 8, 0, UINT8_MAX)

rand_test_func(add, u, 16)
rand_test_func(add, u, 32)
rand_test_func(add, u, 64)

edge_test_func(add, uint16_t, u, 16, UINT16_MAX)
edge_test_func(add, uint32_t, u, 32, UINT32_MAX)
edge_test_func(add, uint64_t, u, 64, UINT64_MAX)

void run_add_u8_tests(void) {
  puts("Testing 8-bit unsigned adds");
  all_test_add_u8();
}

void run_add_u16_tests(unsigned int test_count) {
  puts("Testing 16-bit unsigned adds");
  edge_test_add_u16();
  rand_test_add_u16(test_count);
}

void run_add_u32_tests(unsigned int test_count) {
  puts("Testing 32-bit unsigned adds");
  edge_test_add_u32();
  rand_test_add_u32(test_count);
}

void run_add_u64_tests(unsigned int test_count) {
  puts("Testing 64-bit unsigned adds");
  edge_test_add_u64();
  rand_test_add_u64(test_count);
}

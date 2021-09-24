#include <stdio.h>
#include <stdlib.h>

#include "signed_add_benchmarks.h"
#include "unsigned_add_benchmarks.h"
#include "signed_add_tests.h"
#include "signed_sub_tests.h"
#include "signed_mul_tests.h"
#include "unsigned_add_tests.h"
#include "unsigned_sub_tests.h"
#include "unsigned_mul_tests.h"
#include "timing.h"

#define RANDOM_TEST_COUNT   100000000
#define BENCHMARK_RUN_COUNT 100000000

void test_add_s(void) {
  run_add_s8_tests();
  run_add_s16_tests(RANDOM_TEST_COUNT);
  run_add_s32_tests(RANDOM_TEST_COUNT);
  run_add_s64_tests(RANDOM_TEST_COUNT);
}

void time_add_s(void) {
  run_add_s8_benchmarks(BENCHMARK_RUN_COUNT);
  puts("");
  run_add_s16_benchmarks(BENCHMARK_RUN_COUNT);
  puts("");
  run_add_s32_benchmarks(BENCHMARK_RUN_COUNT);
  puts("");
  run_add_s64_benchmarks(BENCHMARK_RUN_COUNT);
}

void test_add_u(void) {
  run_add_u8_tests();
  run_add_u16_tests(RANDOM_TEST_COUNT);
  run_add_u32_tests(RANDOM_TEST_COUNT);
  run_add_u64_tests(RANDOM_TEST_COUNT);
}

void time_add_u(void) {
  run_add_u8_benchmarks(BENCHMARK_RUN_COUNT);
  puts("");
  run_add_u16_benchmarks(BENCHMARK_RUN_COUNT);
  puts("");
  run_add_u32_benchmarks(BENCHMARK_RUN_COUNT);
  puts("");
  run_add_u64_benchmarks(BENCHMARK_RUN_COUNT);
}

void test_sub_s(void) {
  run_sub_s8_tests();
  run_sub_s16_tests(RANDOM_TEST_COUNT);
  run_sub_s32_tests(RANDOM_TEST_COUNT);
  run_sub_s64_tests(RANDOM_TEST_COUNT);
}

void test_sub_u(void) {
  run_sub_u8_tests();
  run_sub_u16_tests(RANDOM_TEST_COUNT);
  run_sub_u32_tests(RANDOM_TEST_COUNT);
  run_sub_u64_tests(RANDOM_TEST_COUNT);
}

void test_mul_s(void) {
  run_mul_s8_tests();
  run_mul_s16_tests(RANDOM_TEST_COUNT);
  run_mul_s32_tests(RANDOM_TEST_COUNT);
  run_mul_s64_tests(RANDOM_TEST_COUNT);
}

void test_mul_u(void) {
  run_mul_u8_tests();
  run_mul_u16_tests(RANDOM_TEST_COUNT);
  run_mul_u32_tests(RANDOM_TEST_COUNT);
  run_mul_u64_tests(RANDOM_TEST_COUNT);
}

void test_div_s(void) {
#if 0
  run_div_s8_tests();
  run_div_s16_tests(RANDOM_TEST_COUNT);
  run_div_s32_tests(RANDOM_TEST_COUNT);
  run_div_s64_tests(RANDOM_TEST_COUNT);
#endif
}

void test_div_u(void) {
#if 0
  run_div_u8_tests();
  run_div_u16_tests(RANDOM_TEST_COUNT);
  run_div_u32_tests(RANDOM_TEST_COUNT);
  run_div_u64_tests(RANDOM_TEST_COUNT);
#endif
}

int main(void) {
  // test_add_s(); // passes
  time_add_s();
  // test_add_u(); // passes
  time_add_u();
  // test_sub_s(); // passes
  // test_sub_u(); // passes
  // test_mul_s(); // passes
  // test_mul_u(); // passes
#if 0
  test_div_s();
  test_div_u();
#endif

  return EXIT_SUCCESS;
}

/*
 * For 8, 16, 32, and 64 bits:
 *   For signed and unsigned:
 *     For each checked function:
 *       Test against the intrinsic
 *
 * For 8, 16, 32, and 64 bits:
 *   For signed and unsigned:
 *     For each checked function:
 *       Benchmark against the intrinsic
 */

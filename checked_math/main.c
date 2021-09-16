#include <stdio.h>
#include <stdlib.h>

#include "signed_add_benchmarks.h"
#include "signed_add_tests.h"
#include "signed_sub_tests.h"
#include "unsigned_add_benchmarks.h"
#include "unsigned_add_tests.h"
#include "timing.h"

#define RANDOM_TEST_COUNT   100000000
#define BENCHMARK_RUN_COUNT 100000000

void test_sadd(void) {
  run_sadd8_tests();
  run_sadd16_tests(RANDOM_TEST_COUNT);
  run_sadd32_tests(RANDOM_TEST_COUNT);
  run_sadd64_tests(RANDOM_TEST_COUNT);
}

void time_sadd(void) {
  run_sadd8_benchmarks(BENCHMARK_RUN_COUNT);
  puts("");
  run_sadd16_benchmarks(BENCHMARK_RUN_COUNT);
  puts("");
  run_sadd32_benchmarks(BENCHMARK_RUN_COUNT);
  puts("");
  run_sadd64_benchmarks(BENCHMARK_RUN_COUNT);
}

void test_uadd(void) {
  run_uadd8_tests();
  run_uadd16_tests(RANDOM_TEST_COUNT);
  run_uadd32_tests(RANDOM_TEST_COUNT);
  run_uadd64_tests(RANDOM_TEST_COUNT);
}

void time_uadd(void) {
  run_uadd8_benchmarks(BENCHMARK_RUN_COUNT);
  puts("");
  run_uadd16_benchmarks(BENCHMARK_RUN_COUNT);
  puts("");
  run_uadd32_benchmarks(BENCHMARK_RUN_COUNT);
  puts("");
  run_uadd64_benchmarks(BENCHMARK_RUN_COUNT);
}

void test_ssub(void) {
  run_ssub8_tests();
  run_ssub16_tests(RANDOM_TEST_COUNT);
  run_ssub32_tests(RANDOM_TEST_COUNT);
  run_ssub64_tests(RANDOM_TEST_COUNT);
}

void test_usub(void) {
#if 0
  run_usub8_tests();
  run_usub16_tests(RANDOM_TEST_COUNT);
  run_usub32_tests(RANDOM_TEST_COUNT);
  run_usub64_tests(RANDOM_TEST_COUNT);
#endif
}

void test_smul(void) {
#if 0
  run_smul8_tests();
  run_smul16_tests(RANDOM_TEST_COUNT);
  run_smul32_tests(RANDOM_TEST_COUNT);
  run_smul64_tests(RANDOM_TEST_COUNT);
#endif
}

void test_umul(void) {
#if 0
  run_umul8_tests();
  run_umul16_tests(RANDOM_TEST_COUNT);
  run_umul32_tests(RANDOM_TEST_COUNT);
  run_umul64_tests(RANDOM_TEST_COUNT);
#endif
}

void test_sdiv(void) {
#if 0
  run_sdiv8_tests();
  run_sdiv16_tests(RANDOM_TEST_COUNT);
  run_sdiv32_tests(RANDOM_TEST_COUNT);
  run_sdiv64_tests(RANDOM_TEST_COUNT);
#endif
}

void test_udiv(void) {
#if 0
  run_udiv8_tests();
  run_udiv16_tests(RANDOM_TEST_COUNT);
  run_udiv32_tests(RANDOM_TEST_COUNT);
  run_udiv64_tests(RANDOM_TEST_COUNT);
#endif
}

int main(void) {
  // test_sadd();
  // time_sadd();
  // test_uadd();
  // time_uadd();
  test_ssub();
  test_usub();
  test_smul();
  test_umul();
  test_sdiv();
  test_udiv();

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

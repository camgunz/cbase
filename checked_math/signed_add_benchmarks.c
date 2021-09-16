#include <inttypes.h>
#include <stdio.h>

#include "checked_signed_add.h"
#include "timing.h"

#ifdef _MAKE_OVERFLOW
#define _EXTRA 2
#else
#define _EXTRA -2
#endif

void run_checked_sadd8_1(void) {
  int8_t r;
  int o = checked_sadd8_1((INT8_MAX >> 1) + _EXTRA, (INT8_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd8_2(void) {
  int8_t r;
  int o = checked_sadd8_2((INT8_MAX >> 1) + _EXTRA, (INT8_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd8_3(void) {
  int8_t r;
  int o = checked_sadd8_3((INT8_MAX >> 1) + _EXTRA, (INT8_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd8_3b(void) {
  int8_t r;
  int o = checked_sadd8_3b((INT8_MAX >> 1) + _EXTRA, (INT8_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd8_3c(void) {
  int8_t r;
  int o = checked_sadd8_3c((INT8_MAX >> 1) + _EXTRA, (INT8_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd8_4(void) {
  int8_t r;
  int o = checked_sadd8_4((INT8_MAX >> 1) + _EXTRA, (INT8_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd8_5(void) {
  int8_t r;
  int o = checked_sadd8_5((INT8_MAX >> 1) + _EXTRA, (INT8_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_sadd8_benchmarks(unsigned int run_count) {
  double ns1 = time_func(run_checked_sadd8_1, run_count);
  double ns2 = time_func(run_checked_sadd8_2, run_count);
  double ns3 = time_func(run_checked_sadd8_3, run_count);
  double ns4 = time_func(run_checked_sadd8_3b, run_count);
  double ns5 = time_func(run_checked_sadd8_3c, run_count);
  double ns6 = time_func(run_checked_sadd8_4, run_count);
  double ns7 = time_func(run_checked_sadd8_5, run_count);

  printf("checked_sadd8_1:  %g\n", ns1);
  printf("checked_sadd8_2:  %g\n", ns2);
  printf("checked_sadd8_3:  %g\n", ns3);
  printf("checked_sadd8_3b: %g\n", ns4);
  printf("checked_sadd8_3c: %g\n", ns5);
  printf("checked_sadd8_4:  %g\n", ns6);
  printf("checked_sadd8_5:  %g\n", ns7);
}

void run_checked_sadd16_1(void) {
  int16_t r;
  int o = checked_sadd16_1((INT16_MAX >> 1) + _EXTRA, (INT16_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd16_2(void) {
  int16_t r;
  int o = checked_sadd16_2((INT16_MAX >> 1) + _EXTRA, (INT16_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd16_3(void) {
  int16_t r;
  int o = checked_sadd16_3((INT16_MAX >> 1) + _EXTRA, (INT16_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd16_3b(void) {
  int16_t r;
  int o = checked_sadd16_3b((INT16_MAX >> 1) + _EXTRA, (INT16_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd16_3c(void) {
  int16_t r;
  int o = checked_sadd16_3c((INT16_MAX >> 1) + _EXTRA, (INT16_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd16_4(void) {
  int16_t r;
  int o = checked_sadd16_4((INT16_MAX >> 1) + _EXTRA, (INT16_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd16_5(void) {
  int16_t r;
  int o = checked_sadd16_5((INT16_MAX >> 1) + _EXTRA, (INT16_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_sadd16_benchmarks(unsigned int run_count) {
  double ns1 = time_func(run_checked_sadd16_1, run_count);
  double ns2 = time_func(run_checked_sadd16_2, run_count);
  double ns3 = time_func(run_checked_sadd16_3, run_count);
  double ns4 = time_func(run_checked_sadd16_3b, run_count);
  double ns5 = time_func(run_checked_sadd16_3c, run_count);
  double ns6 = time_func(run_checked_sadd16_4, run_count);
  double ns7 = time_func(run_checked_sadd16_5, run_count);

  printf("checked_sadd16_1:  %g\n", ns1);
  printf("checked_sadd16_2:  %g\n", ns2);
  printf("checked_sadd16_3:  %g\n", ns3);
  printf("checked_sadd16_3b: %g\n", ns4);
  printf("checked_sadd16_3c: %g\n", ns5);
  printf("checked_sadd16_4:  %g\n", ns6);
  printf("checked_sadd16_5:  %g\n", ns7);
}

void run_checked_sadd32_1(void) {
  int32_t r;
  int o = checked_sadd32_1((INT32_MAX >> 1) + _EXTRA, (INT32_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd32_2(void) {
  int32_t r;
  int o = checked_sadd32_2((INT32_MAX >> 1) + _EXTRA, (INT32_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd32_3(void) {
  int32_t r;
  int o = checked_sadd32_3((INT32_MAX >> 1) + _EXTRA, (INT32_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd32_3b(void) {
  int32_t r;
  int o = checked_sadd32_3b((INT32_MAX >> 1) + _EXTRA, (INT32_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd32_3c(void) {
  int32_t r;
  int o = checked_sadd32_3c((INT32_MAX >> 1) + _EXTRA, (INT32_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd32_4(void) {
  int32_t r;
  int o = checked_sadd32_4((INT32_MAX >> 1) + _EXTRA, (INT32_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd32_5(void) {
  int32_t r;
  int o = checked_sadd32_5((INT32_MAX >> 1) + _EXTRA, (INT32_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_sadd32_benchmarks(unsigned int run_count) {
  double ns1 = time_func(run_checked_sadd32_1, run_count);
  double ns2 = time_func(run_checked_sadd32_2, run_count);
  double ns3 = time_func(run_checked_sadd32_3, run_count);
  double ns4 = time_func(run_checked_sadd32_3b, run_count);
  double ns5 = time_func(run_checked_sadd32_3c, run_count);
  double ns6 = time_func(run_checked_sadd32_4, run_count);
  double ns7 = time_func(run_checked_sadd32_5, run_count);

  printf("checked_sadd32_1:  %g\n", ns1);
  printf("checked_sadd32_2:  %g\n", ns2);
  printf("checked_sadd32_3:  %g\n", ns3);
  printf("checked_sadd32_3b: %g\n", ns4);
  printf("checked_sadd32_3c: %g\n", ns5);
  printf("checked_sadd32_4:  %g\n", ns6);
  printf("checked_sadd32_5:  %g\n", ns7);
}

void run_checked_sadd64_1(void) {
  int64_t r;
  int o = checked_sadd64_1((INT64_MAX >> 1) + _EXTRA, (INT64_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd64_2(void) {
  int64_t r;
  int o = checked_sadd64_2((INT64_MAX >> 1) + _EXTRA, (INT64_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd64_3(void) {
  int64_t r;
  int o = checked_sadd64_3((INT64_MAX >> 1) + _EXTRA, (INT64_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd64_3b(void) {
  int64_t r;
  int o = checked_sadd64_3b((INT64_MAX >> 1) + _EXTRA, (INT64_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd64_3c(void) {
  int64_t r;
  int o = checked_sadd64_3c((INT64_MAX >> 1) + _EXTRA, (INT64_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd64_4(void) {
  int64_t r;
  int o = checked_sadd64_4((INT64_MAX >> 1) + _EXTRA, (INT64_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_sadd64_5(void) {
  int64_t r;
  int o = checked_sadd64_5((INT64_MAX >> 1) + _EXTRA, (INT64_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_sadd64_benchmarks(unsigned int run_count) {
  double ns1 = time_func(run_checked_sadd64_1, run_count);
  double ns2 = time_func(run_checked_sadd64_2, run_count);
  double ns3 = time_func(run_checked_sadd64_3, run_count);
  double ns4 = time_func(run_checked_sadd64_3b, run_count);
  double ns5 = time_func(run_checked_sadd64_3c, run_count);
  double ns6 = time_func(run_checked_sadd64_4, run_count);
  double ns7 = time_func(run_checked_sadd64_5, run_count);

  printf("checked_sadd64_1:  %g\n", ns1);
  printf("checked_sadd64_2:  %g\n", ns2);
  printf("checked_sadd64_3:  %g\n", ns3);
  printf("checked_sadd64_3b: %g\n", ns4);
  printf("checked_sadd64_3c: %g\n", ns5);
  printf("checked_sadd64_4:  %g\n", ns6);
  printf("checked_sadd64_5:  %g\n", ns7);
}

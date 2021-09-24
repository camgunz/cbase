#include <inttypes.h>
#include <stdio.h>

#include "checked_unsigned_add.h"
#include "timing.h"

#ifdef _MAKE_OVERFLOW
#define _EXTRA 2
#else
#define _EXTRA -2
#endif

void run_checked_add_u8_1(void) {
  uint8_t r;
  int o = checked_add_u8_1((UINT8_MAX >> 1) + _EXTRA, (UINT8_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_add_u8_2(void) {
  uint8_t r;
  int o = checked_add_u8_2((UINT8_MAX >> 1) + _EXTRA, (UINT8_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_add_u8_3(void) {
  uint8_t r;
  int o = checked_add_u8_3((UINT8_MAX >> 1) + _EXTRA, (UINT8_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_add_u8_benchmarks(unsigned int run_count) {
  double ns1 = time_func(run_checked_add_u8_1, run_count);
  double ns2 = time_func(run_checked_add_u8_2, run_count);
  double ns3 = time_func(run_checked_add_u8_3, run_count);

  printf("checked_add_u8_1:  %g\n", ns1);
  printf("checked_add_u8_2:  %g\n", ns2);
  printf("checked_add_u8_3:  %g\n", ns3);
}

void run_checked_add_u16_1(void) {
  uint16_t r;
  int o = checked_add_u16_1((UINT16_MAX >> 1) + _EXTRA, (UINT16_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_add_u16_2(void) {
  uint16_t r;
  int o = checked_add_u16_2((UINT16_MAX >> 1) + _EXTRA, (UINT16_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_add_u16_3(void) {
  uint16_t r;
  int o = checked_add_u16_3((UINT16_MAX >> 1) + _EXTRA, (UINT16_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_add_u16_benchmarks(unsigned int run_count) {
  double ns1 = time_func(run_checked_add_u16_1, run_count);
  double ns2 = time_func(run_checked_add_u16_2, run_count);
  double ns3 = time_func(run_checked_add_u16_3, run_count);

  printf("checked_add_u16_1:  %g\n", ns1);
  printf("checked_add_u16_2:  %g\n", ns2);
  printf("checked_add_u16_3:  %g\n", ns3);
}

void run_checked_add_u32_1(void) {
  uint32_t r;
  int o = checked_add_u32_1((UINT32_MAX >> 1) + _EXTRA, (UINT32_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_add_u32_2(void) {
  uint32_t r;
  int o = checked_add_u32_2((UINT32_MAX >> 1) + _EXTRA, (UINT32_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_add_u32_3(void) {
  uint32_t r;
  int o = checked_add_u32_3((UINT32_MAX >> 1) + _EXTRA, (UINT32_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_add_u32_benchmarks(unsigned int run_count) {
  double ns1 = time_func(run_checked_add_u32_1, run_count);
  double ns2 = time_func(run_checked_add_u32_2, run_count);
  double ns3 = time_func(run_checked_add_u32_3, run_count);

  printf("checked_add_u32_1:  %g\n", ns1);
  printf("checked_add_u32_2:  %g\n", ns2);
  printf("checked_add_u32_3:  %g\n", ns3);
}

void run_checked_add_u64_1(void) {
  uint64_t r;
  int o = checked_add_u64_1((UINT64_MAX >> 1) + _EXTRA, (UINT64_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_add_u64_2(void) {
  uint64_t r;
  int o = checked_add_u64_2((UINT64_MAX >> 1) + _EXTRA, (UINT64_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_checked_add_u64_3(void) {
  uint64_t r;
  int o = checked_add_u64_3((UINT64_MAX >> 1) + _EXTRA, (UINT64_MAX >> 1) + _EXTRA, &r);

  (void)o;
}

void run_add_u64_benchmarks(unsigned int run_count) {
  double ns1 = time_func(run_checked_add_u64_1, run_count);
  double ns2 = time_func(run_checked_add_u64_2, run_count);
  double ns3 = time_func(run_checked_add_u64_3, run_count);

  printf("checked_add_u64_1:  %g\n", ns1);
  printf("checked_add_u64_2:  %g\n", ns2);
  printf("checked_add_u64_3:  %g\n", ns3);
}

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "checked_unsigned_add.h"
#include "rand.h"
#include "timing.h"

static void test_u8(uint8_t a, uint8_t b) {
  uint8_t r1, r2, r3;
  int o1 = checked_uadd8_1(a, b, &r1);
  int o2 = checked_uadd8_2(a, b, &r2);
  int o3 = checked_uadd8_3(a, b, &r3);
  assert(r1 == r2);
  assert(r1 == r3);
  assert(o1 == o2);
  assert(o1 == o3);
}

static void test_u16(uint16_t a, uint16_t b) {
  uint16_t r1, r2, r3;
  int o1 = checked_uadd16_1(a, b, &r1);
  int o2 = checked_uadd16_2(a, b, &r2);
  int o3 = checked_uadd16_3(a, b, &r3);
  assert(r1 == r2);
  assert(r1 == r3);
  assert(o1 == o2);
  assert(o1 == o3);
}

static void rand_test_u16(unsigned int test_count) {
  for (unsigned int i = 0; i < test_count; i++) {
    test_u16(rand16(), rand16());
  }
}

static void edge_test_u16(void) {
  unsigned __int128 x, y;
  __int128 z, w;
  for (x = (__int128)INT16_MAX - 1000U; x < (__int128)INT16_MAX + 1000U; x++) {
    for (y = (__int128)INT16_MAX - 1000U; y < (__int128)INT16_MAX + 1000U; y++) {
      test_u16((uint16_t)x, (uint16_t)y);
    }
  }
  for (z = -1000; z < 1000; z++) {
    for (w = -1000; w < 1000; w++) {
      test_u16((uint16_t)z, (uint16_t)w);
    }
  }
  for (x = (__int128)INT16_MAX - 1000U; x < (__int128)INT16_MAX + 1000U; x++) {
    for (w = -1000; w < 1000; w++) {
      test_u16((uint16_t)x, (uint16_t)w);
      test_u16((uint16_t)w, (uint16_t)x);
    }
  }
}

static void test_u32(uint32_t a, uint32_t b) {
  uint32_t r1, r2, r3;
  int o1 = checked_uadd32_1(a, b, &r1);
  int o2 = checked_uadd32_2(a, b, &r2);
  int o3 = checked_uadd32_3(a, b, &r3);
  assert(r1 == r2);
  assert(r1 == r3);
  assert(o1 == o2);
  assert(o1 == o3);
}

static void rand_test_u32(unsigned int test_count) {
  for (unsigned int i = 0; i < test_count; i++) {
    test_u32(rand32(), rand32());
  }
}

static void edge_test_u32(void) {
  unsigned __int128 x, y;
  __int128 z, w;
  for (x = (__int128)INT32_MAX - 1000U; x < (__int128)INT32_MAX + 1000U; x++) {
    for (y = (__int128)INT32_MAX - 1000U; y < (__int128)INT32_MAX + 1000U; y++) {
      test_u32((uint32_t)x, (uint32_t)y);
    }
  }
  for (z = -1000; z < 1000; z++) {
    for (w = -1000; w < 1000; w++) {
      test_u32((uint32_t)z, (uint32_t)w);
    }
  }
  for (x = (__int128)INT32_MAX - 1000U; x < (__int128)INT32_MAX + 1000U; x++) {
    for (w = -1000; w < 1000; w++) {
      test_u32((uint32_t)x, (uint32_t)w);
      test_u32((uint32_t)w, (uint32_t)x);
    }
  }
}

static void test_u64(uint64_t a, uint64_t b) {
  uint64_t r1, r2, r3;
  int o1 = checked_uadd64_1(a, b, &r1);
  int o2 = checked_uadd64_2(a, b, &r2);
  int o3 = checked_uadd64_3(a, b, &r3);
  assert(r1 == r2);
  assert(r1 == r3);
  assert(o1 == o2);
  assert(o1 == o3);
}

static void rand_test_u64(unsigned int test_count) {
  for (unsigned int i = 0; i < test_count; i++) {
    test_u64(rand64(), rand64());
  }
}

static void edge_test_u64(void) {
  unsigned __int128 x, y;
  __int128 z, w;
  for (x = (__int128)INT64_MAX - 1000U; x < (__int128)INT64_MAX + 1000U; x++) {
    for (y = (__int128)INT64_MAX - 1000U; y < (__int128)INT64_MAX + 1000U; y++) {
      test_u64((uint64_t)x, (uint64_t)y);
    }
  }
  for (z = -1000; z < 1000; z++) {
    for (w = -1000; w < 1000; w++) {
      test_u64((uint64_t)z, (uint64_t)w);
    }
  }
  for (x = (__int128)INT64_MAX - 1000U; x < (__int128)INT64_MAX + 1000U; x++) {
    for (w = -1000; w < 1000; w++) {
      test_u64((uint64_t)x, (uint64_t)w);
      test_u64((uint64_t)w, (uint64_t)x);
    }
  }
}

void run_uadd8_tests(void) {
  puts("Testing 8-bit unsigned adds");
  uint8_t i = INT8_MIN;
  uint8_t j = INT8_MIN;

  while (true) {
    test_u8(i, j);

    if (i != INT8_MAX) {
      i++;
    }
    else if (j == INT8_MAX) {
      break;
    }
    else {
      i = INT8_MIN;
      j++;
    }
  }
}

void run_uadd16_tests(unsigned int test_count) {
  puts("Testing 16-bit unsigned adds");
  edge_test_u16();
  rand_test_u16(test_count);
}

void run_uadd32_tests(unsigned int test_count) {
  puts("Testing 32-bit unsigned adds");
  edge_test_u32();
  rand_test_u32(test_count);
}

void run_uadd64_tests(unsigned int test_count) {
  puts("Testing 64-bit unsigned adds");
  edge_test_u64();
  rand_test_u64(test_count);
}

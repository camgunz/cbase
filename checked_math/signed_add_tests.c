#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "checked_signed_add.h"
#include "rand.h"
#include "timing.h"

static void test_s8(int8_t a, int8_t b) {
  int8_t r1, r2, r3, r3b, r3c, r4, r5;
  int o1 = checked_sadd8_1(a, b, &r1);
  int o2 = checked_sadd8_2(a, b, &r2);
  int o3 = checked_sadd8_3(a, b, &r3);
  int o3b = checked_sadd8_3b(a, b, &r3b);
  int o3c = checked_sadd8_3c(a, b, &r3c);
  int o4 = checked_sadd8_4(a, b, &r4);
  int o5 = checked_sadd8_5(a, b, &r5);
  assert(r1 == r2);
  assert(r1 == r3);
  assert(r1 == r3b);
  assert(r1 == r3c);
  assert(r1 == r4);
  assert(r1 == r5);
  assert(o1 == o2);
  assert(o1 == o3);
  assert(o1 == o3b);
  assert(o1 == o3c);
  assert(o1 == o4);
  assert(o1 == o5);
}

static void test_s16(int16_t a, int16_t b) {
  int16_t r1, r2, r3, r3b, r3c, r4, r5;
  int o1 = checked_sadd16_1(a, b, &r1);
  int o2 = checked_sadd16_2(a, b, &r2);
  int o3 = checked_sadd16_3(a, b, &r3);
  int o3b = checked_sadd16_3b(a, b, &r3b);
  int o3c = checked_sadd16_3c(a, b, &r3c);
  int o4 = checked_sadd16_4(a, b, &r4);
  int o5 = checked_sadd16_5(a, b, &r5);
  assert(r1 == r2);
  assert(r1 == r3);
  assert(r1 == r3b);
  assert(r1 == r3c);
  assert(r1 == r4);
  assert(r1 == r5);
  assert(o1 == o2);
  assert(o1 == o3);
  assert(o1 == o3b);
  assert(o1 == o3c);
  assert(o1 == o4);
  assert(o1 == o5);
}

static void rand_test_s16(unsigned int test_count) {
  for (unsigned int i = 0; i < test_count; i++) {
    test_s16(rand16(), rand16());
  }
}

static void edge_test_s16(void) {
  unsigned __int128 x, y;
  __int128 z, w;
  for (x = (__int128)INT16_MAX - 1000U; x < (__int128)INT16_MAX + 1000U; x++) {
    for (y = (__int128)INT16_MAX - 1000U; y < (__int128)INT16_MAX + 1000U; y++) {
      test_s16((int16_t)x, (int16_t)y);
    }
  }
  for (z = -1000; z < 1000; z++) {
    for (w = -1000; w < 1000; w++) {
      test_s16((int16_t)z, (int16_t)w);
    }
  }
  for (x = (__int128)INT16_MAX - 1000U; x < (__int128)INT16_MAX + 1000U; x++) {
    for (w = -1000; w < 1000; w++) {
      test_s16((int16_t)x, (int16_t)w);
      test_s16((int16_t)w, (int16_t)x);
    }
  }
}

static void test_s32(int32_t a, int32_t b) {
  int32_t r1, r2, r3, r3b, r3c, r4, r5;
  int o1 = checked_sadd32_1(a, b, &r1);
  int o2 = checked_sadd32_2(a, b, &r2);
  int o3 = checked_sadd32_3(a, b, &r3);
  int o3b = checked_sadd32_3b(a, b, &r3b);
  int o3c = checked_sadd32_3c(a, b, &r3c);
  int o4 = checked_sadd32_4(a, b, &r4);
  int o5 = checked_sadd32_5(a, b, &r5);
  assert(r1 == r2);
  assert(r1 == r3);
  assert(r1 == r3b);
  assert(r1 == r3c);
  assert(r1 == r4);
  assert(r1 == r5);
  assert(o1 == o2);
  assert(o1 == o3);
  assert(o1 == o3b);
  assert(o1 == o3c);
  assert(o1 == o4);
  assert(o1 == o5);
}

static void rand_test_s32(unsigned int test_count) {
  for (unsigned int i = 0; i < test_count; i++) {
    test_s32(rand32(), rand32());
  }
}

static void edge_test_s32(void) {
  unsigned __int128 x, y;
  __int128 z, w;
  for (x = (__int128)INT32_MAX - 1000U; x < (__int128)INT32_MAX + 1000U; x++) {
    for (y = (__int128)INT32_MAX - 1000U; y < (__int128)INT32_MAX + 1000U; y++) {
      test_s32((int32_t)x, (int32_t)y);
    }
  }
  for (z = -1000; z < 1000; z++) {
    for (w = -1000; w < 1000; w++) {
      test_s32((int32_t)z, (int32_t)w);
    }
  }
  for (x = (__int128)INT32_MAX - 1000U; x < (__int128)INT32_MAX + 1000U; x++) {
    for (w = -1000; w < 1000; w++) {
      test_s32((int32_t)x, (int32_t)w);
      test_s32((int32_t)w, (int32_t)x);
    }
  }
}

static void test_s64(int64_t a, int64_t b) {
  int64_t r1, r2, r3, r3b, r3c, r4, r5;
  int o1 = checked_sadd64_1(a, b, &r1);
  int o2 = checked_sadd64_2(a, b, &r2);
  int o3 = checked_sadd64_3(a, b, &r3);
  int o3b = checked_sadd64_3b(a, b, &r3b);
  int o3c = checked_sadd64_3c(a, b, &r3c);
  int o4 = checked_sadd64_4(a, b, &r4);
  int o5 = checked_sadd64_5(a, b, &r5);
  assert(r1 == r2);
  assert(r1 == r3);
  assert(r1 == r3b);
  assert(r1 == r3c);
  assert(r1 == r4);
  assert(r1 == r5);
  assert(o1 == o2);
  assert(o1 == o3);
  assert(o1 == o3b);
  assert(o1 == o3c);
  assert(o1 == o4);
  assert(o1 == o5);
}

static void rand_test_s64(unsigned int test_count) {
  for (unsigned int i = 0; i < test_count; i++) {
    test_s64(rand64(), rand64());
  }
}

static void edge_test_s64(void) {
  unsigned __int128 x, y;
  __int128 z, w;
  for (x = (__int128)INT64_MAX - 1000U; x < (__int128)INT64_MAX + 1000U; x++) {
    for (y = (__int128)INT64_MAX - 1000U; y < (__int128)INT64_MAX + 1000U; y++) {
      test_s64((int64_t)x, (int64_t)y);
    }
  }
  for (z = -1000; z < 1000; z++) {
    for (w = -1000; w < 1000; w++) {
      test_s64((int64_t)z, (int64_t)w);
    }
  }
  for (x = (__int128)INT64_MAX - 1000U; x < (__int128)INT64_MAX + 1000U; x++) {
    for (w = -1000; w < 1000; w++) {
      test_s64((int64_t)x, (int64_t)w);
      test_s64((int64_t)w, (int64_t)x);
    }
  }
}

void run_sadd8_tests(void) {
  puts("Testing 8-bit signed adds");
  int8_t i = INT8_MIN;
  int8_t j = INT8_MIN;

  while (true) {
    test_s8(i, j);

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

void run_sadd16_tests(unsigned int test_count) {
  puts("Testing 16-bit signed adds");
  edge_test_s16();
  rand_test_s16(test_count);
}

void run_sadd32_tests(unsigned int test_count) {
  puts("Testing 32-bit signed adds");
  edge_test_s32();
  rand_test_s32(test_count);
}

void run_sadd64_tests(unsigned int test_count) {
  puts("Testing 64-bit signed adds");
  edge_test_s64();
  rand_test_s64(test_count);
}

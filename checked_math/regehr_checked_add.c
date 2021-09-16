#include <limits.h>
#include <stdint.h>

/*
 * checked_add semantics:
 *
 * *rp gets the value of the two's complement addition operation;
 * return value is 1 for overflow, 0 otherwise
 */

#define INT8

#ifdef INT8

typedef int8_t int_t;
typedef uint8_t uint_t;
typedef int16_t wideint_t;
typedef uint16_t wideuint_t;
#define MAX INT8_MAX
#define MIN INT8_MIN

#elif defined INT16

typedef int16_t int_t;
typedef uint16_t uint_t;
typedef int32_t wideint_t;
typedef uint32_t wideuint_t;
#define MAX INT16_MAX
#define MIN INT16_MIN

#elif defined INT32

typedef int32_t int_t;
typedef uint32_t uint_t;
typedef int64_t wideint_t;
typedef uint64_t wideuint_t;
#define MAX INT32_MAX
#define MIN INT32_MIN

#elif defined INT64

typedef int64_t int_t;
typedef uint64_t uint_t;
typedef __int128 wideint_t;
typedef unsigned __int128 wideuint_t;
#define MAX INT64_MAX
#define MIN INT64_MIN

#else

#error Need to define INT8 or INT16 or INT32 or INT64

#endif

#define BITS (8 * sizeof(int_t))

int checked_add_1(int_t a, int_t b, int_t *rp) {
  wideint_t lr = (wideint_t)a + (wideint_t)b;
  *rp = (int_t)lr;
  return lr > MAX || lr < MIN;
}

int checked_add_2(int_t a, int_t b, int_t *rp) {
  int_t r = (uint_t)a + (uint_t)b;
  *rp = r;
  return (a < 0 && b < 0 && r >= 0) || (a >= 0 && b >= 0 && r < 0);
}

int checked_add_3(int_t a, int_t b, int_t *rp) {
  uint_t ur = (uint_t)a + (uint_t)b;
  uint_t sr = ur >> (BITS - 1);
  uint_t sa = (uint_t)a >> (BITS - 1);
  uint_t sb = (uint_t)b >> (BITS - 1);
  *rp = ur;
  return (sa && sb && !sr) || (!sa && !sb && sr);
}

int checked_add_3b(int_t a, int_t b, int_t *rp) {
  static const uint_t mask = (uint_t)1 << (BITS - 1);
  *rp = (uint_t)a + (uint_t)b;
  return ((uint_t)a & mask) == ((uint_t)b & mask) &&
         ((uint_t)a & mask) != ((uint_t) * rp & mask);
}

int checked_add_3c(int_t a, int_t b, int_t *rp) {
  uint_t r = (uint_t)a + (uint_t)b;
  *rp = r;
  return (((uint_t)a ^ r) & ((uint_t)b ^ r)) >> (BITS - 1);
}

int checked_add_4(int_t a, int_t b, int_t *rp) {
  if (b > 0 && a > MAX - b) {
    *rp = (a + MIN) + (b + MIN);
    return 1;
  }
  if (b < 0 && a < MIN - b) {
    *rp = (a - MIN) + (b - MIN);
    return 1;
  }
  *rp = a + b;
  return 0;
}

extern int checked_add_5(int_t a, int_t b, int_t *rp);

#ifdef TEST

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

static uint_t rand64(void) {
  uint64_t a = rand() & 0xffff;
  uint64_t b = rand() & 0xffff;
  uint64_t c = rand() & 0xffff;
  uint64_t d = rand() & 0xffff;
  return (a << 48) | (b << 32) | (c << 16) | d;
}

static void test(int_t a, int_t b) {
  int_t r1, r2, r3, r3b, r3c, r4, r5;
  int_t o1 = checked_add_1(a, b, &r1);
  int_t o2 = checked_add_2(a, b, &r2);
  int_t o3 = checked_add_3(a, b, &r3);
  int_t o3b = checked_add_3b(a, b, &r3b);
  int_t o3c = checked_add_3c(a, b, &r3c);
  int_t o4 = checked_add_4(a, b, &r4);
  int_t o5 = checked_add_5(a, b, &r5);
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

static void run_tests(void) {
  unsigned __int128 x, y;
  __int128 z, w;
  for (x = (__int128)MAX - 1000U; x < (__int128)MAX + 1000U; x++) {
    for (y = (__int128)MAX - 1000U; y < (__int128)MAX + 1000U; y++) {
      test(x, y);
    }
  }
  for (z = -1000; z < 1000; z++) {
    for (w = -1000; w < 1000; w++) {
      test(z, w);
    }
  }
  for (x = (__int128)MAX - 1000U; x < (__int128)MAX + 1000U; x++) {
    for (w = -1000; w < 1000; w++) {
      test(x, w);
      test(w, x);
    }
  }
}

static const int64_t num_random_tests = 100000000;

static void run_random_tests(void) {
  int64_t i;
  for (i = 0; i < num_random_tests; i++) {
    int_t a = rand64();
    int_t b = rand64();
    test(a, b);
  }
}

int main(void) {
  srand(time(NULL));
  run_tests();
  run_random_tests();
  return 0;
}

#endif

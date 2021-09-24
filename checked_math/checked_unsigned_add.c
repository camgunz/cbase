#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

bool checked_add_u8_2(uint8_t a, uint8_t b, uint8_t *rp) {
  *rp = a + b;

  return (((a > (UINT8_MAX >> 1)) && (b > (UINT8_MAX >> 1))) ||
          ((b < a) && ((b << 1) > (UINT8_MAX - (a - b)))) ||
          ((a < b) && ((a << 1) > (UINT8_MAX - (b - a)))));
}

bool checked_add_u8_3(uint8_t a, uint8_t b, uint8_t *rp) {
  uint16_t lr = (uint16_t)a + (uint16_t)b;

  *rp = (uint8_t)lr;

  return lr > UINT8_MAX;
}

bool checked_add_u16_2(uint16_t a, uint16_t b, uint16_t *rp) {
  *rp = a + b;

  return (((a > (UINT16_MAX >> 1)) && (b > (UINT16_MAX >> 1))) ||
          ((b < a) && ((b << 1) > (UINT16_MAX - (a - b)))) ||
          ((a < b) && ((a << 1) > (UINT16_MAX - (b - a)))));
}

bool checked_add_u16_3(uint16_t a, uint16_t b, uint16_t *rp) {
  uint32_t lr = (uint32_t)a + (uint32_t)b;

  *rp = (uint16_t)lr;

  return lr > UINT16_MAX;
}

bool checked_add_u32_2(uint32_t a, uint32_t b, uint32_t *rp) {
  *rp = a + b;

  return (((a > (UINT32_MAX >> 1)) && (b > (UINT32_MAX >> 1))) ||
          ((b < a) && ((b << 1) > (UINT32_MAX - (a - b)))) ||
          ((a < b) && ((a << 1) > (UINT32_MAX - (b - a)))));
}

bool checked_add_u32_3(uint32_t a, uint32_t b, uint32_t *rp) {
  uint64_t lr = (uint64_t)a + (uint64_t)b;

  *rp = (uint32_t)lr;

  return lr > UINT32_MAX;
}

bool checked_add_u64_2(uint64_t a, uint64_t b, uint64_t *rp) {
  *rp = a + b;

  return (((a > (UINT64_MAX >> 1)) && (b > (UINT64_MAX >> 1))) ||
          ((b < a) && ((b << 1) > (UINT64_MAX - (a - b)))) ||
          ((a < b) && ((a << 1) > (UINT64_MAX - (b - a)))));
}

bool checked_add_u64_3(uint64_t a, uint64_t b, uint64_t *rp) {
  unsigned __int128 lr = (unsigned __int128)a + (unsigned __int128)b;

  *rp = (uint64_t)lr;

  return lr > UINT64_MAX;
}

/*
 * char / unsigned char
 * short / unsigned short
 * int / unsigned int
 * long / unsigned long
 * long long / unsigned long long
 * int_leastN_t / uint_leastN_t
 * int_fastN_t / uint_fastN_t
 * intptr_t / uintptr_t
 * intmax_t / uintmax_t
 * ptrdiff_t
 * size_t
 */

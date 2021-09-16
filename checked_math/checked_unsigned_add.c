#include <limits.h>
#include <stdint.h>

int checked_uadd8_1(uint8_t a, uint8_t b, uint8_t *rp) {
  *rp = a + b;

  return (((a > (UINT8_MAX >> 1)) && (b > (UINT8_MAX >> 1))) ||
          ((b < a) && ((b << 1) > (UINT8_MAX - (a - b)))) ||
          ((a < b) && ((a << 1) > (UINT8_MAX - (b - a)))));
}

int checked_uadd8_2(uint8_t a, uint8_t b, uint8_t *rp) {
  uint16_t lr = (uint16_t)a + (uint16_t)b;

  *rp = (uint8_t)lr;

  return lr > UINT8_MAX;
}

int checked_uadd16_1(uint16_t a, uint16_t b, uint16_t *rp) {
  *rp = a + b;

  return (((a > (UINT16_MAX >> 1)) && (b > (UINT16_MAX >> 1))) ||
          ((b < a) && ((b << 1) > (UINT16_MAX - (a - b)))) ||
          ((a < b) && ((a << 1) > (UINT16_MAX - (b - a)))));
}

int checked_uadd16_2(uint16_t a, uint16_t b, uint16_t *rp) {
  uint32_t lr = (uint32_t)a + (uint32_t)b;

  *rp = (uint16_t)lr;

  return lr > UINT16_MAX;
}

int checked_uadd32_1(uint32_t a, uint32_t b, uint32_t *rp) {
  *rp = a + b;

  return (((a > (UINT32_MAX >> 1)) && (b > (UINT32_MAX >> 1))) ||
          ((b < a) && ((b << 1) > (UINT32_MAX - (a - b)))) ||
          ((a < b) && ((a << 1) > (UINT32_MAX - (b - a)))));
}

int checked_uadd32_2(uint32_t a, uint32_t b, uint32_t *rp) {
  uint64_t lr = (uint64_t)a + (uint64_t)b;

  *rp = (uint32_t)lr;

  return lr > UINT32_MAX;
}

int checked_uadd64_1(uint64_t a, uint64_t b, uint64_t *rp) {
  *rp = a + b;

  return (((a > (UINT64_MAX >> 1)) && (b > (UINT64_MAX >> 1))) ||
          ((b < a) && ((b << 1) > (UINT64_MAX - (a - b)))) ||
          ((a < b) && ((a << 1) > (UINT64_MAX - (b - a)))));
}

int checked_uadd64_2(uint64_t a, uint64_t b, uint64_t *rp) {
  __int128 lr = (__int128)a + (__int128)b;

  *rp = (uint64_t)lr;

  return lr > UINT64_MAX;
}

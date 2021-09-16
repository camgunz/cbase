#include <limits.h>
#include <stdint.h>

int checked_sadd8_1(int8_t a, int8_t b, int8_t *rp) {
  int16_t lr = (int16_t)a + (int16_t)b;
  *rp = (int8_t)lr;
  return lr > INT8_MAX || lr < INT8_MIN;
}

int checked_sadd8_2(int8_t a, int8_t b, int8_t *rp) {
  int8_t r = (uint8_t)a + (uint8_t)b;
  *rp = r;
  return (a < 0 && b < 0 && r >= 0) || (a >= 0 && b >= 0 && r < 0);
}

int checked_sadd8_3(int8_t a, int8_t b, int8_t *rp) {
  uint8_t ur = (uint8_t)a + (uint8_t)b;
  uint8_t sr = ur >> (8 - 1);
  uint8_t sa = (uint8_t)a >> (8 - 1);
  uint8_t sb = (uint8_t)b >> (8 - 1);
  *rp = ur;
  return (sa && sb && !sr) || (!sa && !sb && sr);
}

int checked_sadd8_3b(int8_t a, int8_t b, int8_t *rp) {
  static const uint8_t mask = (uint8_t)1 << (8 - 1);
  *rp = (uint8_t)a + (uint8_t)b;
  return ((uint8_t)a & mask) == ((uint8_t)b & mask) &&
         ((uint8_t)a & mask) != ((uint8_t) * rp & mask);
}

int checked_sadd8_3c(int8_t a, int8_t b, int8_t *rp) {
  uint8_t r = (uint8_t)a + (uint8_t)b;
  *rp = r;
  return (((uint8_t)a ^ r) & ((uint8_t)b ^ r)) >> (8 - 1);
}

int checked_sadd8_4(int8_t a, int8_t b, int8_t *rp) {
  if (b > 0 && a > INT8_MAX - b) {
    *rp = (a + INT8_MIN) + (b + INT8_MIN);
    return 1;
  }
  if (b < 0 && a < INT8_MIN - b) {
    *rp = (a - INT8_MIN) + (b - INT8_MIN);
    return 1;
  }
  *rp = a + b;
  return 0;
}

int checked_sadd16_1(int16_t a, int16_t b, int16_t *rp) {
  int32_t lr = (int32_t)a + (int32_t)b;
  *rp = (int16_t)lr;
  return lr > INT16_MAX || lr < INT16_MIN;
}

int checked_sadd16_2(int16_t a, int16_t b, int16_t *rp) {
  int16_t r = (uint16_t)a + (uint16_t)b;
  *rp = r;
  return (a < 0 && b < 0 && r >= 0) || (a >= 0 && b >= 0 && r < 0);
}

int checked_sadd16_3(int16_t a, int16_t b, int16_t *rp) {
  uint16_t ur = (uint16_t)a + (uint16_t)b;
  uint16_t sr = ur >> (16 - 1);
  uint16_t sa = (uint16_t)a >> (16 - 1);
  uint16_t sb = (uint16_t)b >> (16 - 1);
  *rp = ur;
  return (sa && sb && !sr) || (!sa && !sb && sr);
}

int checked_sadd16_3b(int16_t a, int16_t b, int16_t *rp) {
  static const uint16_t mask = (uint16_t)1 << (16 - 1);
  *rp = (uint16_t)a + (uint16_t)b;
  return ((uint16_t)a & mask) == ((uint16_t)b & mask) &&
         ((uint16_t)a & mask) != ((uint16_t) * rp & mask);
}

int checked_sadd16_3c(int16_t a, int16_t b, int16_t *rp) {
  uint16_t r = (uint16_t)a + (uint16_t)b;
  *rp = r;
  return (((uint16_t)a ^ r) & ((uint16_t)b ^ r)) >> (16 - 1);
}

int checked_sadd16_4(int16_t a, int16_t b, int16_t *rp) {
  if (b > 0 && a > INT16_MAX - b) {
    *rp = (a + INT16_MIN) + (b + INT16_MIN);
    return 1;
  }
  if (b < 0 && a < INT16_MIN - b) {
    *rp = (a - INT16_MIN) + (b - INT16_MIN);
    return 1;
  }
  *rp = a + b;
  return 0;
}

int checked_sadd32_1(int32_t a, int32_t b, int32_t *rp) {
  int64_t lr = (int64_t)a + (int64_t)b;
  *rp = (int32_t)lr;
  return lr > INT32_MAX || lr < INT32_MIN;
}

int checked_sadd32_2(int32_t a, int32_t b, int32_t *rp) {
  int32_t r = (uint32_t)a + (uint32_t)b;
  *rp = r;
  return (a < 0 && b < 0 && r >= 0) || (a >= 0 && b >= 0 && r < 0);
}

int checked_sadd32_3(int32_t a, int32_t b, int32_t *rp) {
  uint32_t ur = (uint32_t)a + (uint32_t)b;
  uint32_t sr = ur >> (32 - 1);
  uint32_t sa = (uint32_t)a >> (32 - 1);
  uint32_t sb = (uint32_t)b >> (32 - 1);
  *rp = ur;
  return (sa && sb && !sr) || (!sa && !sb && sr);
}

int checked_sadd32_3b(int32_t a, int32_t b, int32_t *rp) {
  static const uint32_t mask = (uint32_t)1 << (32 - 1);
  *rp = (uint32_t)a + (uint32_t)b;
  return ((uint32_t)a & mask) == ((uint32_t)b & mask) &&
         ((uint32_t)a & mask) != ((uint32_t) * rp & mask);
}

int checked_sadd32_3c(int32_t a, int32_t b, int32_t *rp) {
  uint32_t r = (uint32_t)a + (uint32_t)b;
  *rp = r;
  return (((uint32_t)a ^ r) & ((uint32_t)b ^ r)) >> (32 - 1);
}

int checked_sadd32_4(int32_t a, int32_t b, int32_t *rp) {
  if (b > 0 && a > INT32_MAX - b) {
    *rp = (a + INT32_MIN) + (b + INT32_MIN);
    return 1;
  }
  if (b < 0 && a < INT32_MIN - b) {
    *rp = (a - INT32_MIN) + (b - INT32_MIN);
    return 1;
  }
  *rp = a + b;
  return 0;
}

int checked_sadd64_1(int64_t a, int64_t b, int64_t *rp) {
  __int128 lr = (__int128)a + (__int128)b;
  *rp = (int64_t)lr;
  return lr > INT64_MAX || lr < INT64_MIN;
}

int checked_sadd64_2(int64_t a, int64_t b, int64_t *rp) {
  int64_t r = (uint64_t)a + (uint64_t)b;
  *rp = r;
  return (a < 0 && b < 0 && r >= 0) || (a >= 0 && b >= 0 && r < 0);
}

int checked_sadd64_3(int64_t a, int64_t b, int64_t *rp) {
  uint64_t ur = (uint64_t)a + (uint64_t)b;
  uint64_t sr = ur >> (64 - 1);
  uint64_t sa = (uint64_t)a >> (64 - 1);
  uint64_t sb = (uint64_t)b >> (64 - 1);
  *rp = ur;
  return (sa && sb && !sr) || (!sa && !sb && sr);
}

int checked_sadd64_3b(int64_t a, int64_t b, int64_t *rp) {
  static const uint64_t mask = (uint64_t)1 << (64 - 1);
  *rp = (uint64_t)a + (uint64_t)b;
  return ((uint64_t)a & mask) == ((uint64_t)b & mask) &&
         ((uint64_t)a & mask) != ((uint64_t) * rp & mask);
}

int checked_sadd64_3c(int64_t a, int64_t b, int64_t *rp) {
  uint64_t r = (uint64_t)a + (uint64_t)b;
  *rp = r;
  return (((uint64_t)a ^ r) & ((uint64_t)b ^ r)) >> (64 - 1);
}

int checked_sadd64_4(int64_t a, int64_t b, int64_t *rp) {
  if (b > 0 && a > INT64_MAX - b) {
    *rp = (a + INT64_MIN) + (b + INT64_MIN);
    return 1;
  }
  if (b < 0 && a < INT64_MIN - b) {
    *rp = (a - INT64_MIN) + (b - INT64_MIN);
    return 1;
  }
  *rp = a + b;
  return 0;
}

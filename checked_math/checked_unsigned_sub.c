#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

bool checked_sub_u8_2(uint8_t a, uint8_t b, uint8_t *rp) {
  uint16_t lr = (uint16_t)a - (uint16_t)b;
  *rp = (uint8_t)lr;
  return lr > UINT8_MAX;
}

bool checked_sub_u16_2(uint16_t a, uint16_t b, uint16_t *rp) {
  uint32_t lr = (uint32_t)a - (uint32_t)b;
  *rp = (uint16_t)lr;
  return lr > UINT16_MAX;
}

bool checked_sub_u32_2(uint32_t a, uint32_t b, uint32_t *rp) {
  uint64_t lr = (uint64_t)a - (uint64_t)b;
  *rp = (uint32_t)lr;
  return lr > UINT32_MAX;
}

bool checked_sub_u64_2(uint64_t a, uint64_t b, uint64_t *rp) {
  unsigned __int128 lr = (unsigned __int128)a - (unsigned __int128)b;
  *rp = (uint64_t)lr;
  return lr > UINT64_MAX;
}

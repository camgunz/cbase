#include <stdlib.h>

uint8_t rand8(void) {
  uint64_t a = rand() & 0xffff;
  uint64_t b = rand() & 0xffff;
  uint64_t c = rand() & 0xffff;
  uint64_t d = rand() & 0xffff;

  return (uint8_t)((a << 48) | (b << 32) | (c << 16) | d);
}

uint16_t rand16(void) {
  uint64_t a = rand() & 0xffff;
  uint64_t b = rand() & 0xffff;
  uint64_t c = rand() & 0xffff;
  uint64_t d = rand() & 0xffff;

  return (uint16_t)((a << 48) | (b << 32) | (c << 16) | d);
}

uint32_t rand32(void) {
  uint64_t a = rand() & 0xffff;
  uint64_t b = rand() & 0xffff;
  uint64_t c = rand() & 0xffff;
  uint64_t d = rand() & 0xffff;

  return (uint32_t)((a << 48) | (b << 32) | (c << 16) | d);
}

uint64_t rand64(void) {
  uint64_t a = rand() & 0xffff;
  uint64_t b = rand() & 0xffff;
  uint64_t c = rand() & 0xffff;
  uint64_t d = rand() & 0xffff;

  return (uint64_t)((a << 48) | (b << 32) | (c << 16) | d);
}

#pragma once

#ifndef __CHECKED_UNSIGNED_ADD_H
#define __CHECKED_UNSIGNED_ADD_H

#include <stdint.h>

#define checked_uadd8_3 __builtin_add_overflow
#define checked_uadd16_3 __builtin_add_overflow
#define checked_uadd32_3 __builtin_add_overflow
#define checked_uadd64_3 __builtin_add_overflow

int checked_uadd8_1(uint8_t a, uint8_t b, uint8_t *rp);
int checked_uadd8_2(uint8_t a, uint8_t b, uint8_t *rp);
int checked_uadd16_1(uint16_t a, uint16_t b, uint16_t *rp);
int checked_uadd16_2(uint16_t a, uint16_t b, uint16_t *rp);
int checked_uadd32_1(uint32_t a, uint32_t b, uint32_t *rp);
int checked_uadd32_2(uint32_t a, uint32_t b, uint32_t *rp);
int checked_uadd64_1(uint64_t a, uint64_t b, uint64_t *rp);
int checked_uadd64_2(uint64_t a, uint64_t b, uint64_t *rp);

#endif

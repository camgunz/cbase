#pragma once

#ifndef __CHECKED_UNSIGNED_MUL_H
#define __CHECKED_UNSIGNED_MUL_H

#include <stdbool.h>
#include <stdint.h>

#define checked_mul_u8_1 __builtin_mul_overflow
#define checked_mul_u16_1 __builtin_mul_overflow
#define checked_mul_u32_1 __builtin_mul_overflow
#define checked_mul_u64_1 __builtin_mul_overflow

bool checked_mul_u8_2(uint8_t a, uint8_t b, uint8_t *rp);
bool checked_mul_u16_2(uint16_t a, uint16_t b, uint16_t *rp);
bool checked_mul_u32_2(uint32_t a, uint32_t b, uint32_t *rp);
bool checked_mul_u64_2(uint64_t a, uint64_t b, uint64_t *rp);

#endif

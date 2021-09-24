#pragma once

#ifndef __CHECKED_SIGNED_MUL_H
#define __CHECKED_SIGNED_MUL_H

#include <stdbool.h>
#include <stdint.h>

#define checked_mul_s8_1  __builtin_mul_overflow
#define checked_mul_s16_1 __builtin_mul_overflow
#define checked_mul_s32_1 __builtin_mul_overflow
#define checked_mul_s64_1 __builtin_mul_overflow

bool checked_mul_s8_2(int8_t a, int8_t b, int8_t *rp);
bool checked_mul_s16_2(int16_t a, int16_t b, int16_t *rp);
bool checked_mul_s32_2(int32_t a, int32_t b, int32_t *rp);
bool checked_mul_s64_2(int64_t a, int64_t b, int64_t *rp);

#endif

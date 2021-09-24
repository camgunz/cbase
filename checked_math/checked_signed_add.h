#pragma once

#ifndef __CHECKED_SIGNED_ADD_H
#define __CHECKED_SIGNED_ADD_H

#include <stdbool.h>
#include <stdint.h>

#define checked_add_s8_1  __builtin_add_overflow
#define checked_add_s16_1 __builtin_add_overflow
#define checked_add_s32_1 __builtin_add_overflow
#define checked_add_s64_1 __builtin_add_overflow

bool checked_add_s8_2(int8_t a, int8_t b, int8_t *rp);
bool checked_add_s8_3(int8_t a, int8_t b, int8_t *rp);
bool checked_add_s8_4(int8_t a, int8_t b, int8_t *rp);
bool checked_add_s8_5(int8_t a, int8_t b, int8_t *rp);
bool checked_add_s8_6(int8_t a, int8_t b, int8_t *rp);
bool checked_add_s8_7(int8_t a, int8_t b, int8_t *rp);
bool checked_add_s16_2(int16_t a, int16_t b, int16_t *rp);
bool checked_add_s16_3(int16_t a, int16_t b, int16_t *rp);
bool checked_add_s16_4(int16_t a, int16_t b, int16_t *rp);
bool checked_add_s16_5(int16_t a, int16_t b, int16_t *rp);
bool checked_add_s16_6(int16_t a, int16_t b, int16_t *rp);
bool checked_add_s16_7(int16_t a, int16_t b, int16_t *rp);
bool checked_add_s32_2(int32_t a, int32_t b, int32_t *rp);
bool checked_add_s32_3(int32_t a, int32_t b, int32_t *rp);
bool checked_add_s32_4(int32_t a, int32_t b, int32_t *rp);
bool checked_add_s32_5(int32_t a, int32_t b, int32_t *rp);
bool checked_add_s32_6(int32_t a, int32_t b, int32_t *rp);
bool checked_add_s32_7(int32_t a, int32_t b, int32_t *rp);
bool checked_add_s64_2(int64_t a, int64_t b, int64_t *rp);
bool checked_add_s64_3(int64_t a, int64_t b, int64_t *rp);
bool checked_add_s64_4(int64_t a, int64_t b, int64_t *rp);
bool checked_add_s64_5(int64_t a, int64_t b, int64_t *rp);
bool checked_add_s64_6(int64_t a, int64_t b, int64_t *rp);
bool checked_add_s64_7(int64_t a, int64_t b, int64_t *rp);

#endif

#pragma once

#ifndef __CHECKED_SIGNED_ADD_H
#define __CHECKED_SIGNED_ADD_H

#include <stdint.h>

#define checked_sadd8_5 __builtin_add_overflow
#define checked_sadd16_5 __builtin_add_overflow
#define checked_sadd32_5 __builtin_add_overflow
#define checked_sadd64_5 __builtin_add_overflow

int checked_sadd8_1(int8_t a, int8_t b, int8_t *rp);
int checked_sadd8_2(int8_t a, int8_t b, int8_t *rp);
int checked_sadd8_3(int8_t a, int8_t b, int8_t *rp);
int checked_sadd8_3b(int8_t a, int8_t b, int8_t *rp);
int checked_sadd8_3c(int8_t a, int8_t b, int8_t *rp);
int checked_sadd8_4(int8_t a, int8_t b, int8_t *rp);
int checked_sadd16_1(int16_t a, int16_t b, int16_t *rp);
int checked_sadd16_2(int16_t a, int16_t b, int16_t *rp);
int checked_sadd16_3(int16_t a, int16_t b, int16_t *rp);
int checked_sadd16_3b(int16_t a, int16_t b, int16_t *rp);
int checked_sadd16_3c(int16_t a, int16_t b, int16_t *rp);
int checked_sadd16_4(int16_t a, int16_t b, int16_t *rp);
int checked_sadd32_1(int32_t a, int32_t b, int32_t *rp);
int checked_sadd32_2(int32_t a, int32_t b, int32_t *rp);
int checked_sadd32_3(int32_t a, int32_t b, int32_t *rp);
int checked_sadd32_3b(int32_t a, int32_t b, int32_t *rp);
int checked_sadd32_3c(int32_t a, int32_t b, int32_t *rp);
int checked_sadd32_4(int32_t a, int32_t b, int32_t *rp);
int checked_sadd64_1(int64_t a, int64_t b, int64_t *rp);
int checked_sadd64_2(int64_t a, int64_t b, int64_t *rp);
int checked_sadd64_3(int64_t a, int64_t b, int64_t *rp);
int checked_sadd64_3b(int64_t a, int64_t b, int64_t *rp);
int checked_sadd64_3c(int64_t a, int64_t b, int64_t *rp);
int checked_sadd64_4(int64_t a, int64_t b, int64_t *rp);

#endif

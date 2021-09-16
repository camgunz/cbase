#pragma once

#ifndef __CHECKED_SIGNED_SUB_H
#define __CHECKED_SIGNED_SUB_H

#include <stdint.h>

#define checked_ssub8_1 __builtin_sub_overflow
#define checked_ssub16_1 __builtin_sub_overflow
#define checked_ssub32_1 __builtin_sub_overflow
#define checked_ssub64_1 __builtin_sub_overflow

int checked_ssub8_2(int8_t a, int8_t b, int8_t *rp);
int checked_ssub16_2(int16_t a, int16_t b, int16_t *rp);
int checked_ssub32_2(int32_t a, int32_t b, int32_t *rp);
int checked_ssub64_2(int64_t a, int64_t b, int64_t *rp);

int checked_ssub8_3(int8_t a, int8_t b, int8_t *rp);
int checked_ssub16_3(int16_t a, int16_t b, int16_t *rp);
int checked_ssub32_3(int32_t a, int32_t b, int32_t *rp);
int checked_ssub64_3(int64_t a, int64_t b, int64_t *rp);

int checked_ssub8_3b(int8_t a, int8_t b, int8_t *rp);
int checked_ssub16_3b(int16_t a, int16_t b, int16_t *rp);
int checked_ssub32_3b(int32_t a, int32_t b, int32_t *rp);
int checked_ssub64_3b(int64_t a, int64_t b, int64_t *rp);

int checked_ssub8_3c(int8_t a, int8_t b, int8_t *rp);
int checked_ssub16_3c(int16_t a, int16_t b, int16_t *rp);
int checked_ssub32_3c(int32_t a, int32_t b, int32_t *rp);
int checked_ssub64_3c(int64_t a, int64_t b, int64_t *rp);

int checked_ssub8_4(int8_t a, int8_t b, int8_t *rp);
int checked_ssub16_4(int16_t a, int16_t b, int16_t *rp);
int checked_ssub32_4(int32_t a, int32_t b, int32_t *rp);
int checked_ssub64_4(int64_t a, int64_t b, int64_t *rp);

int checked_ssub8_5(int8_t a, int8_t b, int8_t *rp);
int checked_ssub16_5(int16_t a, int16_t b, int16_t *rp);
int checked_ssub32_5(int32_t a, int32_t b, int32_t *rp);
int checked_ssub64_5(int64_t a, int64_t b, int64_t *rp);

#endif

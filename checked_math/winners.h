#pragma once

#ifndef __WINNERS_H
#define __WINNERS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef OPTIMIZE_SIZE
#define _checked_add_s8 _checked_add_s8_os
#define _checked_add_s16 _checked_add_s16_os
#define _checked_add_s32 _checked_add_s32_os
#define _checked_add_s64 _checked_add_s64_os
#else
#define _checked_add_s8 _checked_add_s8_o3
#define _checked_add_s16 _checked_add_s16_o3
#define _checked_add_s32 _checked_add_s32_o3
#define _checked_add_s64 _checked_add_s64_o3
#endif

bool _checked_add_s8_os(int8_t a, int8_t b, int8_t *rp);
bool _checked_add_s16_os(int16_t a, int16_t b, int16_t *rp);
bool _checked_add_s32_os(int32_t a, int32_t b, int32_t *rp);
bool _checked_add_s64_os(int64_t a, int64_t b, int64_t *rp);

bool _checked_add_s8_o3(int8_t a, int8_t b, int8_t *rp);
bool _checked_add_s16_o3(int16_t a, int16_t b, int16_t *rp);
bool _checked_add_s32_o3(int32_t a, int32_t b, int32_t *rp);
bool _checked_add_s64_o3(int64_t a, int64_t b, int64_t *rp);

bool _checked_add_u8(uint8_t a, uint8_t b, uint8_t *rp);
bool _checked_add_u16(uint16_t a, uint16_t b, uint16_t *rp);
bool _checked_add_u32(uint32_t a, uint32_t b, uint32_t *rp);
bool _checked_add_u64(uint64_t a, uint64_t b, uint64_t *rp);

bool _checked_sub_s8(int8_t a, int8_t b, int8_t *rp);
bool _checked_sub_s16(int16_t a, int16_t b, int16_t *rp);
bool _checked_sub_s32(int32_t a, int32_t b, int32_t *rp);
bool _checked_sub_s64(int32_t a, int32_t b, int32_t *rp); // 128

bool _checked_sub_u8(uint8_t a, uint8_t b, uint8_t *rp);
bool _checked_sub_u16(uint16_t a, uint16_t b, uint16_t *rp);
bool _checked_sub_u32(uint32_t a, uint32_t b, uint32_t *rp);
bool _checked_sub_u64(uint32_t a, uint32_t b, uint32_t *rp); // 128

bool _checked_mul_s8(int8_t a, int8_t b, int8_t *rp);
bool _checked_mul_s16(int16_t a, int16_t b, int16_t *rp);
bool _checked_mul_s32(int32_t a, int32_t b, int32_t *rp);
bool _checked_mul_s64(int64_t a, int64_t b, int64_t *rp); // 128

bool _checked_mul_u8(int8_t a, int8_t b, int8_t *rp);
bool _checked_mul_u16(int16_t a, int16_t b, int16_t *rp);
bool _checked_mul_u32(int32_t a, int32_t b, int32_t *rp);
bool _checked_mul_u64(int64_t a, int64_t b, int64_t *rp); // 128

bool _checked_div_s8(int8_t a, int8_t b, int8_t *rp);
bool _checked_div_s16(int16_t a, int16_t b, int16_t *rp);
bool _checked_div_s32(int32_t a, int32_t b, int32_t *rp);
bool _checked_div_s64(int64_t a, int64_t b, int64_t *rp);

bool _checked_div_u8(uint8_t a, uint8_t b, uint8_t *rp);
bool _checked_div_u16(uint16_t a, uint16_t b, uint16_t *rp);
bool _checked_div_u32(uint32_t a, uint32_t b, uint32_t *rp);
bool _checked_div_u64(uint64_t a, uint64_t b, uint64_t *rp);

#endif

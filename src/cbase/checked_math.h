#pragma once

#ifndef _CBASE_CHECKED_MATH_H__
#define _CBASE_CHECKED_MATH_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cbase/errors.h"

#undef HAVE_BUILTIN_ADD_OVERFLOW
#undef HAVE_BUILTIN_SUB_OVERFLOW
#undef HAVE_BUILTIN_MUL_OVERFLOW
#undef HAVE_BUILTIN_DIV_OVERFLOW
#define CBASE_OPTIMIZE_SIZE
#define CBASE_16BIT_INTS
#define CBASE_32BIT_LONGS
#define CBASE_32BIT_POINTERS
#define CBASE_32BIT_INTMAX

#ifdef HAVE_BUILTIN_ADD_OVERFLOW
#define cb_add_overflow_s8  __builtin_add_overflow
#define cb_add_overflow_char __builtin_add_overflow
#define cb_add_overflow_least8  __builtin_add_overflow
#define cb_add_overflow_fast8  __builtin_add_overflow

#define cb_add_overflow_s16 __builtin_add_overflow
#define cb_add_overflow_short __builtin_add_overflow
#define cb_add_overflow_least16 __builtin_add_overflow
#define cb_add_overflow_fast16 __builtin_add_overflow

#define cb_add_overflow_s32 __builtin_add_overflow
#define cb_add_overflow_least32 __builtin_add_overflow
#define cb_add_overflow_fast32 __builtin_add_overflow

#define cb_add_overflow_s64 __builtin_add_overflow
#define cb_add_overflow_long_long __builtin_add_overflow
#define cb_add_overflow_least64 __builtin_add_overflow
#define cb_add_overflow_fast64 __builtin_add_overflow

#define cb_add_overflow_int __builtin_add_overflow
#define cb_add_overflow_long __builtin_add_overflow
#define cb_add_overflow_intptr __builtin_add_overflow
#define cb_add_overflow_intmax __builtin_add_overflow

#define cb_add_overflow_u8  __builtin_add_overflow
#define cb_add_overflow_uchar __builtin_add_overflow
#define cb_add_overflow_uleast8 __builtin_add_overflow
#define cb_add_overflow_ufast8 __builtin_add_overflow

#define cb_add_overflow_u16 __builtin_add_overflow
#define cb_add_overflow_ushort __builtin_add_overflow
#define cb_add_overflow_uleast16 __builtin_add_overflow
#define cb_add_overflow_ufast16 __builtin_add_overflow

#define cb_add_overflow_u32 __builtin_add_overflow
#define cb_add_overflow_uleast32 __builtin_add_overflow
#define cb_add_overflow_ufast32 __builtin_add_overflow

#define cb_add_overflow_u64 __builtin_add_overflow
#define cb_add_overflow_ulong_long __builtin_add_overflow
#define cb_add_overflow_uleast64 __builtin_add_overflow
#define cb_add_overflow_ufast64 __builtin_add_overflow

#define cb_add_overflow_uint __builtin_add_overflow
#define cb_add_overflow_ulong __builtin_add_overflow
#define cb_add_overflow_uintptr __builtin_add_overflow
#define cb_add_overflow_uintmax __builtin_add_overflow
#define cb_add_overflow_size __builtin_add_overflow
#else
#ifdef CBASE_OPTIMIZE_SIZE
#define _define_add_s8(name, int_t, uint_t) \
    CBASE_API_STATIC bool cb_add_overflow_##name(int_t a, int_t b, int_t *rp) { \
        uint_t r = (uint_t)a + (uint_t)b; \
        *rp = r; \
        return (((uint_t)a ^ r) & ((uint_t)b ^ r)) >> (8 - 1); \
    }

#define _define_add_s16(name, int_t, uint_t) \
    CBASE_API_STATIC bool cb_add_overflow_##name(int_t a, int_t b, int_t *rp) { \
        uint_t ur = (uint_t)a + (uint_t)b; \
        uint_t sr = ur >> (16 - 1); \
        uint_t sa = (uint_t)a >> (16 - 1); \
        uint_t sb = (uint_t)b >> (16 - 1); \
        *rp = ur; \
        return (sa && sb && !sr) || (!sa && !sb && sr); \
    }

#define _define_add_s32(name, int_t, bint_t, min, max) \
    CBASE_API_STATIC bool cb_add_overflow_##name(int_t a, int_t b, int_t *rp) { \
        bint_t lr = (bint_t)a + (bint_t)b; \
        *rp = (int_t)lr; \
        return lr > max || lr < min; \
    }

#define _define_add_s64(name, int_t, uint_t) \
    CBASE_API_STATIC bool cb_add_overflow_##name(int_t a, int_t b, int_t *rp) { \
        static const uint_t mask = (uint_t)1 << (64 - 1);                       \
        *rp = (uint_t)a + (uint_t)b;                                            \
        return ((uint_t)a & mask) == ((uint_t)b & mask) &&                      \
               ((uint_t)a & mask) != ((uint_t)*rp & mask);                      \
    }
#else
#define _define_add_s8(name, int_t, uint_t) \
    CBASE_API_STATIC bool cb_add_overflow_##name(int_t a, int_t b, int_t *rp) { \
        static const uint_t mask = (uint_t)1 << (8 - 1); \
        *rp = (uint_t)a + (uint_t)b; \
        return ((uint_t)a & mask) == ((uint_t)b & mask) && \
               ((uint_t)a & mask) != ((uint_t)*rp & mask); \
    }

#define _define_add_s16(name, int_t, uint_t) \
    CBASE_API_STATIC bool cb_add_overflow_##name(int_t a, int_t b, int_t *rp) { \
        uint_t r = (uint_t)a + (uint_t)b; \
        *rp = r; \
        return (((uint_t)a ^ r) & ((uint_t)b ^ r)) >> (16 - 1); \
    }

#define _define_add_s32(name, int_t, uint_t) \
    CBASE_API_STATIC bool cb_add_overflow_##name(int_t a, int_t b, int_t *rp) { \
        uint_t r = (uint_t)a + (uint_t)b; \
        *rp = r; \
        return (((uint_t)a ^ r) & ((uint_t)b ^ r)) >> (32 - 1); \
    }

#define _define_add_s64(name, int_t, uint_t) \
    CBASE_API_STATIC bool cb_add_overflow_##name(int_t a, int_t b, int_t *rp) { \
        static const uint_t mask = (uint_t)1 << (64 - 1); \
        *rp = (uint_t)a + (uint_t)b; \
        return ((uint_t)a & mask) == ((uint_t)b & mask) && \
               ((uint_t)a & mask) != ((uint_t)*rp & mask); \
    }
#endif

#define _define_add_u8(name, int_t, bint_t, max) \
    CBASE_API_STATIC bool cb_add_overflow_##name(int_t a, int_t b, int_t *rp) { \
        bint_t lr = (bint_t)a + (bint_t)b; \
        *rp = (int_t)lr; \
        return lr > max; \
    }

#define _define_add_u16(name, int_t, bint_t, max) \
    CBASE_API_STATIC bool cb_add_overflow_##name(int_t a, int_t b, int_t *rp) { \
        bint_t lr = (bint_t)a + (bint_t)b; \
        *rp = (int_t)lr; \
        return lr > max; \
    }

#define _define_add_u32(name, int_t, bint_t, max) \
    CBASE_API_STATIC bool cb_add_overflow_##name(int_t a, int_t b, int_t *rp) { \
        bint_t lr = (bint_t)a + (bint_t)b; \
        *rp = (int_t)lr; \
        return lr > max; \
    }

#define _define_add_u64(name, int_t, bint_t, max) \
    CBASE_API_STATIC bool cb_add_overflow_##name(int_t a, int_t b, int_t *rp) { \
        bint_t lr = (bint_t)a + (bint_t)b; \
        *rp = (int_t)lr; \
        return lr > max; \
    }

_define_add_s8(s8, int8_t, uint8_t)
_define_add_s8(char, char, unsigned char)
_define_add_s8(least8, int_least8_t, uint_least8_t)
_define_add_s8(fast8, int_fast8_t, uint_fast8_t)

_define_add_s16(s16, int16_t, uint16_t)
_define_add_s16(short, short, unsigned short)
_define_add_s16(least16, int_least16_t, uint_least16_t)
_define_add_s16(fast16, int_fast16_t, uint_fast16_t)

#ifdef CBASE_OPTIMIZE_SIZE
_define_add_s32(s32, int32_t, int64_t, INT32_MIN, INT32_MAX)
_define_add_s32(least32, int_least32_t, int_least64_t, INT_LEAST32_MIN, INT_LEAST32_MAX)
_define_add_s32(fast32, int_fast32_t, int_fast64_t, INT_FAST32_MIN, INT_FAST32_MAX)
#else
_define_add_s32(s32, int32_t, uint32_t)
_define_add_s32(least32, int_least32_t, uint_least32_t)
_define_add_s32(fast32, int_fast32_t, uint_fast32_t)
#endif

_define_add_s64(s64, int64_t, uint64_t)
_define_add_s64(long_long, long long, unsigned long long)
_define_add_s64(least64, int_least64_t, uint_least64_t)
_define_add_s64(fast64, int_fast64_t, uint_fast64_t)

#ifdef CBASE_16BIT_INTS
_define_add_s16(int, int, unsigned int)
#else
#ifdef CBASE_OPTIMIZE_SIZE
_define_add_s32(int, int, int64_t, INT64_MIN, INT64_MAX)
#else
_define_add_s32(int, int, unsigned int)
#endif
#endif

#ifdef CBASE_32BIT_LONGS
#ifdef CBASE_OPTIMIZE_SIZE
_define_add_s32(long, long, int64_t, LONG_MAX, LONG_MAX)
#else
_define_add_s32(long, long, unsigned long)
#endif
#else
_define_add_s64(long, long, unsigned long)
#endif

#ifdef CBASE_32BIT_POINTERS
#ifdef CBASE_OPTIMIZE_SIZE
_define_add_s32(intptr, intptr_t, int64_t, INTPTR_MIN, INTPTR_MAX)
#else
_define_add_s32(intptr, intptr_t, uintptr_t)
#endif
#else
_define_add_s64(intptr, intptr_t, uintptr_t)
#endif

#ifdef CBASE_32BIT_INTMAX
#ifdef CBASE_OPTIMIZE_SIZE
_define_add_s32(intmax, intmax_t, intmax_t, INTMAX_MIN, INTMAX_MAX)
#else
_define_add_s32(intmax, intmax_t, uintmax_t)
#endif
#else
_define_add_s64(intmax, intmax_t, uintmax_t)
#endif

_define_add_u8(u8, uint8_t, uint16_t, UINT8_MAX)
_define_add_u8(uchar, unsigned char, uint16_t, UCHAR_MAX)
_define_add_u8(uleast8, uint_least8_t, uint_least16_t, UINT_LEAST8_MAX)
_define_add_u8(ufast8, uint_fast8_t, uint_fast16_t, UINT_FAST8_MAX)

_define_add_u16(u16, uint16_t, uint32_t, UINT16_MAX)
_define_add_u16(ushort, unsigned short, uint32_t, USHRT_MAX)
_define_add_u16(uleast16, uint_least16_t, uint_least32_t, UINT_LEAST16_MAX)
_define_add_u16(ufast16, uint_fast16_t, uint_fast32_t, UINT_LEAST16_MAX)

_define_add_u32(u32, uint32_t, int64_t, UINT32_MAX)
_define_add_u32(uleast32, uint_least32_t, int_least64_t, UINT_LEAST32_MAX)
_define_add_u32(ufast32, uint_fast32_t, int_fast64_t, UINT_LEAST32_MAX)

_define_add_u64(u64, uint64_t, uint128_t, UINT64_MAX)
_define_add_u64(ulong_long, unsigned long long, uint128_t, ULLONG_MAX)
_define_add_u64(uleast64, uint_least64_t, uint128_t, UINT_LEAST64_MAX)
_define_add_u64(ufast64, uint_fast64_t, uint128_t, UINT_FAST64_MAX)

#ifdef CBASE_16BIT_INTS
_define_add_u16(uint, unsigned int, uint32_t, UINT_MAX)
#else
_define_add_u32(uint, unsigned int, uint64_t, UINT_MAX)
#endif

#ifdef CBASE_32BIT_LONGS
_define_add_u32(ulong, unsigned long, uint64_t, ULONG_MAX)
#else
_define_add_u64(ulong, unsigned long, uint128_t, ULONG_MAX)
#endif

#ifdef CBASE_32BIT_POINTERS
_define_add_u32(uintptr, uintptr_t, uint64_t, UINTPTR_MAX)
#else
_define_add_u64(uintptr, uintptr_t, uint128_t, UINTPTR_MAX)
#endif

#ifdef CBASE_32BIT_INTMAX
_define_add_u32(uintmax, uintmax_t, uint64_t, UINTMAX_MAX)
#ifdef CBASE_OPTIMIZE_SIZE
#else
_define_add_u32(uintmax, uintmax_t, uintmax_t, UINTMAX_MAX)
#endif
#else
_define_add_s64(uintmax, uintmax_t, uintmax_t, UINTMAX_MAX)
#endif

#ifdef CBASE_32BIT_SIZES
_define_add_u32(size, size_t, uint64_t, SIZE_MAX)
#else
_define_add_u64(size, size_t, uint128_t, SIZE_MAX)
#endif

#endif

#ifdef HAVE_BUILTIN_SUB_OVERFLOW
#define cb_sub_overflow_s8  __builtin_sub_overflow
#define cb_sub_overflow_char __builtin_sub_overflow
#define cb_sub_overflow_least8  __builtin_sub_overflow
#define cb_sub_overflow_fast8  __builtin_sub_overflow

#define cb_sub_overflow_s16 __builtin_sub_overflow
#define cb_sub_overflow_short __builtin_sub_overflow
#define cb_sub_overflow_least16 __builtin_sub_overflow
#define cb_sub_overflow_fast16 __builtin_sub_overfloW

#define cb_sub_overflow_s32 __builtin_sub_overflow
#define cb_sub_overflow_least32 __builtin_sub_overflow
#define cb_sub_overflow_fast32 __builtin_sub_overflow

#define cb_sub_overflow_s64 __builtin_sub_overflow
#define cb_sub_overflow_long_long __builtin_sub_overflow
#define cb_sub_overflow_least64 __builtin_sub_overflow
#define cb_sub_overflow_fast64 __builtin_sub_overflow

#define cb_sub_overflow_int __builtin_sub_overflow
#define cb_sub_overflow_long __builtin_sub_overflow
#define cb_sub_overflow_intptr __builtin_sub_overflow
#define cb_sub_overflow_intmax __builtin_sub_overflow

#define cb_sub_overflow_u8  __builtin_sub_overflow
#define cb_sub_overflow_uchar __builtin_sub_overflow
#define cb_sub_overflow_uleast8 __builtin_sub_overflow
#define cb_sub_overflow_ufast8 __builtin_sub_overflow

#define cb_sub_overflow_u16 __builtin_sub_overflow
#define cb_sub_overflow_ushort __builtin_sub_overflow
#define cb_sub_overflow_uleast16 __builtin_sub_overflow
#define cb_sub_overflow_ufast16 __builtin_sub_overflow

#define cb_sub_overflow_u32 __builtin_sub_overflow
#define cb_sub_overflow_uleast32 __builtin_sub_overflow
#define cb_sub_overflow_ufast32 __builtin_sub_overflow

#define cb_sub_overflow_u64 __builtin_sub_overflow
#define cb_sub_overflow_ulong_long __builtin_sub_overflow
#define cb_sub_overflow_uleast64 __builtin_sub_overflow
#define cb_sub_overflow_ufast64 __builtin_sub_overflow

#define cb_sub_overflow_uint __builtin_sub_overflow
#define cb_sub_overflow_ulong __builtin_sub_overflow
#define cb_sub_overflow_uintptr __builtin_sub_overflow
#define cb_sub_overflow_uintmax __builtin_sub_overflow
#define cb_sub_overflow_size __builtin_sub_overflow
#else
#define _define_signed_sub(name, int_t, bint_t, min, max) \
    CBASE_API_STATIC bool cb_sub_overflow_##name(int_t a, int_t b, int_t *rp) { \
        bint_t lr = (bint_t)a - (bint_t)b; \
        *rp = (int_t)lr; \
        return lr > max || lr < min; \
    }

#define _define_unsigned_sub(name, int_t, bint_t, max) \
    CBASE_API_STATIC bool cb_sub_overflow_##name(int_t a, int_t b, int_t *rp) { \
        bint_t lr = (bint_t)a - (bint_t)b; \
        *rp = (int_t)lr; \
        return lr > max; \
    }

_define_signed_sub(s8, int8_t, int16_t, INT8_MIN, INT8_MAX)
_define_signed_sub(char, char, int16_t, INT8_MIN, INT8_MAX)
_define_signed_sub(least8, int_least8_t, int_least16_t, INT_LEAST8_MIN, INT_LEAST8_MAX)
_define_signed_sub(fast8, int_fast8_t, int_fast16_t, INT_FAST8_MIN, INT_FAST8_MAX)

_define_signed_sub(s16, int16_t, int32_t, INT16_MIN, INT16_MAX)
_define_signed_sub(short, short, int32_t, INT16_MIN, INT16_MAX)
_define_signed_sub(least16, int_least16_t, int_least32_t, INT_LEAST16_MIN, INT_LEAST16_MAX)
_define_signed_sub(fast16, int_fast16_t, int_fast32_t, INT_FAST16_MIN, INT_FAST16_MAX)

_define_signed_sub(s32, int32_t, int64_t, INT32_MIN, INT32_MAX)
_define_signed_sub(least32, int_least32_t, int_least64_t, INT_LEAST32_MIN, INT_LEAST32_MAX)
_define_signed_sub(fast32, int_fast32_t, int_fast64_t, INT_FAST32_MIN, INT_FAST32_MAX)

_define_signed_sub(s64, int64_t, int128_t, INT64_MIN, INT64_MAX)
_define_signed_sub(long_long, long long, int128_t, LLONG_MIN, LLONG_MAX)
_define_signed_sub(least64, int_least64_t, int128_t, INT_LEAST64_MIN, INT_LEAST64_MAX)
_define_signed_sub(fast64, int_fast64_t, int128_t, INT_FAST64_MIN, INT_FAST64_MAX)

#ifdef CBASE_16BIT_INTS
_define_signed_sub(int, int, int32_t, INT_MIN, INT_MAX)
#else
_define_signed_sub(int, int, int64_t, INT_MIN, INT_MAX)
#endif

#ifdef CBASE_32BIT_LONGS
_define_signed_sub(long, long, int64_t, LONG_MIN, LONG_MAX)
#else
_define_signed_sub(long, long, int128_t, LONG_MIN, LONG_MAX)
#endif

#ifdef CBASE_32BIT_POINTERS
_define_signed_sub(intptr, intptr_t, int64_t, INTPTR_MIN, INTPTR_MAX)
#else
_define_signed_sub(intptr, intptr_t, int128_t, INTPTR_MIN, INTPTR_MAX)
#endif

#ifdef CBASE_32BIT_INTMAX
_define_signed_sub(intmax, intmax_t, int64_t, INTMAX_MIN, INTMAX_MAX)
#else
_define_signed_sub(intmax, intmax_t, int128_t, INTMAX_MIN, INTMAX_MAX)
#endif

_define_unsigned_sub(u8, uint8_t, uint16_t, UINT8_MAX)
_define_unsigned_sub(uchar, unsigned char, uint16_t, UCHAR_MAX)
_define_unsigned_sub(uleast8, uint_least8_t, uint_least16_t, UINT_LEAST8_MAX)
_define_unsigned_sub(ufast8, uint_fast8_t, uint_fast16_t, UINT_FAST8_MAX)

_define_unsigned_sub(u16, uint16_t, uint32_t, UINT16_MAX)
_define_unsigned_sub(ushort, unsigned short, uint32_t, UINT16_MAX)
_define_unsigned_sub(uleast16, uint_least16_t, uint_least32_t, UINT_LEAST16_MAX)
_define_unsigned_sub(ufast16, uint_fast16_t, uint_fast32_t, UINT_FAST16_MAX)

_define_unsigned_sub(u32, uint32_t, uint64_t, UINT32_MAX)
_define_unsigned_sub(uleast32, uint_least32_t, uint_least64_t, UINT_LEAST32_MAX)
_define_unsigned_sub(ufast32, uint_fast32_t, uint_fast64_t, UINT_FAST32_MAX)

_define_unsigned_sub(u64, uint64_t, int128_t, UINT64_MAX)
_define_unsigned_sub(ulong_long, unsigned long long, int128_t, ULLONG_MAX)
_define_unsigned_sub(uleast64, uint_least64_t, uint128_t, UINT_LEAST64_MAX)
_define_unsigned_sub(ufast64, uint_fast64_t, uint128_t, UINT_FAST64_MAX)

#ifdef CBASE_16BIT_INTS
_define_unsigned_sub(uint, unsigned int, uint32_t, UINT_MAX)
#else
_define_unsigned_sub(uint, unsigned int, uint64_t, UINT_MAX)
#endif

#ifdef CBASE_32BIT_LONGS
_define_unsigned_sub(ulong, unsigned long, uint64_t, ULONG_MAX)
#else
_define_unsigned_sub(ulong, unsigned long, uint128_t, ULONG_MAX)
#endif

#ifdef CBASE_32BIT_POINTERS
_define_unsigned_sub(uintptr, uintptr_t, uint64_t, UINTPTR_MAX)
#else
_define_unsigned_sub(uintptr, uintptr_t, uint128_t, UINTPTR_MAX)
#endif

#ifdef CBASE_32BIT_INTMAX
_define_unsigned_sub(uintmax, uintmax_t, uint64_t, UINTMAX_MAX)
#else
_define_unsigned_sub(uintmax, uintmax_t, uint128_t, UINTMAX_MAX)
#endif

#ifdef CBASE_32BIT_SIZES
_define_unsigned_sub(size, size_t, uint64_t, SIZE_MAX)
#else
_define_unsigned_sub(size, size_t, uint128_t, SIZE_MAX)
#endif

#endif

#ifdef HAVE_BUILTIN_MUL_OVERFLOW
#define cb_mul_overflow_s8  __builtin_mul_overflow
#define cb_mul_overflow_char __builtin_mul_overflow
#define cb_mul_overflow_least8  __builtin_mul_overflow
#define cb_mul_overflow_fast8  __builtin_mul_overflow

#define cb_mul_overflow_s16 __builtin_mul_overflow
#define cb_mul_overflow_short __builtin_mul_overflow
#define cb_mul_overflow_least16 __builtin_mul_overflow
#define cb_mul_overflow_fast16 __builtin_mul_overfloW

#define cb_mul_overflow_s32 __builtin_mul_overflow
#define cb_mul_overflow_least32 __builtin_mul_overflow
#define cb_mul_overflow_fast32 __builtin_mul_overflow

#define cb_mul_overflow_s64 __builtin_mul_overflow
#define cb_mul_overflow_long_long __builtin_mul_overflow
#define cb_mul_overflow_least64 __builtin_mul_overflow
#define cb_mul_overflow_fast64 __builtin_mul_overflow

#define cb_mul_overflow_int __builtin_mul_overflow
#define cb_mul_overflow_long __builtin_mul_overflow
#define cb_mul_overflow_intptr __builtin_mul_overflow
#define cb_mul_overflow_intmax __builtin_mul_overflow

#define cb_mul_overflow_u8  __builtin_mul_overflow
#define cb_mul_overflow_uchar __builtin_mul_overflow
#define cb_mul_overflow_uleast8 __builtin_mul_overflow
#define cb_mul_overflow_ufast8 __builtin_mul_overflow

#define cb_mul_overflow_u16 __builtin_mul_overflow
#define cb_mul_overflow_ushort __builtin_mul_overflow
#define cb_mul_overflow_uleast16 __builtin_mul_overflow
#define cb_mul_overflow_ufast16 __builtin_mul_overflow

#define cb_mul_overflow_u32 __builtin_mul_overflow
#define cb_mul_overflow_uleast32 __builtin_mul_overflow
#define cb_mul_overflow_ufast32 __builtin_mul_overflow

#define cb_mul_overflow_u64 __builtin_mul_overflow
#define cb_mul_overflow_ulong_long __builtin_mul_overflow
#define cb_mul_overflow_uleast64 __builtin_mul_overflow
#define cb_mul_overflow_ufast64 __builtin_mul_overflow

#define cb_mul_overflow_uint __builtin_mul_overflow
#define cb_mul_overflow_ulong __builtin_mul_overflow
#define cb_mul_overflow_uintptr __builtin_mul_overflow
#define cb_mul_overflow_uintmax __builtin_mul_overflow
#define cb_mul_overflow_size __builtin_mul_overflow
#else
#define _define_signed_mul(name, int_t, bint_t, min, max) \
    CBASE_API_STATIC bool cb_mul_overflow_##name(int_t a, int_t b, int_t *rp) { \
        bint_t lr = (bint_t)a - (bint_t)b; \
        *rp = (int_t)lr; \
        return lr > max || lr < min; \
    }

#define _define_unsigned_mul(name, int_t, bint_t, max) \
    CBASE_API_STATIC bool cb_mul_overflow_##name(int_t a, int_t b, int_t *rp) { \
        *rp = a * b; \
        return ((a > 1) && (b > 1) && ((max / a) < b)); \
    }

_define_signed_mul(s8, int8_t, int16_t, INT8_MIN, INT8_MAX)
_define_signed_mul(char, char, int16_t, INT8_MIN, INT8_MAX)
_define_signed_mul(least8, int_least8_t, int_least16_t, INT_LEAST8_MIN, INT_LEAST8_MAX)
_define_signed_mul(fast8, int_fast8_t, int_fast16_t, INT_FAST8_MIN, INT_FAST8_MAX)

_define_signed_mul(s16, int16_t, int32_t, INT16_MIN, INT16_MAX)
_define_signed_mul(short, short, int32_t, INT16_MIN, INT16_MAX)
_define_signed_mul(least16, int_least16_t, int_least32_t, INT_LEAST16_MIN, INT_LEAST16_MAX)
_define_signed_mul(fast16, int_fast16_t, int_fast32_t, INT_FAST16_MIN, INT_FAST16_MAX)

_define_signed_mul(s32, int32_t, int64_t, INT32_MIN, INT32_MAX)
_define_signed_mul(least32, int_least32_t, int_least64_t, INT_LEAST32_MIN, INT_LEAST32_MAX)
_define_signed_mul(fast32, int_fast32_t, int_fast64_t, INT_FAST32_MIN, INT_FAST32_MAX)

_define_signed_mul(s64, int64_t, int128_t, INT64_MIN, INT64_MAX)
_define_signed_mul(long_long, long long, int128_t, LLONG_MIN, LLONG_MAX)
_define_signed_mul(least64, int_least64_t, int128_t, INT_LEAST64_MIN, INT_LEAST64_MAX)
_define_signed_mul(fast64, int_fast64_t, int128_t, INT_FAST64_MIN, INT_FAST64_MAX)

#ifdef CBASE_16BIT_INTS
_define_signed_mul(int, int, int32_t, INT_MIN, INT_MAX)
#else
_define_signed_mul(int, int, int64_t, INT_MIN, INT_MAX)
#endif

#ifdef CBASE_32BIT_LONGS
_define_signed_mul(long, long, int64_t, LONG_MIN, LONG_MAX)
#else
_define_signed_mul(long, long, int128_t, LONG_MIN, LONG_MAX)
#endif

#ifdef CBASE_32BIT_POINTERS
_define_signed_mul(intptr, intptr_t, int64_t, INTPTR_MIN, INTPTR_MAX)
#else
_define_signed_mul(intptr, intptr_t, int128_t, INTPTR_MIN, INTPTR_MAX)
#endif

#ifdef CBASE_32BIT_INTMAX
_define_signed_mul(intmax, intmax_t, int64_t, INTMAX_MIN, INTMAX_MAX)
#else
_define_signed_mul(intmax, intmax_t, int128_t, INTMAX_MIN, INTMAX_MAX)
#endif

_define_unsigned_mul(u8, uint8_t, uint16_t, UINT8_MAX)
_define_unsigned_mul(uchar, unsigned char, uint16_t, UCHAR_MAX)
_define_unsigned_mul(uleast8, uint_least8_t, uint_least16_t, UINT_LEAST8_MAX)
_define_unsigned_mul(ufast8, uint_fast8_t, uint_fast16_t, UINT_FAST8_MAX)

_define_unsigned_mul(u16, uint16_t, uint32_t, UINT16_MAX)
_define_unsigned_mul(ushort, unsigned short, uint32_t, UINT16_MAX)
_define_unsigned_mul(uleast16, uint_least16_t, uint_least32_t, UINT_LEAST16_MAX)
_define_unsigned_mul(ufast16, uint_fast16_t, uint_fast32_t, UINT_FAST16_MAX)

_define_unsigned_mul(u32, uint32_t, uint64_t, UINT32_MAX)
_define_unsigned_mul(uleast32, uint_least32_t, uint_least64_t, UINT_LEAST32_MAX)
_define_unsigned_mul(ufast32, uint_fast32_t, uint_fast64_t, UINT_FAST32_MAX)

_define_unsigned_mul(u64, uint64_t, int128_t, UINT64_MAX)
_define_unsigned_mul(ulong_long, unsigned long long, int128_t, ULLONG_MAX)
_define_unsigned_mul(uleast64, uint_least64_t, uint128_t, UINT_LEAST64_MAX)
_define_unsigned_mul(ufast64, uint_fast64_t, uint128_t, UINT_FAST64_MAX)

#ifdef CBASE_16BIT_INTS
_define_unsigned_mul(uint, unsigned int, uint32_t, UINT_MAX)
#else
_define_unsigned_mul(uint, unsigned int, uint64_t, UINT_MAX)
#endif

#ifdef CBASE_32BIT_LONGS
_define_unsigned_mul(ulong, unsigned long, uint64_t, ULONG_MAX)
#else
_define_unsigned_mul(ulong, unsigned long, uint128_t, ULONG_MAX)
#endif

#ifdef CBASE_32BIT_POINTERS
_define_unsigned_mul(uintptr, uintptr_t, uint64_t, UINTPTR_MAX)
#else
_define_unsigned_mul(uintptr, uintptr_t, uint128_t, UINTPTR_MAX)
#endif

#ifdef CBASE_32BIT_INTMAX
_define_unsigned_mul(uintmax, uintmax_t, uint64_t,  UINTMAX_MAX)
#else
_define_unsigned_mul(uintmax, uintmax_t, uint128_t, UINTMAX_MAX)
#endif

#ifdef CBASE_32BIT_SIZES
_define_unsigned_mul(size, size_t, uint64_t, SIZE_MAX)
#else
_define_unsigned_mul(size, size_t, uint128_t, SIZE_MAX)
#endif

#endif

#ifdef HAVE_BUILTIN_DIV_OVERFLOW
#define cb_div_overflow_s8  __builtin_div_overflow
#define cb_div_overflow_char __builtin_div_overflow
#define cb_div_overflow_least8  __builtin_div_overflow
#define cb_div_overflow_fast8  __builtin_div_overflow

#define cb_div_overflow_s16 __builtin_div_overflow
#define cb_div_overflow_short __builtin_div_overflow
#define cb_div_overflow_least16 __builtin_div_overflow
#define cb_div_overflow_fast16 __builtin_div_overfloW

#define cb_div_overflow_s32 __builtin_div_overflow
#define cb_div_overflow_least32 __builtin_div_overflow
#define cb_div_overflow_fast32 __builtin_div_overflow

#define cb_div_overflow_s64 __builtin_div_overflow
#define cb_div_overflow_long_long __builtin_div_overflow
#define cb_div_overflow_least64 __builtin_div_overflow
#define cb_div_overflow_fast64 __builtin_div_overflow

#define cb_div_overflow_int __builtin_div_overflow
#define cb_div_overflow_long __builtin_div_overflow
#define cb_div_overflow_intptr __builtin_div_overflow
#define cb_div_overflow_intmax __builtin_div_overflow

#define cb_div_overflow_u8  __builtin_div_overflow
#define cb_div_overflow_uchar __builtin_div_overflow
#define cb_div_overflow_uleast8 __builtin_div_overflow
#define cb_div_overflow_ufast8 __builtin_div_overflow

#define cb_div_overflow_u16 __builtin_div_overflow
#define cb_div_overflow_ushort __builtin_div_overflow
#define cb_div_overflow_uleast16 __builtin_div_overflow
#define cb_div_overflow_ufast16 __builtin_div_overflow

#define cb_div_overflow_u32 __builtin_div_overflow
#define cb_div_overflow_uleast32 __builtin_div_overflow
#define cb_div_overflow_ufast32 __builtin_div_overflow

#define cb_div_overflow_u64 __builtin_div_overflow
#define cb_div_overflow_ulong_long __builtin_div_overflow
#define cb_div_overflow_uleast64 __builtin_div_overflow
#define cb_div_overflow_ufast64 __builtin_div_overflow

#define cb_div_overflow_uint __builtin_div_overflow
#define cb_div_overflow_ulong __builtin_div_overflow
#define cb_div_overflow_uintptr __builtin_div_overflow
#define cb_div_overflow_uintmax __builtin_div_overflow
#define cb_div_overflow_size __builtin_div_overflow
#else
#define _define_signed_div(name, int_t, min) \
    CBASE_API_STATIC bool cb_div_overflow_##name(int_t a, int_t b, int_t *rp) { \
        if (b == 0) { \
            return true; \
        } \
 \
        if (a == 0) { \
            *rp = 0; \
            return false; \
        } \
 \
        if (((a == -1) && (b == min)) || ((b == -1) && (a == min))) { \
            *rp = 0; \
            return true; \
        } \
 \
        *rp = a / b; \
        return false; \
    }

#define _define_unsigned_div(name, int_t) \
    CBASE_API_STATIC bool cb_div_overflow_##name(int_t a, int_t b, int_t *rp) { \
        if (b == 0) { \
            return true; \
        } \
 \
        if (a == 0) { \
            *rp = 0; \
            return false; \
        } \
 \
        *rp = a / b; \
        return false; \
    }

_define_signed_div(s8, int8_t, INT8_MAX)
_define_signed_div(char, char, INT8_MAX)
_define_signed_div(least8, int_least8_t, INT_LEAST8_MAX)
_define_signed_div(fast8, int_fast8_t, INT_FAST8_MAX)

_define_signed_div(s16, int16_t, INT16_MAX)
_define_signed_div(short, short, INT16_MAX)
_define_signed_div(least16, int_least16_t, INT_LEAST16_MAX)
_define_signed_div(fast16, int_fast16_t, INT_FAST16_MAX)

_define_signed_div(s32, int32_t, INT32_MAX)
_define_signed_div(least32, int_least32_t, INT_LEAST32_MAX)
_define_signed_div(fast32, int_fast32_t, INT_FAST32_MAX)

_define_signed_div(s64, int64_t, INT64_MAX)
_define_signed_div(long_long, long long, LLONG_MAX)
_define_signed_div(least64, int_least64_t, INT_LEAST64_MAX)
_define_signed_div(fast64, int_fast64_t, INT_FAST64_MAX)

_define_signed_div(int, int, INT_MAX)
_define_signed_div(long, long, LONG_MAX)
_define_signed_div(intptr, intptr_t, INTPTR_MAX)
_define_signed_div(intmax, intmax_t, INTMAX_MAX)

_define_unsigned_div(u8, uint8_t)
_define_unsigned_div(uchar, unsigned char)
_define_unsigned_div(uleast8, uint_least8_t)
_define_unsigned_div(ufast8, uint_fast8_t)

_define_unsigned_div(u16, uint16_t)
_define_unsigned_div(ushort, unsigned short)
_define_unsigned_div(uleast16, uint_least16_t)
_define_unsigned_div(ufast16, uint_fast16_t)

_define_unsigned_div(u32, uint32_t)
_define_unsigned_div(uleast32, uint_least32_t)
_define_unsigned_div(ufast32, uint_fast32_t)

_define_unsigned_div(u64, uint64_t)
_define_unsigned_div(ulong_long, unsigned long long)
_define_unsigned_div(uleast64, uint_least64_t)
_define_unsigned_div(ufast64, uint_fast64_t)

_define_unsigned_div(uint, unsigned int)
_define_unsigned_div(ulong, unsigned long)
_define_unsigned_div(uintptr, uintptr_t)
_define_unsigned_div(uintmax, uintmax_t)
_define_unsigned_div(size, size_t)

#endif

#ifdef CBASE_DISABLE_CHECKED_MATH
#define _define_cb_safe_math_func(name, op_name, op, int_t) \
    CBASE_API_STATIC int cb_safe_##op_name##_##name(int_t a, int_t b, int_t *res) { \
        *res = a op b; \
        return 0; \
    }
#else
#define _define_cb_safe_math_func(name, op_name, op, int_t) \
    CBASE_API_STATIC int cb_safe_##op_name##_##name(int_t a, int_t b, int_t *res) { \
    if (cb_##op_name##_overflow_##name(a, b, res)) { \
        CBASE_ERROR(CBASE_ERROR_NUMERIC_OVERFLOW); \
    } \
    return 0; \
    }
#endif

_define_cb_safe_math_func(s8, add, +, int8_t)
_define_cb_safe_math_func(s8, sub, -, int8_t)
_define_cb_safe_math_func(s8, mul, *, int8_t)
_define_cb_safe_math_func(s8, div, /, int8_t)

_define_cb_safe_math_func(char, add, +, char)
_define_cb_safe_math_func(char, sub, -, char)
_define_cb_safe_math_func(char, mul, *, char)
_define_cb_safe_math_func(char, div, /, char)

_define_cb_safe_math_func(least8, add, +, int_least8_t)
_define_cb_safe_math_func(least8, sub, -, int_least8_t)
_define_cb_safe_math_func(least8, mul, *, int_least8_t)
_define_cb_safe_math_func(least8, div, /, int_least8_t)

_define_cb_safe_math_func(fast8, add, +, int_fast8_t)
_define_cb_safe_math_func(fast8, sub, -, int_fast8_t)
_define_cb_safe_math_func(fast8, mul, *, int_fast8_t)
_define_cb_safe_math_func(fast8, div, /, int_fast8_t)

_define_cb_safe_math_func(s16, add, +, int16_t)
_define_cb_safe_math_func(s16, sub, -, int16_t)
_define_cb_safe_math_func(s16, mul, *, int16_t)
_define_cb_safe_math_func(s16, div, /, int16_t)

_define_cb_safe_math_func(short, add, +, short)
_define_cb_safe_math_func(short, sub, -, short)
_define_cb_safe_math_func(short, mul, *, short)
_define_cb_safe_math_func(short, div, /, short)

_define_cb_safe_math_func(least16, add, +, int_least16_t)
_define_cb_safe_math_func(least16, sub, -, int_least16_t)
_define_cb_safe_math_func(least16, mul, *, int_least16_t)
_define_cb_safe_math_func(least16, div, /, int_least16_t)

_define_cb_safe_math_func(fast16, add, +, int_fast16_t)
_define_cb_safe_math_func(fast16, sub, -, int_fast16_t)
_define_cb_safe_math_func(fast16, mul, *, int_fast16_t)
_define_cb_safe_math_func(fast16, div, /, int_fast16_t)

_define_cb_safe_math_func(s32, add, +, int32_t)
_define_cb_safe_math_func(s32, sub, -, int32_t)
_define_cb_safe_math_func(s32, mul, *, int32_t)
_define_cb_safe_math_func(s32, div, /, int32_t)

_define_cb_safe_math_func(least32, add, +, int_least32_t)
_define_cb_safe_math_func(least32, sub, -, int_least32_t)
_define_cb_safe_math_func(least32, mul, *, int_least32_t)
_define_cb_safe_math_func(least32, div, /, int_least32_t)

_define_cb_safe_math_func(fast32, add, +, int_fast32_t)
_define_cb_safe_math_func(fast32, sub, -, int_fast32_t)
_define_cb_safe_math_func(fast32, mul, *, int_fast32_t)
_define_cb_safe_math_func(fast32, div, /, int_fast32_t)

_define_cb_safe_math_func(s64, add, +, int64_t)
_define_cb_safe_math_func(s64, sub, -, int64_t)
_define_cb_safe_math_func(s64, mul, *, int64_t)
_define_cb_safe_math_func(s64, div, /, int64_t)

_define_cb_safe_math_func(long_long, add, +, long long)
_define_cb_safe_math_func(long_long, sub, -, long long)
_define_cb_safe_math_func(long_long, mul, *, long long)
_define_cb_safe_math_func(long_long, div, /, long long)

_define_cb_safe_math_func(least64, add, +, int_least64_t)
_define_cb_safe_math_func(least64, sub, -, int_least64_t)
_define_cb_safe_math_func(least64, mul, *, int_least64_t)
_define_cb_safe_math_func(least64, div, /, int_least64_t)

_define_cb_safe_math_func(fast64, add, +, int_fast64_t)
_define_cb_safe_math_func(fast64, sub, -, int_fast64_t)
_define_cb_safe_math_func(fast64, mul, *, int_fast64_t)
_define_cb_safe_math_func(fast64, div, /, int_fast64_t)

_define_cb_safe_math_func(int, add, +, int)
_define_cb_safe_math_func(int, sub, -, int)
_define_cb_safe_math_func(int, mul, *, int)
_define_cb_safe_math_func(int, div, /, int)

_define_cb_safe_math_func(long, add, +, long)
_define_cb_safe_math_func(long, sub, -, long)
_define_cb_safe_math_func(long, mul, *, long)
_define_cb_safe_math_func(long, div, /, long)

_define_cb_safe_math_func(intptr, add, +, intptr_t)
_define_cb_safe_math_func(intptr, sub, -, intptr_t)
_define_cb_safe_math_func(intptr, mul, *, intptr_t)
_define_cb_safe_math_func(intptr, div, /, intptr_t)

_define_cb_safe_math_func(intmax, add, +, intmax_t)
_define_cb_safe_math_func(intmax, sub, -, intmax_t)
_define_cb_safe_math_func(intmax, mul, *, intmax_t)
_define_cb_safe_math_func(intmax, div, /, intmax_t)

_define_cb_safe_math_func(u8, add, +, uint8_t)
_define_cb_safe_math_func(u8, sub, -, uint8_t)
_define_cb_safe_math_func(u8, mul, *, uint8_t)
_define_cb_safe_math_func(u8, div, /, uint8_t)

_define_cb_safe_math_func(uchar, add, +, unsigned char)
_define_cb_safe_math_func(uchar, sub, -, unsigned char)
_define_cb_safe_math_func(uchar, mul, *, unsigned char)
_define_cb_safe_math_func(uchar, div, /, unsigned char)

_define_cb_safe_math_func(uleast8, add, +, uint_least8_t)
_define_cb_safe_math_func(uleast8, sub, -, uint_least8_t)
_define_cb_safe_math_func(uleast8, mul, *, uint_least8_t)
_define_cb_safe_math_func(uleast8, div, /, uint_least8_t)

_define_cb_safe_math_func(ufast8, add, +, uint_fast8_t)
_define_cb_safe_math_func(ufast8, sub, -, uint_fast8_t)
_define_cb_safe_math_func(ufast8, mul, *, uint_fast8_t)
_define_cb_safe_math_func(ufast8, div, /, uint_fast8_t)

_define_cb_safe_math_func(u16, add, +, uint16_t)
_define_cb_safe_math_func(u16, sub, -, uint16_t)
_define_cb_safe_math_func(u16, mul, *, uint16_t)
_define_cb_safe_math_func(u16, div, /, uint16_t)

_define_cb_safe_math_func(ushort, add, +, unsigned short)
_define_cb_safe_math_func(ushort, sub, -, unsigned short)
_define_cb_safe_math_func(ushort, mul, *, unsigned short)
_define_cb_safe_math_func(ushort, div, /, unsigned short)

_define_cb_safe_math_func(uleast16, add, +, uint_least16_t)
_define_cb_safe_math_func(uleast16, sub, -, uint_least16_t)
_define_cb_safe_math_func(uleast16, mul, *, uint_least16_t)
_define_cb_safe_math_func(uleast16, div, /, uint_least16_t)

_define_cb_safe_math_func(ufast16, add, +, uint_fast16_t)
_define_cb_safe_math_func(ufast16, sub, -, uint_fast16_t)
_define_cb_safe_math_func(ufast16, mul, *, uint_fast16_t)
_define_cb_safe_math_func(ufast16, div, /, uint_fast16_t)

_define_cb_safe_math_func(u32, add, +, uint32_t)
_define_cb_safe_math_func(u32, sub, -, uint32_t)
_define_cb_safe_math_func(u32, mul, *, uint32_t)
_define_cb_safe_math_func(u32, div, /, uint32_t)

_define_cb_safe_math_func(uleast32, add, +, uint_least32_t)
_define_cb_safe_math_func(uleast32, sub, -, uint_least32_t)
_define_cb_safe_math_func(uleast32, mul, *, uint_least32_t)
_define_cb_safe_math_func(uleast32, div, /, uint_least32_t)

_define_cb_safe_math_func(ufast32, add, +, uint_fast32_t)
_define_cb_safe_math_func(ufast32, sub, -, uint_fast32_t)
_define_cb_safe_math_func(ufast32, mul, *, uint_fast32_t)
_define_cb_safe_math_func(ufast32, div, /, uint_fast32_t)

_define_cb_safe_math_func(u64, add, +, uint64_t)
_define_cb_safe_math_func(u64, sub, -, uint64_t)
_define_cb_safe_math_func(u64, mul, *, uint64_t)
_define_cb_safe_math_func(u64, div, /, uint64_t)

_define_cb_safe_math_func(ulong_long, add, +, unsigned long long)
_define_cb_safe_math_func(ulong_long, sub, -, unsigned long long)
_define_cb_safe_math_func(ulong_long, mul, *, unsigned long long)
_define_cb_safe_math_func(ulong_long, div, /, unsigned long long)

_define_cb_safe_math_func(uleast64, add, +, uint_least64_t)
_define_cb_safe_math_func(uleast64, sub, -, uint_least64_t)
_define_cb_safe_math_func(uleast64, mul, *, uint_least64_t)
_define_cb_safe_math_func(uleast64, div, /, uint_least64_t)

_define_cb_safe_math_func(ufast64, add, +, uint_fast64_t)
_define_cb_safe_math_func(ufast64, sub, -, uint_fast64_t)
_define_cb_safe_math_func(ufast64, mul, *, uint_fast64_t)
_define_cb_safe_math_func(ufast64, div, /, uint_fast64_t)

_define_cb_safe_math_func(uint, add, +, unsigned int)
_define_cb_safe_math_func(uint, sub, -, unsigned int)
_define_cb_safe_math_func(uint, mul, *, unsigned int)
_define_cb_safe_math_func(uint, div, /, unsigned int)

_define_cb_safe_math_func(ulong, add, +, unsigned long)
_define_cb_safe_math_func(ulong, sub, -, unsigned long)
_define_cb_safe_math_func(ulong, mul, *, unsigned long)
_define_cb_safe_math_func(ulong, div, /, unsigned long)

_define_cb_safe_math_func(uintptr, add, +, uintptr_t)
_define_cb_safe_math_func(uintptr, sub, -, uintptr_t)
_define_cb_safe_math_func(uintptr, mul, *, uintptr_t)
_define_cb_safe_math_func(uintptr, div, /, uintptr_t)

_define_cb_safe_math_func(uintmax, add, +, uintmax_t)
_define_cb_safe_math_func(uintmax, sub, -, uintmax_t)
_define_cb_safe_math_func(uintmax, mul, *, uintmax_t)
_define_cb_safe_math_func(uintmax, div, /, uintmax_t)

_define_cb_safe_math_func(size, add, +, size_t)
_define_cb_safe_math_func(size, sub, -, size_t)
_define_cb_safe_math_func(size, mul, *, size_t)
_define_cb_safe_math_func(size, div, /, size_t)

#ifdef CBASE_DISABLE_POINTER_ARITHMETIC_CHECKS
CBASE_API_STATIC int cb_safe_ptrdiff(const void *p2,
                                     const void *p1,
                                     void **res) {
    *res = (void *)(((const char *)p2) - ((const char *)p1));

    return 0;
}
#else
CBASE_API_STATIC int cb_safe_ptrdiff(const void *p2,
                                     const void *p1,
                                     void **res) {
    CBASE_ERROR_IF((p2 < p1), CBASE_ERROR_OUT_OF_BOUNDS);

    *res = (void *)(((const char *)p2) - ((const char *)p1));

    return 0;
}
#endif

#endif

/* vi: set et ts=4 sw=4: */

#pragma once

#ifndef SWAP_H__
#define SWAP_H__

#include "cbase/internal.h"

#if defined(HAVE_ASM_BYTEORDER_H)
#include <asm/byteorder.h>

#define cbswap16 bswap_16
#define cbswap32 bswap_32
#define cbswap64 bswap_64

#elif defined(HAVE_BYTESWAP_H)
#include <byteswap.h>

#define cbswap16 bswap_16
#define cbswap32 bswap_32
#define cbswap64 bswap_64

#else

#define cbswap16(x) ((uint16_t)((((x) >> 8) & 0xFFU) | (((x)&0xFFU) << 8)))

#define cbswap32(x)                                                           \
    ((uint32_t)((((x)&0xFF000000U) >> 24) | (((x)&0x00FF0000U) >> 8) |        \
                (((x)&0x0000FF00U) << 8) | (((x)&0x000000FFU) << 24)))

#define cbswap64(x)                                                           \
    ((uint64_t)((((x)&0XFF00000000000000ULL) >> 56) |                         \
                (((x)&0X00FF000000000000ULL) >> 40) |                         \
                (((x)&0X0000FF0000000000ULL) >> 24) |                         \
                (((x)&0X000000FF00000000ULL) >> 8) |                          \
                (((x)&0X00000000FF000000ULL) << 8) |                          \
                (((x)&0X0000000000FF0000ULL) << 24) |                         \
                (((x)&0X000000000000FF00ULL) << 40) |                         \
                (((x)&0X00000000000000FFULL) << 56)))

#endif

#ifdef WORDS_BIGENDIAN
#define CB_BIGENDIAN    1
#define CB_LITTLEENDIAN 0

#define cble16(x) (cbswap16(x))
#define cble32(x) (cbswap32(x))
#define cble64(x) (cbswap64(x))

#define cbbe16(x) (x)
#define cbbe32(x) (x)
#define cbbe64(x) (x)
#else
#define CB_BIGENDIAN    0
#define CB_LITTLEENDIAN 1

#define cble16(x) (x)
#define cble32(x) (x)
#define cble64(x) (x)

#define cbbe16(x) (cbswap16(x))
#define cbbe32(x) (cbswap32(x))
#define cbbe64(x) (cbswap64(x))
#endif

#endif

#pragma once

#ifndef _CBASE_UTIL_H__
#define _CBASE_UTIL_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "cbase/checked_math.h"
#include "cbase/errors.h"

CBASE_API
void cb_zero_buf_no_check(void *buf, size_t byte_count);

CBASE_API_STATIC int cb_zero_buf(void *buf, size_t count, size_t size) {
    size_t byte_count = 0;

    CBASE_PROPAGATE_ERROR(cb_safe_mul_size(count, size, &byte_count));

    cb_zero_buf_no_check(buf, byte_count);

    return 0;
}

CBASE_API
void *
_cb_memmem(const void *haystack, size_t hlen, const void *needle, size_t nlen);

#ifndef HAVE_MEMMEM
#define memmem _cb_memmem
#endif

CBASE_API
void cb_memmem_no_check(const void *haystack,
                        size_t hlen,
                        const void *needle,
                        size_t nlen,
                        void **location);

CBASE_API
int cb_memmem(const void *haystack,
              size_t hlen,
              const void *needle,
              size_t nlen,
              void **location);

#endif

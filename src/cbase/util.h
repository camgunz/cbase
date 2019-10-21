#pragma once

#ifndef UTIL_H__
#define UTIL_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "cbase/errors.h"
#include "cbase/status.h"

static inline
size_t positive_ptrdiff(void *p1, void *p2) {
    if (p1 > p2) { /* [TODO] Maybe warn here? */
        return 0;
    }

    return ((char *)p1) - ((char *)p2);
}

static inline
bool cstr_end(const char *cs) {
    return ((!cs) || (!*cs));
}

static inline
bool check_overflow(size_t a, size_t b) {
    return !((a > 1) && (b > 1) && ((SIZE_MAX / a) < b));
}

void zero_buf_fast(void *buf, size_t byte_count);

static inline
bool zero_buf(void *buf, size_t count, size_t size, Status *status) {
    if (!check_overflow(count, size)) {
        return numeric_overflow(status);
    }

    zero_buf_fast(buf, count * size);

    return status_ok(status);
}

#endif

/* vi: set et ts=4 sw=4: */

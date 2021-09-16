#pragma once

#ifndef _CBASE_CHECKED_MATH_H__
#define _CBASE_CHECKED_MATH_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cbase/errors.h"

#define _CBASE_HALF_UINTMAX_MAX (UINTMAX_MAX >> 1)

#ifdef HAVE_BUILTIN_ADD_OVERFLOW
CBASE_API_STATIC bool cb_add_overflowed(uintmax_t a,
                                        uintmax_t b,
                                        uintmax_t *res) {
    return __builtin_add_overflow(a, b, res);
}
#else
bool cb_add_overflowed(uintmax_t a, uintmax_t b, uintmax_t *res) {
    *res = a + b;

    return (((a > _CBASE_HALF_UINTMAX_MAX) && (b > _CBASE_HALF_UINTMAX_MAX)) ||
            ((b < a) && ((b << 1) > (UINTMAX_MAX - (a - b)))) ||
            ((a < b) && ((a << 1) > (UINTMAX_MAX - (b - a)))));
}
#endif

#ifdef HAVE_BUILTIN_SUB_OVERFLOW
CBASE_API_STATIC bool cb_sub_overflowed(uintmax_t a,
                                        uintmax_t b,
                                        uintmax_t *res) {
    return _builtin_sub_overflow(a, b, res);
}
#else
CBASE_API_STATIC bool cb_sub_overflowed(uintmax_t a,
                                        uintmax_t b,
                                        uintmax_t *res) {
    *res = a - b;

    return (a < b);
}
#endif

#ifdef HAVE_BUILTIN_MUL_OVERFLOW
CBASE_API_STATIC bool cb_mul_overflowed(uintmax_t a,
                                        uintmax_t b,
                                        uintmax_t *res) {
    return __builtin_mul_overflow(a, b, res);
}
#else
CBASE_API_STATIC bool cb_mul_overflowed(uintmax_t a,
                                        uintmax_t b,
                                        uintmax_t *res) {
    *res = a * b;

    return ((a > 1) && (b > 1) && ((UINTMAX_MAX / a) < b));
}
#endif

/*
 * We want to at least check dividing the most-negative value by -1.
 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=78473
 */

CBASE_API_STATIC bool cb_sdiv_overflowed(intmax_t a,
                                         intmax_t b,
                                         intmax_t *res) {
    *res = a / b;

    return (a == INTMAX_MIN) && (b == -1);
}

#ifdef CBASE_DISABLE_CHECKED_MATH
CBASE_API_STATIC int cb_safe_add(uintmax_t a, uintmax_t b, uintmax_t *res) {
    *res = a + b;

    return 0;
}
#else
CBASE_API_STATIC int cb_safe_add(uintmax_t a, uintmax_t b, uintmax_t *res) {
    uintmax_t res2 = 0;

    CBASE_ERROR_IF(cb_add_overflowed(a, b, &res2),
                   CBASE_ERROR_NUMERIC_OVERFLOW);

    *res = res2;

    return 0;
}
#endif

#ifdef CBASE_DISABLE_CHECKED_MATH
CBASE_API_STATIC int cb_safe_sub(uintmax_t a, uintmax_t b, uintmax_t *res) {
    *res = a - b;

    return 0;
}
#else
CBASE_API_STATIC int cb_safe_sub(uintmax_t a, uintmax_t b, uintmax_t *res) {
    uintmax_t res2 = 0;

    CBASE_ERROR_IF(cb_sub_overflowed(a, b, &res2),
                   CBASE_ERROR_NUMERIC_OVERFLOW);

    *res = res2;

    return 0;
}
#endif

#ifdef CBASE_DISABLE_CHECKED_MATH
CBASE_API_STATIC int cb_safe_mul(uintmax_t a, uintmax_t b, uintmax_t *res) {
    *res = a * b;

    return 0;
}
#else
CBASE_API_STATIC int cb_safe_mul(uintmax_t a, uintmax_t b, uintmax_t *res) {
    uintmax_t res2 = 0;

    CBASE_ERROR_IF(cb_mul_overflowed(a, b, &res2),
                   CBASE_ERROR_NUMERIC_OVERFLOW);

    *res = res2;

    return 0;
}
#endif

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

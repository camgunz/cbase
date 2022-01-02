#pragma once

#ifndef UTF8_BASE_H__
#define UTF8_BASE_H__

#include "cbase/internal.h"

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#include <utf8proc.h>

#include "cbase/errors.h"

enum
{
    CBASE_UTF8_TOO_LONG = 22000,
    CBASE_UTF8_INVALID_UTF8,
    CBASE_UTF8_UNASSIGNED_RUNE,
    CBASE_UTF8_INVALID_OPTIONS,
    CBASE_UTF8_EMPTY,
    CBASE_UTF8_UNKNOWN_ERROR,
};

static inline int utf8_handle_error_code(ssize_t error_code) {
    switch (error_code) {
    case UTF8PROC_ERROR_NOMEM:
        return CBASE_ERROR_OUT_OF_BOUNDS;
    case UTF8PROC_ERROR_OVERFLOW:
        return CBASE_UTF8_TOO_LONG;
    case UTF8PROC_ERROR_INVALIDUTF8:
        return CBASE_UTF8_INVALID_UTF8;
    case UTF8PROC_ERROR_NOTASSIGNED:
        return CBASE_UTF8_UNASSIGNED_RUNE;
    case UTF8PROC_ERROR_INVALIDOPTS:
        return CBASE_UTF8_INVALID_OPTIONS;
    default:
        return CBASE_UTF8_UNKNOWN_ERROR;
    }

    return 0;
}

#endif

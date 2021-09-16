#pragma once

#ifndef _CBASE_ERRORS_H__
#define _CBASE_ERRORS_H__

#include <limits.h>

#include "cbase/internal.h"

#include "cbase/log.h"

typedef enum
{
    CBASE_ERROR_OUT_OF_BOUNDS = INT_MAX - 1,
    CBASE_ERROR_MEMORY_ALLOC_FAILED = INT_MAX - 2,
    CBASE_ERROR_NOT_FOUND = INT_MAX - 3,
    CBASE_ERROR_NOT_EQUAL = INT_MAX - 4,
    CBASE_ERROR_NUMERIC_OVERFLOW = INT_MAX - 5,
    CBASE_ERROR_NULL_POINTER = INT_MAX - 6,
    CBASE_ERROR_OVERLAPPING_MEMORY = INT_MAX - 7,
    CBASE_ERROR_CODE_COUNT = INT_MAX - CBASE_ERROR_OVERLAPPING_MEMORY,
} ErrorCode;

/* [TODO] Add an option to log file/line here also, for "tracebacks" */
#define CBASE_PROPAGATE_ERROR(call)                                           \
    do {                                                                      \
        int _error = call;                                                    \
        if (_error) {                                                         \
            return _error;                                                    \
        }                                                                     \
    } while (0)

#define CBASE_FREE_AND_PROPAGATE_ERROR(call, free_func, obj)                  \
    do {                                                                      \
        int _error = call;                                                    \
        if (_error) {                                                         \
            free_func((obj));                                                 \
            return _error;                                                    \
        }                                                                     \
    } while (0)

#ifndef ERRORS

#define CBASE_DELEGATE(call)                                           \
    do {                                                                      \
        return call;                                                          \
    } while (0)

#define CBASE_ERROR(code)                                                     \
    do {                                                                      \
        return (code);                                                        \
    } while (0)

#define CBASE_ERROR_IF(cond, code)                                            \
    do {                                                                      \
        int _error = (cond);                                                  \
        if (_error) {                                                         \
            return (code);                                                    \
        }                                                                     \
    } while (0)

#else

#if (ERRORS == ERROR_LEVEL_CONFIGURABLE) || (ERRORS == ERRORS_CONFIGURABLE)
CBASE_API
LogLevel errors_get_log_level(ErrorCode code) CBASE_API_ATTRS;

CBASE_API
void errors_set_log_level(ErrorCode code, LogLevel level) CBASE_API_ATTRS;

#endif

#if ERRORS == ERRORS_CONFIGURABLE
typedef void(ErrorHandler)(ErrorCode code, const char *file, int line);

CBASE_API
ErrorHandler *errors_get_handler(ErrorCode code) CBASE_API_ATTRS;

CBASE_API
void errors_set_handler(ErrorCode code, ErrorHandler handler) CBASE_API_ATTRS;

#endif

_CBASE_API_STATIC
void _default_error_handler(ErrorCode code, const char *file, int line) {
    switch (code) {
    case CBASE_ERROR_OUT_OF_BOUNDS:
        _internal_log_msg(
#if ERRORS == ERROR_LEVELS_DEFAULT
            CBASE_LOG_LEVEL_CRITICAL,
#else
            errors_get_log_level(code),
#endif
            "%s:%u Out of bounds",
            file,
            line);
        break;
    case CBASE_ERROR_MEMORY_ALLOC_FAILED:
        _internal_log_msg(
#if ERRORS == ERROR_LEVELS_DEFAULT
            CBASE_LOG_LEVEL_CRITICAL,
#else
            errors_get_log_level(code),
#endif
            "%s:%u Memory allocation failed",
            file,
            line);
        break;
    case CBASE_ERROR_NOT_FOUND:
        _internal_log_msg(
#if ERRORS == ERROR_LEVELS_DEFAULT
            CBASE_LOG_LEVEL_FAILURE,
#else
            errors_get_log_level(code),
#endif
            "%s:%u Value not found",
            file,
            line);
        break;
    case CBASE_ERROR_NOT_EQUAL:
        _internal_log_msg(
#if ERRORS == ERROR_LEVELS_DEFAULT
            CBASE_LOG_LEVEL_FAILURE,
#else
            errors_get_log_level(code),
#endif
            "%s:%u Values not equal",
            file,
            line);
        break;
    case CBASE_ERROR_NUMERIC_OVERFLOW:
        _internal_log_msg(
#if ERRORS == ERROR_LEVELS_DEFAULT
            CBASE_LOG_LEVEL_ERROR,
#else
            errors_get_log_level(code),
#endif
            "%s:%u Numeric overflow",
            file,
            line);
        break;
    case CBASE_ERROR_NULL_POINTER:
        _internal_log_msg(
#if ERRORS == ERROR_LEVELS_DEFAULT
            CBASE_LOG_LEVEL_ERROR,
#else
            errors_get_log_level(code),
#endif
            "%s:%u Null pointer",
            file,
            line);
        break;
    case CBASE_ERROR_OVERLAPPING_MEMORY:
        _internal_log_msg(
#if ERRORS == ERROR_LEVELS_DEFAULT
            CBASE_LOG_LEVEL_ERROR,
#else
            errors_get_log_level(code),
#endif
            "%s:%u Overlapping memory not allowed here",
            file,
            line);
        break;
    default:
        _internal_log_msg(CBASE_LOG_LEVEL_CRITICAL,
                          "%s:%u General error",
                          file,
                          line);
        break;
    }
}

#define CBASE_DELEGATE(call)                                           \
    do {                                                                      \
        int _error = call;                                                    \
        if (_error) {                                                         \
            _default_error_handler(error, __FILE__, __LINE__);                     \
        }                                                                     \
        return _error;                                                    \
    } while (0)

#define CBASE_ERROR(code)                                                     \
    do {                                                                      \
        _default_error_handler(code, __FILE__, __LINE__);                     \
        return (code);                                                        \
    } while (0)

#define CBASE_ERROR_IF(cond, code)                                            \
    do {                                                                      \
        int _error = (cond);                                                  \
        if (_error) {                                                         \
            _default_error_handler(code, __FILE__, __LINE__);                 \
            return (code);                                                    \
        }                                                                     \
    } while (0)

#endif

#endif

/* vi: set et ts=4 sw=4: */

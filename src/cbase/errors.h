#pragma once

#ifndef ERRORS_H__
#define ERRORS_H__

enum {
    ERROR_OUT_OF_BOUNDS = 1,
    ERROR_MEMORY_ALLOCATION_FAILED,
    ERROR_NOT_FOUND,
    ERROR_NOT_EQUAL,
    ERROR_NUMERIC_OVERFLOW,
    ERROR_GENERAL_ERROR,
};

#define index_out_of_bounds(status) status_critical( \
    status,                                          \
    "base",                                          \
    ERROR_OUT_OF_BOUNDS,                             \
    "index out of bounds"                            \
)

#define alloc_failure(status) status_critical( \
    status,                                    \
    "base",                                    \
    ERROR_MEMORY_ALLOCATION_FAILED,            \
    "memory allocation failed"                 \
)

#define not_found(status) status_failure( \
    status,                               \
    "base",                               \
    ERROR_NOT_FOUND,                      \
    "search term not found"               \
)

#define not_equal(status) status_failure( \
    status,                               \
    "base",                               \
    ERROR_NOT_EQUAL,                      \
    "values not equal"                    \
)

#define numeric_overflow(status) status_error( \
    status,                                    \
    "base",                                    \
    ERROR_NUMERIC_OVERFLOW,                    \
    "numeric overflow"                         \
)

#define general_error(status) status_critical( \
    status,                                    \
    "base",                                    \
    ERROR_GENERAL_ERROR,                       \
    "General error"                            \
)

#endif

/* vi: set et ts=4 sw=4: */

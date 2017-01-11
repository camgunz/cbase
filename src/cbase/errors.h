#ifndef ERRORS_H__
#define ERRORS_H__

enum {
    ERROR_OUT_OF_BOUNDS = 1,
    ERROR_MEMORY_ALLOCATION_FAILED,
    ERROR_NOT_FOUND
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

#endif

/* vi: set et ts=4 sw=4: */

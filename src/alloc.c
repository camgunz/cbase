#include "cbase/internal.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "cbase/alloc.h"
#include "cbase/checked_math.h"
#include "cbase/errors.h"

#ifndef cb_sysfree
CBASE_API_DEALLOC void cb_sysfree(void *ptr) {
    free(ptr);
}
#endif

#ifndef cb_sysmalloc
CBASE_API_MALLOC(cb_sysfree, 1)
void *cb_sysmalloc(size_t size) {
    return malloc(size);
}
#endif

#ifndef cb_syscalloc
CBASE_API_MALLOC(cb_sysfree, 1)
void *cb_syscalloc(size_t count, size_t size) {
    return calloc(count, size);
}
#endif

#ifndef cb_sysrealloc
CBASE_API void *cb_sysrealloc(void *ptr, size_t size) {
    return realloc(ptr, size);
}
#endif

#ifndef cb_sysmemcpy
CBASE_API void *cb_sysmemcpy(void * restrict dest,
                             const void * restrict src,
                             size_t size) {
    return memmove(dest, src, size);
}
#endif

#ifdef CBASE_DISABLE_CHECKED_MATH_IN_ALLOCATIONS
CBASE_API_MALLOC(_cb_free, 1)
static void *_cb_uniform_sysmalloc(size_t count, size_t size) {
    return cb_sysmalloc(count * size);
}
#else
CBASE_API_MALLOC(_cb_free, 1)
static void *_cb_uniform_sysmalloc(size_t count, size_t size) {
    size_t byte_count = 0;

    CBASE_ERROR_IF(cb_safe_mul(count, size, &byte_count), NULL);

    return cb_sysmalloc(byte_count);
}
#endif

#ifdef CBASE_DISABLE_CHECKED_MATH_IN_ALLOCATIONS
static void *_cb_uniform_sysrealloc(void *ptr, size_t count, size_t size) {
    return cb_sysrealloc(ptr, count * size);
}
#else
static void *_cb_uniform_sysrealloc(void *ptr, size_t count, size_t size) {
    size_t byte_count = 0;

    CBASE_ERROR_IF(cb_safe_mul(count, size, &byte_count), NULL);

    return cb_sysrealloc(ptr, byte_count);
}
#endif

int _cb_malloc(size_t count, size_t size, void **ptr) {
    void *new_ptr = _cb_uniform_sysmalloc(count, size);

    CBASE_ERROR_IF(!new_ptr, CBASE_ERROR_MEMORY_ALLOC_FAILED);

    *ptr = new_ptr;

    return 0;
}

int _cb_calloc(size_t count, size_t size, void **ptr) {
    void *new_ptr = cb_syscalloc(count, size);

    CBASE_ERROR_IF(!new_ptr, CBASE_ERROR_MEMORY_ALLOC_FAILED);

    *ptr = new_ptr;

    return 0;
}

int _cb_realloc(size_t count, size_t size, void **ptr) {
    void *new_ptr = _cb_uniform_sysrealloc(*ptr, count, size);

    CBASE_ERROR_IF(!new_ptr, CBASE_ERROR_MEMORY_ALLOC_FAILED);

    *ptr = new_ptr;

    return 0;
}

void _cb_free(void *ptr) {
    cb_sysfree(ptr);
}

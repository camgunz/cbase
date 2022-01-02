#pragma once

#ifndef _CBASE_ALLOC_H__
#define _CBASE_ALLOC_H__

#include "cbase/internal.h"

#include <stdlib.h>
#include <string.h>

#include "cbase/checked_math.h"
#include "cbase/errors.h"

#ifndef cb_sysfree
CBASE_API_DEALLOC
void cb_sysfree(void *ptr);
#endif

#ifndef cb_sysmalloc
CBASE_API_MALLOC(cb_sysfree, 1)
void *cb_sysmalloc(size_t size);
#endif

#ifndef cb_syscalloc
CBASE_API_MALLOC(cb_sysfree, 1)
void *cb_syscalloc(size_t count, size_t size);
#endif

#ifndef cb_sysrealloc
CBASE_API
void *cb_sysrealloc(void *ptr, size_t size);
#endif

#ifndef cb_sysmemcpy
CBASE_API
void *cb_sysmemcpy(void * restrict dest,
                   const void * restrict src,
                   size_t size);
#endif

#ifdef CBASE_DISABLE_CHECKED_MATH_IN_ALLOCATIONS
CBASE_API_STATIC
int _cb_malloc(size_t count, size_t size, void **ptr) {
    void *new_ptr = cb_sysmalloc(count * size);

    CBASE_ERROR_IF(!new_ptr, CBASE_ERROR_MEMORY_ALLOC_FAILED);

    *ptr = new_ptr;

    return 0;
}
#else
CBASE_API_STATIC
int _cb_malloc(size_t count, size_t size, void **ptr) {
    size_t byte_count = 0;

    CBASE_ERROR_IF(cb_safe_mul_size(count, size, &byte_count),
                   CBASE_ERROR_NUMERIC_OVERFLOW);

    void *new_ptr = cb_sysmalloc(byte_count);

    CBASE_ERROR_IF(!new_ptr, CBASE_ERROR_MEMORY_ALLOC_FAILED);

    *ptr = new_ptr;

    return 0;
}
#endif

#define cb_malloc(_count, _size, _ptr)                                        \
    _cb_malloc((_count), (_size), (void **)(_ptr))

CBASE_API_STATIC
int _cb_calloc(size_t count, size_t size, void **ptr) {
    void *new_ptr = cb_syscalloc(count, size);

    CBASE_ERROR_IF(!new_ptr, CBASE_ERROR_MEMORY_ALLOC_FAILED);

    *ptr = new_ptr;

    return 0;
}

#define cb_calloc(_count, _size, _ptr)                                        \
    _cb_calloc((_count), (_size), (void **)(_ptr))

#ifdef CBASE_DISABLE_CHECKED_MATH_IN_ALLOCATIONS
CBASE_API_STATIC
int _cb_realloc(size_t count, size_t size, void **ptr) {
    void *new_ptr = cb_sysrealloc(ptr, count * size);

    CBASE_ERROR_IF(!new_ptr, CBASE_ERROR_MEMORY_ALLOC_FAILED);

    *ptr = new_ptr;

    return 0;
}
#else
CBASE_API_STATIC
int _cb_realloc(size_t count, size_t size, void **ptr) {
    size_t byte_count = 0;

    CBASE_ERROR_IF(cb_safe_mul_size(count, size, &byte_count),
                   CBASE_ERROR_NUMERIC_OVERFLOW);

    void *new_ptr = cb_sysrealloc(ptr, byte_count);

    CBASE_ERROR_IF(!new_ptr, CBASE_ERROR_MEMORY_ALLOC_FAILED);

    *ptr = new_ptr;

    return 0;
}
#endif

#define cb_realloc(_count, _size, _ptr)                                       \
    _cb_realloc((_count), (_size), (void **)(_ptr))

CBASE_API_STATIC
void cb_free(void *ptr) {
    cb_sysfree(ptr);
}

#ifdef CBASE_DISABLE_CHECKED_MATH_IN_ALLOCATIONS
CBASE_API_STATIC
int cb_memmove(void * restrict dest,
               const void * restrict src,
               size_t count,
               size_t size) {
    (void)memmove(dest, src, count * size);

    return 0;
}
#else
CBASE_API_STATIC
int cb_memmove(void * restrict dest,
               const void * restrict src,
               size_t count,
               size_t size) {
    size_t byte_count = 0;

    CBASE_ERROR_IF(cb_safe_mul_size(count, size, &byte_count),
                   CBASE_ERROR_NUMERIC_OVERFLOW);

    (void)memmove(dest, src, byte_count);

    return 0;
}
#endif

CBASE_API_STATIC
int cb_memdup(const void *ptr, size_t byte_count, void **out) {
    void *new_ptr = NULL;

    CBASE_PROPAGATE_ERROR(cb_malloc(byte_count, 1, &new_ptr));

    CBASE_FREE_AND_PROPAGATE_ERROR(cb_memmove(new_ptr, ptr, byte_count, 1),
                                   cb_free,
                                   new_ptr);

    *out = new_ptr;

    return 0;
}

CBASE_API_STATIC
int cb_strndup(const char *cs, size_t len, char **ptr) {
    char *new_str = NULL;

#ifdef CBASE_DISABLE_CHECKED_MATH_IN_ALLOCATIONS
    CBASE_PROPAGATE_ERROR(
        cb_malloc(len + sizeof(char), sizeof(char), &new_str));
#else
    size_t byte_count = 0;

    CBASE_PROPAGATE_ERROR(cb_safe_add_size(len, sizeof(char), &byte_count));
    CBASE_PROPAGATE_ERROR(cb_malloc(byte_count, sizeof(char), &new_str));
#endif

    CBASE_PROPAGATE_ERROR(cb_memmove(new_str, cs, len, sizeof(char)));

    *(new_str + len) = '\0';

    *ptr = new_str;

    return 0;
}

CBASE_API_STATIC
int cb_strdup(const char *cs, char **ptr) {
    CBASE_PROPAGATE_ERROR(cb_strndup(cs, strlen(cs), ptr));

    return 0;
}

#endif

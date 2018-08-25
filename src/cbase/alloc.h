#pragma once

#ifndef ALLOC_H__
#define ALLOC_H__

#define _cbmalloc(count, size, ptr, status) \
    __cbmalloc(count, size, (void **)ptr, status)

#define _cbcalloc(count, size, ptr, status) \
    __cbcalloc(count, size, (void **)ptr, status)

#define _cbrealloc(count, size, ptr, status) \
    __cbrealloc(count, size, (void **)ptr, status)

#ifndef cbbase_malloc
#define cbbase_malloc malloc
#endif

#ifndef cbbase_calloc
#define cbbase_calloc calloc
#endif

#ifndef cbbase_realloc
#define cbbase_realloc realloc
#endif

#ifndef cbbase_free
#define cbbase_free free
#endif

#ifndef cbbase_memmove
#define cbbase_memmove memmove
#endif

#ifndef cbmalloc
#define cbmalloc _cbmalloc
#endif

#ifndef cbcalloc
#define cbcalloc _cbcalloc
#endif

#ifndef cbrealloc
#define cbrealloc _cbrealloc
#endif

#ifndef cbfree
#define cbfree __cbfree
#endif

#ifndef cbmemmove
#define cbmemmove __cbmemmove
#endif

#ifndef cbmemdup
#define cbmemdup __cbmemdup
#endif

#ifndef cbstrndup
#define cbstrndup __cbstrndup
#endif

#ifndef cbstrdup
#define cbstrdup __cbstrdup
#endif

bool __cbmalloc(size_t count, size_t size, void **ptr, Status *status);

bool __cbcalloc(size_t count, size_t size, void **ptr, Status *status);

bool __cbrealloc(size_t count, size_t size, void **ptr, Status *status);

void __cbfree(void *ptr);

bool __cbmemmove(void *dest, const void *src, size_t count, size_t size,
                                                            Status *status);

bool __cbmemcpy(void *dest, const void *src, size_t count, size_t size,
                                                           Status *status);

bool __cbmemdup(const void *ptr, size_t byte_count, Status *status);

bool __cbstrndup(const char *cs, size_t len, char **ptr, Status *status);

bool __cbstrdup(const char *cs, char **ptr, Status *status);

#endif

/* vi: set et ts=4 sw=4: */

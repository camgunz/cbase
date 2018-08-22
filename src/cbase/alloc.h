#pragma once

#ifndef ALLOC_H__
#define ALLOC_H__

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
#define cbmalloc __cbmalloc
#endif

#ifndef cbcalloc
#define cbcalloc __cbcalloc
#endif

#ifndef cbrealloc
#define cbrealloc __cbrealloc
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

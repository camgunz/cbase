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

/* [TODO] Look for reallocarray and use here if found */
static inline
bool __cbmalloc(size_t count, size_t size, void **ptr, Status *status) {
    void *new_ptr = NULL;

    if (!check_overflow(count, size)) {
        return numeric_overflow(status);
    }

    new_ptr = cbbase_malloc(count * size);

    if (!new_ptr) {
        return alloc_failure(status);
    }

    *ptr = new_ptr;

    return status_ok(status);
}

static inline
bool __cbcalloc(size_t count, size_t size, void **ptr, Status *status) {
    void *new_ptr = cbbase_calloc(count, size);

    if (!new_ptr) {
        return alloc_failure(status);
    }

    *ptr = new_ptr;

    return status_ok(status);
}

static inline
bool __cbrealloc(size_t count, size_t size, void **ptr, Status *status) {
    void *new_ptr = NULL;

    if (!check_overflow(count, size)) {
        return numeric_overflow(status);
    }

    new_ptr = cbbase_realloc(*ptr, count * size);

    if (!new_ptr) {
        return alloc_failure(status);
    }

    *ptr = new_ptr;

    return status_ok(status);
}

static inline
void __cbfree(void *ptr) {
    cbbase_free(ptr);
}

static inline
bool __cbmemmove(void *dest, const void *src, size_t count, size_t size,
                                                            Status *status) {
    if (!check_overflow(count, size)) {
        return numeric_overflow(status);
    }

    (void)cbbase_memmove(dest, src, count * size);

    return status_ok(status);
}

static inline
bool __cbmemcpy(void *dest, const void *src, size_t count, size_t size,
                                                           Status *status) {
    return cbmemmove(dest, src, count, size, status);
}

static inline
bool __cbmemdup(const void *ptr, size_t byte_count, Status *status) {
    void *buf = NULL;

    return (
        cbmalloc(byte_count, 1, &buf, status) &&
        cbmemmove(buf, ptr, byte_count, 1, status)
    );
}

static inline
bool __cbstrndup(const char *cs, size_t len, char **ptr, Status *status) {
    char *new_str = NULL;
    
    if (!cbmalloc(len + 1, sizeof(char), (void **)new_str, status)) {
        return false;
    }

    if (!cbmemmove(new_str, cs, len, sizeof(char), status)) {
        return false;
    }

    *(new_str + len) = '\0';

    *ptr = new_str;

    return status_ok(status);
}

static inline
bool __cbstrdup(const char *cs, char **ptr, Status *status) {
    return cbstrndup(cs, strlen(cs), ptr, status);
}

#endif

/* vi: set et ts=4 sw=4: */

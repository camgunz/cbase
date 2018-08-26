#include "cbase.h"

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

bool __cbcalloc(size_t count, size_t size, void **ptr, Status *status) {
    void *new_ptr = cbbase_calloc(count, size);

    if (!new_ptr) {
        return alloc_failure(status);
    }

    *ptr = new_ptr;

    return status_ok(status);
}

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

void __cbfree(void *ptr) {
    cbbase_free(ptr);
}

bool __cbmemmove(void *dest, const void *src, size_t count, size_t size,
                                                            Status *status) {
    if (!check_overflow(count, size)) {
        return numeric_overflow(status);
    }

    (void)cbbase_memmove(dest, src, count * size);

    return status_ok(status);
}

bool __cbmemcpy(void *dest, const void *src, size_t count, size_t size,
                                                           Status *status) {
    return cbmemmove(dest, src, count, size, status);
}

bool __cbmemdup(const void *ptr, size_t byte_count, Status *status) {
    void *buf = NULL;

    return (
        cbmalloc(byte_count, 1, &buf, status) &&
        cbmemmove(buf, ptr, byte_count, 1, status)
    );
}

bool __cbstrndup(const char *cs, size_t len, char **ptr, Status *status) {
    char *new_str = NULL;
    
    if (!cbmalloc(len + 1, sizeof(char), &new_str, status)) {
        return false;
    }

    if (!cbmemmove(new_str, cs, len, sizeof(char), status)) {
        return false;
    }

    *(new_str + len) = '\0';

    *ptr = new_str;

    return status_ok(status);
}

bool __cbstrdup(const char *cs, char **ptr, Status *status) {
    return cbstrndup(cs, strlen(cs), ptr, status);
}

/* vi: set et ts=4 sw=4: */

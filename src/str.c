#include "cbase.h"

bool string_printf(String *s, Status *status, const char *fmt, ...) {
    va_list args;
    va_list args2;
    size_t size;

    va_start(args, fmt);

    va_copy(args2, args);

    size = vsnprintf(NULL, 0, fmt, args2);

    if (!string_ensure_capacity(s, size, status)) {
        va_end(args);
        return false;
    }

    vsnprintf(s->data, size + 1, fmt, args);

    va_end(args);

    if (!utf8len(s->data, &s->len, status)) {
        return false;
    }

    s->byte_len = size;

    return status_ok(status);
}

bool string_init(String *s, const char *data, Status *status) {
    s->len = 0;
    s->byte_len = 0;
    s->alloc = 0;
    s->data = NULL;

    return string_assign(s, data, status);
}

bool string_init_len(String *s, const char *data, size_t len, Status *status) {
    s->len = 0;
    s->byte_len = 0;
    s->alloc = 0;
    s->data = NULL;

    return string_assign_len(s, data, len, status);
}

bool string_init_full(String *s, const char *data, size_t len,
                                                   size_t byte_len,
                                                   Status *status) {
    s->len = 0;
    s->byte_len = 0;
    s->alloc = 0;
    s->data = NULL;

    return string_assign_full(s, data, len, byte_len, status);
}

bool string_init_from_sslice(String *s, SSlice *ss, Status *status) {
    if (!string_ensure_capacity(s, ss->byte_len, status)) {
        return false;
    }

    s->len = ss->len;
    s->byte_len = ss->byte_len;
    memmove(s->data, ss->data, ss->byte_len);
    s->data[s->byte_len] = '\0';

    return status_ok(status);
}

bool string_new(String **s, const char *data, Status *status) {
    String *new_string = cbmalloc(1, sizeof(String));

    if (!new_string) {
        return alloc_failure(status);
    }

    if (!string_init(new_string, data, status)) {
        cbfree(new_string);
        return alloc_failure(status);
    }

    *s = new_string;

    return status_ok(status);
}

bool string_new_len(String **s, const char *data, size_t byte_len,
                                                  Status *status) {
    String *new_string = cbmalloc(1, sizeof(String));

    if (!new_string) {
        return alloc_failure(status);
    }

    if (!string_init_len(new_string, data, byte_len, status)) {
        cbfree(new_string);
        return alloc_failure(status);
    }

    *s = new_string;

    return status_ok(status);
}

bool string_new_full(String **s, const char *data, size_t len,
                                                   size_t byte_len,
                                                   Status *status) {
    String *new_string = cbmalloc(1, sizeof(String));

    if (!new_string) {
        return alloc_failure(status);
    }

    if (!string_init_full(new_string, data, len, byte_len, status)) {
        cbfree(new_string);
        return alloc_failure(status);
    }

    *s = new_string;

    return status_ok(status);
}

bool string_ensure_capacity(String *s, size_t byte_len, Status *status) {
    if ((byte_len > 0) && (s->alloc < (byte_len + 1))) {
        char *new_data = cbrealloc(s->data, byte_len + 1, sizeof(char));

        if (!new_data) {
            return alloc_failure(status);
        }

        s->data = new_data;
        s->alloc = byte_len + 1;
    }

    return status_ok(status);
}

bool string_assign(String *s, const char *data, Status *status) {
    size_t len = 0;
    size_t byte_len = 0;
    
    if (data) {
        if (!utf8len(data, &len, status)) {
            return false;
        }
        byte_len = strlen(data);
    }

    return string_assign_full(s, data, len, byte_len, status);
}

bool string_assign_len(String *s, const char *data, size_t byte_len,
                                                    Status *status) {
    size_t len = 0;

    if (data) {
        if (!utf8len(data, &len, status)) {
            return false;
        }
    }

    return string_assign_full(s, data, len, byte_len, status);
}

bool string_assign_full(String *s, const char *data, size_t len,
                                                     size_t byte_len,
                                                     Status *status) {
    if (!string_ensure_capacity(s, byte_len, status)) {
        return false;
    }

    string_assign_cstr_full_fast(s, data, len, byte_len);

    return status_ok(status);
}

bool string_assign_slice(String *s, SSlice *sslice, Status *status) {
    if (!string_ensure_capacity(s, sslice->byte_len, status)) {
        return false;
    }

    string_assign_fast(s, sslice);

    return status_ok(status);
}

bool string_shrink(String *s, Status *status) {
    if (s->alloc > (s->byte_len + 1)) {
        char *new_data = cbrealloc(s->data, s->byte_len + 1, sizeof(char));

        if (!new_data) {
            return alloc_failure(status);
        }

        s->data = new_data;
        s->alloc = s->byte_len + 1;
    }

    return status_ok(status);
}

bool string_copy(String *dst, String *src, Status *status) {
    if (!string_ensure_capacity(dst, src->byte_len, status)) {
        return false;
    }

    string_copy_fast(dst, src);

    return status_ok(status);
}

bool string_slice(String *s, size_t index, size_t len, SSlice *sslice,
                                                       Status *status) {
    ssize_t error;

    if (!string_slice_fast(s, index, len, sslice, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool string_prepend(String *s, SSlice *sslice, Status *status) {
    if (!string_ensure_capacity(s, s->byte_len + sslice->byte_len, status)) {
        return false;
    }

    string_prepend_fast(s, sslice);

    return status_ok(status);
}

bool string_insert(String *s, size_t pos, SSlice *sslice, Status *status) {
    ssize_t error;

    if (!string_ensure_capacity(s, s->byte_len + sslice->byte_len, status)) {
        return false;
    }

    if (!string_insert_fast(s, pos, sslice, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool string_insert_cstr_full(String *s, size_t pos, const char *data,
                                                    size_t len,
                                                    size_t byte_len,
                                                    Status *status) {
    ssize_t error;

    if (!string_ensure_capacity(s, s->byte_len + byte_len, status)) {
        return false;
    }

    if (!string_insert_cstr_fast(s, pos, data, len, byte_len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool string_insert_cstr_fast(String *s, size_t pos, const char *data,
                                                    size_t len,
                                                    size_t byte_len,
                                                    ssize_t *error) {
    char *start = s->data;

    if (pos) {
        if (!utf8_index_fast(s->data, pos, &start, error)) {
            return false;
        }
    }

    size_t byte_offset = (start - s->data) - 1;

    if (byte_offset < s->byte_len) {
        memmove(start + byte_len, start, s->byte_len - byte_offset);
    }

    memmove(start, data, byte_len);

    s->len += len;
    s->byte_len += byte_len;

    return true;
}

bool string_append(String *s, SSlice *sslice, Status *status) {
    if (!string_ensure_capacity(s, s->byte_len + sslice->byte_len, status)) {
        return false;
    }

    string_append_fast(s, sslice);

    return status_ok(status);
}

bool string_delete_fast(String *s, size_t index, size_t len, ssize_t *error) {
    char *start = NULL;
    char *end = NULL;

    if (index) {
        if (!utf8_index_fast(s->data, index, &start, error)) {
            return false;
        }
    }
    else {
        start = s->data;
    }

    if (!utf8_skip_fast(start, len, &end, error)) {
        return false;
    }

    memmove(start, end, (s->byte_len - (end - s->data)) + 1);

    s->len -= len;
    s->byte_len -= (end - start);

    return true;
}

bool string_delete(String *s, size_t index, size_t len, Status *status) {
    ssize_t error;

    if ((index + len) > (s->len + 1)) {
        return index_out_of_bounds(status);
    }

    if (!string_delete_fast(s, index, len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

void string_free(String *s) {
    if (s->data) {
        cbfree(s->data);
        s->data = NULL;
    }

    s->len = 0;
    s->byte_len = 0;
    s->alloc = 0;
}

/* vi: set et ts=4 sw=4: */

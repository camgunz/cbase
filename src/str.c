#include "cbase.h"

#define empty(status) status_failure( \
    status,                           \
    "string",                         \
    STRING_EMPTY,                     \
    "String is empty"                 \
)

bool string_printf(String *s, Status *status, const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);

    if (!string_vprintf(s, status, fmt, args)) {
        va_end(args);
        return false;
    }

    va_end(args);

    return status_ok(status);
}

bool string_vprintf(String *s, Status *status, const char *fmt, va_list args) {
    va_list args2;
    size_t size;

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

bool string_append_printf(String *s, Status *status, const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);

    if (!string_append_vprintf(s, status, fmt, args)) {
        va_end(args);
        return false;
    }

    va_end(args);

    return status_ok(status);
}

bool string_append_vprintf(String *s, Status *status, const char *fmt,
                                                      va_list args) {
    va_list args2;
    size_t size;

    va_copy(args2, args);

    size = vsnprintf(NULL, 0, fmt, args2) + s->byte_len;

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

bool string_init_from_sslice(String *s, SSlice *sslice, Status *status) {
    s->len = 0;
    s->byte_len = 0;
    s->alloc = 0;
    s->data = NULL;

    if (!string_ensure_capacity(s, sslice->byte_len, status)) {
        return false;
    }

    s->len = sslice->len;
    s->byte_len = sslice->byte_len;
    cbmemmove(s->data, sslice->data, sslice->byte_len);
    s->data[s->byte_len] = '\0';

    return status_ok(status);
}

bool string_init_from_slice(String *s, Slice *slice, const char *encoding,
                                                     Status *status) {
    s->len = 0;
    s->byte_len = 0;
    s->alloc = 0;
    s->data = NULL;

    if (!string_ensure_capacity(s, 64, status)) {
        return false;
    }

    return string_assign_slice(s, slice, encoding, status);
}

bool string_init_from_buffer(String *s, Buffer *buffer, const char *encoding,
                                                        Status *status) {
    Slice slice;

    return (
        buffer_slice(buffer, 0, buffer->len, &slice, status) &&
        string_init_from_slice(s, &slice, encoding, status)
    );
}

bool string_new(String **s, const char *data, Status *status) {
    String *new_string = cbmalloc(1, sizeof(String));

    if (!new_string) {
        return alloc_failure(status);
    }

    if (!string_init(new_string, data, status)) {
        cbfree(new_string);
        return false;
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
        return false;
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
        return false;
    }

    *s = new_string;

    return status_ok(status);
}

bool string_new_from_sslice(String **s, SSlice *sslice, Status *status) {
    String *new_string = cbmalloc(1, sizeof(String));

    if (!new_string) {
        return alloc_failure(status);
    }

    if (!string_init_from_sslice(new_string, sslice, status)) {
        cbfree(new_string);
        return false;
    }

    *s = new_string;

    return status_ok(status);
}

bool string_new_from_slice(String **s, Slice *slice, const char *encoding,
                                                  Status *status) {
    String *new_string = cbmalloc(1, sizeof(String));

    if (!new_string) {
        return alloc_failure(status);
    }

    if (!string_init_from_slice(new_string, slice, encoding, status)) {
        cbfree(new_string);
        return false;
    }

    *s = new_string;

    return status_ok(status);
}

bool string_new_from_buffer(String **s, Buffer *buffer, const char *encoding,
                                                        Status *status) {
    String *new_string = cbmalloc(1, sizeof(String));

    if (!new_string) {
        return alloc_failure(status);
    }

    if (!string_init_from_buffer(new_string, buffer, encoding, status)) {
        cbfree(new_string);
        return false;
    }

    *s = new_string;

    return status_ok(status);
}

bool string_ensure_capacity(String *s, size_t byte_len, Status *status) {
    if (s->alloc < (byte_len + 1)) {
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

bool string_assign_sslice(String *s, SSlice *sslice, Status *status) {
    if (!string_ensure_capacity(s, sslice->byte_len, status)) {
        return false;
    }

    string_assign_fast(s, sslice);

    return status_ok(status);
}

bool string_assign_slice(String *s, Slice *slice, const char *encoding,
                                                  Status *status) {
    while (true) {
        Slice out;
        ptrdiff_t bytes_written;

        out.len = s->alloc;
        out.data = s->data;

        if (charset_convert(slice, encoding, "UTF-8", &out, status)) {
            s->byte_len = out.data - s->data;

            if (!utf8len(s->data, &s->len, status)) {
                return false;
            }

            break;
        }

        if (!status_match(status, "charset",
                                  CHARSET_OUTPUT_BUFFER_TOO_SMALL)) {
            return false;
        }

        bytes_written = out.data - s->data;

        if (!string_ensure_capacity(s, s->alloc * 2, status)) {
            return false;
        }

        out.len = s->alloc - bytes_written;
        out.data = s->data + bytes_written;
    }

    return status_ok(status);
}

bool string_assign_buffer(String *s, Buffer *buffer, const char *encoding,
                                                     Status *status) {
    Slice slice;

    return (
        buffer_slice(buffer, 0, buffer->len, &slice, status) &&
        string_assign_slice(s, &slice, encoding, status)
    );
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
        cbmemmove(start + byte_len, start, s->byte_len - byte_offset);
    }

    cbmemmove(start, data, byte_len);

    s->len += len;
    s->byte_len += byte_len;

    return status_ok(status);
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

    cbmemmove(start, end, (s->byte_len - (end - s->data)) + 1);

    s->len -= len;
    s->byte_len -= (end - start);

    return status_ok(status);
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

bool string_get_first_rune(String *s, rune *r, Status *status) {
    if (string_empty(s)) {
        return empty(status);
    }

    return utf8_get_first_rune(s->data, r, status);
}

bool string_encode(String *s, const char *encoding, Buffer *out,
                                                    Status *status) {
    Slice outsl;

    outsl.len = out->alloc;
    outsl.data = out->data;

    while (true) {
        Slice in;

        in.len = s->byte_len;
        in.data = s->data;

        if (charset_convert(&in, "UTF-8", encoding, &outsl, status)) {
            out->len = outsl.data - out->data;
            break;
        }

        if (status_match(status, "charset", CHARSET_OUTPUT_BUFFER_TOO_SMALL)) {
            ptrdiff_t bytes_written = outsl.data - out->data;

            if (!buffer_ensure_capacity(out, out->alloc * 2, status)) {
                return false;
            }

            outsl.len = out->alloc - bytes_written;
            outsl.data = out->data + bytes_written;
        }
        else if (status_match(status, "charset",
                                      CHARSET_BUFFER_DATA_UNINITIALIZED)) {
            if (!buffer_ensure_capacity(out, 64, status)) {
                return false;
            }

            outsl.len = out->alloc;
            outsl.data = out->data;
        }
        else {
            return false;
        }
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

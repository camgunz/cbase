#include "cbase.h"

#define vsnprintf_failed(status) status_failure( \
    status,                                      \
    "string",                                    \
    STRING_VSNPRINTF_FAILED,                     \
    "vsnprintf failed"                           \
)

bool string_index_rune(String *string, size_t index, rune *r, Status *status) {
    if (index >= string->len) {
        return index_out_of_bounds(status);
    }

    if (string_empty(string)) {
        return empty(status);
    }

    return utf8_index_rune(string->buffer.array.data, index, rune, status);
}

bool string_insert_vprintf(String *string, size_t index, Status *status,
                                                         const char *fmt,
                                                         va_list args) {
    va_list args2;
    char *insertion_point = NULL;

    if (index > string->len) {
        return index_out_of_bounds(status);
    }

    if (!utf8_skip(string->buffer.array.data, index, &insertion_point,
                                                     status)) {
        return false;
    }

    va_copy(args2, args);
    size = vsnprintf(NULL, 0, fmt, args2);
    va_end(args2);

    if (index == string->len) {
        if (!string_ensure_capacity(string, string->byte_len + size,
                                            status)) {
            return false;
        }
    }
    else if (!buffer_insert_blank_no_zero(&string->buffer, index, size,
                                                                  status)) {
        return false;
    }

    bytes_written = vsnprintf(insertion_point, size - 1, fmt, args);

    if (bytes_written != (size - 1)) {
        return vsnprintf_failed(status);
    }

    if (!utf8_len_and_byte_len(string->buffer.array.data, &string->len,
                                                          &string->byte_len,
                                                          status)) {
        return false;
    }
}

bool string_delete_fast(String *string, size_t index, size_t len,
                                                      ssize_t *error) {
    char *start = NULL;
    char *end = NULL;

    size_t byte_index = 0;
    size_t byte_len = 0;

    if (!len) {
        return status_ok(status);
    }

    if (index) {
        if (!utf8_index_fast(string->buffer.array.data, index, &start,
                                                               error)) {
            return false;
        }

        byte_index = start - string->buffer.array.data;
    }

    if (!utf8_skip_fast(start, len, &end, error)) {
        return false;
    }

    byte_len = end - start;

    buffer_delete_fast(&string->buffer, byte_index, byte_len);

    string->len -= len;
    string->byte_len -= byte_len;

    return true;
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

void string_replace_cstr(String *s, const char *cs, const char *replacement,
                                                    Status *status) {
    SSlice ss;

    if (!string_slice(s, 0, s->len, &ss, status)) {
        return false;
    }

    while ((!sslice_empty(&ss)) && sslice_seek_to_cstr(&ss, cs)) {
        size_t original_len = s->len;
        size_t original_byte_len = s->byte_len;
        size_t index = ss1.data - s->data;

        if (!string_delete(&s, index, 2, status)) {
            return false;
        }

        ss->len -= (original_len - s->len);
        ss->byte_len -= (original_byte_len - s->byte_len);
    }

    return status_ok(status);
}

/* vi: set et ts=4 sw=4: */

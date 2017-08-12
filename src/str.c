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

/* [FIXME] Should be a `bool *equals` output param */
bool string_first_rune_equals(String *s, rune r, Status *status) {
    rune r2 = 0;

    if (!string_get_first_rune(s, &r2, status)) {
        return false;
    }

    return r2 == r;
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

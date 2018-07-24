#include "cbase.h"

#define empty(status) status_failure( \
    status,                           \
    "strbase",                        \
    STRBASE_EMPTY,                    \
    "String data is empty"            \
)

bool strbase_encode(const char *data, size_t byte_len, const char *encoding,
                                                       Buffer *out,
                                                       Status *status) {
    Slice outsl;

    outsl.len = out->array.alloc;
    outsl.data = out->array.elements;

    while (true) {
        Slice in;

        slice_assign_data(&in, data, byte_len);

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

bool strbase_skip_runes_fast(char **data, size_t *len, size_t *byte_len,
                                                       size_t rune_count) {
    char *cursor = NULL;
    ptrdiff_t diff = 0;

    strbase_index_fast(*data, *byte_len, rune_count, &cursor);

    diff = cursor - *data;

    if (diff < 0) {
        diff = 0;
    }

    *data = cursor;
    *byte_len = diff;
    *len = *len - rune_count;
}

bool strbase_skip_runes(char **data, size_t *len, size_t *byte_len,
                                                  size_t rune_count,
                                                  Status *status) {
    char *cursor = NULL;
    ptrdiff_t diff = 0;

    if (!strbase_index(*data, *byte_len, rune_count, &cursor, status)) {
        return false;
    }

    diff = cursor - *data;

    if (diff < 0) {
        diff = 0;
    }

    *data = cursor;
    *byte_len = diff;
    *len = *len - rune_count;

    return status_ok(status);
}

bool strbase_skip_rune_if_equals(char **data, size_t *len,
                                              size_t *byte_len,
                                              rune r,
                                              Status *status) {
    rune r2 = 0;
    size_t rune_byte_len = 0;

    if (!strbase_index_rune_len(*data, *byte_len, 0, &r2, &rune_byte_len,
                                                          status)) {
        return false;
    }

    if (r2 == r) {
        *data += rune_byte_len;
        *len -= 1;
        *byte_len -= rune_byte_len;
    }

    return status_ok(status);
}

bool strbase_skip_rune_if_matches(char **data, size_t *len,
                                               size_t *byte_len,
                                               RuneMatchFunc *matches,
                                               Status *status) {
    rune r = 0;
    size_t rune_byte_len = 0;

    if (!strbase_index_rune_len(*data, *byte_len, 0, &r, &rune_byte_len,
                                                         status)) {
        return false;
    }

    if (matches(r)) {
        *data += rune_byte_len;
        *len -= 1;
        *byte_len -= rune_byte_len;
    }

    return status_ok(status);
}

bool strbase_pop_rune(char **data, rune *r, Status *status) {
    rune r2 = 0;
    size_t rune_byte_len = 0;

    if (!strbase_index_rune_len(*data, *byte_len, 0, &r2, &rune_byte_len,
                                                          status)) {
        return false;
    }

    *data += rune_byte_len;
    *len -= 1;
    *byte_len -= rune_byte_len;

    *r = r2;

    return status_ok(status);
}

bool strbase_pop_rune_if_equals(char **data, rune r, Status *status) {
    rune r2 = 0;
    size_t rune_byte_len = 0;

    if (!strbase_index_rune_len(*data, *byte_len, 0, &r2, &rune_byte_len,
                                                          status)) {
        return false;
    }

    if (r2 == r) {
        *data += rune_byte_len;
        *len -= 1;
        *byte_len -= rune_byte_len;
    }

    return status_ok(status);
}

bool strbase_pop_rune_if_matches(char **data, size_t *len,
                                              size_t *byte_len,
                                              RuneMatchFunc *matches,
                                              rune *r,
                                              Status *status) {
    rune r2 = 0;
    size_t rune_byte_len = 0;

    if (!strbase_index_rune_len(*data, *byte_len, 0, &r2, &rune_byte_len,
                                                          status)) {
        return false;
    }

    if (matches(r2)) {
        *data += rune_byte_len;
        *len -= 1;
        *byte_len -= rune_byte_len;
        *r = r2;
    }

    return status_ok(status);
}

bool strbase_seek_to_rune(char **data, size_t *len, size_t *byte_len,
                                                    rune r,
                                                    Status *status) {
    char *cursor = *data;

    for (size_t i = 0; i < *len; i++) {
        rune r2 = 0;
        size_t rune_byte_len = 0;

        strbase_get_first_rune_len_fast(cursor, &r2, &rune_byte_len);

        if (r2 == r) {
            *len -= i;
            *byte_len -= (cursor - *data);
            *data = cursor;
            return status_ok(status);
        }

        cursor += rune_byte_len;
    }

    return not_found(status);
}

bool strbase_seek_to_utf8_data(char **data, size_t *len, size_t *byte_len,
                                                         const char *data2,
                                                         size_t byte_len2,
                                                         Status *status) {
    char *cursor = *data;

    for (size_t i = 0; i < *len; i++) {
        rune r2 = 0;
        size_t rune_byte_len = 0;

        strbase_get_first_rune_len_fast(cursor, &r2, &rune_byte_len);

        if (memcmp(*data + i, data2 + i, byte_len2) == 0) {
            *len -= i;
            *byte_len -= (cursor - *data);
            *data = cursor;
            return status_ok(status);
        }

        cursor += rune_byte_len;
    }

    return not_found(status);
}

bool strbase_seek_to_match(char **data, size_t *len, size_t *byte_len,
                                                     RuneMatchFunc matches,
                                                     Status *status) {
    char *cursor = *data;

    for (size_t i = 0; i < *len; i++) {
        rune r2 = 0;
        size_t rune_byte_len = 0;

        strbase_get_first_rune_len_fast(cursor, &r2, &rune_byte_len);

        if (matches(r)) {
            *len -= i;
            *byte_len -= (cursor - *data);
            *data = cursor;
            return status_ok(status);
        }

        cursor += rune_byte_len;
    }

    return not_found(status);
}

bool strbase_truncate_runes(const char *data, size_t *len, size_t *byte_len,
                            size_t rune_count, Status *status) {
    char *cursor = NULL;
    ptrdiff_t new_byte_len = 0;

    if (!strbase_index_reverse(data, *byte_len, *len - rune_count, &cursor,
                                                                   status)) {
        return false;
    }

    new_byte_len = cursor - data;

    if (new_byte_len < 0) {
        new_byte_len = 0;
    }

    *len = (*len - rune_count);
    *byte_len = new_byte_len;

    return status_ok(status);
}


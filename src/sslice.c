#include "cbase.h"

#define empty(status) status_failure( \
    status,                           \
    "sslice",                         \
    SSLICE_EMPTY,                     \
    "SSlice is empty"                 \
)

#define not_subslice(status) status_failure( \
    status,                                  \
    "sslice",                                \
    SSLICE_NOT_SUBSLICE,                     \
    "SSlice is not a subslice"               \
)

bool sslice_starts_with_cstr(SSlice *s, const char *cs) {
    size_t byte_len = strlen(cs);

    if (byte_len > s->byte_len) {
        return false;
    }

    return utf8ncmp(s->data, cs, byte_len);
}

bool sslice_get_first_rune(SSlice *s, rune *r, Status *status) {
    if (sslice_empty(s)) {
        return empty(status);
    }

    return utf8_get_first_rune(s->data, r, status);
}

bool sslice_skip_rune(SSlice *s, Status *status) {
    return sslice_skip_runes(s, 1, status);
}

bool sslice_skip_runes(SSlice *s, size_t len, Status *status) {
    char *cursor = NULL;

    if (sslice_empty(s)) {
        return empty(status);
    }

    if (!utf8_skip(s->data, len, &cursor, status)) {
        return false;
    }

    ptrdiff_t bytes_read = cursor - s->data;

    s->len -= bytes_read;
    s->byte_len -= bytes_read;
    s->data += bytes_read;
    return status_ok(status);
}

bool sslice_skip_rune_if_equals(SSlice *s, rune r, Status *status) {
    rune r2;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(s->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (r2 != r) {
        return not_equal(status);
    }

    s->len--;
    s->byte_len -= bytes_read;
    s->data += bytes_read;

    return status_ok(status);
}

bool sslice_pop_rune(SSlice *s, rune *r, Status *status) {
    size_t bytes_read;

    if (!utf8_get_first_rune_len(s->data, r, &bytes_read, status)) {
        return false;
    }

    s->len--;
    s->byte_len -= bytes_read;
    s->data += bytes_read;

    return status_ok(status);
}

bool sslice_first_rune_equals(SSlice *s, rune r, Status *status) {
    rune r2 = 0;

    if (!sslice_get_first_rune(s, &r2, status)) {
        return false;
    }

    return r2 == r;
}

bool sslice_pop_rune_if_alpha(SSlice *s, rune *r, Status *status) {
    rune r2 = 0;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(s->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (!rune_is_alpha(r2)) {
        return not_found(status);
    }

    if (r) {
        *r = r2;
    }

    s->len--;
    s->byte_len -= bytes_read;
    s->data += bytes_read;

    return status_ok(status);
}

bool sslice_pop_rune_if_hex_digit(SSlice *s, rune *r, Status *status) {
    rune r2 = 0;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(s->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (!rune_is_hex_digit(r2)) {
        return not_found(status);
    }

    if (r) {
        *r = r2;
    }

    s->len--;
    s->byte_len -= bytes_read;
    s->data += bytes_read;

    return status_ok(status);
}

bool sslice_pop_rune_if_digit(SSlice *s, rune *r, Status *status) {
    rune r2 = 0;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(s->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (!rune_is_digit(r2)) {
        return not_found(status);
    }

    if (r) {
        *r = r2;
    }

    s->len--;
    s->byte_len -= bytes_read;
    s->data += bytes_read;

    return status_ok(status);
}

bool sslice_pop_rune_if_oct_digit(SSlice *s, rune *r, Status *status) {
    rune r2 = 0;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(s->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (!rune_is_oct_digit(r2)) {
        return not_found(status);
    }

    if (r) {
        *r = r2;
    }

    s->len--;
    s->byte_len -= bytes_read;
    s->data += bytes_read;

    return status_ok(status);
}

bool sslice_pop_rune_if_bin_digit(SSlice *s, rune *r, Status *status) {
    rune r2 = 0;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(s->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (!rune_is_bin_digit(r2)) {
        return not_found(status);
    }

    if (r) {
        *r = r2;
    }

    s->len--;
    s->byte_len -= bytes_read;
    s->data += bytes_read;

    return status_ok(status);
}

bool sslice_pop_rune_if_whitespace(SSlice *s, rune *r, Status *status) {
    rune r2 = 0;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(s->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (!rune_is_whitespace(r2)) {
        return not_found(status);
    }

    if (r) {
        *r = r2;
    }

    s->len--;
    s->byte_len -= bytes_read;
    s->data += bytes_read;

    return status_ok(status);
}

bool sslice_pop_rune_if_alnum(SSlice *s, rune *r, Status *status) {
    rune r2 = 0;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(s->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (!(rune_is_alpha(r2) || rune_is_digit(r2))) {
        return not_found(status);
    }

    if (r) {
        *r = r2;
    }

    s->len--;
    s->byte_len -= bytes_read;
    s->data += bytes_read;

    return status_ok(status);
}

bool sslice_seek_to(SSlice *s, rune r, Status *status) {
    rune r2;
    size_t bytes_read;
    SSlice cursor;

    sslice_copy(&cursor, s);

    if (!s->byte_len) {
        return empty(status);
    }

    while (true) {
        if (!cursor.byte_len) {
            break;
        }

        if (!utf8_get_first_rune_len(cursor.data, &r2, &bytes_read, status)) {
            return false;
        }

        if (r2 == r) {
            sslice_copy(s, &cursor);
            return status_ok(status);
        }

        cursor.len--;
        cursor.byte_len -= bytes_read;
        cursor.data += bytes_read;
    }

    return not_found(status);
}

bool sslice_seek_to_cstr(SSlice *s, const char *cs, Status *status) {
    size_t cslen = strlen(cs);
    SSlice cursor;

    sslice_copy(&cursor, s);

    while (cursor.byte_len >= cslen) {
        if (utf8ncmp(cursor.data, cs, cslen)) {
            sslice_copy(s, &cursor);
            return status_ok(status);
        }

        if (!sslice_skip_rune(&cursor, status)) {
            return false;
        }
    }

    return not_found(status);
}

bool sslice_seek_to_whitespace(SSlice *s, Status *status) {
    SSlice cursor;

    sslice_copy(&cursor, s);

    while (true) {
        rune r;
        size_t len;

        if (!utf8_get_first_rune_len(cursor.data, &r, &len, status)) {
            return false;
        }

        if (rune_is_whitespace(r)) {
            sslice_copy(s, &cursor);
            return status_ok(status);
        }

        cursor.len--;
        cursor.byte_len -= len;
        cursor.data += len;
    }
}

bool sslice_seek_to_subslice(SSlice *s, SSlice *subslice, Status *status) {
    if (subslice->data < s->data) {
        return not_subslice(status);
    }

    if (subslice->data >= (s->data + s->byte_len)) {
        return index_out_of_bounds(status);
    }

    if (s->data == subslice->data) {
        return status_ok(status);
    }

    size_t start_byte_len = subslice->data - s->data;
    size_t start_len;

    if (!utf8nlen(s->data, start_byte_len, &start_len, status)) {
        return false;
    }

    s->len -= start_len;
    s->byte_len -= start_byte_len;
    s->data = subslice->data;

    return status_ok(status);
}

bool sslice_seek_past_subslice(SSlice *s, SSlice *subslice, Status *status) {
    size_t start_len = 0;
    char *start = subslice->data + subslice->byte_len;
    char *current_end = s->data + s->byte_len;

    if (start < s->data) {
        return not_subslice(status);
    }

    if (start >= current_end) {
        sslice_clear(s);
        return status_ok(status);
    }

    size_t start_byte_len = subslice->data - s->data;

    if (start_byte_len) {
        if (!utf8nlen(s->data, start_byte_len, &start_len, status)) {
            return false;
        }
    }

    s->len -= (start_len + subslice->len);
    s->byte_len -= (start_byte_len + subslice->len);
    s->data = start;

    return status_ok(status);
}

bool sslice_seek_past_whitespace(SSlice *s, Status *status) {
    SSlice cursor;

    sslice_copy(&cursor, s);

    while (true) {
        rune r;
        size_t len;

        if (!utf8_get_first_rune_len(cursor.data, &r, &len, status)) {
            return false;
        }

        if (!rune_is_whitespace(r)) {
            sslice_copy(s, &cursor);
            return status_ok(status);
        }

        cursor.len--;
        cursor.byte_len -= len;
        cursor.data += len;
    }
}

bool sslice_truncate_runes(SSlice *s, size_t rune_count, Status *status) {
    if (rune_count >= s->len) {
        sslice_clear(s);
        return status_ok(status);
    }

    size_t offset;

    if (!utf8_get_end_offset(s->data, rune_count, s->byte_len, &offset,
                                                               status)) {
        return false;
    }

    s->len -= rune_count;
    s->byte_len -= offset;

    return status_ok(status);
}

bool sslice_truncate_whitespace(SSlice *s, Status *status) {
    SSlice cursor;

    sslice_copy(&cursor, s);

    while (cursor.byte_len) {
        rune r;
        size_t offset;

        if (!utf8_get_end_rune_offset(cursor.data, cursor.byte_len,
                                                   &r,
                                                   &offset,
                                                   status)) {
            return false;
        }

        if (!rune_is_whitespace(r)) {
            sslice_copy(s, &cursor);
            return status_ok(status);
        }

        cursor.len--;
        cursor.byte_len -= offset;
    }

    return not_found(status);
}

bool sslice_truncate_at(SSlice *s, rune r, Status *status) {
    SSlice cursor;

    sslice_copy(&cursor, s);

    while (cursor.byte_len) {
        rune r2;
        size_t offset;

        if (!utf8_get_end_rune_offset(cursor.data, cursor.byte_len,
                                                   &r2,
                                                   &offset,
                                                   status)) {
            return false;
        }

        if (r2 == r) {
            sslice_copy(s, &cursor);
            return status_ok(status);
        }

        cursor.len--;
        cursor.byte_len -= offset;
    }

    return not_found(status);
}

bool sslice_truncate_at_whitespace(SSlice *s, Status *status) {
    SSlice cursor;

    sslice_copy(&cursor, s);

    while (cursor.byte_len) {
        rune r;
        size_t offset;

        if (!utf8_get_end_rune_offset(cursor.data, cursor.byte_len,
                                                   &r,
                                                   &offset,
                                                   status)) {
            return false;
        }

        if (rune_is_whitespace(r)) {
            sslice_copy(s, &cursor);
            return status_ok(status);
        }

        cursor.len--;
        cursor.byte_len -= offset;
    }

    return not_found(status);
}

bool sslice_truncate_at_subslice(SSlice *s, SSlice *subslice, Status *status) {
    if (subslice->data < s->data) {
        return not_subslice(status);
    }

    if (((size_t)(subslice->data - s->data)) >= s->len) {
        return not_subslice(status);
    }

    s->byte_len = subslice->data - s->data;
    if (!utf8nlen(s->data, s->byte_len, &s->len, status)) {
        return false;
    }

    return status_ok(status);
}

char* sslice_to_cstr(SSlice *s) {
    return cbstrndup(s->data, s->byte_len);
}

/* vi: set et ts=4 sw=4: */

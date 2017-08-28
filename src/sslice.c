#include "cbase.h"

#define not_subslice(status) status_failure( \
    status,                                  \
    "sslice",                                \
    SSLICE_NOT_SUBSLICE,                     \
    "SSlice is not a subslice"               \
)

bool sslice_index_rune(SSlice *sslice, size_t index, rune *r, Status *status) {
    return utf8_index_rune(sslice->data, index, r, status);
}

bool sslice_skip_runes(SSlice *sslice, size_t rune_count, Status *status) {
    char *saved_data = sslice->data;

    if (!utf8_index(sslice->data, sslice->byte_len, rune_count, &sslice->data,
                                                                status)) {
        return false;
    }

    sslice->byte_len -= sslice->data - saved_data;

    return status_ok(status);
}

bool sslice_skip_rune_if_equals(SSlice *sslice, rune r, Status *status) {
    rune r2;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(sslice->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (r2 != r) {
        return not_equal(status);
    }

    sslice->len = sslice->len - 1;
    sslice->byte_len -= bytes_read;
    sslice->data += bytes_read;

    return status_ok(status);
}

bool sslice_pop_rune(SSlice *sslice, rune *r, Status *status) {
    size_t bytes_read;

    if (!utf8_get_first_rune_len(sslice->data, r, &bytes_read, status)) {
        return false;
    }

    sslice->len--;
    sslice->byte_len -= bytes_read;
    sslice->data += bytes_read;

    return status_ok(status);
}

bool sslice_starts_with_rune(SSlice *sslice, rune r, bool *starts_with,
                                                     Status *status) {
    return utf8_starts_with_rune(sslice->data, sslice->byte_len, r,
                                                                 starts_with,
                                                                 status);
}

bool sslice_starts_with_cstr(SSlice *sslice, const char *cs, bool *starts_with,
                                                             Status *status) {
    return utf8_starts_with_cstr(sslice->data, sslice->byte_len, cs,
                                                                 starts_with,
                                                                 status);
}

bool sslice_starts_with_sslice(SSlice *sslice1, SSlice *sslice2,
                                                bool *starts_with
                                                Status *status) {
    return utf8_starts_with_data(sslice1->data, sslice1->byte_len,
                                 sslice2->data, sslice2->byte_len,
                                                starts_with,
                                                status);
}

bool sslice_ends_with_rune(SSlice *sslice, rune r, bool *ends_with,
                                                   Status *status) {
    return utf8_ends_with_rune(sslice->data, sslice->byte_len, r, ends_with,
                                                                  status);
}

bool sslice_ends_with_cstr(SSlice *sslice, const char *cs, bool *ends_with,
                                                           Status *status) {
    return utf8_ends_with_cstr(sslice->data, sslice->byte_len, cs, ends_with,
                                                                   status);
}

bool sslice_ends_with_sslice(SSlice *sslice1, SSlice *sslice2,
                                              bool *ends_with,
                                              Status *status) {
    return utf8_ends_with_data(sslice1->data, sslice1->byte_len,
                               sslice2->data, sslice2->byte_len,
                                              ends_with,
                                              status);
}

bool sslice_pop_rune_if_matches(SSlice *sslice, RuneMatchFunc *matches,
                                                rune *r,
                                                Status *status) {
    rune r2 = 0;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(sslice->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (!matches(r2)) {
        return not_found(status);
    }

    *r = r2;

    sslice->len--;
    sslice->byte_len -= bytes_read;
    sslice->data += bytes_read;

    return status_ok(status);
}

bool sslice_seek_to(SSlice *sslice, rune r, Status *status) {
    SSlice copy;

    if (sslice_empty(sslice)) {
        return empty(status);
    }

    sslice_copy(&copy, sslice);

    while (true) {
        rune r2;
        size_t bytes_read = 0;

        if (sslice_empty(&copy)) {
            break;
        }

        if (!utf8_get_first_rune_len(sslice->data, &r2, &bytes_read, status)) {
            return false;
        }

        if (r2 == r) {
            sslice_copy(sslice, &copy);
            return status_ok(status);
        }

        copy->len--;
        copy->byte_len -= bytes_read;
        copy->data += bytes_read;
    }

    return not_found(status);
}

bool sslice_seek_to_cstr(SSlice *sslice, const char *cs, Status *status) {
    size_t cslen = strlen(cs);
    SSlice copy;

    sslice_copy(&copy, sslice);

    while (copy.byte_len >= cslen) {
        if (utf8_equal_fast(copy.data, cs, cslen)) {
            sslice_copy(sslice, &copy);
            return status_ok(status);
        }

        if (!sslice_skip_rune(&copy, status)) {
            return false;
        }
    }

    return not_found(status);
}

bool sslice_seek_to_whitespace(SSlice *sslice, Status *status) {
    SSlice cursor;

    sslice_copy(&cursor, sslice);

    while (true) {
        rune r;
        size_t len;

        if (!utf8_get_first_rune_len(cursor.data, &r, &len, status)) {
            return false;
        }

        if (rune_is_whitespace(r)) {
            sslice_copy(sslice, &cursor);
            return status_ok(status);
        }

        cursor.len--;
        cursor.byte_len -= len;
        cursor.data += len;
    }
}

bool sslice_seek_to_subslice(SSlice *sslice, SSlice *subslice,
                                             Status *status) {
    if (subslice->data < sslice->data) {
        return not_subslice(status);
    }

    if (subslice->data >= (sslice->data + sslice->byte_len)) {
        return index_out_of_bounds(status);
    }

    if (sslice->data == subslice->data) {
        return status_ok(status);
    }

    size_t start_byte_len = subslice->data - sslice->data;
    size_t start_len;

    utf8_len(sslice->data, sslice->byte_len, &start_len);

    s->len -= start_len;
    s->byte_len -= start_byte_len;
    s->data = subslice->data;

    return status_ok(status);
}

bool sslice_seek_past_subslice(SSlice *sslice, SSlice *subslice,
                                               Status *status) {
    size_t start_len = 0;
    char *start = subslice->data + subslice->byte_len;
    char *current_end = sslice->data + sslice->byte_len;

    if (start < sslice->data) {
        return not_subslice(status);
    }

    if (start >= current_end) {
        sslice_clear(sslice);
        return status_ok(status);
    }

    size_t start_byte_len = subslice->data - sslice->data;

    if (start_byte_len) {
        utf8_len(sslice->data, start_byte_len, &start_len);
    }

    sslice->len -= (start_len + subslice->len);
    sslice->byte_len -= (start_byte_len + subslice->len);
    sslice->data = start;

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

bool sslice_truncate_runes(SSlice *sslice, size_t rune_count, Status *status) {
    char *end_point = NULL;

    if (sslice->len < rune_count) {
        sslice_clear(sslice);
        return status_ok(status);
    }

    if (rune_count > (sslice->len / 2)) {
        if (!utf8_index_reverse(sslice->data, sslice->byte_len,
                                              sslice->len - rune_count,
                                              &end_point,
                                              status)) {
            return false;
        }
    }
    else if (utf8_index(sslice->data, sslice->byte_len, sslice->len,
                                                        &end_point,
                                                        status)) {
        return false;
    }

    s->len -= rune_count;
    s->byte_len = end_point - sslice->data;

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

/* vi: set et ts=4 sw=4: */

#include "cbase.h"

void strbase_assign_full(char *dst_data, size_t dst_len, size_t dst_byte_len,
                         char *src_data, size_t src_len, size_t src_byte_len) {
    dst_data = src_data;
    dst_len = src_len;
    dst_byte_len = src_byte_len;
}

bool strbase_assign_cstr(char **dst_data, size_t *len, size_t *byte_len,
                                                       char *cs,
                                                       Status *status) {
    if (!cs) {
        *len = 0;
        *byte_len = 0;
    }
    else if (!utf8_process_cstr(cs, len, byte_len, status)) {
        return status_propagate(status);
    }

    *dst_data = cs;

    return status_ok(status);
}

bool strbase_empty(const char *data, size_t len, size_t byte_len) {
    return (cstr_end(data) || (!len) || (!byte_len));
}

bool strbase_equals(const char *data1, size_t len1, size_t byte_len1,
                    const char *data2, size_t len2, size_t byte_len2) {
    return (
        (len1 == len2) &&
        (byte_len1 == byte_len2) &&
        (memcmp(data1, data2, byte_len1) == 0)
    );
}

bool strbase_equals_cstr_full(const char *data, size_t byte_len,
                                                const char *cs,
                                                size_t cs_byte_len) {
    return strbase_equals(data, 0, byte_len, cs, 0, cs_byte_len);
}

bool strbase_equals_cstr(const char *data, size_t byte_len, const char *cs) {
    return strbase_equals_cstr_full(data, byte_len, cs, strlen(cs));
}

bool strbase_equals_utf8_data(const char *data1, size_t byte_len1,
                              const char *data2, size_t byte_len2) {
    return strbase_equals(data1, 0, byte_len1, data2, 0, byte_len2);
}

bool strbase_equals_utf8_slice(const char *data, size_t byte_len,
                                                 Slice *slice) {
    return strbase_equals_utf8_data(data, byte_len, slice->data, slice->len);
}

bool strbase_equals_utf8_buffer(const char *data, size_t byte_len,
                                                  Buffer *buffer) {
    return strbase_equals_utf8_data(
        data, byte_len, buffer->array.elements, buffer->array.len
    );
}

void strbase_copy(char **dst_data, size_t *dst_len, size_t *dst_byte_len,
                  const char *src_data, size_t src_len, size_t src_byte_len) {
    *dst_data = (char *)src_data;
    *dst_len = src_len;
    *dst_byte_len = src_byte_len;
}

#define strbase_index_fast utf8_index_fast
#define strbase_index utf8_index
#define strbase_index_rune_fast utf8_index_rune_fast
#define strbase_index_rune utf8_index_rune
#define strbase_index_rune_len_fast utf8_index_rune_len_fast
#define strbase_index_rune_len utf8_index_rune_len
#define strbase_index_reverse_fast utf8_index_reverse_fast
#define strbase_index_reverse utf8_index_reverse
#define strbase_index_rune_reverse_fast utf8_index_rune_reverse_fast
#define strbase_index_rune_reverse utf8_index_rune_reverse
#define strbase_index_rune_len_reverse_fast utf8_index_rune_len_reverse_fast
#define strbase_index_rune_len_reverse utf8_index_rune_len_reverse
#define strbase_get_first_rune_fast utf8_get_first_rune_fast
#define strbase_get_first_rune utf8_get_first_rune
#define strbase_get_first_rune_len_fast utf8_get_first_rune_len_fast
#define strbase_get_first_rune_len utf8_get_first_rune_len
#define strbase_get_last_rune_len_fast utf8_get_last_rune_len_fast
#define strbase_get_last_rune_len utf8_get_last_rune_len
#define strbase_starts_with_data_fast utf8_starts_with_data_fast
#define strbase_starts_with_data utf8_starts_with_data
#define strbase_starts_with_cstr_fast utf8_starts_with_cstr_fast
#define strbase_starts_with_cstr utf8_starts_with_cstr
#define strbase_starts_with_rune_fast utf8_starts_with_rune_fast
#define strbase_starts_with_rune utf8_starts_with_rune
#define strbase_ends_with_data_fast utf8_ends_with_data_fast
#define strbase_ends_with_data utf8_ends_with_data
#define strbase_ends_with_cstr_fast utf8_ends_with_cstr_fast
#define strbase_ends_with_cstr utf8_ends_with_cstr
#define strbase_ends_with_rune_fast utf8_ends_with_rune_fast
#define strbase_ends_with_rune utf8_ends_with_rune
#define strbase_iterate utf8_iterate
#define strbase_iterate_fast utf8_iterate_fast

bool strbase_encode(const char *data, size_t byte_len, const char *encoding,
                                                       Buffer *out,
                                                       Status *status) {
    Slice outsl;

    outsl.len = out->array.alloc;
    outsl.data = out->array.elements;

    while (true) {
        Slice in;

        slice_assign_data(&in, (char *)data, byte_len);

        if (slice_encode(&in, "UTF-8", encoding, out, status)) {
            out->array.len = outsl.data - (char *)out->array.elements;
            break;
        }

        if (status_match(status, "charset", CHARSET_OUTPUT_BUFFER_TOO_SMALL)) {
            ptrdiff_t bytes_written = outsl.data - (char *)out->array.elements;

            if (!buffer_ensure_capacity(out, out->array.alloc * 2, status)) {
                return status_propagate(status);
            }

            outsl.data = out->array.elements + bytes_written;
            outsl.len = out->array.alloc - bytes_written;
        }
        else if (status_match(status, "charset",
                                      CHARSET_BUFFER_DATA_UNINITIALIZED)) {
            if (!buffer_ensure_capacity(out, 64, status)) {
                return status_propagate(status);
            }

            outsl.data = out->array.elements;
            outsl.len = out->array.alloc;
        }
        else {
            return status_propagate(status);
        }
    }

    return status_ok(status);
}


bool strbase_localize(const char *data, size_t byte_len, Buffer *out,
                                                         Status *status) {
    return strbase_encode(data, byte_len, "wchar_t", out, status);
}

void strbase_skip_runes_fast(char **data, size_t *len, size_t *byte_len,
                                                       size_t rune_count) {
    while (rune_count-- > 0) {
        rune r;
        utf8_iterate_fast(data, byte_len, &r);
    }

    *len -= rune_count;
}

bool strbase_skip_runes(char **data, size_t *len, size_t *byte_len,
                                                  size_t rune_count,
                                                  Status *status) {
    if (*len > rune_count) {
        return index_out_of_bounds(status);
    }

    while (rune_count-- > 0) {
        rune r;
        if (!utf8_iterate(data, byte_len, &r, status)) {
            return status_propagate(status);
        }
    }

    *len -= rune_count;

    return status_ok(status);
}

void strbase_skip_rune_fast(char **data, size_t *len, size_t *byte_len) {
    strbase_skip_runes_fast(data, len, byte_len, 1);
}

bool strbase_skip_rune(char **data, size_t *len, size_t *byte_len,
                                                 Status *status) {
    return strbase_skip_runes(data, len, byte_len, 1, status);
}

bool strbase_skip_rune_if_matches(char **data, size_t *len,
                                               size_t *byte_len,
                                               RuneMatchFunc *matches,
                                               Status *status) {
    rune r = 0;
    size_t rune_byte_len = 0;

    if (!strbase_index_rune_len(*data, *byte_len, 0, &r, &rune_byte_len,
                                                         status)) {
        return status_propagate(status);
    }

    if (matches(r)) {
        *data += rune_byte_len;
        *len -= 1;
        *byte_len -= rune_byte_len;
    }

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
        return status_propagate(status);
    }

    if (r2 == r) {
        *data += rune_byte_len;
        *len -= 1;
        *byte_len -= rune_byte_len;
    }

    return status_ok(status);
}

bool strbase_skip_rune_if_alpha(char **data, size_t *len, size_t *byte_len,
                                                          Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_alpha, status
    );
}

bool strbase_skip_rune_if_hex_digit(char **data, size_t *len, size_t *byte_len,
                                                              Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_hex_digit, status
    );
}

bool strbase_skip_rune_if_digit(char **data, size_t *len, size_t *byte_len,
                                                          Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_digit, status
    );
}

bool strbase_skip_rune_if_oct_digit(char **data, size_t *len, size_t *byte_len,
                                                              Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_oct_digit, status
    );
}

bool strbase_skip_rune_if_bin_digit(char **data, size_t *len, size_t *byte_len,
                                                              Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_bin_digit, status
    );
}

bool strbase_skip_rune_if_alnum(char **data, size_t *len, size_t *byte_len,
                                                          Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_alnum, status
    );
}

bool strbase_skip_rune_if_whitespace(char **data, size_t *len,
                                                  size_t *byte_len,
                                                  Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_whitespace, status
    );
}

bool strbase_pop_rune(char **data, size_t *len, size_t *byte_len,
                                                rune *r,
                                                Status *status) {
    rune r2 = 0;
    size_t rune_byte_len = 0;

    if (!strbase_index_rune_len(*data, *byte_len, 0, &r2, &rune_byte_len,
                                                          status)) {
        return status_propagate(status);
    }

    *data += rune_byte_len;
    *len -= 1;
    *byte_len -= rune_byte_len;
    *r = r2;

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
        return status_propagate(status);
    }

    if (matches(r2)) {
        *data += rune_byte_len;
        *len -= 1;
        *byte_len -= rune_byte_len;
        *r = r2;
    }

    return status_ok(status);
}

bool strbase_pop_rune_if_alpha(char **data, size_t *len, size_t *byte_len,
                                                         rune *r,
                                                         Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_alpha, r, status
    );
}

bool strbase_pop_rune_if_hex_digit(char **data, size_t *len, size_t *byte_len,
                                                             rune *r,
                                                             Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_hex_digit, r, status
    );
}

bool strbase_pop_rune_if_digit(char **data, size_t *len, size_t *byte_len,
                                                         rune *r,
                                                         Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_digit, r, status
    );
}

bool strbase_pop_rune_if_oct_digit(char **data, size_t *len, size_t *byte_len,
                                                             rune *r,
                                                             Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_oct_digit, r, status
    );
}

bool strbase_pop_rune_if_bin_digit(char **data, size_t *len, size_t *byte_len,
                                                             rune *r,
                                                             Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_bin_digit, r, status
    );
}

bool strbase_pop_rune_if_alnum(char **data, size_t *len, size_t *byte_len,
                                                         rune *r,
                                                         Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_alnum, r, status
    );
}

bool strbase_pop_rune_if_whitespace(char **data, size_t *len,
                                                 size_t *byte_len,
                                                 rune *r,
                                                 Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_whitespace, r, status
    );
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
            *byte_len -= (cursor - *data);
            *data = cursor;
            *len -= i;
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
            *byte_len -= (cursor - *data);
            *data = cursor;
            *len -= i;
            return status_ok(status);
        }

        cursor += rune_byte_len;
    }

    return not_found(status);
}

bool strbase_seek_to_cstr(char **data, size_t *len, size_t *byte_len,
                                                    const char *cs,
                                                    Status *status) {
    return strbase_seek_to_utf8_data(
        data, len, byte_len, cs, strlen(cs), status
    );
}

bool strbase_seek_to_match(char **data, size_t *len, size_t *byte_len,
                                                     RuneMatchFunc matches,
                                                     Status *status) {
    char *cursor = *data;

    for (size_t i = 0; i < *len; i++) {
        rune r2 = 0;
        size_t rune_byte_len = 0;

        strbase_get_first_rune_len_fast(cursor, &r2, &rune_byte_len);

        if (matches(r2)) {
            *data = cursor;
            *len -= i;
            *byte_len -= (cursor - *data);
            return status_ok(status);
        }

        cursor += rune_byte_len;
    }

    return not_found(status);
}

bool strbase_seek_to_whitespace(char **data, size_t *len,
                                             size_t *byte_len,
                                             Status *status) {
    return strbase_seek_to_match(
        data, len, byte_len, rune_is_whitespace, status
    );
}

bool strbase_seek_past_whitespace(char **data, size_t *len, size_t *byte_len,
															Status *status) {
    while (!cstr_end(*data)) {
        rune r;
        size_t rune_byte_len = 0;

        if (!utf8_get_first_rune_len(*data, &r, &rune_byte_len, status)) {
            return status_propagate(status);
        }

        if (!rune_is_whitespace(r)) {
            return status_ok(status);
        }

        *data += rune_byte_len;
        *len -= 1;
        *byte_len -= rune_byte_len;
    }

    return not_found(status);
}

bool strbase_truncate_runes(const char *data, size_t *len, size_t *byte_len,
                                                           size_t rune_count,
                                                           Status *status) {
    char *cursor = NULL;
    size_t new_byte_len = 0;

    if (!strbase_index_reverse(data, *byte_len, *len - rune_count, &cursor,
                                                                   status)) {
        return status_propagate(status);
    }

    if (cursor <= data) {
        new_byte_len = 0;
    }
    else {
        new_byte_len = cursor - data;
    }

    *len -= rune_count;
    *byte_len = new_byte_len;

    return status_ok(status);
}

bool strbase_truncate_whitespace(const char *data, size_t *len,
                                                   size_t *byte_len,
                                                   Status *status) {
    while (*byte_len) {
        rune r;
        size_t rune_byte_len;

        if (!utf8_get_last_rune_len(data, *byte_len, &r, &rune_byte_len,
                                                         status)) {
            return status_propagate(status);
        }

        if (!rune_is_whitespace(r)) {
            return status_ok(status);
        }

        *len -= 1;
        *byte_len -= rune_byte_len;

    }

    return not_found(status);
}

bool strbase_truncate_at_rune(const char *data, size_t *len, size_t *byte_len,
														     rune r,
														     Status *status) {
    while (*byte_len) {
        rune r2;
        size_t rune_byte_len;

        if (!utf8_get_last_rune_len(data, *byte_len, &r2, &rune_byte_len,
                                                          status)) {
            return status_propagate(status);
        }

        if (r2 == r) {
            return status_ok(status);
        }

        *len -= 1;
        *byte_len -= rune_byte_len;
    }

    return not_found(status);
}

bool strbase_truncate_at_whitespace(const char *data, size_t *len,
                                                      size_t *byte_len,
                                                      Status *status) {
    while (*byte_len) {
        rune r;
        size_t rune_byte_len;

        if (!utf8_get_last_rune_len(data, *byte_len, &r, &rune_byte_len,
                                                         status)) {
            return status_propagate(status);
        }

        if (rune_is_whitespace(r)) {
            return status_ok(status);
        }

        *len -= 1;
        *byte_len -= rune_byte_len;
    }

    return not_found(status);
}

void strbase_clear(size_t *len, size_t *byte_len) {
    *len = 0;
    *byte_len = 0;
}

#include "cbase.h"

#define empty(status) status_failure( \
    status,                           \
    "sbuffer",                        \
    SBUFFER_EMPTY,                    \
    "SBuffer is empty"                \
)

bool sbuffer_empty(size_t len, size_t byte_len) {
    return len == 0 && byte_len == 0;
}

void sbuffer_clear(size_t *len, size_t *byte_len) {
    *len = 0;
    *byte_len = 0;
}

bool sbuffer_equals(char *data1, size_t len1, size_t byte_len1,
                    char *data2, size_t len2, size_t byte_len2) {
    return (
        (len1 == len2) &&
        (byte_len1 == byte_len2) &&
        (memcmp(data1, data2, byte_len1) == 0)
    );
}

bool sbuffer_equals_cstr(const char *data, const char *cs) {
    return utf8cmp(cs, data);
}

void sbuffer_copy(char **dst_data, size_t *dst_len, size_t dst_byte_len,
                  char *src_data, size_t src_len, size_t src_byte_len) {
    *dst_data = src_data;
    *dst_len = src_len;
    *dst_byte_len = dst_byte_len;
}

bool sbuffer_get_first_rune(char *data, rune *r, Status *status) {
    if (sbuffer_empty(s)) {
        return empty(status);
    }

    return utf8_get_first_rune(data, r, status);
}

bool sbuffer_starts_with(char *data, rune r, bool *starts_with,
                                             Status *status) {
    rune r2 = 0;

    if (sbuffer_empty(s)) {
        *starts_with = false;
        return status_ok(status);
    }

    if (!utf8_get_first_rune(data, &r2, status)) {
        return false;
    }
    
    *starts_with = r2 == r;

    return status_ok(status);
}

bool sbuffer_starts_with_cstr(char *data, size_t byte_len, const char *cs,
                                                           bool *starts_with,
                                                           Status *status) {
    if (sbuffer_empty(s)) {
        *starts_with = false;
        return status_ok(status);
    }

    return (strlen(cs) <= byte_len) && (memcmp(data, cs, byte_len) == 0);
}

bool sbuffer_ends_with(char *data, size_t byte_len, rune r, bool *ends_with,
                                                            Status *status) {
    rune r2;

    if (sbuffer_empty(s)) {
        *ends_with = false;
        return status_ok(status);
    }

    if (!utf8_get_end_rune(data, byte_len, &r2, status)) {
        return false;
    }

    *ends_with = r2 == r;

    return status_ok(status);
}

bool sbuffer_ends_with_cstr(char *data, size_t byte_len, const char *cs,
                                                         bool *ends_with,
                                                         Status *status) {
    size_t cstr_byte_len = strlen(cs);

    if (sbuffer_empty(s)) {
        *ends_with = false;
        return status_ok(status);
    }

    return (
        (cstr_byte_len <= byte_len) &&
        (memcmp(data + (byte_len - cstr_byte_len), cs, cstr_byte_len) == 0)
    );
}

bool sbuffer_skip_runes(char **data, size_t *len, size_t *byte_len,
                                                  size_t rune_count,
                                                  Status *status) {
    char *data_value = *data;
    size_t len_value = *len;
    size_t byte_len_value = *byte_len;
    char *cursor = NULL;
    ptrdiff_t bytes_read = 0;

    if (sbuffer_empty(len_value, byte_len_value))
        return empty(status);
    }

    if (!utf8_skip(data_value, rune_count, &cursor, status)) {
        return false;
    }

    bytes_read = cursor - s->data;

    *len -= bytes_read;
    *byte_len -= bytes_read;
    *data += bytes_read;

    return status_ok(status);
}

bool sbuffer_skip_rune(char **data, size_t *len, size_t *byte_len,
                                                 Status *status) {
    return sbuffer_skip_runes(data, len, byte_len, 1, status);
}

bool sbuffer_truncate_runes(char *data, size_t *len, size_t *byte_len,
                                                     size_t rune_count,
                                                     Status *status) {
    size_t offset;

    if (rune_count >= (*len)) {
        sbuffer_clear(len, byte_len);
        return status_ok(status);
    }

    if (!utf8_get_end_offset(data, rune_count, *byte_len, &offset, status)) {
        return false;
    }

    s->len -= rune_count;
    s->byte_len -= offset;

    return status_ok(status);
}

bool sbuffer_truncate_rune(char *data, size_t *len, size_t *byte_len,
                                                    Status *status) {
    return sbuffer_truncate_runes(data, len, byte_len, 1, status);
}

bool sbuffer_skip_rune_if_equals(char **data, size_t *len, size_t *byte_len,
                                                           rune r,
                                                           Status *status) {
    rune r2;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(s->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (r2 != r) {
        return not_equal(status);
    }

    *len = *len - 1;
    *byte_len -= bytes_read;
    *data += bytes_read;

    return status_ok(status);
}

bool sbuffer_pop_rune(char **data, size_t *len, size_t *byte_len,
                                               rune *r,
                                               Status *status) {
    size_t bytes_read;

    if (!utf8_get_first_rune_len(*data, r, &bytes_read, status)) {
        return false;
    }

    *len--;
    *byte_len -= bytes_read;
    *data += bytes_read;

    return status_ok(status);
}

bool sbuffer_pop_rune_if_matches(char **data, size_t *len,
                                              size_t *byte_len,
                                              RuneMatchFunc *matches,
                                              rune *r,
                                              Status *status) {
    rune r2 = 0;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(s->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (!matches(r2)) {
        return not_found(status);
    }

    *r = r2;

    *len--;
    *byte_len -= bytes_read;
    *data += bytes_read;

    return status_ok(status);
}

bool sbuffer_skip_rune_if_matches(char **data, size_t *len,
                                               size_t *byte_len,
                                               RuneMatchFunc *matches,
                                               Status *status) {
    rune r;

    return sbuffer_pop_rune_if_matches(data, len, byte_len, matches,
                                                            &r,
                                                            status);
}

bool sbuffer_seek_to(char **data, size_t *len, size_t *byte_len,
                                               rune r,
                                               Status *status) {
    rune r2;
    size_t bytes_read;
    char *data_copy = NULL;
    size_t len_copy = 0;
    size_t byte_len_copy = 0;

    if (!byte_len) {
        return empty(status);
    }

    sbuffer_copy(
        &data_copy, &len_copy, &byte_len_copy,
        *data, *len, *byte_len
    );

    while (true) {
        if (!byte_len_copy) {
            break;
        }

        if (!utf8_get_first_rune_len(data, &r2, &bytes_read, status)) {
            return false;
        }

        if (r2 == r) {
            sbuffer_copy(
                data, len, byte_len,
                data_copy, len_copy, byte_len_copy
            );

            return status_ok(status);
        }


        data_copy += bytes_read;
        len_copy--;
        byte_len_copy -= bytes_read;
    }

    return not_found(status);
}

bool sbuffer_seek_to_cstr(char **data, size_t len, size_t byte_len,
                                                   const char *cs,
                                                   Status *status) {
    size_t cslen = strlen(cs);
    char *data_copy = NULL;
    size_t len_copy = 0;
    size_t byte_len_copy = 0;

    sbuffer_copy(
        &data_copy, &len_copy, &byte_len_copy,
        *data, *len, *byte_len
    );

    while (byte_len_copy >= cslen) {
        if (utf8ncmp(data_copy, cs, cslen)) {
            sbuffer_copy(
                data, len, byte_len,
                data_copy, len_copy, byte_len_copy
            );

            return status_ok(status);
        }

        if (!sbuffer_skip_rune(&data_copy, &len_copy, &byte_len_copy,
                                                      status)) {
            return false;
        }
    }

    return not_found(status);
}

void sbuffer_seek_to_end(char **data, size_t *len, size_t *byte_len) {
    *data += *byte_len;
    *len = 0;
    *byte_len = 0;
}

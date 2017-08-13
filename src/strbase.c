#include "cbase.h"

#define empty(status) status_failure( \
    status,                           \
    "strbase",                        \
    STRBASE_EMPTY,                    \
    "String data is empty"            \
)

bool strbase_get_first_rune(char *data, size_t len, size_t byte_len,
                                                    rune *r,
                                                    Status *status) {
    if (strbase_empty(len, byte_len)) {
        return empty(status);
    }

    return utf8_get_first_rune(data, r, status);
}

bool strbase_skip_runes(char **data, size_t *len, size_t *byte_len,
                                                  size_t rune_count,
                                                  Status *status) {
    char *data_value = *data;
    size_t len_value = *len;
    size_t byte_len_value = *byte_len;
    char *cursor = NULL;
    ptrdiff_t bytes_read = 0;

    if (strbase_empty(len_value, byte_len_value)) {
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

bool strbase_truncate_runes(char *data, size_t *len, size_t *byte_len,
                                                     size_t rune_count,
                                                     Status *status) {
    size_t offset;

    if (rune_count >= (*len)) {
        strbase_clear(len, byte_len);
        return status_ok(status);
    }

    if (!utf8_get_end_offset(data, rune_count, *byte_len, &offset, status)) {
        return false;
    }

    s->len -= rune_count;
    s->byte_len -= offset;

    return status_ok(status);
}

bool strbase_skip_rune_if_equals(char **data, size_t *len, size_t *byte_len,
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

bool strbase_pop_rune(char **data, size_t *len, size_t *byte_len,
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

bool strbase_pop_rune_if_matches(char **data, size_t *len,
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

bool strbase_seek_to(char **data, size_t *len, size_t *byte_len,
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

    strbase_copy(
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
            strbase_copy(
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

bool strbase_seek_to_cstr(char **data, size_t len, size_t byte_len,
                                                   const char *cs,
                                                   Status *status) {
    size_t cslen = strlen(cs);
    char *data_copy = NULL;
    size_t len_copy = 0;
    size_t byte_len_copy = 0;

    strbase_copy(
        &data_copy, &len_copy, &byte_len_copy,
        *data, *len, *byte_len
    );

    while (byte_len_copy >= cslen) {
        if (utf8ncmp(data_copy, cs, cslen)) {
            strbase_copy(
                data, len, byte_len,
                data_copy, len_copy, byte_len_copy
            );

            return status_ok(status);
        }

        if (!strbase_skip_rune(&data_copy, &len_copy, &byte_len_copy,
                                                      status)) {
            return false;
        }
    }

    return not_found(status);
}


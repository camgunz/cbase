#include "cbase.h"

#include <utf8proc.h>

#define utf8_too_long(status) status_critical(   \
    status,                                      \
    "utf8",                                      \
    UTF8_TOO_LONG,                               \
    "UTF-8 data is too long"                     \
)

#define invalid_utf8(status) status_critical( \
    status,                                   \
    "utf8",                                   \
    UTF8_INVALID_UTF8,                        \
    "UTF-8 data is invalid"                   \
)

#define unassigned_codepoint_found(status) status_critical( \
    status,                                                 \
    "utf8",                                                 \
    UTF8_UNASSIGNED_CODEPOINT,                              \
    "found unassigned codepoint in UTF-8 data"              \
)

#define invalid_options(status) status_critical( \
    status,                                      \
    "utf8",                                      \
    UTF8_INVALID_OPTIONS,                        \
    "invalid options passed to utf8proc"         \
)

#define empty(status) status_failure( \
    status,                           \
    "utf8",                           \
    UTF8_EMPTY,                       \
    "No data passed"                  \
)

#define unknown_error(status) status_critical( \
    status,                                    \
    "utf8",                                    \
    UTF8_UNKNOWN_ERROR,                        \
    "unknown utf8proc error"                   \
)

bool utf8_handle_error_code(ssize_t error_code, Status *status) {
    switch (error_code) {
        case UTF8PROC_ERROR_NOMEM:
            return alloc_failure(status);
        case UTF8PROC_ERROR_OVERFLOW:
            return utf8_too_long(status);
        case UTF8PROC_ERROR_INVALIDUTF8:
            return invalid_utf8(status);
        case UTF8PROC_ERROR_NOTASSIGNED:
            return unassigned_codepoint_found(status);
        case UTF8PROC_ERROR_INVALIDOPTS:
            return invalid_options(status);
        default:
            return unknown_error(status);
    }

    return status_ok(status);
}

bool utf8len(const char *data, size_t *len, Status *status) {
    ssize_t error;

    if (!utf8len_fast(data, len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool utf8len_fast(const char *data, size_t *len, ssize_t *error) {
    size_t local_len = 0;

    while (*data) {
        rune r;
        ssize_t bytes_read = utf8proc_iterate(
            (const unsigned char *)data, -1, &r
        );

        if (bytes_read < 1) {
            *error = bytes_read;
            return false;
        }

        local_len++;
        data += bytes_read;
    }

    *len = local_len;

    return true;
}

bool utf8nlen(const char *data, size_t n, size_t *len, Status *status) {
    ssize_t error;

    if (!utf8nlen_fast(data, n, len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool utf8nlen_fast(const char *data, size_t n, size_t *len, ssize_t *error) {
    size_t local_len = 0;
    size_t local_byte_len = 0;

    while ((local_byte_len < n) && *data) {
        rune r;
        ssize_t bytes_read = utf8proc_iterate(
            (const unsigned char *)data, n, &r
        );

        if (bytes_read < 1) {
            *error = bytes_read;
            return false;
        }

        local_len++;
        local_byte_len += bytes_read;
        data += bytes_read;
    }

    *len = local_len;

    return true;
}

bool utf8_index(const char *data, size_t len, char **cursor,
                                              Status *status) {
    ssize_t error = 0;

    if (!utf8_index_fast(data, len, cursor, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool utf8_index_fast(const char *data, size_t len, char **cursor,
                                                   ssize_t *error) {
    char *local_cursor = (char *)data;

    for (size_t i = 0; i < (len - 1); i++) {
        rune r;
        ssize_t bytes_read = utf8proc_iterate(
            (const unsigned char *)local_cursor, -1, &r
        );

        if (bytes_read < 1) {
            *error = bytes_read;
            return false;
        }

        local_cursor += bytes_read;
    }

    *cursor = local_cursor;

    return true;
}

bool utf8_skip(const char *data, size_t len, char **cursor,
                                             Status *status) {
    ssize_t error = 0;

    if (!utf8_skip_fast(data, len, cursor, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool utf8_skip_fast(const char *data, size_t len, char **cursor,
                                                  ssize_t *error) {
    char *local_cursor = (char *)data;

    for (size_t i = 0; i < len; i++) {
        rune r;
        ssize_t bytes_read = utf8proc_iterate(
            (const unsigned char *)local_cursor, -1, &r
        );

        if (bytes_read < 1) {
            *error = bytes_read;
            return false;
        }

        local_cursor += bytes_read;
    }

    *cursor = local_cursor;

    return true;
}

bool utf8_slice(const char *data, size_t index, size_t len, char **start,
                                                            char **end,
                                                            Status *status) {
    ssize_t error = 0;

    if (!utf8_slice_fast(data, index, len, start, end, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool utf8_slice_fast(const char *data, size_t index, size_t len,
                                                     char **start,
                                                     char **end,
                                                     ssize_t *error) {
    char *local_start = NULL;
    char *local_end = NULL;

    if (!utf8_skip_fast(data, index, &local_start, error)) {
        return false;
    }

    if (!utf8_skip_fast(local_start, len, &local_end, error)) {
        return false;
    }

    *start = local_start;
    *end = local_end;

    return true;
}

bool utf8_get_first_rune(const char *data, rune *r, Status *status) {
    ssize_t bytes_read;

    if (!utf8_get_first_rune_fast(data, r, &bytes_read)) {
        return utf8_handle_error_code(bytes_read, status);
    }

    return status_ok(status);
}

bool utf8_get_first_rune_fast(const char *data, rune *r, ssize_t *error) {
    *error = utf8proc_iterate((const unsigned char *)data, -1, r);

    return (*error >= 1);
}

bool utf8_get_first_rune_len(const char *data, rune *r, size_t *len,
                                                        Status *status) {
    ssize_t error = 0;

    if (!utf8_get_first_rune_len_fast(data, r, len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool utf8_get_first_rune_len_fast(const char *data, rune *r, size_t *len,
                                                             ssize_t *error) {
    rune r2;
    ssize_t bytes_read = utf8proc_iterate(
        (const unsigned char *)data, -1, &r2
    );

    if (bytes_read < 1) {
        *error = bytes_read;
        return false;
    }

    *len = bytes_read;
    *r = r2;

    return true;
}

bool utf8_get_end_offset(const char *data, size_t rune_count, size_t byte_len,
                                                              size_t *offset,
                                                              Status *status) {
    size_t i = 0;
    size_t local_rune_count = 0;

    if (!byte_len) {
        return empty(status);
    }

    for (i = 1; i <= byte_len; i++) {
        size_t byte_count;

        for (byte_count = 1; byte_count <= 4; byte_count++) {
            char *b = ((char *)data) + byte_len - i;

            if (((*b) & 0xC0) != 0x80) {
                local_rune_count++;
                break;
            }
        }

        if (byte_count == 5) {
            return invalid_utf8(status);
        }

        if (local_rune_count == rune_count) {
            break;
        }
    }

    *offset = i;

    return status_ok(status);
}

bool utf8_get_end_rune_offset(const char *data, size_t byte_len,
                                                rune *r,
                                                size_t *offset,
                                                Status *status) {
    if (!byte_len) {
        return empty(status);
    }

    size_t max_byte_count = 4;

    if (byte_len < max_byte_count) {
        max_byte_count = byte_len;
    }

    for (size_t byte_count = 1; byte_count <= max_byte_count; byte_count++) {
        char *b = ((char *)data) + byte_len - byte_count;

        if (((*b) & 0xC0) != 0x80) {
            rune r2;
            ssize_t bytes_read = utf8proc_iterate(
                (const unsigned char *)b, byte_count, &r2
            );

            if (bytes_read < 1) {
                return utf8_handle_error_code(bytes_read, status);
            }

            *r = r2;
            *offset = byte_count;

            return status_ok(status);
        }
    }

    return invalid_utf8(status);
}

bool rune_to_string(rune r, char **out, Status *status) {
    uint8_t buf[4] = {0};
    ssize_t bytes_written;
    char *s;

    if (!utf8proc_codepoint_valid(r)) {
        return invalid_utf8(status);
    }

    bytes_written = utf8proc_encode_char(r, &buf[0]);

    if (bytes_written < 1) {
        return utf8_handle_error_code(bytes_written, status);
    }

    s = cbmalloc(bytes_written + 1, sizeof(byte));

    if (!s) {
        return alloc_failure(status);
    }

    buf[bytes_written] = '\0';

    cbmemmove(s, &buf[0], (bytes_written + 1) * sizeof(byte));

    *out = s;

    return status_ok(status);
}

/* vi: set et ts=4 sw=4: */

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

#define unknown_error(status) status_critical( \
    status,                                    \
    "utf8",                                    \
    UTF8_UNKNOWN_ERROR,                        \
    "unknown utf8proc error"                   \
)

#define empty(status) status_failure( \
    status,                           \
    "utf8",                           \
    UTF8_EMPTY,                       \
    "UTF8 data is empty"              \
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

bool utf8_process_fast(const char *data, size_t byte_len, size_t *len,
                                                          ssize_t *error) {
    const unsigned char *cursor = data;
    size_t total_bytes_read = 0;
    size_t local_len = 0;

    while ((data) && (*data) && (total_bytes_read < byte_len)) {
        rune r;
        ssize_t bytes_read = utf8proc_iterate(cursor, -1, &r);

        if (bytes_read < 1) {
            *error = bytes_read;
            return false;
        }

        local_len++;
        total_bytes_read += bytes_read;
        cursor = data + total_bytes_read;
    }

    if (len) {
        *len = local_len;
    }

    return true;
}

bool utf8_process_cstr_fast(const char *data, size_t *len, size_t *byte_len,
                                                           ssize_t *error) {
    const unsigned char *cursor = data;
    size_t local_byte_len = 0;
    size_t local_len = 0;

    while ((cursor) && (*cursor)) {
        rune r;
        ssize_t bytes_read = utf8proc_iterate(cursor, -1, &r);

        if (bytes_read < 1) {
            *error = bytes_read;
            return false;
        }

        local_len++;
        local_byte_len += bytes_read;
        cursor = data + local_byte_len;
    }

    if (len) {
        *len = local_len;
    }

    if (byte_len) {
        *byte_len = local_byte_len;
    }

    return true;
}

void utf8_index_fast(const char *data, size_t byte_len, size_t index,
                                                        char **cursor) {
    char *local_cursor = data;

    while (true) {
        if ((local_cursor - data) >= byte_len) {
            break;
        }

        if (!index) {
            break;
        }

        if (utf8_byte_is_sequence_start(*local_cursor)) {
            index--;
        }

        local_cursor++;
    }

    *cursor = local_cursor;
}

void utf8_cstr_index_fast(const char *data, size_t index, char **cursor) {
    char *local_cursor = data;

    while (true) {
        if (!local_cursor) {
            break;
        }

        if (!*local_cursor) {
            break;
        }

        if (!rune_count) {
            break;
        }

        if (utf8_byte_is_sequence_start(*local_cursor)) {
            rune_count--;
        }

        local_cursor++;
    }

    *cursor = local_cursor;
}

void utf8_index_reverse_fast(const char *data, size_t byte_len,
                                               size_t index,
                                               char **cursor) {
    char *local_cursor = data + (byte_len - 1);

    while (true) {
        if (local_cursor == data) {
            break;
        }

        if (!index) {
            break;
        }

        if (utf8_byte_is_sequence_start(*local_cursor)) {
            index--;
        }

        local_cursor--;
    }

    *cursor = local_cursor;
}

void utf8_iterate_fast(char **data, size_t *byte_len, rune *r) {
    size_t rune_byte_len = 0;

    utf8_decode_len(*data, r, &rune_byte_len);
    *data += rune_byte_len;
    *byte_len -= rune_byte_len;
}

bool utf8_iterate(char **data, size_t *byte_len, rune *r, Status *status) {
    if ((!(*data)) || (!(**data)) || (*byte_len == 0)) {
        return empty(status);
    }

    utf8_iterate_fast(data, byte_len, r);

    return status_ok(status);
}

bool rune_to_string(rune r, char **out, Status *status) {
    uint8_t buf[4] = {0};
    ssize_t bytes_written;
    char *s;

    bytes_written = utf8proc_encode_char(r, &buf[0]);

    if (bytes_written < 1) {
        return utf8_handle_error_code(bytes_written, status);
    }

    if (!cbmalloc(bytes_written + 1, sizeof(char), (void **)&s, status)) {
        return false;
    }

    if (!cbmemmove(s, &buf[0], bytes_written, sizeof(char))) {
        return false;
    }

    s[bytes_written] = '\0';

    *out = s;

    return status_ok(status);
}

/* vi: set et ts=4 sw=4: */

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

static inline
bool utf8_byte_is_sequence_start(char b) {
    return (b & 0xC0) != 0x80;
}

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

    while (total_bytes_read < byte_len) {
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

static inline
bool utf8_process(const char *data, size_t byte_len, size_t *len,
                                                     Status *status) {
    ssize_t error = 0;

    if (!utf8_process_fast(data, byte_len, len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
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

static inline
bool utf8_process_cstr(const char *data, size_t *len, size_t *byte_len,
                                                      Status *status) {
    ssize_t error = 0;

    if (!utf8_process_cstr_fast(data, len, byte_len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

static inline
bool utf8_validate_fast(const char *data, size_t byte_len, ssize_t *error) {
    return utf8_process_fast(data, byte_len, NULL, error);
}

static inline
bool utf8_validate(const char *data, size_t byte_len, Status *status) {
    return utf8_process(data, byte_len, NULL, status);
}

static inline
bool utf8_validate_cstr_fast(const char *data, ssize_t *error) {
    return utf8_process_cstr_fast(data, NULL, NULL, error);
}

static inline
bool utf8_validate_cstr(const char *data, Status *status) {
    return utf8_process_cstr(data, NULL, NULL, status);
}

static inline
bool utf8_len_fast(const char *data, size_t byte_len, size_t *len,
                                                      ssize_t *error) {
    return utf8_validate_fast(data, byte_len, len, error);
}

static inline
bool utf8_len(const char *data, size_t byte_le, size_t *len, Status *status) {
    return utf8_validate(data, byte_len, len, status);
}

static inline
bool utf8_cstr_len_fast(const char *data, size_t *len, size_t *byte_len,
                                                       ssize_t *error) {
    return utf8_validate_cstr_fast(data, len, byte_len, error);
}

static inline
bool utf8_cstr_len(const char *data, size_t *len, size_t *byte_len,
                                                  Status *status) {
    return utf8_validate_cstr(data, len, byte_len, status);
}

void utf8_skip_fast(const char *data, size_t byte_len, size_t rune_count,
                                                       char **cursor) {
    char *local_cursor;

    for (local_cursor = data; rune_count; local_cursor++) {
        if (utf8_byte_is_sequence_start(*local_cursor)) {
            rune_count--;
        }
    }

    *cursor = local_cursor;
}

void utf8_skip_fast(const char *data, size_t byte_len, size_t rune_count,
                                                       char **cursor) {
    size_t skipped_runes = 0;

    for (size_t i = 0; i < byte_len; i++) {
        if (utf8_byte_is_sequence_start(data[i])) {
            skipped_runes++;

            if (skipped_runes == rune_count) {
                break;
            }
        }
    }
}

void utf8_cstr_skip_fast(const char *data, size_t rune_count, char **cursor) {
    size_t skipped_runes = 0;

    for (char *b = data; ((b) && (*b)); b++) {
        if (utf8_byte_is_sequence_start(*b)) {
            skipped_runes++;

            if (skipped_runes == rune_count) {
                break;
            }
        }
    }
}

bool utf8_skip_fast(const char *data, size_t rune_count, char **cursor,
                                                         ssize_t *error) {
    const unsigned char *local_cursor = data;

    for (size_t i = 0; i < rune_count; i++) {
        rune r;
        ssize_t bytes_read = utf8proc_iterate(local_cursor, -1, &r);

        if (bytes_read < 1) {
            *error = bytes_read;
            return false;
        }

        local_cursor += bytes_read;
    }

    *cursor = local_cursor;

    return status_ok(status);
}


bool utf8_index_fast(const char *data, size_t index, char **cursor,
                                                     ssize_t *error) {
    const unsigned char *local_cursor = data;

    for (size_t i = 0; i < (index - 1); i++) {
        rune r;
        ssize_t bytes_read = utf8proc_iterate(local_cursor, -1, &r);

        if (bytes_read < 1) {
            *error = bytes_read;
            return false;
        }

        local_cursor += bytes_read;
    }

    *cursor = local_cursor;

    return status_ok(status);
}

bool utf8_index_rune_fast(const char *data, size_t index, rune *r,
                                                          ssize_t *error) {
    rune r2;
    char *local_cursor = (char *)data;

    for (size_t i = 0; i < (index - 1); i++) {
        ssize_t bytes_read = utf8proc_iterate(
            (const unsigned char *)local-cursor, -1, &r2
        );

        if (bytes_read < 1) {
            *error = bytes_read;
            return false;
        }

        local_cursor += bytes_read;
    }

    *r = r2;

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

    return status_ok(status);
}

bool utf8_get_first_rune_fast(const char *data, rune *r, ssize_t *error) {
    *error = utf8proc_iterate((const unsigned char *)data, -1, r);

    return (*error >= 1);
}

bool utf8_index_rune_reverse_fast(const char *data, size_t byte_len,
                                                    size_t index,
                                                    rune *r,
                                                    ssize_t *error) {
    char *cursor = NULL;

    for (size_t i = 0; i < byte_len; i++) {
        cursor = ((char *)data) + (byte_len - (i + 1));

        if (((*cursor) & 0xC0) != 0x80) {
            index--;

            if (!index) {
                break;
            }
        }
    }

    size_t byte_count = byte_len - (cursor - data);

    if (byte_count > 4) {
        byte_count = 4;
    }

    ssize_t bytes_read = utf8proc_iterate((const unsigned char *)cursor,
                                          byte_count,
                                          &r2);

    if (bytes_read < 1) {
        return utf8_handle_error_code(bytes_read, status);
    }

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

    if (!cbmalloc(bytes_written + 1, sizeof(char), (void **)&s, status)) {
        return false;
    }

    buf[bytes_written] = '\0';

    if (!cbmemmove(s, &buf[0], (bytes_written + 1), sizeof(byte))) {
        return false;
    }

    *out = s;

    return status_ok(status);
}

/* vi: set et ts=4 sw=4: */

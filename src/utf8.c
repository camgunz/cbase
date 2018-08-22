#include "cbase.h"

#include <utf8proc.h>

#define utf8_too_long(status) status_critical( \
    status,                                    \
    "utf8",                                    \
    UTF8_TOO_LONG,                             \
    "UTF-8 data is too long"                   \
)

#define no_data_passed(status) status_critical( \
    status,                                     \
    "utf8",                                     \
    UTF8_EMPTY,                                 \
    "No data passed"                            \
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
    "Found unassigned codepoint in UTF-8 data"              \
)

#define invalid_options(status) status_critical( \
    status,                                      \
    "utf8",                                      \
    UTF8_INVALID_OPTIONS,                        \
    "Invalid options passed to utf8proc"         \
)

#define unknown_error(status) status_critical( \
    status,                                    \
    "utf8",                                    \
    UTF8_UNKNOWN_ERROR,                        \
    "Unknown utf8proc error"                   \
)

/* [TODO] Bounds checking */

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

inline
bool utf8_byte_is_sequence_start(char b) {
    return (b & 0xC0) != 0x80;
}

bool utf8_process_fast(const char *data, size_t byte_len, size_t *len,
                                                          ssize_t *error) {
    const unsigned char *cursor = (const unsigned char *)data;
    size_t total_bytes_read = 0;
    size_t local_len = 0;

    while ((!cstr_end(data)) && (total_bytes_read < byte_len)) {
        rune r;
        ssize_t bytes_read = utf8proc_iterate(cursor, -1, &r);

        if (bytes_read < 1) {
            *error = bytes_read;
            return false;
        }

        local_len++;
        total_bytes_read += bytes_read;
        cursor = (const unsigned char *)(data + total_bytes_read);
    }

    if (len) {
        *len = local_len;
    }

    return true;
}

inline
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
    const unsigned char *cursor = (const unsigned char *)data;
    size_t local_byte_len = 0;
    size_t local_len = 0;

    while (!cstr_end((const char *)cursor)) {
        rune r;
        ssize_t bytes_read = utf8proc_iterate(cursor, -1, &r);

        if (bytes_read < 1) {
            *error = bytes_read;
            return false;
        }

        local_len++;
        local_byte_len += bytes_read;
        cursor = (const unsigned char *)(data + local_byte_len);
    }

    if (len) {
        *len = local_len;
    }

    if (byte_len) {
        *byte_len = local_byte_len;
    }

    return true;
}

inline
bool utf8_process_cstr(const char *data, size_t *len, size_t *byte_len,
                                                      Status *status) {
    ssize_t error = 0;

    if (!utf8_process_cstr_fast(data, len, byte_len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

inline
bool utf8_validate_fast(const char *data, size_t byte_len, ssize_t *error) {
    return utf8_process_fast(data, byte_len, NULL, error);
}

inline
bool utf8_validate(const char *data, size_t byte_len, Status *status) {
    return utf8_process(data, byte_len, NULL, status);
}

inline
bool utf8_validate_cstr_fast(const char *data, ssize_t *error) {
    return utf8_process_cstr_fast(data, NULL, NULL, error);
}

inline
bool utf8_validate_cstr(const char *data, Status *status) {
    return utf8_process_cstr(data, NULL, NULL, status);
}

inline
bool utf8_validate_len_fast(const char *data, size_t byte_len,
                                              size_t *len,
                                              ssize_t *error) {
    return utf8_process_fast(data, byte_len, len, error);
}

inline
bool utf8_validate_len(const char *data, size_t byte_len, size_t *len,
                                                          Status *status) {
    return utf8_process(data, byte_len, len, status);
}

inline
bool utf8_cstr_validate_len_fast(const char *data, size_t *len,
                                                   size_t *byte_len,
                                                   ssize_t *error) {
    return utf8_process_cstr_fast(data, len, byte_len, error);
}

inline
bool utf8_cstr_validate_len(const char *data, size_t *len, size_t *byte_len,
                                                           Status *status) {
    return utf8_process_cstr(data, len, byte_len, status);
}

inline
void utf8_len(const char *data, size_t byte_len, size_t *len) {
    size_t rune_count = 0;

    for (size_t i = 0; i < byte_len; i++) {
        if (utf8_byte_is_sequence_start(data[i])) {
            rune_count++;
        }
    }

    *len = rune_count;
}

inline
void utf8_cstr_len(const char *data, size_t *len) {
    size_t rune_count = 0;

    for (const char *cursor = data; (cursor) && (*cursor); cursor++) {
        if (utf8_byte_is_sequence_start(*cursor)) {
            rune_count++;
        }
    }

    *len = rune_count;
}

inline
bool utf8_equal_fast(const char *s1, const char *s2, size_t byte_len) {
    return memcmp(s1, s2, byte_len) == 0;
}

inline
bool utf8_equal(const char *s1, const char *s2, size_t byte_len,
                                                bool *equal,
                                                Status *status) {
    if (cstr_end(s1) || cstr_end(s2)) {
        return no_data_passed(status);
    }

    *equal = utf8_equal_fast(s1, s2, byte_len);

    return status_ok(status);
}

inline
bool utf8_cstr_equal_fast(const char *s1, const char *s2) {
    return strcmp(s1, s2) == 0;
}

inline
bool utf8_cstr_equal(const char *s1, const char *s2, bool *equal,
                                                     Status *status) {
    if (cstr_end(s1) || cstr_end(s2)) {
        return no_data_passed(status);
    }

    *equal = utf8_cstr_equal_fast(s1, s2);

    return status_ok(status);
}

inline
void utf8_decode(const char *data, rune *r) {
    const unsigned char *udata = (const unsigned char *)data;

    if (udata[0] < 0x80) {
        *r = udata[0];
    }
    else if (udata[0] < 0xE0) {
        *r = ((udata[0] & 0x1F) << 6) | (udata[1] & 0x3F);
    }
    else if (udata[0] < 0xF0) {
        *r = ((udata[0] & 0xF) << 12) | ((udata[1] & 0x3F) << 6)
                                      |  (udata[2] & 0x3F);
    }
    else {
        *r = ((udata[0] & 7) << 18) | ((udata[1] & 0x3F) << 12)
                                    | ((udata[2] & 0x3F) << 6)
                                    |  (udata[3] & 0x3F);
    }
}

inline
void utf8_decode_len(const char *data, rune *r, size_t *len) {
    const unsigned char *udata = (const unsigned char *)data;

    if (udata[0] < 0x80) {
        *r = udata[0];
        *len = 1;
    }
    else if (udata[0] < 0xE0) {
        *r = ((udata[0] & 0x1F) << 6) | (udata[1] & 0x3F);
        *len = 2;
    }
    else if (udata[0] < 0xF0) {
        *r = ((udata[0] & 0xF) << 12) | ((udata[1] & 0x3F) << 6)
                                      |  (udata[2] & 0x3F);
        *len = 3;
    }
    else {
        *r = ((udata[0] & 7) << 18) | ((udata[1] & 0x3F) << 12)
                                    | ((udata[2] & 0x3F) << 6)
                                    |  (udata[3] & 0x3F);
        *len = 4;
    }
}

void utf8_index_fast(const char *data, size_t byte_len, size_t index,
                                                        char **cursor) {
    char *local_cursor = (char *)data;

    while (true) {
        size_t delta = local_cursor - data;

        if (delta >= byte_len) {
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

inline
bool utf8_index(const char *data, size_t byte_len, size_t index,
                                                   char **cursor,
                                                   Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_index_fast(data, byte_len, index, cursor);

    return status_ok(status);
}

inline
void utf8_index_rune_fast(const char *data, size_t byte_len, size_t index,
                                                             rune *r) {
    char *cursor = NULL;

    utf8_index_fast(data, byte_len, index, &cursor);
    utf8_decode(data, r);
}

inline
bool utf8_index_rune(const char *data, size_t byte_len, size_t index,
                                                        rune *r,
                                                        Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_index_rune_fast(data, byte_len, index, r);

    return status_ok(status);
}

inline
void utf8_index_rune_len_fast(const char *data, size_t byte_len, size_t index,
                                                                 rune *r,
                                                                 size_t *len) {
    char *cursor = NULL;

    utf8_index_fast(data, byte_len, index, &cursor);
    utf8_decode_len(data, r, len);
}

inline
bool utf8_index_rune_len(const char *data, size_t byte_len, size_t index,
                                                            rune *r,
                                                            size_t *len,
                                                            Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_index_rune_len_fast(data, byte_len, index, r, len);

    return status_ok(status);
}

void utf8_cstr_index_fast(const char *data, size_t index, char **cursor) {
    char *local_cursor = (char *)data;

    for (; !cstr_end(local_cursor); local_cursor++) {
        if (utf8_byte_is_sequence_start(*local_cursor)) {
            index--;
        }
    }

    *cursor = local_cursor;
}

inline
bool utf8_cstr_index(const char *data, size_t index, char **cursor,
                                                     Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_cstr_index_fast(data, index, cursor);

    return status_ok(status);
}

inline
void utf8_cstr_index_rune_fast(const char *data, size_t index, rune *r) {
    char *cursor = NULL;

    utf8_cstr_index_fast(data, index, &cursor);
    utf8_decode(data, r);
}

inline
bool utf8_cstr_index_rune(const char *data, size_t index, rune *r,
                                                          Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_cstr_index_rune_fast(data, index, r);

    return status_ok(status);
}

inline
void utf8_cstr_index_rune_len_fast(const char *data, size_t index,
                                                     rune *r,
                                                     size_t *len) {
    utf8_cstr_index_rune_fast(data, index, r);
    utf8_decode_len(data, r, len);
}

inline
bool utf8_cstr_index_rune_len(const char *data, size_t index, rune *r,
                                                              size_t *len,
                                                              Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_cstr_index_rune_len_fast(data, index, r, len);

    return status_ok(status);
}

void utf8_index_reverse_fast(const char *data, size_t byte_len,
                                               size_t index,
                                               char **cursor) {
    char *local_cursor = (char *)data + (byte_len - 1);

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

inline
bool utf8_index_reverse(const char *data, size_t byte_len, size_t index,
                                                           char **cursor,
                                                           Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_index_reverse_fast(data, byte_len, index, cursor);

    return status_ok(status);
}

inline
void utf8_index_rune_reverse_fast(const char *data, size_t byte_len,
                                                    size_t index,
                                                    rune *r) {
    /* [TODO] Bounds checking */
    char *cursor = NULL;

    utf8_index_reverse_fast(data, byte_len, index, &cursor);
    utf8_decode(cursor, r);
}

inline
bool utf8_index_rune_reverse(const char *data, size_t byte_len,
                                               size_t index,
                                               rune *r,
                                               Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_index_rune_reverse_fast(data, byte_len, index, r);

    return status_ok(status);
}

inline
void utf8_index_rune_len_reverse_fast(const char *data, size_t byte_len,
                                                        size_t index,
                                                        rune *r,
                                                        size_t *len) {
    char *cursor = NULL;

    utf8_index_reverse_fast(data, byte_len, index, &cursor);
    utf8_decode_len(cursor, r, len);
}

inline
bool utf8_index_rune_len_reverse(const char *data, size_t byte_len,
                                                   size_t index,
                                                   rune *r,
                                                   size_t *len,
                                                   Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_index_rune_len_reverse_fast(data, byte_len, index, r, len);

    return status_ok(status);
}

inline
void utf8_cstr_index_reverse_fast(const char *data, size_t index,
                                                    char **cursor) {
    utf8_index_reverse_fast(data, strlen(data), index, cursor);
}

inline
bool utf8_cstr_index_reverse(const char *data, size_t index,
                                               char **cursor,
                                               Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_cstr_index_reverse_fast(data, index, cursor);

    return status_ok(status);
}

inline
void utf8_cstr_index_rune_reverse_fast(const char *data, size_t index,
                                                         rune *r) {
    char *cursor = NULL;

    utf8_cstr_index_reverse_fast(data, index, &cursor);
    utf8_decode(cursor, r);
}

inline
bool utf8_cstr_index_rune_reverse(const char *data, size_t index,
                                                    rune *r,
                                                    Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_cstr_index_rune_reverse_fast(data, index, r);

    return status_ok(status);
}

inline
void utf8_cstr_index_rune_len_reverse_fast(const char *data, size_t index,
                                                             rune *r,
                                                             size_t *len) {
    char *cursor = NULL;

    utf8_cstr_index_reverse_fast(data, index, &cursor);
    utf8_decode_len(cursor, r, len);
}

inline
bool utf8_cstr_index_rune_len_reverse(const char *data, size_t index,
                                                        rune *r,
                                                        size_t *len,
                                                        Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_cstr_index_rune_len_reverse_fast(data, index, r, len);

    return status_ok(status);
}

inline
void utf8_get_first_rune_fast(const char *data, rune *r) {
    utf8_decode(data, r);
}

inline
bool utf8_get_first_rune(const char *data, rune *r, Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_get_first_rune_fast(data, r);

    return status_ok(status);
}

inline
void utf8_get_first_rune_len_fast(const char *data, rune *r, size_t *len) {
    utf8_decode_len(data, r, len);
}

inline
bool utf8_get_first_rune_len(const char *data, rune *r, size_t *len,
                                                        Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_get_first_rune_len_fast(data, r, len);

    return status_ok(status);
}

inline
void utf8_cstr_get_first_rune_fast(const char *data, rune *r) {
    utf8_decode(data, r);
}

inline
bool utf8_cstr_get_first_rune(const char *data, rune *r, Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_cstr_get_first_rune_fast(data, r);

    return status_ok(status);
}

inline
void utf8_cstr_get_first_rune_len_fast(const char *data, rune *r,
                                                         size_t *len) {
    utf8_decode_len(data, r, len);
}

inline
bool utf8_cstr_get_first_rune_len(const char *data, rune *r, size_t *len,
                                                             Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_cstr_get_first_rune_len_fast(data, r, len);

    return status_ok(status);
}

inline
void utf8_get_last_rune_fast(const char *data, size_t byte_len, rune *r) {
    utf8_index_rune_reverse_fast(data, byte_len, 1, r);
}

inline
bool utf8_get_last_rune(const char *data, size_t byte_len, rune *r,
                                                           Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_get_last_rune_fast(data, byte_len, r);

    return status_ok(status);
}

inline
void utf8_get_last_rune_len_fast(const char *data, size_t byte_len,
                                                   rune *r,
                                                   size_t *len) {
    utf8_index_rune_len_reverse_fast(data, byte_len, 1, r, len);
}

inline
bool utf8_get_last_rune_len(const char *data, size_t byte_len,
                                              rune *r,
                                              size_t *len,
                                              Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    utf8_get_last_rune_len_fast(data, byte_len, r, len);

    return status_ok(status);
}

inline
void utf8_cstr_get_last_rune_fast(const char *data, rune *r) {
    utf8_get_last_rune_fast(data, strlen(data), r);
}

inline
bool utf8_cstr_get_last_rune(const char *data, rune *r, Status *status) {
    return utf8_get_last_rune(data, strlen(data), r, status);
}

inline
void utf8_cstr_get_last_rune_len_fast(const char *data, rune *r,
                                                        size_t *len) {
    utf8_get_last_rune_len_fast(data, strlen(data), r, len);
}

inline
bool utf8_cstr_get_last_rune_len(const char *data, rune *r, size_t *len,
                                                            Status *status) {
    return utf8_get_last_rune_len(data, strlen(data), r, len, status);
}

inline
void utf8_slice_fast(const char *data, size_t len, size_t byte_len,
                                                   size_t index,
                                                   char **start,
                                                   char **end) {
    utf8_index_fast(data, byte_len, index, start);
    utf8_index_fast(*start, byte_len, len, end);
}

inline
bool utf8_slice(const char *data, size_t len, size_t byte_len,
                                              size_t index,
                                              char **start,
                                              char **end,
                                              Status *status) {
    if (index >= len) {
        return index_out_of_bounds(status);
    }

    utf8_slice_fast(data, len, byte_len, index, start, end);

    return status_ok(status);
}

inline
bool utf8_starts_with_data_fast(const char *s1, size_t byte_len1,
                                const char *s2, size_t byte_len2) {
    return (
        (byte_len2 <= byte_len1) &&
        (utf8_equal_fast(s1, s2, byte_len2))
    );
}

inline
bool utf8_starts_with_data(const char *s1, size_t byte_len1,
                           const char *s2, size_t byte_len2,
                                           bool *starts_with,
                                           Status *status) {
    if (cstr_end(s1) || cstr_end(s2)) {
        return no_data_passed(status);
    }

    *starts_with = utf8_starts_with_data_fast(s1, byte_len1, s2, byte_len2);

    return status_ok(status);
}

inline
bool utf8_starts_with_cstr_fast(const char *data, size_t byte_len,
                                                  const char *cs) {
    return utf8_starts_with_data_fast(data, byte_len, cs, strlen(cs));
}

inline
bool utf8_starts_with_cstr(const char *data, size_t byte_len,
                                             const char *cs,
                                             bool *starts_with,
                                             Status *status) {
    if (cstr_end(data) || cstr_end(cs)) {
        return no_data_passed(status);
    }

    *starts_with = utf8_starts_with_cstr_fast(data, byte_len, cs);

    return status_ok(status);
}

inline
bool utf8_starts_with_rune_fast(const char *data, rune r) {
    rune r2 = 0;

    utf8_get_first_rune_fast(data, &r2);

    return r2 == r;
}

inline
bool utf8_starts_with_rune(const char *data, rune r, bool *starts_with,
                                                     Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    *starts_with = utf8_starts_with_rune_fast(data, r);

    return status_ok(status);
}

inline
bool utf8_cstr_starts_with_data_fast(const char *cs, const char *data,
                                                     size_t byte_len) {
    return utf8_starts_with_data_fast(cs, strlen(cs), data, byte_len);
}

inline
bool utf8_cstr_starts_with_data(const char *cs, const char *data,
                                                size_t byte_len,
                                                bool *starts_with,
                                                Status *status) {
    if (cstr_end(cs) || cstr_end(data)) {
        return no_data_passed(status);
    }

    *starts_with = utf8_cstr_starts_with_data_fast(cs, data, byte_len);

    return status_ok(status);
}

inline
bool utf8_cstr_starts_with_cstr_fast(const char *cs1, const char *cs2) {
    return utf8_starts_with_data_fast(cs1, strlen(cs1), cs2, strlen(cs2));
}

inline
bool utf8_cstr_starts_with_cstr(const char *cs1, const char *cs2,
                                                 bool *starts_with,
                                                 Status *status) {
    if (cstr_end(cs1) || cstr_end(cs2)) {
        return no_data_passed(status);
    }

    *starts_with = utf8_cstr_starts_with_cstr_fast(cs1, cs2);

    return status_ok(status);
}

inline
bool utf8_cstr_starts_with_rune_fast(const char *data, rune r) {
    rune r2 = 0;

    utf8_cstr_get_first_rune_fast(data, &r2);

    return r2 == r;
}

inline
bool utf8_cstr_starts_with_rune(const char *data, rune r, bool *starts_with,
                                                          Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    *starts_with = utf8_cstr_starts_with_rune_fast(data, r);

    return status_ok(status);
}

inline
bool utf8_ends_with_data_fast(const char *s1, size_t byte_len1,
                              const char *s2, size_t byte_len2) {
    return (
        (byte_len2 <= byte_len1) &&
        (utf8_equal_fast(s1 + (byte_len1 - byte_len2), s2, byte_len2))
    );
}

inline
bool utf8_ends_with_data(const char *s1, size_t byte_len1,
                         const char *s2, size_t byte_len2,
                                         bool *ends_with,
                                         Status *status) {
    if (cstr_end(s1) || cstr_end(s2)) {
        return no_data_passed(status);
    }

    *ends_with = utf8_ends_with_data_fast(s1, byte_len1, s2, byte_len2);

    return status_ok(status);
}

inline
bool utf8_ends_with_cstr_fast(const char *data, size_t byte_len,
                                                const char *cs) {
    return utf8_ends_with_data_fast(data, byte_len, cs, strlen(cs));
}

inline
bool utf8_ends_with_cstr(const char *data, size_t byte_len,
                                           const char *cs,
                                           bool *ends_with,
                                           Status *status) {
    if (cstr_end(data) || cstr_end(cs)) {
        return no_data_passed(status);
    }

    *ends_with = utf8_ends_with_cstr_fast(data, byte_len, cs);

    return status_ok(status);
}

inline
bool utf8_ends_with_rune_fast(const char *data, size_t byte_len, rune r) {
    rune r2 = 0;

    utf8_get_last_rune_fast(data, byte_len, &r2);

    return r2 == r;
}

inline
bool utf8_ends_with_rune(const char *data, size_t byte_len,
                                           rune r,
                                           bool *ends_with,
                                           Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    *ends_with = utf8_ends_with_rune_fast(data, byte_len, r);

    return status_ok(status);
}

inline
bool utf8_cstr_ends_with_data_fast(const char *cs, const char *data,
                                                   size_t byte_len) {
    return utf8_ends_with_data_fast(cs, strlen(cs), data, byte_len);
}

inline
bool utf8_cstr_ends_with_data(const char *cs, const char *data,
                                              size_t byte_len,
                                              bool *ends_with,
                                              Status *status) {
    if (cstr_end(cs) || cstr_end(data)) {
        return no_data_passed(status);
    }

    *ends_with = utf8_cstr_ends_with_data_fast(cs, data, byte_len);

    return status_ok(status);
}

inline
bool utf8_cstr_ends_with_cstr_fast(const char *cs1, const char *cs2) {
    return utf8_ends_with_data_fast(cs1, strlen(cs1), cs2, strlen(cs2));
}

inline
bool utf8_cstr_ends_with_cstr(const char *cs1, const char *cs2,
                                               bool *ends_with,
                                               Status *status) {
    if (cstr_end(cs1) || cstr_end(cs2)) {
        return no_data_passed(status);
    }

    *ends_with = utf8_cstr_ends_with_cstr_fast(cs1, cs2);

    return status_ok(status);
}

inline
bool utf8_cstr_ends_with_rune_fast(const char *data, rune r) {
    rune r2 = 0;

    utf8_cstr_get_last_rune_fast(data, &r2);

    return r2 == r;
}

inline
bool utf8_cstr_ends_with_rune(const char *data, rune r, bool *ends_with,
                                                        Status *status) {
    if (cstr_end(data)) {
        return no_data_passed(status);
    }

    *ends_with = utf8_cstr_ends_with_rune_fast(data, r);

    return status_ok(status);
}

void utf8_iterate_fast(char **data, size_t *byte_len, rune *r) {
    size_t rune_byte_len = 0;

    utf8_decode_len(*data, r, &rune_byte_len);
    *data += rune_byte_len;
    *byte_len -= rune_byte_len;
}

bool utf8_iterate(char **data, size_t *byte_len, rune *r, Status *status) {
    if (cstr_end(*data) || (*byte_len == 0)) {
        return no_data_passed(status);
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
        return status_propagate(status);
    }

    if (!cbmemmove(s, buf, bytes_written, sizeof(char), status)) {
        return status_propagate(status);
    }

    s[bytes_written] = '\0';

    *out = s;

    return status_ok(status);
}

/* vi: set et ts=4 sw=4: */

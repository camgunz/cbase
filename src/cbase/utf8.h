#ifndef UTF8_H__
#define UTF8_H__

enum {
    UTF8_TOO_LONG = 1,
    UTF8_INVALID_UTF8,
    UTF8_UNASSIGNED_CODEPOINT,
    UTF8_INVALID_OPTIONS,
    UTF8_EMPTY,
    UTF8_UNKNOWN_ERROR
};

/* [TODO] Bounds checking */

bool utf8_handle_error_code(ssize_t error_code, Status *status);

static inline
bool utf8_byte_is_sequence_start(char b) {
    return (b & 0xC0) != 0x80;
}

bool utf8_process_fast(const char *data, size_t byte_len, size_t *len,
                                                          ssize_t *error);

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
                                                           ssize_t *error);

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
bool utf8_validate_len_fast(const char *data, size_t byte_len,
                                              size_t *len,
                                              ssize_t *error) {
    return utf8_process_fast(data, byte_len, len, error);
}

static inline
bool utf8_validate_len(const char *data, size_t byte_len, size_t *len,
                                                          Status *status) {
    return utf8_process(data, byte_len, len, status);
}

static inline
bool utf8_cstr_validate_len_fast(const char *data, size_t *len,
                                                   size_t *byte_len,
                                                   ssize_t *error) {
    return utf8_process_cstr_fast(data, len, byte_len, error);
}

static inline
bool utf8_cstr_validate_len(const char *data, size_t *len, size_t *byte_len,
                                                           Status *status) {
    return utf8_process_cstr(data, len, byte_len, status);
}

static inline
void utf8_len(const char *data, size_t byte_len, size_t *len) {
    size_t rune_count = 0;

    for (size_t i = 0; i < byte_len; i++) {
        if (utf8_byte_is_sequence_start(data[i])) {
            rune_count++;
        }
    }

    *len = rune_count;
}

static inline
void utf8_cstr_len(const char *data, size_t *len) {
    size_t rune_count = 0;

    for (const char *cursor = data; (cursor) && (*cursor); cursor++) {
        if (utf8_byte_is_sequence_start(*cursor)) {
            rune_count++;
        }
    }

    *len = rune_count;
}

static inline
bool utf8_equal_fast(const char *s1, const char *s2, size_t byte_len) {
    return memcmp(s1, s2, byte_len) == 0;
}

static inline
bool utf8_equal(const char *s1, const char *s2, size_t byte_len,
                                                bool *equal,
                                                Status *status) {
    if ((!s1) || (!*s1) || (!s2) || (!*s2)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *equal = utf8_equal_fast(s1, s2, byte_len);

    return status_ok(status);
}

static inline
bool utf8_cstr_equal_fast(const char *s1, const char *s2) {
    return strcmp(s1, s2) == 0;
}

static inline
bool utf8_cstr_equal(const char *s1, const char *s2, bool *equal,
                                                     Status *status) {
    if ((!s1) || (!*s1) || (!s2) || (!*s2)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *equal = utf8_cstr_equal_fast(s1, s2);

    return status_ok(status);
}

static inline
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

static inline
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
                                                        char **cursor);

static inline
bool utf8_index(const char *data, size_t byte_len, size_t index,
                                                   char **cursor,
                                                   Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_index_fast(data, byte_len, index, cursor);

    return status_ok(status);
}

static inline
void utf8_index_rune_fast(const char *data, size_t byte_len, size_t index,
                                                             rune *r) {
    char *cursor = NULL;

    utf8_index_fast(data, byte_len, index, &cursor);
    utf8_decode(data, r);
}

static inline
bool utf8_index_rune(const char *data, size_t byte_len, size_t index,
                                                        rune *r,
                                                        Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_index_rune_fast(data, byte_len, index, r);

    return status_ok(status);
}

static inline
void utf8_index_rune_len_fast(const char *data, size_t byte_len, size_t index,
                                                                 rune *r,
                                                                 size_t *len) {
    char *cursor = NULL;

    utf8_index_fast(data, byte_len, index, &cursor);
    utf8_decode(data, r);
    *len = cursor - data;
}

static inline
bool utf8_index_rune_len(const char *data, size_t byte_len, size_t index,
                                                            rune *r,
                                                            size_t *len,
                                                            Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_index_rune_len_fast(data, byte_len, index, r, len);

    return status_ok(status);
}

void utf8_cstr_index_fast(const char *data, size_t index, char **cursor);

static inline
bool utf8_cstr_index(const char *data, size_t index, char **cursor,
                                                     Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_cstr_index_fast(data, index, cursor);

    return status_ok(status);
}

static inline
void utf8_cstr_index_rune_fast(const char *data, size_t index, rune *r) {
    char *cursor = NULL;

    utf8_cstr_index_fast(data, index, &cursor);
    utf8_decode(data, r);
}

static inline
bool utf8_cstr_index_rune(const char *data, size_t index, rune *r,
                                                          Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_cstr_index_rune_fast(data, index, r);

    return status_ok(status);
}

static inline
void utf8_cstr_index_rune_len_fast(const char *data, size_t index,
                                                     rune *r,
                                                     size_t *len) {
    char *cursor = NULL;

    utf8_cstr_index_rune_fast(data, index, r);
    utf8_decode(data, r);
    *len = cursor - data;
}

static inline
bool utf8_cstr_index_rune_len(const char *data, size_t index, rune *r,
                                                              size_t *len,
                                                              Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_cstr_index_rune_len_fast(data, index, r, len);

    return status_ok(status);
}

void utf8_index_reverse_fast(const char *data, size_t byte_len,
                                               size_t index,
                                               char **cursor);

static inline
bool utf8_index_reverse(const char *data, size_t byte_len, size_t index,
                                                           char **cursor,
                                                           Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_index_reverse_fast(data, byte_len, index, cursor);

    return status_ok(status);
}

static inline
void utf8_index_rune_reverse_fast(const char *data, size_t byte_len,
                                                    size_t index,
                                                    rune *r) {
    char *cursor = NULL;

    utf8_index_reverse_fast(data, byte_len, index, &cursor);
    utf8_decode(cursor, r);
}

static inline
bool utf8_index_rune_reverse(const char *data, size_t byte_len,
                                               size_t index,
                                               rune *r,
                                               Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_index_rune_reverse_fast(data, byte_len, index, r);

    return status_ok(status);
}

static inline
void utf8_index_rune_len_reverse_fast(const char *data, size_t byte_len,
                                                        size_t index,
                                                        rune *r,
                                                        size_t *len) {
    char *cursor = NULL;

    utf8_index_reverse_fast(data, byte_len, index, &cursor);
    utf8_decode_len(cursor, r, len);
}

static inline
bool utf8_index_rune_len_reverse(const char *data, size_t byte_len,
                                                   size_t index,
                                                   rune *r,
                                                   size_t *len,
                                                   Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_index_rune_len_reverse_fast(data, byte_len, index, r, len);

    return status_ok(status);
}

static inline
void utf8_cstr_index_reverse_fast(const char *data, size_t index,
                                                    char **cursor) {
    utf8_index_reverse_fast(data, strlen(data), index, cursor);
}

static inline
bool utf8_cstr_index_reverse(const char *data, size_t index,
                                               char **cursor,
                                               Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_cstr_index_reverse_fast(data, index, cursor);

    return status_ok(status);
}

static inline
void utf8_cstr_index_rune_reverse_fast(const char *data, size_t index,
                                                         rune *r) {
    char *cursor = NULL;

    utf8_cstr_index_reverse_fast(data, index, &cursor);
    utf8_decode(cursor, r);
}

static inline
bool utf8_cstr_index_rune_reverse(const char *data, size_t index,
                                                    rune *r,
                                                    Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_cstr_index_rune_reverse_fast(data, index, r);

    return status_ok(status);
}

static inline
void utf8_cstr_index_rune_len_reverse_fast(const char *data, size_t index,
                                                             rune *r,
                                                             size_t *len) {
    char *cursor = NULL;

    utf8_cstr_index_reverse_fast(data, index, &cursor);
    utf8_decode_len(cursor, r, len);
}

static inline
bool utf8_cstr_index_rune_len_reverse(const char *data, size_t index,
                                                        rune *r,
                                                        size_t *len,
                                                        Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_cstr_index_rune_len_reverse_fast(data, index, r, len);

    return status_ok(status);
}

static inline
void utf8_get_first_rune_fast(const char *data, rune *r) {
    utf8_decode(data, r);
}

static inline
bool utf8_get_first_rune(const char *data, rune *r, Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_get_first_rune_fast(data, r);

    return status_ok(status);
}

static inline
void utf8_get_first_rune_len_fast(const char *data, rune *r, size_t *len) {
    utf8_decode_len(data, r, len);
}

static inline
bool utf8_get_first_rune_len(const char *data, rune *r, size_t *len,
                                                        Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_get_first_rune_len_fast(data, r, len);

    return status_ok(status);
}

static inline
void utf8_cstr_get_first_rune_fast(const char *data, rune *r) {
    utf8_decode(data, r);
}

static inline
bool utf8_cstr_get_first_rune(const char *data, rune *r, Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_cstr_get_first_rune_fast(data, r);

    return status_ok(status);
}

static inline
void utf8_cstr_get_first_rune_len_fast(const char *data, rune *r,
                                                         size_t *len) {
    utf8_decode_len(data, r, len);
}

static inline
bool utf8_cstr_get_first_rune_len(const char *data, rune *r, size_t *len,
                                                             Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_cstr_get_first_rune_len_fast(data, r, len);

    return status_ok(status);
}

static inline
void utf8_get_last_rune_fast(const char *data, size_t byte_len, rune *r) {
    utf8_index_rune_reverse_fast(data, byte_len, 1, r);
}

static inline
bool utf8_get_last_rune(const char *data, size_t byte_len, rune *r,
                                                           Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_get_last_rune_fast(data, byte_len, r);

    return status_ok(status);
}

static inline
void utf8_get_last_rune_len_fast(const char *data, size_t byte_len,
                                                   rune *r,
                                                   size_t *len) {
    utf8_index_rune_len_reverse_fast(data, byte_len, 1, r, len);
}

static inline
bool utf8_get_last_rune_len(const char *data, size_t byte_len,
                                              rune *r,
                                              size_t *len,
                                              Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    utf8_get_last_rune_len_fast(data, byte_len, r, len);

    return status_ok(status);
}

static inline
void utf8_cstr_get_last_rune_fast(const char *data, rune *r) {
    utf8_get_last_rune_fast(data, strlen(data), r);
}

static inline
bool utf8_cstr_get_last_rune(const char *data, rune *r, Status *status) {
    return utf8_get_last_rune(data, strlen(data), r, status);
}

static inline
void utf8_cstr_get_last_rune_len_fast(const char *data, rune *r,
                                                        size_t *len) {
    utf8_get_last_rune_len_fast(data, strlen(data), r, len);
}

static inline
bool utf8_cstr_get_last_rune_len(const char *data, rune *r, size_t *len,
                                                            Status *status) {
    return utf8_get_last_rune_len(data, strlen(data), r, len, status);
}

static inline
void utf8_slice_fast(const char *data, size_t byte_len, size_t index,
                                                        size_t len,
                                                        char **start,
                                                        char **end) {
    utf8_index_fast(data, byte_len, index, start);
    utf8_index_fast(*start, byte_len, len, end);
}

static inline
bool utf8_starts_with_data_fast(const char *s1, size_t byte_len1,
                                const char *s2, size_t byte_len2) {
    return (
        (byte_len2 <= byte_len1) &&
        (utf8_equal_fast(s1, s2, byte_len2))
    );
}

static inline
bool utf8_starts_with_data(const char *s1, size_t byte_len1,
                           const char *s2, size_t byte_len2,
                                           bool *starts_with,
                                           Status *status) {
    if ((!s1) || (!*s1) || (!s2) || (!*s2)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *starts_with = utf8_starts_with_data_fast(s1, byte_len1, s2, byte_len2);

    return status_ok(status);
}

static inline
bool utf8_starts_with_cstr_fast(const char *data, size_t byte_len,
                                                  const char *cs) {
    return utf8_starts_with_data_fast(data, byte_len, cs, strlen(cs));
}

static inline
bool utf8_starts_with_cstr(const char *data, size_t byte_len,
                                             const char *cs,
                                             bool *starts_with,
                                             Status *status) {
    if ((!data) || (!*data) || (!cs) || (!*cs)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *starts_with = utf8_starts_with_cstr_fast(data, byte_len, cs);

    return status_ok(status);
}

static inline
bool utf8_starts_with_rune_fast(const char *data, size_t byte_len, rune r) {
    rune r2 = 0;

    utf8_get_first_rune(data, byte_len, &r2);

    return r2 == r;
}

static inline
bool utf8_starts_with_rune(const char *data, size_t byte_len,
                                             rune r,
                                             bool *starts_with,
                                             Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *starts_with = utf8_starts_with_rune_fast(data, byte_len, r);

    return status_ok(status);
}

static inline
bool utf8_cstr_starts_with_data_fast(const char *cs, const char *data,
                                                     size_t byte_len) {
    return utf8_starts_with_data_fast(cs, strlen(cs), data, byte_len);
}

static inline
bool utf8_cstr_starts_with_data(const char *cs, const char *data,
                                                size_t byte_len,
                                                bool *starts_with,
                                                Status *status) {
    if ((!cs) || (!*cs) || (!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *starts_with = utf8_cstr_starts_with_data_fast(cs, data, byte_len);

    return status_ok(status);
}

static inline
bool utf8_cstr_starts_with_cstr_fast(const char *cs1, const char *cs2) {
    return utf8_starts_with_data_fast(cs1, strlen(cs1), cs2, strlen(cs2));
}

static inline
bool utf8_cstr_starts_with_cstr(const char *cs1, const char *cs2,
                                                 bool *starts_with,
                                                 Status *status) {
    if ((!cs1) || (!*cs1) || (!cs2) || (!*cs2)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *starts_with = utf8_cstr_starts_with_cstr_fast(cs1, cs2);

    return status_ok(status);
}

static inline
bool utf8_cstr_starts_with_rune_fast(const char *data, rune r) {
    rune r2 = 0;

    utf8_cstr_get_first_rune_fast(data, &r2);

    return r2 == r;
}

static inline
bool utf8_cstr_starts_with_rune(const char *data, rune r, bool *starts_with,
                                                          Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *starts_with = utf8_cstr_starts_with_rune_fast(data, r);

    return status_ok(status);
}

static inline
bool utf8_ends_with_data_fast(const char *s1, size_t byte_len1,
                              const char *s2, size_t byte_len2) {
    return (
        (byte_len2 <= byte_len1) &&
        (utf8_equal_fast(s1 + (byte_len1 - byte_len2), s2, byte_len2))
    );
}

static inline
bool utf8_ends_with_data(const char *s1, size_t byte_len1,
                         const char *s2, size_t byte_len2,
                                         bool *ends_with,
                                         Status *status) {
    if ((!s1) || (!*s1) || (!s2) || (!*s2)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *ends_with = utf8_ends_with_data_fast(s1, byte_len1, s2, byte_len2);

    return status_ok(status);
}

static inline
bool utf8_ends_with_cstr_fast(const char *data, size_t byte_len,
                                                const char *cs) {
    return utf8_ends_with_data_fast(data, byte_len, cs, strlen(cs));
}

static inline
bool utf8_ends_with_cstr(const char *data, size_t byte_len,
                                           const char *cs,
                                           bool *ends_with,
                                           Status *status) {
    if ((!data) || (!*data) || (!cs) || (!*cs)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *ends_with = utf8_ends_with_cstr_fast(data, byte_len, cs);

    return status_ok(status);
}

static inline
bool utf8_ends_with_rune_fast(const char *data, size_t byte_len, rune r) {
    rune r2 = 0;

    utf8_get_last_rune(data, byte_len, &r2);

    return r2 == r;
}

static inline
bool utf8_ends_with_rune(const char *data, size_t byte_len,
                                           rune r,
                                           bool *ends_with,
                                           Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *ends_with = utf8_ends_with_rune_fast(data, byte_len, r);

    return status_ok(status);
}

static inline
bool utf8_cstr_ends_with_data_fast(const char *cs, const char *data,
                                                   size_t byte_len) {
    return utf8_ends_with_data_fast(cs, strlen(cs), data, byte_len);
}

static inline
bool utf8_cstr_ends_with_data(const char *cs, const char *data,
                                              size_t byte_len,
                                              bool *ends_with,
                                              Status *status) {
    if ((!cs) || (!*cs) || (!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *ends_with = utf8_cstr_ends_with_data_fast(cs, data, byte_len);

    return status_ok(status);
}

static inline
bool utf8_cstr_ends_with_cstr_fast(const char *cs1, const char *cs2) {
    return utf8_ends_with_data_fast(cs1, strlen(cs1), cs2, strlen(cs2));
}

static inline
bool utf8_cstr_ends_with_cstr(const char *cs1, const char *cs2,
                                               bool *ends_with,
                                               Status *status) {
    if ((!cs1) || (!*cs1) || (!cs2) || (!*cs2)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *ends_with = utf8_cstr_ends_with_cstr_fast(cs1, cs2);

    return status_ok(status);
}

static inline
bool utf8_cstr_ends_with_rune_fast(const char *data, rune r) {
    rune r2 = 0;

    utf8_cstr_get_last_rune_fast(data, &r2);

    return r2 == r;
}

static inline
bool utf8_cstr_ends_with_rune(const char *data, rune r, bool *ends_with,
                                                        Status *status) {
    if ((!data) || (!*data)) {
        return status_failure(status, "utf8", UTF8_EMPTY, "No data passed");
    }

    *ends_with = utf8_cstr_ends_with_rune_fast(data, r);

    return status_ok(status);
}

bool rune_to_string(rune r, char **out, Status *status);

#endif

/* vi: set et ts=4 sw=4: */

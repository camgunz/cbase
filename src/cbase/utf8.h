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
bool utf8_equal(const char *s1, const char *s2, size_t n) {
    return memcmp(s1, s2, n) == 0;
}

static inline
bool utf8_cstr_equal(const char *s1, const char *s2) {
    return strcmp(s1, s2) == 0;
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

bool rune_to_string(rune r, char **out, Status *status);

#endif

/* vi: set et ts=4 sw=4: */

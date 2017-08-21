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

/*
 * [FIXME] There's no clear indication whether or not data needs to be NULL-
 *         terminated.
 */

bool utf8_handle_error_code(ssize_t error_code, Status *status);

bool utf8len_fast(const char *data, size_t *len, ssize_t *error);

static inline
bool utf8_validate(const char *data, size_t byte_len, Status *status) {
    ssize_t error = 0;

    if (!utf8_validate_fast(data, byte_len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

static inline
bool utf8len(const char *data, size_t *len, Status *status) {
    ssize_t error;

    if (!utf8len_fast(data, len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool utf8_len_and_byte_len_fast(const char *data, size_t *len,
                                                  size_t *byte_len,
                                                  ssize_t *error);

static inline
bool utf8_len_and_byte_len(const char *data, size_t *len, size_t *byte_len,
                                                          Status *status) {
    ssize_t error;

    if (!utf8_len_and_byte_len_fast(data, len, byte_len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool utf8nlen_fast(const char *data, size_t n, size_t *len, ssize_t *error);

static inline
bool utf8nlen(const char *data, size_t n, size_t *len, Status *status) {
    ssize_t error;

    if (!utf8nlen_fast(data, n, len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

static inline
bool utf8cmp(const char *s1, const char *s2) {
    return strcmp(s1, s2) == 0;
}

static inline
bool utf8ncmp(const char *s1, const char *s2, size_t n) {
    return memcmp(s1, s2, n) == 0;
}

bool utf8_index_fast(const char *data, size_t index, char **cursor,
                                                     ssize_t *error);

static inline
bool utf8_index(const char *data, size_t index, char **cursor,
                                                Status *status) {
    ssize_t error = 0;

    if ((!data) || (!*data)) {
        return empty(status);
    }

    if (!utf8_index_fast(data, index, cursor, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool utf8_index_rune_fast(const char *data, size_t index, rune *r,
                                                          ssize_t *error);

static inline
bool utf8_index_rune(const char *data, size_t index, rune *r, Status *status) {
    ssize_t error = 0;

    if ((!data) || (!*data)) {
        return empty(status);
    }

    if (!utf8_index_rune_fast(data, index, r, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool utf8_index_rune_reverse_fast(const char *data, size_t byte_len,
                                                    size_t index,
                                                    rune *r,
                                                    ssize_t *error);
static inline
bool utf8_index_rune_reverse(const char *data, size_t byte_len,
                                               size_t index,
                                               rune *r,
                                               Status *status) {
    ssize_t error = 0;

    if ((!data) || (!*data) || (!byte_len)) {
        return empty(status);
    }

    if (!utf8_index_rune_reverse_fast(data, byte_len, index, r, &error)) {
        return utf8_handle_error_code(bytes_read, status);
    }

    return status_ok(status);
}

bool utf8_skip_fast(const char *data, size_t len, char **cursor,
                                                  ssize_t *error);

static inline
bool utf8_skip(const char *data, size_t len, char **cursor,
                                             Status *status) {
    ssize_t error = 0;

    if ((!data) || (!*data) || (!len)) {
        return empty(status);
    }

    if (!utf8_skip_fast(data, len, cursor, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool utf8_slice_fast(const char *data, size_t index, size_t len,
                                                     char **start,
                                                     char **end,
                                                     ssize_t *error);

static inline
bool utf8_slice(const char *data, size_t index, size_t len, char **start,
                                                            char **end,
                                                            Status *status) {
    ssize_t error = 0;

    if (!utf8_slice_fast(data, index, len, start, end, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}


bool utf8_get_first_rune_len_fast(const char *data, rune *r, size_t *len,
                                                             ssize_t *error);

static inline
bool utf8_get_first_rune_len(const char *data, rune *r, size_t *len,
                                                        Status *status) {
    ssize_t error = 0;

    if (!utf8_get_first_rune_len_fast(data, r, len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

bool utf8_get_first_rune_fast(const char *data, rune *r, ssize_t *error);

static inline
bool utf8_get_first_rune(const char *data, rune *r, Status *status) {
    ssize_t bytes_read;

    if (!utf8_get_first_rune_fast(data, r, &bytes_read)) {
        return utf8_handle_error_code(bytes_read, status);
    }

    return status_ok(status);
}

bool utf8_get_end_offset(const char *data, size_t rune_count, size_t byte_len,
                                                              size_t *offset,
                                                              Status *status);

bool utf8_get_end_rune_offset(const char *data, size_t byte_len,
                                                rune *r,
                                                size_t *offset,
                                                Status *status);

static inline
bool utf8_get_end_rune(const char *data, size_t byte_len, rune *r,
                                                          Status *status) {
    size_t offset = 0;

    return utf8_get_end_rune_offset(data, byte_len, r, &offset, status);
}

bool rune_to_string(rune r, char **out, Status *status);

#endif

/* vi: set et ts=4 sw=4: */

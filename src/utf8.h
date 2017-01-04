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
bool utf8len(const char *data, size_t *len, Status *status);
bool utf8len_fast(const char *data, size_t *len, ssize_t *error);
bool utf8nlen(const char *data, size_t n, size_t *len, Status *status);
bool utf8nlen_fast(const char *data, size_t n, size_t *len, ssize_t *error);
bool utf8_index(const char *data, size_t len, char **cursor,
                                              Status *status);
bool utf8_index_fast(const char *data, size_t len, char **cursor,
                                                   ssize_t *error);
bool utf8_skip(const char *data, size_t len, char **cursor,
                                             Status *status);
bool utf8_skip_fast(const char *data, size_t len, char **cursor,
                                                  ssize_t *error);
bool utf8_get_first_rune(const char *data, rune *r, Status *status);
bool utf8_get_first_rune_fast(const char *data, rune *r, ssize_t *error);
bool utf8_get_first_rune_len(const char *data, rune *r, size_t *len,
                                                        Status *status);
bool utf8_get_first_rune_len_fast(const char *data, rune *r, size_t *len,
                                                             ssize_t *error);
bool utf8_get_end_offset(const char *data, size_t rune_count, size_t byte_len,
                                                              size_t *offset,
                                                              Status *status);
bool utf8_get_end_rune_offset(const char *data, size_t byte_len,
                                                rune *r,
                                                size_t *offset,
                                                Status *status);
bool utf8_slice(const char *data, size_t index, size_t len,
                                                char **start,
                                                char **end,
                                                Status *status);
bool utf8_slice_fast(const char *data, size_t index, size_t len,
                                                     char **start,
                                                     char **end,
                                                     ssize_t *error);

static inline bool utf8cmp(const char *s1, const char *s2) {
    return strcmp(s1, s2) == 0;
}

static inline bool utf8ncmp(const char *s1, const char *s2, size_t n) {
    return memcmp(s1, s2, n) == 0;
}

#endif

/* vi: set et ts=4 sw=4: */

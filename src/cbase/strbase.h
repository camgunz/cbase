#ifndef SBUFFER_H__
#define SBUFFER_H__

enum {
    SBUFFER_EMPTY = 1,
};

bool sbuffer_get_first_rune(char *data, rune *r, Status *status);
bool sbuffer_skip_runes(char **data, size_t *len, size_t *byte_len,
                                                  size_t rune_count,
                                                  Status *status);
bool sbuffer_seek_to(char **data, size_t *len, size_t *byte_len,
                                               rune r,
                                               Status *status);

static inline
bool sbuffer_empty(size_t len, size_t byte_len) {
    return len == 0 && byte_len == 0;
}

static inline
void sbuffer_clear(size_t *len, size_t *byte_len) {
    *len = 0;
    *byte_len = 0;
}

static inline
bool sbuffer_equals(char *data1, size_t len1, size_t byte_len1,
                    char *data2, size_t len2, size_t byte_len2) {
    return (
        (len1 == len2) &&
        (byte_len1 == byte_len2) &&
        (memcmp(data1, data2, byte_len1) == 0)
    );
}

static inline
bool sbuffer_equals_cstr(const char *data, const char *cs) {
    return utf8cmp(cs, data);
}

static inline
void sbuffer_copy(char **dst_data, size_t *dst_len, size_t dst_byte_len,
                  char *src_data, size_t src_len, size_t src_byte_len) {
    *dst_data = src_data;
    *dst_len = src_len;
    *dst_byte_len = dst_byte_len;
}

static inline
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

static inline
bool sbuffer_starts_with_cstr(char *data, size_t byte_len, const char *cs,
                                                           bool *starts_with,
                                                           Status *status) {
    if (sbuffer_empty(s)) {
        *starts_with = false;
        return status_ok(status);
    }

    return (strlen(cs) <= byte_len) && (memcmp(data, cs, byte_len) == 0);
}

static inline
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

static inline
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

static inline
bool sbuffer_skip_rune(char **data, size_t *len, size_t *byte_len,
                                                 Status *status) {
    return sbuffer_skip_runes(data, len, byte_len, 1, status);
}

static inline
bool sbuffer_truncate_rune(char *data, size_t *len, size_t *byte_len,
                                                    Status *status) {
    return sbuffer_truncate_runes(data, len, byte_len, 1, status);
}

static inline
bool sbuffer_skip_rune_if_matches(char **data, size_t *len,
                                               size_t *byte_len,
                                               RuneMatchFunc *matches,
                                               Status *status) {
    rune r;

    return sbuffer_pop_rune_if_matches(data, len, byte_len, matches,
                                                            &r,
                                                            status);
}

static inline
void sbuffer_seek_to_end(char **data, size_t *len, size_t *byte_len) {
    *data += *byte_len;
    *len = 0;
    *byte_len = 0;
}

#endif

/* vi: set et ts=4 sw=4: */
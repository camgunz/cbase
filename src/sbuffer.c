
bool sbuffer_empty(size_t len, size_t byte_len) {
    return len == 0 && byte_len == 0;
}

void sbuffer_clear(size_t *len, size_t *byte_len) {
    *len = 0;
    *byte_len = 0;
}

bool sbuffer_equals(char *data1, size_t len1, size_t byte_len1,
                    char *data2, size_t len2, size_t byte_len2) {
    return (
        (len1 == len2) &&
        (byte_len1 == byte_len2) &&
        (utf8ncmp(data1, data2, byte_len1)
    );
}

void sbuffer_copy(char **dst_data, size_t *dst_len, size_t dst_byte_len,
                  char *src_data, size_t src_len, size_t src_byte_len) {
    *dst_data = src_data;
    *dst_len = src_len;
    *dst_byte_len = dst_byte_len;
}

static inline bool sbuffer_starts_with_cstr(char *data, size_t byte_len,
                                                        const char *cs) {
    return (
        (strlen(cs) <= byte_len) &&
        utf8ncmp(data, cs, byte_len)
    );
}

static inline bool sbuffer_ends_with_cstr(char *data, size_t byte_len,
                                                      const char *cs) {
    size_t cstr_byte_len = strlen(cs);

    return (
        (cstr_byte_len <= s->byte_len) &&
        utf8cmp(s->data + (s->byte_len - cstr_byte_len), cs)
    );
}

static inline bool sbuffer_skip_rune(SSlice *s, Status *status) {
    return sslice_skip_runes(s, 1, status);
}

static inline bool sslice_truncate_rune(SSlice *s, Status *status) {
    return sslice_truncate_runes(s, 1, status);
}

static inline void sslice_seek_to_end(SSlice *s) {
    s->data += s->byte_len;
    s->len = 0;
    s->byte_len = 0;
}


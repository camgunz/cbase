#ifndef STRBASE_H__
#define STRBASE_H__

enum {
    STRBASE_EMPTY = 1,
};

static inline
bool strbase_empty(const char *data, size_t len, size_t byte_len) {
    return ((!data) || (!*data) || (!len) || (!byte_len));
}

static inline
bool strbase_equals(const char *data1, size_t len1, size_t byte_len1,
                    const char *data2, size_t len2, size_t byte_len2) {
    return (
        (len1 == len2) &&
        (byte_len1 == byte_len2) &&
        (memcmp(data1, data2, byte_len1) == 0)
    );
}

static inline
bool strbase_equals_cstr_full(const char *data, size_t byte_len,
                                                const char *cs,
                                                size_t cs_byte_len) {
    return (
        (byte_len == cs_byte_len) &&
        (memcmp(data, cs, byte_len) == 0 )
    );
}

static inline
bool strbase_equals_cstr(const char *data, size_t byte_len, const char *cs) {
    return strbase_equals_str_full(data, byte_len, cs, strlen(cs));
}

static inline
bool strbase_equals_utf8_data(const char *data1, size_t byte_len1,
                              const char *data2, size_t byte_len) {
    return (
        (byte_len1 == byte_len2) &&
        (memcmp(data1, data2, byte_len1) == 0)
    );
}

static inline
bool strbase_equals_sslice(const char *data, size_t byte_len, SSlice *sslice) {
    return strbase_equals_utf8_data(
        data, byte_len, sslice->data, sslice->byte_len
    );
}

static inline
bool strbase_equals_string(const char *data, size_t byte_len, String *string) {
    return strbase_equals_utf8_data(
        data, byte_len, string->data, string->byte_len
    );
}

static inline
bool strbase_equals_utf8_slice(const char *data, size_t byte_len,
                                                 Slice *slice) {
    return strbase_equals_utf8_data(
        data, byte_len, slice->data, slice->byte_len
    );
}

static inline
bool strbase_equals_utf8_buffer(const char *data, size_t byte_len,
                                                  Buffer *buffer) {
    return strbase_equals_utf8_data(
        data, byte_len, buffer->data, buffer->byte_len
    );
}

static inline
void strbase_copy(char **dst_data, size_t *dst_len, size_t *dst_byte_len,
                  const char *src_data, size_t src_len, size_t src_byte_len) {
    *dst_data = (char *)src_data;
    *dst_len = src_len;
    *dst_byte_len = src_byte_len;
}

#define strbase_index_fast utf8_index_fast
#define strbase_index utf8_index
#define strbase_index_rune_fast utf8_index_rune_fast
#define strbase_index_rune utf8_index_rune
#define strbase_index_rune_len_fast utf8_index_rune_len_fast
#define strbase_index_rune_len utf8_index_rune_len
#define strbase_index_reverse_fast utf8_index_reverse_fast
#define strbase_index_reverse utf8_index_reverse
#define strbase_index_rune_reverse_fast utf8_index_rune_reverse_fast
#define strbase_index_rune_reverse utf8_index_rune_reverse
#define strbase_index_rune_len_reverse_fast utf8_index_rune_len_reverse_fast
#define strbase_index_rune_len_reverse utf8_index_rune_len_reverse
#define strbase_get_first_rune_fast utf8_get_first_rune_fast
#define strbase_get_first_rune utf8_get_first_rune
#define strbase_get_first_rune_len_fast utf8_get_first_rune_len_fast
#define strbase_get_first_rune_len utf8_get_first_rune_len
#define strbase_get_last_rune_len_fast utf8_get_last_rune_len_fast
#define strbase_get_last_rune_len utf8_get_last_rune_len
#define strbase_starts_with_data_fast utf8_starts_with_data_fast
#define strbase_starts_with_data utf8_starts_with_data
#define strbase_starts_with_cstr_fast utf8_starts_with_cstr_fast
#define strbase_starts_with_cstr utf8_starts_with_cstr
#define strbase_starts_with_rune_fast utf8_starts_with_rune_fast
#define strbase_starts_with_rune utf8_starts_with_rune
#define strbase_ends_with_data_fast utf8_ends_with_data_fast
#define strbase_ends_with_data utf8_ends_with_data
#define strbase_ends_with_cstr_fast utf8_ends_with_cstr_fast
#define strbase_ends_with_cstr utf8_ends_with_cstr
#define strbase_ends_with_rune_fast utf8_ends_with_rune_fast
#define strbase_ends_with_rune utf8_ends_with_rune

/*****************************************************************************/

bool strbase_encode(String *string, const char *encoding, Buffer *out,
                                                         Status *status);

bool strbase_encode(String *string, const char *encoding, Buffer *out,
                                                         Status *status);
bool strbase_localize(String *string, Buffer *out, Status *status) {

bool strbase_pop_rune(String *string, rune *r, Status *status);
bool strbase_pop_rune_if_equals(String *string, rune *r, Status *status);
bool strbase_pop_rune_if_matches(String *string, RuneMatchFunc *matches,
                                                rune *r,
                                                Status *status);

static inline
bool strbase_pop_rune_if_alpha(SSlice *sslice, rune *r, Status *status) {
    return strbase_pop_rune_if_matches(sslice, rune_is_alpha, r, status);
}

static inline
bool strbase_pop_rune_if_hex_digit(SSlice *sslice, rune *r, Status *status) {
    return strbase_pop_rune_if_matches(sslice, rune_is_hex_digit, r, status);
}

static inline
bool strbase_pop_rune_if_digit(SSlice *sslice, rune *r, Status *status) {
    return strbase_pop_rune_if_matches(sslice, rune_is_digit, r, status);
}

static inline
bool strbase_pop_rune_if_oct_digit(SSlice *sslice, rune *r, Status *status) {
    return strbase_pop_rune_if_matches(sslice, rune_is_oct_digit, r, status);
}

static inline
bool strbase_pop_rune_if_bin_digit(SSlice *sslice, rune *r, Status *status) {
    return strbase_pop_rune_if_matches(sslice, rune_is_bin-digit, r, status);
}

static inline
bool strbase_pop_rune_if_alnum(SSlice *sslice, rune *r, Status *status) {
    return strbase_pop_rune_if_matches(sslice, rune_is_alnum, r, status);
}

static inline
bool strbase_pop_rune_if_whitespace(SSlice *sslice, rune *r, Status *status) {
    return strbase_pop_rune_if_matches(sslice, rune_is_whitespace, r, status);
}

bool strbase_seek_to(char **data, size_t *len, size_t *byte_len,
                                               rune r,
                                               Status *status);
bool strbase_seek_to_rune(String *string, rune r, Status *status);

bool  strbase_seek_to(SSlice *sslice, rune r, Status *status);
bool  strbase_seek_to_cstr(SSlice *sslice, const char *cs, Status *status);
bool  strbase_seek_to_whitespace(SSlice *sslice, Status *status);
bool  strbase_seek_to_subslice(SSlice *sslice, SSlice *subslice,
                                              Status *status);
bool  strbase_seek_past_subslice(SSlice *sslice, SSlice *subslice,
                                                Status *status);
bool  strbase_seek_past_whitespace(SSlice *sslice, Status *status);

static inline
bool strbase_truncate_runes(SSlice *sslice, size_t rune_count, Status *status) {
    return strbase_truncate_runes(
        &sslice->data, &sslice->len, &sslice->byte_len, rune_count, status
    );
}

bool  strbase_truncate_whitespace(SSlice *sslice, Status *status);
bool  strbase_truncate_at(SSlice *sslice, rune r, Status *status);
bool  strbase_truncate_at_whitespace(SSlice *sslice, Status *status);
bool  strbase_truncate_at_subslice(SSlice *sslice, SSlice *subslice,
                                                  Status *status);

static inline
bool strbase_skip_runes_fast(char **data, size_t *len, size_t *byte_len,
                                                       size_t rune_count) {
    char *cursor = NULL;
    ptrdiff_t diff = 0;

    strbase_index_fast(*data, *byte_len, rune_count, &cursor);

    diff = cursor - *data;

    if (diff < 0) {
        diff = 0;
    }

    *data = cursor;
    *byte_len = diff;
    *len = *len - rune_count;
}

bool strbase_skip_runes(char **data, size_t *len, size_t *byte_len,
                                                  size_t rune_count,
                                                  Status *status) {
    char *cursor = NULL;
    ptrdiff_t diff = 0;

    if (!strbase_index(*data, *byte_len, rune_count, &cursor, status)) {
        return false;
    }

    diff = cursor - *data;

    if (diff < 0) {
        diff = 0;
    }

    *data = cursor;
    *byte_len = diff;
    *len = *len - rune_count;

    return status_ok(status);
}

static inline
bool strbase_skip_rune(char **data, size_t *len, size_t *byte_len,
                                                 Status *status) {
    return strbase_skip_runes(data, len, byte_len, 1, status);
}

bool strbase_skip_rune_if_equals(String *string, rune r, Status *status);

static inline
bool strbase_skip_rune_if_matches(char **data, size_t *len,
                                               size_t *byte_len,
                                               RuneMatchFunc *matches,
                                               Status *status) {
    rune r = 0;
    size_t rune_byte_len = 0;

    if (!utf8_index_rune_len(*data, *byte_len, 0, &r, &rune_byte_len,
                                                      status)) {
        return false;
    }

    if (matches(r)) {
        *data += rune_byte_len;
        *len -= 1;
        *byte_len -= rune_byte_len;
    }

    return status_ok(status);
}

static inline
bool strbase_truncate_runes(const char *data, size_t *len, size_t *byte_len,
                            size_t rune_count, Status *status) {
    char *cursor = NULL;
    ptrdiff_t new_byte_len = 0;

    if (!utf8_index_reverse(data, *byte_len, *len - rune_count, &cursor,
                                                                status)) {
        return false;
    }

    new_byte_len = cursor - data;

    if (new_byte_len < 0) {
        new_byte_len = 0;
    }

    *len = (*len - rune_count);
    *byte_len = new_byte_len;

    return status_ok(status);
}

static inline
bool strbase_truncate_rune(const char *data, size_t *len, size_t *byte_len,
                                                          Status *status) {
    return strbase_truncate_runes(data, len, byte_len, 1, status);
}

static inline
void strbase_clear(size_t *len, size_t *byte_len) {
    *len = 0;
    *byte_len = 0;
}

#endif

/* vi: set et ts=4 sw=4: */

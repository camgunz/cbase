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
    return strbase_equals(data, 0, byte_len, cs, 0, cs_byte_len);
}

static inline
bool strbase_equals_cstr(const char *data, size_t byte_len, const char *cs) {
    return strbase_equals_cstr_full(data, byte_len, cs, strlen(cs));
}

static inline
bool strbase_equals_utf8_data(const char *data1, size_t byte_len1,
                              const char *data2, size_t byte_len2) {
    return strbase_equals(data1, 0, byte_len1, data2, 0, byte_len2);
}

static inline
bool strbase_equals_utf8_slice(const char *data, size_t byte_len,
                                                 Slice *slice) {
    return strbase_equals_utf8_data(data, byte_len, slice->data, slice->len);
}

static inline
bool strbase_equals_utf8_buffer(const char *data, size_t byte_len,
                                                  Buffer *buffer) {
    return strbase_equals_utf8_data(
        data, byte_len, buffer->array.elements, buffer->array.len
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

bool strbase_encode(const char *data, size_t byte_len, const char *encoding,
                                                       Buffer *out,
                                                       Status *status);

static inline
bool strbase_localize(const char *data, size_t byte_len, Buffer *out,
                                                         Status *status) {
    return strbase_encode(data, byte_len, "wchar_t", out, status);
}

bool strbase_skip_runes_fast(char **data, size_t *len, size_t *byte_len,
                                                       size_t rune_count);
bool strbase_skip_runes(char **data, size_t *len, size_t *byte_len,
                                                  size_t rune_count,
                                                  Status *status);

static inline
void strbase_skip_rune_fast(char **data, size_t *len, size_t *byte_len) {
    strbase_skip_runes_fast(data, len, byte_len, 1);
}

static inline
bool strbase_skip_rune(char **data, size_t *len, size_t *byte_len,
                                                 Status *status) {
    return strbase_skip_runes(data, len, byte_len, 1, status);
}

/*
 * [TODO] strbase_skip_rune_* should be defined in terms of
 *        strbase_skip_runes_*, which should use strbase_iterate
 */

bool strbase_skip_rune_if_equals(char **data, size_t *len,
                                              size_t *byte_len,
                                              rune r,
                                              Status *status);

bool strbase_skip_rune_if_matches(char **data, size_t *len,
                                               size_t *byte_len,
                                               RuneMatchFunc *matches,
                                               Status *status);

static inline
bool strbase_skip_rune_if_alpha(char **data, size_t *len, size_t *byte_len,
                                                          Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_alpha, status
    );
}

static inline
bool strbase_skip_rune_if_hex_digit(char **data, size_t *len, size_t *byte_len,
                                                              Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_hex_digit, status
    );
}

static inline
bool strbase_skip_rune_if_digit(char **data, size_t *len, size_t *byte_len,
                                                          Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_digit, status
    );
}

static inline
bool strbase_skip_rune_if_oct_digit(char **data, size_t *len, size_t *byte_len,
                                                              Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_oct_digit, status
    );
}

static inline
bool strbase_skip_rune_if_bin_digit(char **data, size_t *len, size_t *byte_len,
                                                              Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_bin-digit, status
    );
}

static inline
bool strbase_skip_rune_if_alnum(char **data, size_t *len, size_t *byte_len,
                                                          Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_alnum, status
    );
}

static inline
bool strbase_skip_rune_if_whitespace(char **data, size_t *len,
                                                  size_t *byte_len,
                                                  Status *status) {
    return strbase_skip_rune_if_matches(
        data, len, byte_len, rune_is_whitespace, status
    );
}

static inline
bool strbase_pop_rune_if_alpha(char **data, size_t *len, size_t *byte_len,
                                                         rune *r,
                                                         Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_alpha, r, status
    );
}

static inline
bool strbase_pop_rune_if_hex_digit(char **data, size_t *len, size_t *byte_len,
                                                             rune *r,
                                                             Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_hex_digit, r, status
    );
}

static inline
bool strbase_pop_rune_if_digit(char **data, size_t *len, size_t *byte_len,
                                                         rune *r,
                                                         Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_digit, r, status
    );
}

static inline
bool strbase_pop_rune_if_oct_digit(char **data, size_t *len, size_t *byte_len,
                                                             rune *r,
                                                             Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_oct_digit, r, status
    );
}

static inline
bool strbase_pop_rune_if_bin_digit(char **data, size_t *len, size_t *byte_len,
                                                             rune *r,
                                                             Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_bin-digit, r, status
    );
}

static inline
bool strbase_pop_rune_if_alnum(char **data, size_t *len, size_t *byte_len,
                                                         rune *r,
                                                         Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_alnum, r, status
    );
}

static inline
bool strbase_pop_rune_if_whitespace(char **data, size_t *len,
                                                 size_t *byte_len,
                                                 rune *r,
                                                 Status *status) {
    return strbase_pop_rune_if_matches(
        data, len, byte_len, rune_is_whitespace, r, status
    );
}

bool strbase_seek_to_rune(char **data, size_t *len, size_t *byte_len,
                                                    rune r,
                                                    Status *status);
bool strbase_seek_to_utf8_data(char **data, size_t *len, size_t *byte_len,
                                                         const char *data2,
                                                         size_t *byte_len2,
                                                         Status *status);

static inline
bool strbase_seek_to_cstr(char **data, size_t *len, size_t *byte_len,
                                                    const char *cs,
                                                    Status *status) {
    return strbase_seek_to_utf8_data(
        data, len, byte_len, cs, strlen(cs), status
    );
}

bool strbase_seek_to_match(char **data, size_t *len, size_t *byte_len,
                                                     RuneMatchFunc matches,
                                                     Status *status) {
    
}

static inline
bool strbase_seek_to_whitespace(char **data, size_t *len,
                                             size_t *byte_len,
                                             RuneMatchFunc matches,
                                             Status *status);

bool strbase_seek_past_whitespace(char **data, size_t *len, size_t *byte_len, Status *status);

static inline
bool strbase_truncate_runes(char **data, size_t *len, size_t *byte_len,
                                                      size_t rune_count,
                                                      Status *status) {
    return strbase_truncate_runes(data, len, byte_len, rune_count, status);
}

bool strbase_truncate_whitespace(char **data, size_t *len, size_t *byte_len,
                                                            Status *status);
bool strbase_truncate_at(char **data, size_t *len, size_t *byte_len, rune r, Status *status);
bool strbase_truncate_at_whitespace(char **data, size_t *len, size_t *byte_len, Status *status);
bool strbase_truncate_at_subslice(char **data, size_t *len, size_t *byte_len, SSlice *subslice,
                                                   Status *status);
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

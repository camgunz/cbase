#pragma once

#ifndef STRBASE_H__
#define STRBASE_H__

struct SSliceStruct;

enum {
    STRBASE_EMPTY = 1,
};

#define strbase_is_empty(status) status_failure( \
    status,                                      \
    "strbase",                                   \
    STRBASE_EMPTY,                               \
    "String data is empty"                       \
)

void strbase_assign_full(char *dst_data, size_t dst_len, size_t dst_byte_len,
                         char *src_data, size_t src_len, size_t src_byte_len);

bool strbase_assign_cstr(char **dst_data, size_t *len, size_t *byte_len,
                                                       char *cs,
                                                       Status *status);

bool strbase_empty(const char *data, size_t len, size_t byte_len);

bool strbase_equals(const char *data1, size_t len1, size_t byte_len1,
                    const char *data2, size_t len2, size_t byte_len2);

bool strbase_equals_cstr_full(const char *data, size_t byte_len,
                                                const char *cs,
                                                size_t cs_byte_len);

bool strbase_equals_cstr(const char *data, size_t byte_len, const char *cs);

bool strbase_equals_utf8_data(const char *data1, size_t byte_len1,
                              const char *data2, size_t byte_len2);

bool strbase_equals_utf8_slice(const char *data, size_t byte_len,
                                                 Slice *slice);

bool strbase_equals_utf8_buffer(const char *data, size_t byte_len,
                                                  Buffer *buffer);

void strbase_copy(char **dst_data, size_t *dst_len, size_t *dst_byte_len,
                  const char *src_data, size_t src_len, size_t src_byte_len);

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

bool strbase_encode(const char *data, size_t byte_len, const char *encoding,
                                                       Buffer *out,
                                                       Status *status);


bool strbase_localize(const char *data, size_t byte_len, Buffer *out,
                                                         Status *status);

void strbase_skip_runes_fast(char **data, size_t *len, size_t *byte_len,
                                                       size_t rune_count);

bool strbase_skip_runes(char **data, size_t *len, size_t *byte_len,
                                                  size_t rune_count,
                                                  Status *status);

void strbase_skip_rune_fast(char **data, size_t *len, size_t *byte_len);

bool strbase_skip_rune(char **data, size_t *len, size_t *byte_len,
                                                 Status *status);

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

bool strbase_skip_rune_if_alpha(char **data, size_t *len, size_t *byte_len,
                                                          Status *status);

bool strbase_skip_rune_if_hex_digit(char **data, size_t *len, size_t *byte_len,
                                                              Status *status);

bool strbase_skip_rune_if_digit(char **data, size_t *len, size_t *byte_len,
                                                          Status *status);

bool strbase_skip_rune_if_oct_digit(char **data, size_t *len, size_t *byte_len,
                                                              Status *status);

bool strbase_skip_rune_if_bin_digit(char **data, size_t *len, size_t *byte_len,
                                                              Status *status);

bool strbase_skip_rune_if_alnum(char **data, size_t *len, size_t *byte_len,
                                                          Status *status);

bool strbase_skip_rune_if_whitespace(char **data, size_t *len,
                                                  size_t *byte_len,
                                                  Status *status);

bool strbase_pop_rune(char **data, size_t *len, size_t *byte_len,
                                                rune *r,
                                                Status *status);

bool strbase_pop_rune_if_equals(char **data, size_t *len, size_t *byte_len,
                                                          rune r,
                                                          Status *status);

bool strbase_pop_rune_if_matches(char **data, size_t *len,
                                              size_t *byte_len,
                                              RuneMatchFunc *matches,
                                              rune *r,
                                              Status *status);

bool strbase_pop_rune_if_alpha(char **data, size_t *len, size_t *byte_len,
                                                         rune *r,
                                                         Status *status);

bool strbase_pop_rune_if_hex_digit(char **data, size_t *len, size_t *byte_len,
                                                             rune *r,
                                                             Status *status);

bool strbase_pop_rune_if_digit(char **data, size_t *len, size_t *byte_len,
                                                         rune *r,
                                                         Status *status);

bool strbase_pop_rune_if_oct_digit(char **data, size_t *len, size_t *byte_len,
                                                             rune *r,
                                                             Status *status);

bool strbase_pop_rune_if_bin_digit(char **data, size_t *len, size_t *byte_len,
                                                             rune *r,
                                                             Status *status);

bool strbase_pop_rune_if_alnum(char **data, size_t *len, size_t *byte_len,
                                                         rune *r,
                                                         Status *status);

bool strbase_pop_rune_if_whitespace(char **data, size_t *len,
                                                 size_t *byte_len,
                                                 rune *r,
                                                 Status *status);

bool strbase_seek_to_rune(char **data, size_t *len, size_t *byte_len,
                                                    rune r,
                                                    Status *status);

bool strbase_seek_to_utf8_data(char **data, size_t *len, size_t *byte_len,
                                                         const char *data2,
                                                         size_t byte_len2,
                                                         Status *status);

bool strbase_seek_to_cstr(char **data, size_t *len, size_t *byte_len,
                                                    const char *cs,
                                                    Status *status);

bool strbase_seek_to_match(char **data, size_t *len, size_t *byte_len,
                                                     RuneMatchFunc matches,
                                                     Status *status);

bool strbase_seek_to_whitespace(char **data, size_t *len,
                                             size_t *byte_len,
                                             Status *status);

bool strbase_seek_past_whitespace(char **data, size_t *len, size_t *byte_len,
                                                            Status *status);

bool strbase_truncate_runes(const char *data, size_t *len, size_t *byte_len,
                            size_t rune_count, Status *status);
bool strbase_truncate_whitespace(char **data, size_t *len, size_t *byte_len,
                                                           Status *status);

bool strbase_truncate_at(char **data, size_t *len, size_t *byte_len,
                                                   rune r,
                                                   Status *status);

bool strbase_truncate_at_whitespace(char **data, size_t *len, size_t *byte_len,
                                                              Status *status);

bool strbase_truncate_at_subslice(char **data, size_t *len,
                                               size_t *byte_len,
                                               struct SSliceStruct *subslice,
                                               Status *status);

bool strbase_truncate_rune(const char *data, size_t *len, size_t *byte_len,
                                                          Status *status);

void strbase_clear(size_t *len, size_t *byte_len);

#endif

/* vi: set et ts=4 sw=4: */

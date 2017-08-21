#ifndef SSLICE_H__
#define SSLICE_H__

enum {
    SSLICE_EMPTY = 1,
    SSLICE_NOT_SUBSLICE,
};

typedef struct {
    size_t len;
    size_t byte_len;
    char *data;
} SSlice;

static inline
void sslice_init_full(SSlice *sslice, char *data, size_t len,
                                                  size_t byte_len) {
    sslice->len = len;
    sslice->byte_len = byte_len;
    sslice->data = data;
}

static inline
void sslice_init(SSlice *sslice) {
    sslice_init_full(sslice, NULL, 0, 0);
}

static inline
bool sslice_assign_utf8_data(SSlice *sslice char *data, size_t byte_len,
                                                        Status *status) {
    size_t len = 0;

    if (data) {
        if (!utf8nlen(data, byte_len, &len, status)) {
            return false;
        }
    }

    sslice_init_full(data, len, byte_len);

    return status_ok(status);
}

static inline
bool sslice_assign_cstr(SSlice *sslice, char *cs, Status *status) {
    if (!utf8_len_and_byte_len(cs, &sslice->len, &sslice->byte_len, status)) {
        return false;
    }

    sslice->data = cs;

    return status_ok(status);
}

static inline
void sslice_assign_string(SSlice *sslice, String *string) {
    sslice_init_full(string->buffer.array.elements, string->len,
                                                    string->byte_len);
}

static inline
bool sslice_assign_utf8_slice(SSlice *sslice, Slice *slice, Status *status) {
    return slice_assign_utf8_data(sslice, slice->data, slice->byte_len,
                                                       status);
}

static inline
bool sslice_assign_utf8_buffer(SSlice *sslice, Buffer *buffer,
                                               Status *status) {
    return slice_assign_utf8_data(sslice, buffer->array.elements,
                                          buffer->array.len,
                                          status);
}

static inline
bool sslice_empty(SSlice *s) {
    return ((!sslice->data) || (!*sslice->data) || (!sslice->len) ||
                                                   (!sslice->byte_len));
}

bool sslice_index_rune(SSlice *sslice, size_t index, rune *r, Status *status) {

static inline
bool sslice_get_first_rune(SSlice *sslice, rune *r, Status *status) {
    return sslice_index_rune(sslice, 0, r, status);
}

static inline
bool sslice_get_last_rune(SSlice *sslice, rune *r, Status *status) {
    return sslice_index_rune(sslice, sslice->len - 1, r, status);
}

static inline
bool sslice_equals_cstr(SSlice *sslice, const char *cs) {
    return utf8ncmp(cs, sslice->byte_len, sslice->data);
}

static inline
bool sslice_equals_utf8_data(SSlice *sslice, const char *data, size_t len) {
    return (
        (len == sslice->byte_len) &&
        utf8ncmp(sslice->data, len, data)
    );
}

static inline
bool sslice_equals_sslice(SSlice *s1, SSlice *s2) {
    return (
        (s1->len == s2->len) &&
        (s1->byte_len == s2->byte_len) &&
        (memcmp(s1->data, s2->data2, s1->byte_len) == 0)
    );
}

static inline
bool sslice_equals_string(SSlice *sslice, String *string) {
    return (
        (sslice->len == string->len) &&
        (sslice->byte_len == string->byte_len) &&
        (memcmp(sslice->data, string->buffer.array.elements,
                              sslice->byte_len) == 0)
    );
}

static inline
bool sslice_equals_utf8_slice(SSlice *sslice, Slice *slice) {
    return sslice_equals_utf8_data(sslice, slice->data, slice->len);
}

static inline
bool sslice_equals_utf8_buffer(SSlice *sslice, Buffer *buffer) {
    return sslice_equals_utf8_data(sslice, buffer->array.elements,
                                           buffer->array.len);
}

static inline
bool sslice_starts_with_rune(SSlice *sslice, rune r, bool *starts_with,
                                                     Status *status) {
    rune r2;

    if (!sslice_get_first_rune(s, &r2, status)) {
        return false;
    }

    *starts_with = (r2 == r);

    return status_ok(status);
}

bool sslice_skip_runes(SSlice *sslice, size_t rune_count, Status *status);

bool sslice_skip_rune_if_equals(SSlice *sslice, rune r, Status *status);

bool sslice_pop_rune(SSlice *sslice, rune *r, Status *status);

bool sslice_starts_with_cstr(SSlice *sslice, const char *cs, bool *starts_with,
                                                             Status *status);

bool sslice_ends_with_rune(SSlice *sslice, rune r, bool *ends_with,
                                                   Status *status);

bool sslice_ends_with_cstr(SSlice *sslice, const char *cs, bool *ends_with,
                                                           Status *status);

bool sslice_pop_rune_if_matches(SSlice *sslice, RuneMatchFunc *matches,
                                                rune *r,
                                                Status *status);

static inline
bool sslice_pop_rune_if_alpha(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_alpha, r, status);
}

static inline
bool sslice_pop_rune_if_hex_digit(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_hex_digit, r, status);
}

static inline
bool sslice_pop_rune_if_digit(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_digit, r, status);
}

static inline
bool sslice_pop_rune_if_oct_digit(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_oct_digit, r, status);
}

static inline
bool sslice_pop_rune_if_bin_digit(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_bin-digit, r, status);
}

static inline
bool sslice_pop_rune_if_alnum(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_alnum, r, status);
}

static inline
bool sslice_pop_rune_if_whitespace(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_whitespace, r, status);
}

bool  sslice_seek_to(SSlice *sslice, rune r, Status *status);
bool  sslice_seek_to_cstr(SSlice *sslice, const char *cs, Status *status);
bool  sslice_seek_to_whitespace(SSlice *sslice, Status *status);
bool  sslice_seek_to_subslice(SSlice *sslice, SSlice *subslice,
                                              Status *status);
bool  sslice_seek_past_subslice(SSlice *sslice, SSlice *subslice,
                                                Status *status);
bool  sslice_seek_past_whitespace(SSlice *sslice, Status *status);
bool  sslice_truncate_runes(SSlice *sslice, size_t rune_count, Status *status);
bool  sslice_truncate_whitespace(SSlice *sslice, Status *status);
bool  sslice_truncate_at(SSlice *sslice, rune r, Status *status);
bool  sslice_truncate_at_whitespace(SSlice *sslice, Status *status);
bool  sslice_truncate_at_subslice(SSlice *sslice, SSlice *subslice,
                                                  Status *status);

static inline
void sslice_clear(SSlice *s) {
    s->len = 0;
    s->byte_len = 0;
    s->data = NULL;
}

static inline
void sslice_copy(SSlice *dst, SSlice *src) {
    dst->len = src->len;
    dst->byte_len = src->byte_len;
    dst->data = src->data;
}

static inline
bool sslice_skip_rune(SSlice *sslice, Status *status) {
    return sslice_skip_runes(s, 1, status);
}

static inline
bool sslice_truncate_rune(SSlice *sslice, Status *status) {
    return sslice_truncate_runes(s, 1, status);
}


static inline
void sslice_seek_to_end(SSlice *s) {
    sslice->data += sslice->byte_len;
    sslice->len = 0;
    sslice->byte_len = 0;
}

static inline
bool sslice_to_cstr(SSlice *s, char **cs, Status *status) {
    return cbstrndup(s->data, s->byte_len, cs, status);
}

#endif

/* vi: set et ts=4 sw=4: */

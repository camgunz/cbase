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

bool  sslice_init_from_cstr(SSlice *s, char *cs, Status *status);
bool  sslice_skip_rune_if_equals(SSlice *s, rune r, Status *status);
bool  sslice_pop_rune(SSlice *s, rune *r, Status *status);
bool  sslice_first_rune_equals(SSlice *s, rune r, Status *status);
bool  sslice_pop_rune_if_alpha(SSlice *s, rune *r, Status *status);
bool  sslice_pop_rune_if_hex_digit(SSlice *s, rune *r, Status *status);
bool  sslice_pop_rune_if_digit(SSlice *s, rune *r, Status *status);
bool  sslice_pop_rune_if_oct_digit(SSlice *s, rune *r, Status *status);
bool  sslice_pop_rune_if_bin_digit(SSlice *s, rune *r, Status *status);
bool  sslice_pop_rune_if_whitespace(SSlice *s, rune *r, Status *status);
bool  sslice_pop_rune_if_alnum(SSlice *s, rune *r, Status *status);
bool  sslice_seek_to(SSlice *s, rune r, Status *status);
bool  sslice_seek_to_cstr(SSlice *s, const char *cs, Status *status);
bool  sslice_seek_to_whitespace(SSlice *s, Status *status);
bool  sslice_seek_to_subslice(SSlice *s, SSlice *subslice, Status *status);
bool  sslice_seek_past_subslice(SSlice *s, SSlice *subslice, Status *status);
bool  sslice_seek_past_whitespace(SSlice *s, Status *status);
bool  sslice_truncate_runes(SSlice *s, size_t rune_count, Status *status);
bool  sslice_truncate_whitespace(SSlice *s, Status *status);
bool  sslice_truncate_at(SSlice *s, rune r, Status *status);
bool  sslice_truncate_at_whitespace(SSlice *s, Status *status);
bool  sslice_truncate_at_subslice(SSlice *s, SSlice *subslice, Status *status);
char* sslice_to_cstr(SSlice *s);

static inline bool sslice_empty(SSlice *s) {
    return sbuffer_empty(s->len, s->byte_len);
}

static inline void sslice_clear(SSlice *s) {
    sbuffer_clear(&s->len, &s->byte_len);
}

static inline bool sslice_equals(SSlice *s1, SSlice *s2) {
    return sbuffer_equals(
        s1->data, s1->len, s1->byte_len,
        s2->data, s2->len, s2->byte_len
    );
}

static inline bool sslice_equals_cstr(SSlice *s, const char *cs) {
    return sbuffer_equals_cstr(s->data, cs);
}

static inline void sslice_copy(SSlice *dst, SSlice *src) {
    return sbuffer_copy(
        &dst->data, &dst->len, &dst->byte_len,
        src->data, src->len, src->byte_len
    );
}

static inline bool sslice_get_first_rune(SSlice *s, rune *r, Status *status) {
    return sbuffer_get_first_rune(s->data, r, status);
}

static inline bool sslice_starts_with(SSlice *s, rune r, bool *starts_with,
                                                         Status *status) {
    return sbuffer_starts_with(s->data, r, starts_with, status);
}

static inline bool sslice_starts_with_cstr(SSlice *s, const char *cs,
                                                      bool *starts_with,
                                                      Status *status) {
    return sbuffer_starts_with_cstr(
        s->data,
        s->byte_len,
        cs,
        starts_with,
        status
    );
}

static inline bool sslice_ends_with(SSlice *s, rune r, bool *ends_with,
                                                       Status *status) {
    return sbuffer_ends_with(s->data, s->byte_len, r, ends_with, status);
}

static inline bool sbuffer_ends_with_cstr(SSlice *s, const char *cs,
                                                     bool *ends_with,
                                                     Status *status) {
    return sbuffer_ends_with_cstr(s->data, s->byte_len, cs, ends_with, status);
}

static inline bool sslice_skip_runes(SSlice *s, size_t rune_count,
                                                Status *status) {
    return sslice_skip_runes(&s->data, &s->len, &s->byte_len, rune_count,
                                                              status);
}

static inline bool sslice_skip_rune(SSlice *s, Status *status) {
    return sslice_skip_runes(s, 1, status);
}

static inline bool slice_truncate_runes(SSlice *s, size_t rune_count,
                                                   Status *status) {
    return sbuffer_truncate_runes(s->data, &s->len, &s->byte_len, rune_count,
                                                                  status);
}

static inline bool sslice_truncate_rune(SSlice *s, Status *status) {
    return sslice_truncate_runes(s, 1, status);
}

static inline bool sslice_skip_rune_if_equals(SSlice *s, rune r,
                                                         Status *status) {
    return sbuffer_skip_rune_if_equals(&s->data, &s->len, &s->byte_len,
                                                          r,
                                                          status);
}

static inline bool sslice_pop_rune(SSlice *s, rune *r, Status *status) {
    return sbuffer_pop_rune(&s->data, &s->len, &s->byte_len, r, status);
}


static inline bool sslice_pop_rune_if_matches(SSlice *s,
                                              RuneMatchFunc *matches,
                                              rune *r,
                                              Status *status) {
    return sbuffer_pop_rune_if_matches(&s->data, &s->len, &s->byte_len,
                                                          matches,
                                                          r,
                                                          status);
}

static inline bool sslice_seek_to(SSlice *s, rune r, Status *status) {
    return sbuffer_seek_to(&s->data, &s->len, &s->byte_len, r, status);
}

static inline bool sslice_seek_to_cstr(SSlice *s, const char *cs,
                                                  Status *status) {
    return sbuffer_seek_to_cstr(&s->data, &s->len, &s->byte_len, cs, status);
}

static inline void sslice_seek_to_end(SSlice *s) {
    sbuffer_seek_to_end(&s->data, &s->len, &s->byte_len);
}

#endif

/* vi: set et ts=4 sw=4: */

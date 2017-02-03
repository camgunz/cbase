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

bool  sslice_starts_with_cstr(SSlice *s, const char *cs);
bool  sslice_get_first_rune(SSlice *s, rune *r, Status *status);
bool  sslice_skip_rune(SSlice *s, Status *status);
bool  sslice_skip_runes(SSlice *s, size_t rune_count, Status *status);
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
    return (
        s->len == 0 &&
        s->byte_len == 0 &&
        s->data == NULL
    );
}

static inline void sslice_clear(SSlice *s) {
    s->len = 0;
    s->byte_len = 0;
}

static inline bool sslice_equals_cstr(SSlice *s, const char *cs) {
    return utf8ncmp(s->data, cs, s->byte_len) && cs[s->byte_len] == '\0';
}

static inline bool sslice_equals(SSlice *s1, SSlice *s2) {
    return (
        (s1->len == s2->len) &&
        (s1->byte_len == s2->byte_len) &&
        (utf8ncmp(s1->data, s2->data, s1->byte_len))
    );
}

static inline void sslice_copy(SSlice *dst, SSlice *src) {
    dst->len = src->len;
    dst->byte_len = src->byte_len;
    dst->data = src->data;
}

static inline bool sslice_truncate_rune(SSlice *s, Status *status) {
    return sslice_truncate_runes(s, 1, status);
}

#endif

/* vi: set et ts=4 sw=4: */

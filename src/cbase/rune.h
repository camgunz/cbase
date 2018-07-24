#ifndef RUNE_H__
#define RUNE_H__

typedef int32_t rune;

typedef bool(RuneMatchFunc)(rune r);

bool  rune_is_alpha(rune r);
bool  rune_is_hex_digit(rune r);
bool  rune_is_digit(rune r);
bool  rune_is_oct_digit(rune r);
bool  rune_is_bin_digit(rune r);

static inline
bool rune_is_alnum(rune r) {
    return rune_is_alpha(r) || rune_is_digit(r);
}

bool  rune_is_whitespace(rune r);
char* runedup(rune r);

#endif

/* vi: set et ts=4 sw=4: */


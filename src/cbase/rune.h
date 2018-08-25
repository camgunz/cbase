#pragma once

#ifndef RUNE_H__
#define RUNE_H__

typedef int32_t rune;

typedef bool(RuneMatchFunc)(rune r);

bool  rune_is_alpha(rune r);
bool  rune_is_hex_digit(rune r);
bool  rune_is_digit(rune r);
bool  rune_is_oct_digit(rune r);
bool  rune_is_bin_digit(rune r);
bool  rune_is_alnum(rune r);
bool  rune_is_whitespace(rune r);
bool  rune_equals_rune(rune r1, rune r2);
bool  rune_to_string(rune r, char **out, Status *status);

#endif

/* vi: set et ts=4 sw=4: */


#pragma once

#ifndef _CBASE_RUNE_H__
#define _CBASE_RUNE_H__

#include "cbase/internal.h"

#include <stdint.h>

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#include <utf8proc.h>

#include "cbase/errors.h"
#include "cbase/alloc.h"
#include "cbase/utf8_base.h"

typedef int32_t rune;

typedef bool(RuneMatchFunc)(rune r);

CBASE_API_STATIC
bool rune_is_digit(rune r) {
    return utf8proc_category(r) == UTF8PROC_CATEGORY_ND;
}

CBASE_API_STATIC
bool rune_is_hex_digit(rune r) {
    switch (r) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'a':
        case 'A':
        case 'b':
        case 'B':
        case 'c':
        case 'C':
        case 'd':
        case 'D':
        case 'e':
        case 'E':
        case 'f':
        case 'F':
            return true;
        default:
            break;
    }

    return false;
}

CBASE_API_STATIC
bool rune_is_not_hex_digit(rune r) {
    return !rune_is_hex_digit(r);
}

CBASE_API_STATIC
bool rune_is_oct_digit(rune r) {
    switch (r) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
            return true;
        default:
            break;
    }

    return false;
}

CBASE_API_STATIC
bool rune_is_not_oct_digit(rune r) {
    return !rune_is_oct_digit(r);
}

CBASE_API_STATIC
bool rune_is_bin_digit(rune r) {
    switch (r) {
        case '0':
        case '1':
            return true;
        default:
            break;
    }

    return false;
}

CBASE_API_STATIC
bool rune_is_not_bin_digit(rune r) {
    return !rune_is_bin_digit(r);
}

CBASE_API_STATIC
bool rune_is_alpha(rune r) {
    utf8proc_category_t category = utf8proc_category(r);

    switch (category) {
        case UTF8PROC_CATEGORY_LU:
        case UTF8PROC_CATEGORY_LL:
        case UTF8PROC_CATEGORY_LT:
        case UTF8PROC_CATEGORY_LM:
        case UTF8PROC_CATEGORY_LO:
            return true;
        default:
            return false;
    }
}

CBASE_API_STATIC
bool rune_is_not_alpha(rune r) {
    return !rune_is_alpha(r);
}

CBASE_API_STATIC
bool rune_is_alnum(rune r) {
    return rune_is_alpha(r) || rune_is_digit(r);
}

CBASE_API_STATIC
bool rune_is_not_alnum(rune r) {
    return !rune_is_alnum(r);
}

CBASE_API_STATIC
bool rune_is_blankspace(rune r) {
    utf8proc_category_t category = utf8proc_category(r);

    switch (category) {
        case UTF8PROC_CATEGORY_ZS:
        case UTF8PROC_CATEGORY_ZL:
        case UTF8PROC_CATEGORY_ZP:
            return true;
        default:
            break;
    }

    switch (r) {
        case '\t':
        case '\r':
        case '\n':
            return true;
        default:
            break;
    }

    return false;
}

CBASE_API_STATIC
bool rune_is_not_blankspace(rune r) {
    return !rune_is_blankspace(r);
}

CBASE_API_STATIC
bool rune_equals_rune(rune r1, rune r2) {
    return r1 == r2;
}

CBASE_API_STATIC
bool rune_not_equals_rune(rune r1, rune r2) {
    return !rune_equals_rune(r1, r2);
}

CBASE_API_STATIC
int rune_encode(rune r, char buf[4], size_t *rune_byte_len) {
    ssize_t bytes_written;

    bytes_written = utf8proc_encode_char(r, (uint8_t *)&buf[0]);

    if (bytes_written < 1) {
        return utf8_handle_error_code(bytes_written);
    }

    *rune_byte_len = (size_t)bytes_written;

    return 0;
}

CBASE_API_STATIC
int rune_to_cstr(rune r, char buf[5]) {
    ssize_t bytes_written;

    bytes_written = utf8proc_encode_char(r, (uint8_t *)&buf[0]);

    if (bytes_written < 1) {
        return utf8_handle_error_code(bytes_written);
    }

    for (size_t i = (size_t)bytes_written; i < 5; i++) {
        buf[i] = '\0';
    }

    return 0;
}

#endif

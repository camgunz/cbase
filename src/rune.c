#include <utf8proc.h>

#include "cbase.h"

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

bool rune_is_digit(rune r) {
    return utf8proc_category(r) == UTF8PROC_CATEGORY_ND;
}

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

bool rune_is_whitespace(rune r) {
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

/* vi: set et ts=4 sw=4: */


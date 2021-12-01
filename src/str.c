#include "cbase/internal.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "cbase/array_slice.h"
#include "cbase/charset.h"
#include "cbase/errors.h"
#include "cbase/rune.h"
#include "cbase/utf8.h"
#include "cbase/str.h"

int string_assign_transcoded_data(String *string,
                                  const char *src,
                                  size_t byte_len,
                                  const char *src_encoding) {
    while (true) {
        size_t len = string->alloc;

        int error = charset_convert_data(src,
                                         byte_len,
                                         src_encoding,
                                         "utf-8",
                                         string->data,
                                         &len);
        if (!error) {
            string->len = len;
            break;
        }

        if (error != CBASE_CHARSET_OUTPUT_BUFFER_TOO_SMALL) {
            CBASE_PROPAGATE_ERROR(error);
        }

        CBASE_PROPAGATE_ERROR(
            string_ensure_capacity(string, string->alloc * 2));
    }

    return 0;
}

int string_index_rune(String *string, size_t rune_index, rune *r) {
    return utf8_index_rune(string->data, string->len, rune_index, r);
}

int string_index_rune_reverse(String *string, size_t rune_index, rune *r) {
    return utf8_index_rune_reverse(string->data, string->len, rune_index, r);
}

int string_get_first_rune(String *string, rune *r) {
    return string_index_rune(string, 0, r);
}

int string_get_last_rune(String *string, rune *r) {
    return string_index_rune_reverse(string, 0, r);
}

int string_starts_with_rune(String *string, rune r, bool *starts_with) {
    return utf8_starts_with_rune(string->data, string->len, r, starts_with);
}

int string_ends_with_rune(String *string, rune r, bool *ends_with) {
    return utf8_ends_with_rune(string->data, string->len, r, ends_with);
}

void string_slice_runes_fast(String *string,
                             size_t rune_index,
                             size_t rune_count,
                             SSlice *sslice) {
    char *start = NULL;
    char *end = NULL;

    utf8_slice_fast(string->data,
                    string->len,
                    rune_index,
                    rune_count,
                    &start,
                    &end);

    sslice_assign(sslice, start, positive_ptrdiff(start, end));
}

int string_slice_runes(String *string,
                       size_t index,
                       size_t len,
                       SSlice *sslice) {
    char *start = NULL;
    char *end = NULL;

    CBASE_PROPAGATE_ERROR(
        utf8_slice(string->data, string->len, index, len, &start, &end));

    sslice_assign(sslice, start, positive_ptrdiff(start, end));

    return 0;
}

void string_delete_runes_fast(String *string,
                              size_t index,
                              size_t rune_count) {
    char *start = string->data;
    size_t byte_index = 0;

    if (!rune_count) {
        return;
    }

    if (index) {
        utf8_index_fast(string->data, string->len, index, &start);
        byte_index = start - (char *)string->data;
    }

    size_t temp_len = string->len - byte_index;

    utf8_skip_runes_fast(&start, &temp_len, rune_count);

    string_delete_many_fast(string, byte_index, temp_len);
}

int string_delete_runes(String *string, size_t index, size_t rune_count) {
    char *start = string->data;
    size_t byte_index = 0;

    if (!rune_count) {
        return 0;
    }

    if (index) {
        CBASE_PROPAGATE_ERROR(
            utf8_index(string->data, string->len, index, &start));

        byte_index = start - (char *)string->data;
    }

    size_t temp_len = string->len - byte_index;

    CBASE_PROPAGATE_ERROR(utf8_skip_runes(&start, &temp_len, rune_count));
    CBASE_PROPAGATE_ERROR(string_delete_many(string, byte_index, temp_len));

    return 0;
}

void string_delete_rune_fast(String *string, size_t index) {
    string_delete_runes_fast(string, index, 1);
}

int string_delete_rune(String *string, size_t index) {
    return string_delete_runes(string, index, 1);
}

int string_skip_rune(String *string) {
    return string_delete_runes(string, 0, 1);
}

int string_skip_runes(String *string, size_t rune_count) {
    return string_delete_runes(string, 0, rune_count);
}

int string_skip_rune_if_equals(String *string, rune r) {
    rune r2;

    CBASE_PROPAGATE_ERROR(string_get_first_rune(string, &r2));

    CBASE_ERROR_IF((r2 != r), CBASE_ERROR_NOT_EQUAL);

    return string_skip_rune(string);
}

int string_pop_rune(String *string, rune *r) {
    CBASE_PROPAGATE_ERROR(string_get_first_rune(string, r));
    CBASE_PROPAGATE_ERROR(string_skip_rune(string));

    return 0;
}

int string_pop_rune_if_matches(String *string,
                               RuneMatchFunc *matches,
                               rune *r) {
    rune r2 = 0;

    CBASE_PROPAGATE_ERROR(utf8_get_first_rune(string->data, string->len, &r2));

    CBASE_ERROR_IF((!matches(r2)), CBASE_ERROR_NOT_FOUND);

    *r = r2;

    return string_skip_rune(string);
}

int string_skip_rune_if_matches(String *string, RuneMatchFunc *matches) {
    rune r = 0;

    return string_pop_rune_if_matches(string, matches, &r);
}

int string_seek_to_rune(String *string, rune r) {
}

int string_truncate_runes(String *string, size_t rune_count) {
}

int string_truncate_rune(String *string) {
}

CBASE_VPRINTF_FUNCTION(3)
int string_insert_vprintf(String *string,
                          size_t index,
                          const char *fmt,
                          va_list args) {
    va_list args2;
    int byte_size;

    CBASE_ERROR_IF((index > string->len), CBASE_ERROR_OUT_OF_BOUNDS);

    va_copy(args2, args);
    byte_size = vsnprintf(NULL, 0, fmt, args2);
    va_end(args2);

    CBASE_ERROR_IF((byte_size < 0), CBASE_STRING_VSNPRINTF_FAILED);

    CBASE_PROPAGATE_ERROR(
        string_ensure_capacity(string, string->len + (size_t)byte_size));

    char *cursor = string->data;
    size_t len = string->len;

    CBASE_PROPAGATE_ERROR(utf8_skip_runes(&cursor, &len, index));

    string_shift_data_right_fast_no_zero(string, index, (size_t)byte_size);

    int bytes_written = vsnprintf(cursor, byte_size + 1, fmt, args);

    CBASE_ERROR_IF((bytes_written != (byte_size - 1)),
                   CBASE_STRING_VSNPRINTF_FAILED);

    string->len += bytes_written;

    return 0;
}

CBASE_PRINTF_FUNCTION(3, 4)
int string_insert_printf(String *string, size_t index, const char *fmt, ...) {
    va_list args;
    int res = 0;

    va_start(args, fmt);
    res = string_insert_vprintf(string, index, fmt, args);
    va_end(args);

    return res;
}

CBASE_VPRINTF_FUNCTION(2)
int string_vprintf(String *string, const char *fmt, va_list args) {
    string_clear(string);
    return string_insert_vprintf(string, 0, fmt, args);
}

CBASE_PRINTF_FUNCTION(2, 3)
int string_printf(String *string, const char *fmt, ...) {
    va_list args;
    int res = 0;

    va_start(args, fmt);
    res = string_vprintf(string, fmt, args);
    va_end(args);

    return res;
}

CBASE_VPRINTF_FUNCTION(2)
int string_init_vprintf(String *string, const char *fmt, va_list args) {
    string_init(string);
    return string_vprintf(string, fmt, args);
}

CBASE_PRINTF_FUNCTION(2, 3)
int string_init_printf(String *string, const char *fmt, ...) {
    int res = 0;
    va_list args;

    va_start(args, fmt);
    res = string_init_vprintf(string, fmt, args);
    va_end(args);

    return res;
}

CBASE_VPRINTF_FUNCTION(2)
int string_new_vprintf(String **string, const char *fmt, va_list args) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(string_init_vprintf(*string, fmt, args),
                                   cbfree,
                                   *string);

    return 0;
}

CBASE_PRINTF_FUNCTION(2, 3)
int string_new_printf(String **string, const char *fmt, ...) {
    va_list args;
    int res = 0;

    va_start(args, fmt);
    res = string_new_vprintf(string, fmt, args);
    va_end(args);

    return res;
}

CBASE_VPRINTF_FUNCTION(2)
int string_prepend_vprintf(String *string, const char *fmt, va_list args) {
    return string_insert_vprintf(string, 0, fmt, args);
}

CBASE_PRINTF_FUNCTION(2, 3)
int string_prepend_printf(String *string, const char *fmt, ...) {
    va_list args;
    int res = 0;

    va_start(args, fmt);
    res = string_prepend_vprintf(string, fmt, args);
    va_end(args);

    return res;
}

CBASE_VPRINTF_FUNCTION(2)
int string_append_vprintf(String *string, const char *fmt, va_list args) {
    return string_insert_vprintf(string, string->len, fmt, args);
}

CBASE_PRINTF_FUNCTION(2, 3)
int string_append_printf(String *string, const char *fmt, ...) {
    va_list args;
    int res = 0;

    va_start(args, fmt);
    res = string_append_vprintf(string, fmt, args);
    va_end(args);

    return res;
}

/* vi: set et ts=4 sw=4: */

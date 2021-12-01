#include "cbase/internal.h"

#include <string.h>

#include <utf8proc.h>

#include "cbase/errors.h"
#include "cbase/data_slice.h"
#include "cbase/utf8.h"
#include "cbase/util.h"

/*
 * [TODO]
 * - Rebase on data_slice
 * - There should be utf8_find_* versions of the utf8_seek_* functions, and the
 *   utf8_seek_* functions should be defined in terms of those, just like
 *   utf8_find_data -> utf8_seek_to_data
 * - Expand `utf8_pop_*` to `pop_left` and `pop_right`
 * - Namespace everything here
 */

bool utf8_byte_is_sequence_start(char b) {
    return (b & 0xC0) != 0x80;
}

int utf8_validate_len_fast(const char *data, size_t byte_len, size_t *len) {
    const unsigned char *cursor = (const unsigned char *)data;
    size_t total_bytes_read = 0;
    size_t local_len = 0;

    while (total_bytes_read < byte_len) {
        rune r;
        ssize_t bytes_read = utf8proc_iterate(cursor, -1, &r);

        if (bytes_read < 1) {
            CBASE_ERROR(utf8_handle_error_code(bytes_read));
        }

        local_len++;
        total_bytes_read += bytes_read;
        cursor = (const unsigned char *)(data + total_bytes_read);
    }

    *len = local_len;

    return 0;
}

int utf8_validate_len(const char *data, size_t byte_len, size_t *len) {
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    return utf8_validate_len_fast(data, byte_len, len);
}

int utf8_validate_fast(const char *data, size_t byte_len) {
    const unsigned char *cursor = (const unsigned char *)data;
    size_t total_bytes_read = 0;

    while (total_bytes_read < byte_len) {
        rune r;
        ssize_t bytes_read = utf8proc_iterate(cursor, -1, &r);

        if (bytes_read < 1) {
            CBASE_ERROR(utf8_handle_error_code(bytes_read));
        }

        total_bytes_read += bytes_read;
        cursor = (const unsigned char *)(data + total_bytes_read);
    }

    return 0;
}

int utf8_validate(const char *data, size_t byte_len) {
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    return utf8_validate_fast(data, byte_len);
}

void utf8_len_fast(const char *data, size_t byte_len, size_t *len) {
    size_t rune_count = 0;

    for (size_t i = 0; i < byte_len; i++) {
        if (utf8_byte_is_sequence_start(data[i])) {
            rune_count++;
        }
    }

    *len = rune_count;
}

int utf8_len(const char *data, size_t byte_len, size_t *len) {
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    utf8_len_fast(data, byte_len, len);

    return 0;
}

void utf8_calc_rune_byte_len_fast(const char *data, size_t *rune_byte_len) {
    const unsigned char ubyte = *(const unsigned char *)data;

    if (ubyte < 0x80) {
        *rune_byte_len = 1;
    }
    else if (ubyte < 0xE0) {
        *rune_byte_len = 2;
    }
    else if (ubyte < 0xF0) {
        *rune_byte_len = 3;
    }
    else {
        *rune_byte_len = 4;
    }
}

void utf8_decode_fast(const char *data, rune *r) {
    const unsigned char *udata = (const unsigned char *)data;
    const unsigned char ubyte = *udata;

    if (ubyte < 0x80) {
        *r = ubyte;
    }
    else if (ubyte < 0xE0) {
        *r = ((ubyte & 0x1F) << 6) | (udata[1] & 0x3F);
    }
    else if (ubyte < 0xF0) {
        *r = ((ubyte & 0xF) << 12) | ((udata[1] & 0x3F) << 6) |
             (udata[2] & 0x3F);
    }
    else {
        *r = ((ubyte & 7) << 18) | ((udata[1] & 0x3F) << 12) |
             ((udata[2] & 0x3F) << 6) | (udata[3] & 0x3F);
    }
}

int utf8_decode(const char *data, size_t byte_len, rune *r) {
    CBASE_ERROR_IF(byte_len == 0, CBASE_UTF8_EMPTY);
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    utf8_decode_fast(data, r);

    return 0;
}

void utf8_decode_len_fast(const char *data, rune *r, size_t *rune_byte_len) {
    const unsigned char *udata = (const unsigned char *)data;
    const unsigned char ubyte = *udata;

    if (ubyte < 0x80) {
        *r = ubyte;
        *rune_byte_len = 1;
    }
    else if (ubyte < 0xE0) {
        *r = ((ubyte & 0x1F) << 6) | (udata[1] & 0x3F);
        *rune_byte_len = 2;
    }
    else if (ubyte < 0xF0) {
        *r = ((ubyte & 0xF) << 12) | ((udata[1] & 0x3F) << 6) |
             (udata[2] & 0x3F);
        *rune_byte_len = 3;
    }
    else {
        *r = ((ubyte & 7) << 18) | ((udata[1] & 0x3F) << 12) |
             ((udata[2] & 0x3F) << 6) | (udata[3] & 0x3F);
        *rune_byte_len = 4;
    }
}

int utf8_decode_len(const char *data,
                    size_t byte_len,
                    rune *r,
                    size_t *rune_byte_len) {
    CBASE_ERROR_IF(byte_len == 0, CBASE_UTF8_EMPTY);
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    utf8_decode_len_fast(data, r, rune_byte_len);

    return 0;
}

void utf8_index_fast(const char *data,
                     size_t byte_len,
                     size_t index,
                     char **cursor) {
    char *cursor2 = (char *)data;
    size_t clen = byte_len;

    while (index-- >= 0) {
        utf8_iterate_fast(&cursor2, &clen);
    }

    *cursor = cursor2;
}

int utf8_index(const char *data,
               size_t byte_len,
               size_t index,
               char **cursor) {
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    char *cursor2 = (char *)data;
    size_t clen = byte_len;

    while (index-- >= 0) {
        CBASE_PROPAGATE_ERROR(utf8_iterate(&cursor2, &clen));
    }

    *cursor = cursor2;

    return 0;
}

void utf8_index_rune_len_fast(const char *data,
                              size_t byte_len,
                              size_t index,
                              rune *r,
                              size_t *rune_byte_len) {
    char *cursor = (char *)data;
    size_t clen = byte_len;

    while (index-- > 0) {
        utf8_iterate_fast(&cursor, &clen);
    }

    utf8_iterate_rune_len_fast(&cursor, &clen, r, rune_byte_len);
}

int utf8_index_rune_len(const char *data,
                        size_t byte_len,
                        size_t index,
                        rune *r,
                        size_t *rune_byte_len) {
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    char *cursor = (char *)data;
    size_t clen = byte_len;
    rune r2 = 0;
    size_t rune_byte_len2 = 0;

    while (index-- > 0) {
        CBASE_PROPAGATE_ERROR(utf8_iterate(&cursor, &clen));
    }

    CBASE_PROPAGATE_ERROR(
        utf8_iterate_rune_len(&cursor, &clen, &r2, &rune_byte_len2));

    *r = r2;
    *rune_byte_len = rune_byte_len2;

    return 0;
}

void utf8_index_rune_fast(const char *data,
                          size_t byte_len,
                          size_t index,
                          rune *r) {
    char *cursor = (char *)data;
    size_t clen = byte_len;

    while (index-- > 0) {
        utf8_iterate_fast(&cursor, &clen);
    }

    utf8_iterate_rune_fast(&cursor, &clen, r);
}

int utf8_index_rune(const char *data, size_t byte_len, size_t index, rune *r) {
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    char *cursor = (char *)data;
    size_t clen = byte_len;
    rune r2 = 0;

    while (index-- > 0) {
        CBASE_PROPAGATE_ERROR(utf8_iterate(&cursor, &clen));
    }

    CBASE_PROPAGATE_ERROR(utf8_iterate_rune(&cursor, &clen, &r2));

    *r = r2;

    return 0;
}

void utf8_index_reverse_fast(const char *data,
                             size_t byte_len,
                             size_t index,
                             char **cursor) {
    char *cursor2 = (char *)data;
    size_t clen = byte_len;

    while (index-- >= 0) {
        utf8_iterate_reverse_fast(&cursor2, &clen);
    }

    *cursor = cursor2;
}

int utf8_index_reverse(const char *data,
                       size_t byte_len,
                       size_t index,
                       char **cursor) {
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    char *cursor2 = (char *)data;
    size_t clen = byte_len;

    while (index-- >= 0) {
        CBASE_PROPAGATE_ERROR(utf8_iterate_reverse(&cursor2, &clen));
    }

    *cursor = cursor2;

    return 0;
}

void utf8_index_rune_len_reverse_fast(const char *data,
                                      size_t byte_len,
                                      size_t index,
                                      rune *r,
                                      size_t *rune_byte_len) {
    char *cursor = (char *)data;
    size_t clen = byte_len;

    while (index-- > 0) {
        utf8_iterate_reverse_fast(&cursor, &clen);
    }

    utf8_iterate_rune_len_reverse_fast(&cursor, &clen, r, rune_byte_len);
}

int utf8_index_rune_len_reverse(const char *data,
                                size_t byte_len,
                                size_t index,
                                rune *r,
                                size_t *rune_byte_len) {
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    char *cursor = (char *)data;
    size_t clen = byte_len;
    rune r2 = 0;
    size_t rune_byte_len2 = 0;

    while (index-- > 0) {
        CBASE_PROPAGATE_ERROR(utf8_iterate_reverse(&cursor, &clen));
    }

    CBASE_PROPAGATE_ERROR(
        utf8_iterate_rune_len_reverse(&cursor, &clen, &r2, &rune_byte_len2));

    *r = r2;
    *rune_byte_len = rune_byte_len2;

    return 0;
}

void utf8_index_rune_reverse_fast(const char *data,
                                  size_t byte_len,
                                  size_t index,
                                  rune *r) {
    char *cursor = (char *)data;
    size_t clen = byte_len;

    while (index-- > 0) {
        utf8_iterate_reverse_fast(&cursor, &clen);
    }

    utf8_iterate_rune_reverse_fast(&cursor, &clen, r);
}

int utf8_index_rune_reverse(const char *data,
                            size_t byte_len,
                            size_t index,
                            rune *r) {
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    char *cursor = (char *)data;
    size_t clen = byte_len;
    rune r2 = 0;

    while (index-- > 0) {
        CBASE_PROPAGATE_ERROR(utf8_iterate_reverse(&cursor, &clen));
    }

    CBASE_PROPAGATE_ERROR(utf8_iterate_rune_reverse(&cursor, &clen, &r2));

    *r = r2;

    return 0;
}

void utf8_get_first_rune_len_fast(const char *data,
                                  rune *r,
                                  size_t *rune_byte_len) {
    utf8_decode_len_fast(data, r, rune_byte_len);
}

int utf8_get_first_rune_len(const char *data,
                            size_t byte_len,
                            rune *r,
                            size_t *rune_byte_len) {
    CBASE_ERROR_IF(byte_len == 0, CBASE_UTF8_EMPTY);
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    utf8_get_first_rune_len_fast(data, r, rune_byte_len);

    return 0;
}

void utf8_get_first_rune_fast(const char *data, rune *r) {
    utf8_decode_fast(data, r);
}

int utf8_get_first_rune(const char *data, size_t byte_len, rune *r) {
    CBASE_ERROR_IF(byte_len == 0, CBASE_UTF8_EMPTY);
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    utf8_get_first_rune_fast(data, r);

    return 0;
}

void utf8_get_last_rune_len_fast(const char *data,
                                 size_t byte_len,
                                 rune *r,
                                 size_t *rune_byte_len) {
    utf8_index_rune_len_reverse_fast(data, byte_len, 1, r, rune_byte_len);
}

int utf8_get_last_rune_len(const char *data,
                           size_t byte_len,
                           rune *r,
                           size_t *rune_byte_len) {
    CBASE_ERROR_IF(byte_len == 0, CBASE_UTF8_EMPTY);
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    utf8_get_last_rune_len_fast(data, byte_len, r, rune_byte_len);

    return 0;
}

void utf8_get_last_rune_fast(const char *data, size_t byte_len, rune *r) {
    utf8_index_rune_reverse_fast(data, byte_len, 1, r);
}

int utf8_get_last_rune(const char *data, size_t byte_len, rune *r) {
    CBASE_ERROR_IF(byte_len == 0, CBASE_UTF8_EMPTY);
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    utf8_get_last_rune_fast(data, byte_len, r);

    return 0;
}

void utf8_slice_fast(const char *data,
                     size_t byte_len,
                     size_t index,
                     size_t len,
                     char **start,
                     char **end) {
    utf8_index_fast(data, byte_len, index, start);
    utf8_index_fast(*start, byte_len, len, end);
}

int utf8_slice(const char *data,
               size_t byte_len,
               size_t index,
               size_t len,
               char **start,
               char **end) {
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    char *start2 = NULL;
    char *end2 = NULL;

    CBASE_PROPAGATE_ERROR(utf8_index(data, byte_len, index, &start2));
    CBASE_PROPAGATE_ERROR(utf8_index(start2, byte_len, len, &end2));

    *start = start2;
    *end = end2;

    return 0;
}

bool utf8_starts_with_rune_fast(const char *data, rune r) {
    rune r2 = 0;

    utf8_get_first_rune_fast(data, &r2);

    return r2 == r;
}

int utf8_starts_with_rune(const char *data,
                          size_t byte_len,
                          rune r,
                          bool *starts_with) {
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    rune r2 = 0;
    int error = utf8_get_first_rune(data, byte_len, &r2);

    switch (error) {
    case 0:
        *starts_with = r2 == r;

        return 0;
    case CBASE_UTF8_EMPTY:
        *starts_with = false;

        return 0;
    default:
        return error;
    }
}

bool utf8_ends_with_rune_fast(const char *data, size_t byte_len, rune r) {
    rune r2 = 0;

    utf8_get_last_rune_fast(data, byte_len, &r2);

    return r2 == r;
}

int utf8_ends_with_rune(const char *data,
                        size_t byte_len,
                        rune r,
                        bool *ends_with) {
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    rune r2 = 0;
    int error = utf8_get_last_rune(data, byte_len, &r2);

    switch (error) {
    case 0:
        *ends_with = r2 == r;
        return 0;
    case CBASE_UTF8_EMPTY:
        *ends_with = false;
        return 0;
    default:
        return error;
    }

    return 0;
}

void utf8_iterate_fast(char **data, size_t *byte_len) {
    size_t rune_byte_len = 0;

    utf8_calc_rune_byte_len_fast(*data, &rune_byte_len);
    *data += rune_byte_len;
    *byte_len -= rune_byte_len;
}

int utf8_iterate(char **data, size_t *byte_len) {
    CBASE_ERROR_IF(*byte_len == 0, CBASE_UTF8_EMPTY);
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    utf8_iterate_fast(data, byte_len);

    return 0;
}

void utf8_iterate_rune_len_fast(char **data,
                                size_t *byte_len,
                                rune *r,
                                size_t *rune_byte_len) {
    utf8_decode_len_fast(*data, r, rune_byte_len);
    *data += *rune_byte_len;
    *byte_len -= *rune_byte_len;
}

int utf8_iterate_rune_len(char **data,
                          size_t *byte_len,
                          rune *r,
                          size_t *rune_byte_len) {
    CBASE_ERROR_IF(*byte_len == 0, CBASE_UTF8_EMPTY);
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    utf8_iterate_rune_len_fast(data, byte_len, r, rune_byte_len);

    return 0;
}

void utf8_iterate_rune_fast(char **data, size_t *byte_len, rune *r) {
    size_t rune_byte_len = 0;

    utf8_decode_len_fast(*data, r, &rune_byte_len);
    *data += rune_byte_len;
    *byte_len -= rune_byte_len;
}

int utf8_iterate_rune(char **data, size_t *byte_len, rune *r) {
    CBASE_ERROR_IF(*byte_len == 0, CBASE_UTF8_EMPTY);
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    utf8_iterate_rune_fast(data, byte_len, r);

    return 0;
}

void utf8_iterate_reverse_fast(char **data, size_t *byte_len) {
    for (size_t i = 1; i <= 4; i++) {
        char *start = ((*data) + (*byte_len) - i);

        if (utf8_byte_is_sequence_start(*start)) {
            *data = start;
            *byte_len -= i;
            break;
        }
    }
}

int utf8_iterate_reverse(char **data, size_t *byte_len) {
    CBASE_ERROR_IF(*byte_len == 0, CBASE_UTF8_EMPTY);
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    for (size_t i = 1; i <= 4; i++) {
        char *start = ((*data) + (*byte_len) - i);

        if (utf8_byte_is_sequence_start(*start)) {
            *data = start;
            *byte_len -= i;

            return 0;
        }
    }

    CBASE_ERROR(CBASE_UTF8_INVALID_UTF8);
}

void utf8_iterate_rune_len_reverse_fast(char **data,
                                        size_t *byte_len,
                                        rune *r,
                                        size_t *rune_byte_len) {
    for (size_t i = 1; i <= 4; i++) {
        char *start = ((*data) + (*byte_len) - i);

        if (utf8_byte_is_sequence_start(*start)) {
            utf8_decode_len_fast(start, r, rune_byte_len);
            *data = start;
            *byte_len -= i;
            break;
        }
    }
}

int utf8_iterate_rune_len_reverse(char **data,
                                  size_t *byte_len,
                                  rune *r,
                                  size_t *rune_byte_len) {
    CBASE_ERROR_IF(*byte_len == 0, CBASE_UTF8_EMPTY);
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    for (size_t i = 1; i <= 4; i++) {
        char *start = ((*data) + (*byte_len) - i);

        if (utf8_byte_is_sequence_start(*start)) {
            CBASE_PROPAGATE_ERROR(utf8_decode_len(start, 1, r, rune_byte_len));
            *data = start;
            *byte_len -= i;

            return 0;
        }
    }

    CBASE_ERROR(CBASE_UTF8_INVALID_UTF8);
}

void utf8_iterate_rune_reverse_fast(char **data, size_t *byte_len, rune *r) {
    for (size_t i = 1; i <= 4; i++) {
        char *start = ((*data) + (*byte_len) - i);

        if (utf8_byte_is_sequence_start(*start)) {
            utf8_decode_fast(start, r);
            *data = start;
            *byte_len -= i;
            break;
        }
    }
}

int utf8_iterate_rune_reverse(char **data, size_t *byte_len, rune *r) {
    CBASE_ERROR_IF(*byte_len == 0, CBASE_UTF8_EMPTY);
    CBASE_ERROR_IF(data == NULL, CBASE_ERROR_NULL_POINTER);

    for (size_t i = 1; i <= 4; i++) {
        char *start = ((*data) + (*byte_len) - i);

        if (utf8_byte_is_sequence_start(*start)) {
            CBASE_PROPAGATE_ERROR(utf8_decode(start, 1, r));
            *data = start;
            *byte_len -= i;

            return 0;
        }
    }

    CBASE_ERROR(CBASE_UTF8_INVALID_UTF8);
}

void utf8_skip_runes_fast(char **data, size_t *len, size_t rune_count) {
    char *cursor = NULL;

    utf8_index_fast(*data, *len, rune_count, &cursor);

    *len = cursor - *data;
    *data = cursor;
}

int utf8_skip_runes(char **data, size_t *len, size_t rune_count) {
    CBASE_ERROR_IF((*len > rune_count), CBASE_ERROR_OUT_OF_BOUNDS);

    char *cursor = NULL;

    CBASE_PROPAGATE_ERROR(utf8_index(*data, *len, rune_count, &cursor));

    *len = cursor - *data;
    *data = cursor;

    return 0;
}

void utf8_skip_rune_fast(char **data, size_t *len) {
    utf8_skip_runes_fast(data, len, 1);
}

int utf8_skip_rune(char **data, size_t *len) {
    return utf8_skip_runes(data, len, 1);
}

void utf8_skip_runes_if_matching_fast(char **data,
                                      size_t *len,
                                      RuneMatchFunc *matches) {
    char *cursor = *data;
    size_t clen = *len;
    rune r = 0;

    do {
        utf8_iterate_rune_fast(&cursor, &clen, &r);
    } while (!matches(r));

    *len -= positive_ptrdiff(cursor, *data);
    *data = cursor;
}

int utf8_skip_runes_if_matching(char **data,
                                size_t *len,
                                RuneMatchFunc *matches) {
    char *cursor = *data;
    size_t clen = *len;
    rune r = 0;

    do {
        CBASE_PROPAGATE_ERROR(utf8_iterate_rune(&cursor, &clen, &r));
    } while (!matches(r));

    *len -= positive_ptrdiff(cursor, *data);
    *data = cursor;

    return 0;
}

void utf8_skip_rune_if_matching_fast(char **data,
                                     size_t *len,
                                     RuneMatchFunc *matches) {
    char *cursor = *data;
    size_t clen = *len;
    rune r = 0;

    utf8_iterate_rune_fast(&cursor, &clen, &r);

    if (matches(r)) {
        *len -= positive_ptrdiff(cursor, *data);
        *data = cursor;
    }
}

int utf8_skip_rune_if_matching(char **data,
                               size_t *len,
                               RuneMatchFunc *matches) {
    char *cursor = *data;
    size_t clen = *len;
    rune r = 0;

    CBASE_PROPAGATE_ERROR(utf8_iterate_rune(&cursor, &clen, &r));

    if (matches(r)) {
        *len -= positive_ptrdiff(cursor, *data);
        *data = cursor;
    }

    return 0;
}

void utf8_skip_rune_if_equals_fast(char **data, size_t *len, rune r) {
    char *cursor = *data;
    size_t clen = *len;
    rune r2 = 0;

    utf8_iterate_rune_fast(&cursor, &clen, &r2);

    if (r2 == r) {
        *len -= positive_ptrdiff(cursor, *data);
        *data = cursor;
    }
}

int utf8_skip_rune_if_equals(char **data, size_t *len, rune r) {
    char *cursor = *data;
    size_t clen = *len;
    rune r2 = 0;

    CBASE_PROPAGATE_ERROR(utf8_iterate_rune(&cursor, &clen, &r2));

    if (r2 == r) {
        *len -= positive_ptrdiff(cursor, *data);
        *data = cursor;
    }

    return 0;
}

int utf8_pop_rune_fast(char **data, size_t *len, rune *r) {
    rune r2 = 0;
    size_t rune_byte_len = 0;

    utf8_index_rune_len_fast(*data, *len, 0, &r2, &rune_byte_len);

    *data += rune_byte_len;
    *len -= rune_byte_len;
    *r = r2;

    return 0;
}

int utf8_pop_rune(char **data, size_t *len, rune *r) {
    rune r2 = 0;
    size_t rune_byte_len = 0;

    CBASE_PROPAGATE_ERROR(
        utf8_index_rune_len(*data, *len, 0, &r2, &rune_byte_len));

    *data += rune_byte_len;
    *len -= rune_byte_len;
    *r = r2;

    return 0;
}

void utf8_pop_rune_if_matching_fast(char **data,
                                    size_t *len,
                                    RuneMatchFunc *matches,
                                    rune *r) {
    rune r2 = 0;
    size_t rune_byte_len = 0;

    utf8_index_rune_len_fast(*data, *len, 0, &r2, &rune_byte_len);

    if (matches(r2)) {
        *data += rune_byte_len;
        *len -= rune_byte_len;
        *r = r2;
    }
}

int utf8_pop_rune_if_matching(char **data,
                              size_t *len,
                              RuneMatchFunc *matches,
                              rune *r) {
    rune r2 = 0;
    size_t rune_byte_len = 0;

    CBASE_PROPAGATE_ERROR(
        utf8_index_rune_len(*data, *len, 0, &r2, &rune_byte_len));

    if (matches(r2)) {
        *data += rune_byte_len;
        *len -= rune_byte_len;
        *r = r2;
    }

    return 0;
}

void utf8_seek_to_match_fast(char **data, size_t *len, RuneMatchFunc matches) {
    char *cursor = *data;
    size_t clen = *len;

    while (positive_ptrdiff(cursor, *data) < *len) {
        rune r = 0;

        utf8_iterate_rune_fast(&cursor, &clen, &r);

        if (matches(r)) {
            *len -= positive_ptrdiff(cursor, *data);
            *data = cursor;

            return;
        }
    }
}

int utf8_seek_to_match(char **data, size_t *len, RuneMatchFunc matches) {
    char *cursor = *data;
    size_t clen = *len;

    while (positive_ptrdiff(cursor, *data) < *len) {
        rune r = 0;

        CBASE_PROPAGATE_ERROR(utf8_iterate_rune(&cursor, &clen, &r));

        if (matches(r)) {
            *len -= positive_ptrdiff(cursor, *data);
            *data = cursor;

            return 0;
        }
    }

    return CBASE_ERROR_NOT_FOUND;
}

int utf8_seek_to_rune(char **data, size_t *len, rune r) {
    char utf8_data[5] = {0};
    size_t utf8_byte_len = 0;

    CBASE_PROPAGATE_ERROR(rune_encode(r, &utf8_data[0], &utf8_byte_len));

    return utf8_seek_to_data(data, len, &utf8_data[0], utf8_byte_len);
}

void utf8_truncate_runes_fast(const char *data,
                              size_t *len,
                              size_t rune_count) {
    char *cursor = NULL;

    if (rune_count == 0) {
        return;
    }

    utf8_index_reverse_fast(data, *len, rune_count - 1, &cursor);

    *len = positive_ptrdiff(cursor, (void *)data);
}

int utf8_truncate_runes(const char *data, size_t *len, size_t rune_count) {
    char *cursor = NULL;

    if (rune_count == 0) {
        return 0;
    }

    CBASE_PROPAGATE_ERROR(
        utf8_index_reverse(data, *len, rune_count - 1, &cursor));

    *len = positive_ptrdiff(cursor, (void *)data);

    return 0;
}

void utf8_truncate_if_matching_fast(const char *data,
                                    size_t *len,
                                    RuneMatchFunc *matches) {
    char *cursor = (char *)data;
    size_t len2 = *len;
    rune r = 0;

    do {
        utf8_iterate_rune_reverse_fast(&cursor, &len2, &r);
    } while (matches(r));

    *len = len2;
}

int utf8_truncate_if_matching(const char *data,
                              size_t *len,
                              RuneMatchFunc *matches) {
    char *cursor = (char *)data;
    size_t len2 = *len;
    rune r = 0;

    do {
        CBASE_PROPAGATE_ERROR(utf8_iterate_rune_reverse(&cursor, &len2, &r));
    } while (matches(r));

    *len = len2;

    return 0;
}

void utf8_truncate_if_equals_fast(const char *data, size_t *len, rune r) {
    char *cursor = (char *)data;
    size_t len2 = *len;
    rune r2 = 0;

    do {
        utf8_iterate_rune_reverse_fast(&cursor, &len2, &r2);
    } while (r == r2);

    *len = len2;
}

int utf8_truncate_if_equals(const char *data, size_t *len, rune r) {
    char *cursor = (char *)data;
    size_t len2 = *len;
    rune r2 = 0;

    do {
        CBASE_PROPAGATE_ERROR(utf8_iterate_rune_reverse(&cursor, &len2, &r2));
    } while (r == r2);

    *len = len2;

    return 0;
}

void utf8_truncate_if_not_equals_fast(const char *data, size_t *len, rune r) {
    char *cursor = (char *)data;
    size_t len2 = *len;
    rune r2 = 0;

    do {
        utf8_iterate_rune_reverse_fast(&cursor, &len2, &r2);
    } while (r != r2);

    *len = len2;
}

int utf8_truncate_if_not_equals(const char *data, size_t *len, rune r) {
    char *cursor = (char *)data;
    size_t len2 = *len;
    rune r2 = 0;

    do {
        CBASE_PROPAGATE_ERROR(utf8_iterate_rune_reverse(&cursor, &len2, &r2));
    } while (r != r2);

    *len = len2;

    return 0;
}

bool utf8_equal_fast(const char *s1, const char *s2, size_t byte_len) {
    return cbase_data_equals_fast(s1, byte_len, s2, byte_len, 0);
}

int utf8_equal(const char *s1, const char *s2, size_t byte_len, bool *equal) {
    return cbase_data_equals(s1, byte_len, s2, byte_len, 0, equal);
}

void utf8_find_data_fast(const char *haystack,
                         size_t hlen,
                         const char *needle,
                         size_t nlen,
                         bool *found,
                         size_t *location) {
    cbase_data_find_fast(haystack, hlen, needle, nlen, 0, found, location);
}

int utf8_find_data(const char *haystack,
                   size_t hlen,
                   const char *needle,
                   size_t nlen,
                   bool *found,
                   size_t *location) {
    return cbase_data_find(haystack, hlen, needle, nlen, 0, found, location);
}

bool utf8_starts_with_data_fast(const char *s1,
                                size_t byte_len1,
                                const char *s2,
                                size_t byte_len2) {
    return cbase_data_starts_with_fast(s1, byte_len1, s2, byte_len2);
}

int utf8_starts_with_data(const char *s1,
                          size_t byte_len1,
                          const char *s2,
                          size_t byte_len2,
                          bool *starts_with) {
    return cbase_data_starts_with(s1, byte_len1, s2, byte_len2, starts_with);
}

bool utf8_ends_with_data_fast(const char *s1,
                              size_t byte_len1,
                              const char *s2,
                              size_t byte_len2) {
    return cbase_data_ends_with_fast(s1, byte_len1, s2, byte_len2);
}

int utf8_ends_with_data(const char *s1,
                        size_t byte_len1,
                        const char *s2,
                        size_t byte_len2,
                        bool *ends_with) {
    return cbase_data_ends_with(s1, byte_len1, s2, byte_len2, ends_with);
}

void utf8_seek_to_data_fast(char **data,
                            size_t *len,
                            const char *data2,
                            size_t len2) {
    bool found = false;
    size_t location = 0;

    utf8_find_data_fast(*data, *len, data2, len2, &found, &location);

    if (!found) {
        return;
    }

    *len -= location;
    *data += location;
}

int utf8_seek_to_data(char **data,
                      size_t *len,
                      const char *data2,
                      size_t len2) {
    bool found = false;
    size_t location = 0;

    CBASE_PROPAGATE_ERROR(
        utf8_find_data(*data, *len, data2, len2, &found, &location));

    if (!found) {
        CBASE_ERROR(CBASE_ERROR_NOT_FOUND);
    }

    *len -= location;
    *data += location;

    return 0;
}

/* vi: set et ts=4 sw=4: */

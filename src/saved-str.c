#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "cbase/sslice.h"
#include "cbase/utf8.h"
#include "cbase/str.h"

void string_assign_cstr_full_fast(String *string, const char *cs,
                                                  size_t len,
                                                  size_t byte_len) {
    buffer_assign_fast(&string->buffer, cs, byte_len + 1);
    string->len = len;
}

int string_assign_cstr_full(String *string, const char *cs, size_t len,
                                                            size_t byte_len) {
    CBASE_PROPAGATE_ERROR(buffer_assign(&string->buffer, cs, byte_len + 1));

    string->len = len;

    return 0;
}

int string_assign_cstr(String *string, const char *cs) {
    size_t len = 0;
    size_t byte_len = 0;

    CBASE_PROPAGATE_ERROR(utf8_process_cstr(cs, &len, &byte_len));

    return string_assign_cstr_full(string, cs, len, byte_len);
}

void string_assign_utf8_data_full_fast(String *string, const char *data,
                                                       size_t len,
                                                       size_t byte_len) {
    char terminating_null = '\0';

    buffer_assign_fast(&string->buffer, data, byte_len);
    buffer_append_fast(&string->buffer, &terminating_null, 1);

    string->len = len;
}

int string_assign_utf8_data_full(String *string, const char *data,
                                                 size_t len,
                                                 size_t byte_len) {
    CBASE_PROPAGATE_ERROR(
        buffer_ensure_capacity(&string->buffer, byte_len + 1)
    );

    string_assign_utf8_data_full_fast(string, data, len, byte_len);

    return 0;
}

void string_assign_utf8_data_fast(String *string, const char *data,
                                                  size_t byte_len) {
    size_t len = 0;

    if (data) {
        utf8_len(data, byte_len, &len);
    }

    string_assign_utf8_data_full_fast(string, data, len, byte_len);
}

int string_assign_utf8_data(String *string, const char *data,
                                            size_t byte_len) {
    size_t len = 0;

    if (data) {
        utf8_len(data, byte_len, &len);
    }

    return string_assign_utf8_data_full(string, data, len, byte_len);
}

void string_assign_sslice_fast(String *string, SSlice *sslice) {
    string_assign_utf8_data_full_fast(string, sslice->data, sslice->len,
                                                            sslice->byte_len);
}

int string_assign_sslice(String *string, SSlice *sslice) {
    return string_assign_utf8_data_full(string, sslice->data,
                                                sslice->len,
                                                sslice->byte_len);
}

int string_assign_data_fast(String *string, const char *data,
                                            size_t byte_len,
                                            const char *encoding) {
    Buffer input;

    CBASE_PROPAGATE_ERROR(buffer_init_from_data(&input, data, byte_len));

    CBASE_FREE_AND_PROPAGATE_ERROR(
        buffer_encode(&input, encoding, "utf-8", &string->buffer),
        buffer_free,
        &input
    );

    string_assign_utf8_data_fast(string, input.data, input.len);

    buffer_free(&input);
    return 0;
}

int string_assign_data(String *string, const char *data,
                                       size_t byte_len,
                                       const char *encoding) {
    Buffer input;
    int error = 0;

    CBASE_PROPAGATE_ERROR(buffer_init_from_data(&input, data, byte_len));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        buffer_encode(&input, encoding, "utf-8", &string->buffer),
        buffer_free,
        &input
    );

    error = string_assign_utf8_data(string, input.data, input.len);

    buffer_free(&input);
    return error;
}

int string_assign_slice_fast(String *string, Slice *slice,
                                             const char *encoding) {
    return string_assign_data_fast(string, slice->data, slice->len, encoding);
}

int string_assign_slice(String *string, Slice *slice, const char *encoding) {
    return string_assign_data(string, slice->data, slice->len, encoding);
}

void string_assign_utf8_slice_fast(String *string, Slice *slice) {
    string_assign_utf8_data_fast(string, slice->data, slice->len);
}

int string_assign_utf8_slice(String *string, Slice *slice) {
    return string_assign_utf8_data(string, slice->data, slice->len);
}

int string_assign_local_slice_fast(String *string, Slice *slice) {
    return string_assign_data_fast(string, slice->data, slice->len, "wchar_t");
}

int string_assign_local_slice(String *string, Slice *slice) {
    return string_assign_data(string, slice->data, slice->len, "wchar_t");
}

int string_assign_buffer_fast(String *string, Buffer *buffer,
                                              const char *encoding) {
    return string_assign_data_fast(string, buffer->data, buffer->len,
                                                         encoding);
}

int string_assign_buffer(String *string, Buffer *buffer, const char *encoding) {
    return string_assign_data(string, buffer->data, buffer->len, encoding);
}

void string_assign_utf8_buffer_full_fast(String *string, Buffer *buffer,
                                                         size_t len) {
    string_assign_utf8_data_full_fast(string, buffer->data, len, buffer->len);
}

int string_assign_utf8_buffer_full(String *string, Buffer *buffer,
                                                   size_t len) {
    return string_assign_utf8_data_full(string, buffer->data, len,
                                                              buffer->len);
}

void string_assign_utf8_buffer_fast(String *string, Buffer *buffer) {
    string_assign_utf8_data_fast(string, buffer->data, buffer->len);
}

int string_assign_utf8_buffer(String *string, Buffer *buffer) {
    return string_assign_utf8_data(string, buffer->data, buffer->len);
}

int string_assign_local_buffer_fast(String *string, Buffer *buffer) {
    return string_assign_buffer_fast(string, buffer, "wchar_t");
}

int string_assign_local_buffer(String *string, Buffer *buffer) {
    return string_assign_buffer(string, buffer, "wchar_t");
}

void string_assign_string_fast(String *dst, String *src) {
    string_assign_utf8_buffer_full_fast(dst, &src->buffer, src->len);
}

int string_assign_string(String *dst, String *src) {
    return string_assign_utf8_buffer_full(dst, &src->buffer, src->len);
}

int string_ensure_capacity(String *string, size_t byte_len) {
    return buffer_ensure_capacity(&string->buffer, byte_len + 1);
}

void string_init(String *string) {
    buffer_init(&string->buffer);
    string->len = 0;
}

int string_init_alloc(String *string, size_t alloc) {
    CBASE_PROPAGATE_ERROR(buffer_init_alloc(&string->buffer, alloc));

    string->len = 0;

    return 0;
}

int string_init_from_cstr(String *string, const char *cs) {
    string_init(string);
    return string_assign_cstr(string, cs);
}

int string_init_from_cstr_full(String *string, const char *cs,
                                               size_t len,
                                               size_t byte_len) {
    string_init(string);
    return string_assign_cstr_full(string, cs, len, byte_len);
}

int string_init_from_utf8_data(String *string, const char *data,
                                               size_t byte_len) {
    string_init(string);
    return string_assign_utf8_data(string, data, byte_len);
}

int string_init_from_utf8_data_full(String *string, const char *data,
                                                    size_t len,
                                                    size_t byte_len) {
    string_init(string);
    return string_assign_utf8_data_full(string, data, len, byte_len);
}

int string_init_from_sslice(String *string, SSlice *sslice) {
    string_init(string);
    return string_assign_sslice(string, sslice);
}

int string_init_from_string(String *string, String *input) {
    string_init(string);
    return string_assign_string(string, input);
}

int string_init_from_slice(String *string, Slice *slice,
                                           const char *encoding) {
    string_init(string);
    return string_assign_slice(string, slice, encoding);
}

int string_init_from_utf8_slice(String *string, Slice *slice) {
    string_init(string);
    return string_assign_utf8_slice(string, slice);
}

int string_init_from_local_slice(String *string, Slice *slice) {
    string_init(string);
    return string_assign_local_slice(string, slice);
}

int string_init_from_buffer(String *string, Buffer *buffer,
                                            const char *encoding) {
    string_init(string);
    return string_assign_buffer(string, buffer, encoding);
}

int string_init_from_utf8_buffer(String *string, Buffer *buffer) {
    string_init(string);
    return string_assign_utf8_buffer(string, buffer);
}

int string_init_from_local_buffer(String *string, Buffer *buffer) {
    string_init(string);
    return string_assign_local_buffer(string, buffer);
}

int string_new(String **string) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));

    string_init(*string);

    return 0;
}

int string_new_alloc(String **string, size_t alloc) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_alloc(*string, alloc),
        cbfree,
        *string
    );

    return 0;
}

int string_new_from_cstr(String **string, const char *cs) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_from_cstr(*string, cs),
        cbfree,
        *string
    );

    return 0;
}

int string_new_from_cstr_full(String **string, const char *cs,
                                               size_t len,
                                               size_t byte_len) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_from_cstr_full(*string, cs, len, byte_len),
        cbfree,
        *string
    );

    return 0;
}

int string_new_from_utf8_data_full(String **string, const char *data,
                                                    size_t len,
                                                    size_t byte_len) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_from_utf8_data_full(*string, data, len, byte_len),
        cbfree,
        *string
    );

    return 0;
}

int string_new_from_sslice(String **string, SSlice *sslice) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_from_sslice(*string, sslice),
        cbfree,
        *string
    );

    return 0;
}

int string_new_from_string(String **string, String *input) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_from_string(*string, input),
        cbfree,
        *string
    );

    return 0;
}

int string_new_from_slice(String **string, Slice *slice, const char *encoding) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_from_slice(*string, slice, encoding),
        cbfree,
        *string
    );

    return 0;
}

int string_new_from_utf8_slice(String **string, Slice *slice) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_from_utf8_slice(*string, slice),
        cbfree,
        *string
    );

    return 0;
}

int string_new_from_local_slice(String **string, Slice *slice) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_from_local_slice(*string, slice),
        cbfree,
        *string
    );

    return 0;
}

int string_new_from_buffer(String **string, Buffer *buffer,
                                            const char *encoding) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_from_buffer(*string, buffer, encoding),
        cbfree,
        *string
    );

    return 0;
}

int string_new_from_utf8_buffer(String **string, Buffer *buffer) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_from_utf8_buffer(*string, buffer),
        cbfree,
        *string
    );

    return 0;
}

int string_new_from_local_buffer(String **string, Buffer *buffer) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_from_local_buffer(*string, buffer),
        cbfree,
        *string
    );

    return 0;
}

int string_compact(String *string) {
    return buffer_compact(&string->buffer);
}

int string_index_rune(String *string, size_t index, rune *r) {
    return utf8_index_rune(string->buffer.data, string->buffer.len, index, r);
}

int string_index_rune_reverse(String *string, size_t index, rune *r) {
    return strbase_index_rune_reverse(string->buffer.data, string->len, index,
                                                                        r);
}

int string_get_first_rune(String *string, rune *r) {
    return string_index_rune(string, 0, r);
}

int string_get_last_rune(String *string, rune *r) {
    return utf8_get_last_rune(string->buffer.data, string->buffer.len, r);
}

bool string_equals_cstr(String *string, const char *cs) {
    return buffer_equals_data(&string->buffer, cs, strlen(cs));
}

bool string_equals_utf8_data(String *string, const char *data,
                                             size_t byte_len) {
    return buffer_equals_data(&string->buffer, data, byte_len);
}

bool string_equals_sslice(String *string, SSlice *sslice) {
    return buffer_equals_data(&string->buffer, sslice->data, sslice->byte_len);
}

bool string_equals_string(String *s1, String *s2) {
    return buffer_equals_buffer(&s1->buffer, &s2->buffer);
}

bool string_equals_utf8_slice(String *string, Slice *slice) {
    return buffer_equals_data(&string->buffer, slice->data, slice->len);
}

bool string_equals_utf8_buffer(String *string, Buffer *buffer) {
    return buffer_equals_buffer(&string->buffer, buffer);
}

int string_starts_with_rune(String *string, rune r, bool *starts_with) {
    rune r2;

    CBASE_PROPAGATE_ERROR(string_get_first_rune(string, &r2));

    *starts_with = (r2 == r);

    return 0;
}

int string_starts_with_cstr_len(String *string, const char *cs,
                                                size_t byte_len,
                                                bool *starts_with) {
    int error = buffer_equals_data_at(&string->buffer, 0, cs, byte_len,
                                                              starts_with);
    if (error == CBASE_ERROR_OUT_OF_BOUNDS) {
        *starts_with = false;
        error = 0;
    }

    return error;
}

int string_starts_with_cstr(String *string, const char *cs, bool *starts_with) {
    return string_starts_with_cstr_len(string, cs, strlen(cs), starts_with);
}

int string_ends_with_rune(String *string, rune r, bool *ends_with) {
    rune r2 = 0;

    CBASE_PROPAGATE_ERROR(
        utf8_get_last_rune(string->buffer.data, string->buffer.len, &r2)
    );

    *ends_with = (r2 == r);

    return 0;
}

int string_ends_with_utf8_data(String *string, const char *cs,
                                               size_t byte_len,
                                               bool *ends_with) {
    size_t index = string->buffer.len - byte_len;

    return buffer_equals_data_at(&string->buffer, index, cs, byte_len,
                                                             ends_with);
}

int string_ends_with_cstr(String *string, const char *cs, bool *ends_with) {
    return string_ends_with_utf8_data(string, cs, strlen(cs) + 1, ends_with);
}

void string_slice_fast(String *string, size_t index, size_t len,
                                                     SSlice *sslice) {
    char *start = NULL;
    char *end = NULL;

    utf8_slice_fast(string->buffer.data, string->buffer.len, index, len,
                                                                    &start,
                                                                    &end);

    sslice_assign_full(sslice, start, len, end - start);
}

int string_slice(String *string, size_t index, size_t len, SSlice *sslice) {
    char *start = NULL;
    char *end = NULL;

    CBASE_ERROR_IF(((index + len) > string->len), CBASE_ERROR_OUT_OF_BOUNDS);

    utf8_slice_fast(string->buffer.data, string->buffer.len, index, len,
                                                                    &start,
                                                                    &end);

    sslice_assign_full(sslice, start, len, end - start);

    return 0;
}

void string_slice_full(String *string, SSlice *sslice) {
    sslice_assign_full(sslice, string->buffer.data, string->len,
                                                    string->buffer.len);
}

void string_delete_fast(String *string, size_t index, size_t rune_count) {
    char *start = string->buffer.data;

    size_t byte_index = 0;
    size_t byte_len = 0;

    if (!rune_count) {
        return;
    }

    if (index) {
        utf8_index_fast(string->buffer.data, string->buffer.len, index,
                                                                     &start);
        byte_index = start - (char *)string->buffer.dat;
    }

    size_t temp_len = string->len;
    size_t temp_byte_len = string->buffer.len;

    strbase_skip_runes_fast(&start, &temp_len, &temp_byte_len, rune_count);

    buffer_delete_fast(&string->buffer, byte_index, temp_byte_len - byte_len);

    string->len -= rune_count;
}


int string_delete(String *string, size_t index, size_t rune_count) {
    char *start = string->buffer.data;

    size_t byte_index = 0;
    size_t byte_len = 0;

    if (!rune_count) {
        return 0;
    }

    if (index) {
        CBASE_PROPAGATE_ERROR(
            utf8_index(string->buffer.data, string->buffer.len, index, &start)
        );

        byte_index = start - (char *)string->buffer.data;
    }

    size_t temp_len = string->len;
    size_t temp_byte_len = string->buffer.len;

    CBASE_PROPAGATE_ERROR(
        strbase_skip_runes(&start, &temp_len, &temp_byte_len, rune_count)
    );

    CBASE_PROPAGATE_ERROR(
        buffer_delete(&string->buffer, byte_index, temp_byte_len - byte_len)
    );

    string->len -= rune_count;

    return 0;
}

int string_skip_rune(String *string) {
    return string_delete(string, 0, 1);
}

int string_skip_runes(String *string, size_t rune_count) {
    return string_delete(string, 0, rune_count);
}

int string_skip_rune_if_equals(String *string, rune r) {
    rune r2;

    CBASE_PROPAGATE_ERROR(
        string_get_first_rune(string, &r2)
    );

    CBASE_ERROR_IF((r2 != r), CBASE_ERROR_NOT_EQUAL);

    return string_skip_runes(string, 1);
}

int string_pop_rune(String *string, rune *r) {
    CBASE_PROPAGATE_ERROR(string_get_first_rune(string, r));
    CBASE_PROPAGATE_ERROR(string_delete(string, 0, 1));
}

int string_pop_rune_if_matches(String *string, RuneMatchFunc *matches,
                                               rune *r) {
    rune r2 = 0;
    size_t bytes_read = 0;

    CBASE_PROPAGATE_ERROR(
        utf8_get_first_rune_len(string->buffer.data, &r2, &bytes_read)
    );

    CBASE_ERROR_IF((!matches(r2)), CBASE_ERROR_NOT_FOUND);

    *r = r2;

    return string_delete(string, 0, 1);
}

int string_skip_rune_if_matches(String *string, RuneMatchFunc *matches) {
    rune r = 0;

    return string_pop_rune_if_matches(string, matches, &r);
}

int string_seek_to_rune(String *string, rune r) {
    for (size_t i = 0; i < string->len; i++) {
        char *substring = NULL;
        rune r2;

        CBASE_PROPAGATE_ERROR(
            utf8_index(string->buffer.data, string->buffer.len, i, &substring)
        );

        CBASE_PROPAGATE_ERROR(utf8_get_first_rune(substring, &r2));

        if (r2 == r) {
            return string_delete(string, 0, i);
        }
    }

    CBASE_ERROR(CBASE_ERROR_NOT_FOUND);
}

int string_seek_to_cstr(String *string, const char *cs) {
    for (size_t i = 0; i < string->len; i++) {
        bool equal = false;
        char *substring = NULL;

        CBASE_PROPAGATE_ERROR(
            utf8_index(string->buffer.data, string->buffer.len, i, &substring)
        );

        CBASE_PROPAGATE_ERROR(utf8_cstr_equal(substring, cs, &equal));

        if (equal) {
            return string_delete(string, 0, i);
        }
    }

    CBASE_ERROR(CBASE_ERROR_NOT_FOUND);
}

int string_truncate_runes(String *string, size_t rune_count) {
    return string_delete(string, string->len - rune_count, rune_count);
}

int string_truncate_rune(String *string) {
    return string_truncate_runes(string, 1);
}

char* string_to_cstr(String *string) {
    char *out = NULL;

    if (cbstrdup(string->buffer.data, &out)) {
        return NULL;
    }

    return out;
}

void string_insert_cstr_full_fast(String *string, size_t index,
                                                  const char *cs,
                                                  size_t len,
                                                  size_t byte_len) {
    buffer_insert_data_fast(&string->buffer, index, cs, byte_len + 1);
    string->len += len;
}

int string_insert_cstr_full(String *string, size_t index, const char *cs,
                                                          size_t len,
                                                          size_t byte_len) {
    CBASE_ERROR_IF((index > string->len), CBASE_ERROR_OUT_OF_BOUNDS);

    CBASE_PROPAGATE_ERROR(
        string_ensure_capacity(string, string->buffer.len + byte_len)
    );

    string_insert_cstr_full_fast(string, index, cs, len, byte_len);

    return 0;
}

int string_insert_cstr(String *string, size_t index, const char *cs) {
    size_t len = 0;
    size_t byte_len = 0;

    if (cs) {
        CBASE_PROPAGATE_ERROR(utf8_process_cstr(cs, &len, &byte_len));
    }

    return string_insert_cstr_full(string, index, cs, len, byte_len);
}

void string_insert_utf8_data_full_fast(String *string, size_t index,
                                                       const char *data,
                                                       size_t len,
                                                       size_t byte_len) {
    buffer_insert_data_fast(&string->buffer, index, data, byte_len);
    buffer_insert_data_fast(&string->buffer, index + byte_len, "\0", 1);
    string->len += len;
}

int string_insert_utf8_data_full(String *string, size_t index,
                                                 const char *data,
                                                 size_t len,
                                                 size_t byte_len) {
    CBASE_ERROR_IF((index > string->len), CBASE_ERROR_OUT_OF_BOUNDS);

    CBASE_PROPAGATE_ERROR(
        string_ensure_capacity(string, string->buffer.len + byte_len)
    );

    string_insert_utf8_data_full_fast(string, index, data, len, byte_len);

    return 0;
}

void string_insert_utf8_data_fast(String *string, size_t index,
                                                  const char *data,
                                                  size_t byte_len) {
    size_t len = 0;

    if (data) {
        utf8_len(data, byte_len, &len);
    }

    string_insert_utf8_data_full_fast(
        string, index, data, len, byte_len
    );
}

int string_insert_utf8_data(String *string, size_t index, const char *data,
                                                          size_t byte_len) {

    size_t len = 0;

    if (data) {
        utf8_len(data, byte_len, &len);
    }

    return string_insert_utf8_data_full(string, index, data, len, byte_len);
}

void string_insert_sslice_fast(String *string, size_t index, SSlice *sslice) {
    string_insert_utf8_data_full_fast(string, index, sslice->data,
                                                     sslice->len,
                                                     sslice->byte_len);
}

int string_insert_sslice(String *string, size_t index, SSlice *sslice) {
    return string_insert_utf8_data_full(string, index, sslice->data,
                                                       sslice->len,
                                                       sslice->byte_len);
}

void string_insert_string_fast(String *dst, size_t index, String *src) {
    string_insert_cstr_full_fast(dst, index, src->buffer.data,
                                             src->len,
                                             src->buffer.len);
}

int string_insert_string(String *dst, size_t index, String *src) {
    return string_insert_cstr_full(dst, index, src->buffer.data,
                                               src->len,
                                               src->buffer.len);
}

int string_insert_slice_fast(String *string, size_t index,
                                             Slice *slice,
                                             const char *encoding) {
    Buffer output;

    CBASE_PROPAGATE_ERROR(buffer_init_alloc(&output, 64));

    CBASE_FREE_AND_PROPAGATE_ERROR(
        slice_encode(slice, encoding, "utf-8", &output),
        buffer_free,
        &output
    );

    string_insert_utf8_data_fast(string, index, output.data, output.len);

    buffer_free(&output);

    return 0;
}

int string_insert_slice(String *string, size_t index, Slice *slice,
                                                      const char *encoding) {
    Buffer output;

    CBASE_PROPAGATE_ERROR(buffer_init_alloc(&output, 64));

    CBASE_FREE_AND_PROPAGATE_ERROR(
        slice_encode(slice, encoding, "utf-8", &output),
        buffer_free,
        &output
    );

    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_insert_utf8_data(string, index, output.data, output.len),
        buffer_free,
        &output
    );

    buffer_free(&output);

    return 0;
}

void string_insert_utf8_slice_fast(String *string, size_t index,
                                                   Slice *slice) {
    string_insert_utf8_data_fast(string, index, slice->data, slice->len);
}

int string_insert_utf8_slice(String *string, size_t index, Slice *slice) {
    return string_insert_utf8_data(string, index, slice->data, slice->len);
}

int string_insert_local_slice_fast(String *string, size_t index,
                                                   Slice *slice) {
    return string_insert_slice_fast(string, index, slice, "wchar_t");
}

int string_insert_local_slice(String *string, size_t index, Slice *slice) {
    return string_insert_slice(string, index, slice, "wchar_t");
}

int string_insert_buffer_fast(String *string, size_t index,
                                              Buffer *buffer,
                                              const char *encoding) {
    Buffer output;

    CBASE_PROPAGATE_ERROR(buffer_init_alloc(&output, 64));

    CBASE_FREE_AND_PROPAGATE_ERROR(
        buffer_encode(buffer, encoding, "utf-8", &output),
        buffer_free,
        &output
    );

    string_insert_utf8_data_fast(string, index, output.data, output.len);

    buffer_free(&output);

    return 0;
}

int string_insert_buffer(String *string, size_t index, Buffer *buffer,
                                                       const char *encoding) {
    Buffer output;

    CBASE_PROPAGATE_ERROR(buffer_init_alloc(&output, 64));

    CBASE_FREE_AND_PROPAGATE_ERROR(
        buffer_encode(buffer, encoding, "utf-8", &output),
        buffer_free,
        &output
    );

    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_insert_utf8_data(string, index, output.data, output.len),
        buffer_free,
        &output
    );

    buffer_free(&output);

    return 0;
}

int string_insert_utf8_buffer_fast(String *string, size_t index,
                                                   Buffer *buffer) {
    return string_insert_utf8_data(string, index, buffer->data, buffer->len);
}

int string_insert_utf8_buffer(String *string, size_t index, Buffer *buffer) {
    return string_insert_utf8_data(string, index, buffer->data, buffer->len);
}

int string_insert_local_buffer_fast(String *string, size_t index,
                                                    Buffer *buffer) {
    return string_insert_buffer_fast(string, index, buffer, "wchar_t");
}

int string_insert_local_buffer(String *string, size_t index, Buffer *buffer) {
    return string_insert_buffer(string, index, buffer, "wchar_t");
}

int string_insert_data_fast(String *string, size_t index,
                                            const char *data,
                                            size_t byte_len,
                                            const char *encoding) {
    Slice slice;

    slice.data = (char *)data;
    slice.len = byte_len;

    return string_insert_slice_fast(string, index, &slice, encoding);
}

int string_insert_data(String *string, size_t index, const char *data,
                                                     size_t byte_len,
                                                     const char *encoding) {
    Slice slice;

    slice.data = (char *)data;
    slice.len = byte_len;

    return string_insert_slice(string, index, &slice, encoding);
}

int string_insert_local_data_fast(String *string, size_t index,
                                                  const char *data,
                                                  size_t byte_len) {
    return string_insert_data_fast(string, index, data, byte_len, "wchar_t");
}

int string_insert_local_data(String *string, size_t index, const char *data,
                                                           size_t byte_len) {
    return string_insert_data(string, index, data, byte_len, "wchar_t");
}

void string_prepend_cstr_full_fast(String *string, const char *cs,
                                                   size_t len,
                                                   size_t byte_len) {
    string_insert_cstr_full_fast(string, 0, cs, len, byte_len);
}

int string_prepend_cstr_full(String *string, const char *cs, size_t len,
                                                             size_t byte_len) {
    return string_insert_cstr_full(string, 0, cs, len, byte_len);
}

int string_prepend_cstr(String *string, const char *cs) {
    return string_insert_cstr(string, 0, cs);
}

void string_prepend_utf8_data_full_fast(String *string, const char *data,
                                                        size_t len,
                                                        size_t byte_len) {
    string_insert_utf8_data_full_fast(string, 0, data, len, byte_len);
}

int string_prepend_utf8_data_full(String *string, const char *data,
                                                  size_t len,
                                                  size_t byte_len) {
    return string_insert_utf8_data_full(string, 0, data, len, byte_len);
}

int string_prepend_utf8_data(String *string, const char *data,
                                             size_t byte_len) {
    return string_insert_utf8_data(string, 0, data, byte_len);
}

void string_prepend_sslice_fast(String *string, SSlice *sslice) {
    string_insert_sslice_fast(string, 0, sslice);
}

int string_prepend_sslice(String *string, SSlice *sslice) {
    return string_insert_sslice(string, 0, sslice);
}

void string_prepend_string_fast(String *dst, String *src) {
    string_insert_string_fast(dst, 0, src);
}

int string_prepend_string(String *dst, String *src) {
    return string_insert_string(dst, 0, src);
}

int string_prepend_slice_fast(String *string, Slice *slice,
                                              const char *encoding) {
    return string_insert_slice_fast(string, 0, slice, encoding);
}

int string_prepend_slice(String *string, Slice *slice, const char *encoding) {
    return string_insert_slice(string, 0, slice, encoding);
}

void string_prepend_utf8_slice_fast(String *string, Slice *slice) {
    string_insert_utf8_slice_fast(string, 0, slice);
}

int string_prepend_utf8_slice(String *string, Slice *slice) {
    return string_insert_utf8_slice(string, 0, slice);
}

int string_prepend_local_slice_fast(String *string, Slice *slice) {
    return string_insert_local_slice_fast(string, 0, slice);
}

int string_prepend_local_slice(String *string, Slice *slice) {
    return string_insert_local_slice(string, 0, slice);
}

int string_prepend_buffer_fast(String *string, Buffer *buffer,
                                               const char *encoding) {
    return string_insert_buffer_fast(string, 0, buffer, encoding);
}

int string_prepend_buffer(String *string, Buffer *buffer, const char *encoding) {
    return string_insert_buffer(string, 0, buffer, encoding);
}

int string_prepend_utf8_buffer_fast(String *string, Buffer *buffer) {
    return string_insert_utf8_buffer_fast(string, 0, buffer);
}

int string_prepend_utf8_buffer(String *string, Buffer *buffer) {
    return string_insert_utf8_buffer(string, 0, buffer);
}

int string_prepend_local_buffer_fast(String *string, Buffer *buffer) {
    return string_insert_local_buffer_fast(string, 0, buffer);
}

int string_prepend_local_buffer(String *string, Buffer *buffer) {
    return string_insert_local_buffer(string, 0, buffer);
}

int string_prepend_data_fast(String *string, const char *data,
                                             size_t byte_len,
                                             const char *encoding) {
    return string_insert_data_fast(string, 0, data, byte_len, encoding);
}

int string_prepend_data(String *string, const char *data,
                                        size_t byte_len,
                                        const char *encoding) {
    return string_insert_data(string, 0, data, byte_len, encoding);
}

int string_prepend_local_data_fast(String *string, const char *data,
                                                   size_t byte_len) {
    return string_insert_local_data_fast(string, 0, data, byte_len);
}

int string_prepend_local_data(String *string, const char *data,
                                              size_t byte_len) {
    return string_insert_local_data(string, 0, data, byte_len);
}

void string_append_cstr_full_fast(String *string, const char *cs,
                                                  size_t len,
                                                  size_t byte_len) {
    string_insert_cstr_full_fast(string, string->len, cs, len, byte_len);
}

int string_append_cstr_full(String *string, const char *cs, size_t len,
                                                            size_t byte_len) {
    return string_insert_cstr_full(string, string->len, cs, len, byte_len);
}

int string_append_cstr(String *string, const char *cs) {
    return string_insert_cstr(string, string->len, cs);
}

void string_append_utf8_data_full_fast(String *string, const char *data,
                                                       size_t len,
                                                       size_t byte_len) {
    string_insert_utf8_data_full_fast(string, string->len, data, len, byte_len);
}

int string_append_utf8_data_full(String *string, const char *data,
                                                 size_t len,
                                                 size_t byte_len) {
    return string_insert_utf8_data_full(string, string->len, data, len, byte_len);
}

int string_append_utf8_data(String *string, const char *data,
                                            size_t byte_len) {
    return string_insert_utf8_data(string, string->len, data, byte_len);
}

void string_append_sslice_fast(String *string, SSlice *sslice) {
    string_insert_sslice_fast(string, string->len, sslice);
}

int string_append_sslice(String *string, SSlice *sslice) {
    return string_insert_sslice(string, string->len, sslice);
}

void string_append_string_fast(String *dst, String *src) {
    string_insert_string_fast(dst, dst->len, src);
}

int string_append_string(String *dst, String *src) {
    return string_insert_string(dst, dst->len, src);
}

int string_append_slice_fast(String *string, Slice *slice,
                                             const char *encoding) {
    return string_insert_slice_fast(string, string->len, slice, encoding);
}

int string_append_slice(String *string, Slice *slice, const char *encoding) {
    return string_insert_slice(string, string->len, slice, encoding);
}

void string_append_utf8_slice_fast(String *string, Slice *slice) {
    string_insert_utf8_slice_fast(string, string->len, slice);
}

int string_append_utf8_slice(String *string, Slice *slice) {
    return string_insert_utf8_slice(string, string->len, slice);
}

int string_append_local_slice_fast(String *string, Slice *slice) {
    return string_insert_local_slice_fast(string, string->len, slice);
}

int string_append_local_slice(String *string, Slice *slice) {
    return string_insert_local_slice(string, string->len, slice);
}

int string_append_buffer_fast(String *string, Buffer *buffer,
                                              const char *encoding) {
    return string_insert_buffer_fast(string, string->len, buffer, encoding);
}

int string_append_buffer(String *string, Buffer *buffer, const char *encoding) {
    return string_insert_buffer(string, string->len, buffer, encoding);
}

int string_append_utf8_buffer_fast(String *string, Buffer *buffer) {
    return string_insert_utf8_buffer_fast(string, string->len, buffer);
}

int string_append_utf8_buffer(String *string, Buffer *buffer) {
    return string_insert_utf8_buffer(string, string->len, buffer);
}

int string_append_local_buffer_fast(String *string, Buffer *buffer) {
    return string_insert_local_buffer_fast(string, string->len, buffer);
}

int string_append_local_buffer(String *string, Buffer *buffer) {
    return string_insert_local_buffer(string, string->len, buffer);
}

int string_append_data_fast(String *string, const char *data,
                                            size_t byte_len,
                                            const char *encoding) {
    return string_insert_data_fast(string, string->len, data, byte_len,
                                                              encoding);
}

int string_append_data(String *string, const char *data,
                                       size_t byte_len,
                                       const char *encoding) {
    return string_insert_data(string, string->len, data, byte_len, encoding);
}

int string_append_local_data_fast(String *string, const char *data,
                                                  size_t byte_len) {
    return string_insert_local_data_fast(string, string->len, data, byte_len);
}

int string_append_local_data(String *string, const char *data,
                                             size_t byte_len) {
    return string_insert_local_data(string, string->len, data, byte_len);
}

int string_encode(String *string, const char *encoding, Buffer *out) {
    return strbase_encode(string->buffer.data, string->buffer.len, encoding,
                                                                   out);
}

int string_localize(String *string, Buffer *out) {
    return strbase_localize(string->buffer.data, string->buffer.len, out);
}

void string_clear(String *string) {
    buffer_clear(&string->buffer);
    strbase_clear(&string->len, &string->buffer.len);
}

void string_free(String *string) {
    buffer_free(&string->buffer);
    strbase_clear(&string->len, &string->buffer.len);
}

__attribute__((format(printf, 3, 0)))
int string_insert_vprintf(String *string, size_t index, const char *fmt,
                                                        va_list args) {
    va_list args2;
    int byte_size;

    CBASE_ERROR_IF((index > string->len), CBASE_ERROR_OUT_OF_BOUNDS);

    va_copy(args2, args);
    byte_size = vsnprintf(NULL, 0, fmt, args2);
    va_end(args2);

    CBASE_ERROR_IF((byte_size < 0), CBASE_STRING_VSNPRINTF_FAILED);

    CBASE_PROPAGATE_ERROR(
        string_ensure_capacity(string, string->buffer.len + (size_t)byte_size)
    );

    char *cursor = string->buffer.data;
    size_t len = string->len;
    size_t byte_len = string->buffer.len;

    CBASE_PROPAGATE_ERROR(strbase_skip_runes(&cursor, &len, &byte_len, index));

    CBASE_PROPAGATE_ERROR(
        buffer_insert_blank_data_no_zero(
            &string->buffer,
            cursor - (char *)string->buffer.data,
            (size_t)byte_size
        )
    );

    int bytes_written = vsnprintf(cursor, byte_size + 1, fmt, args);

    CBASE_ERROR_IF(
        (bytes_written != (byte_size - 1)),
        CBASE_STRING_VSNPRINTF_FAILED
    );

    CBASE_PROPAGATE_ERROR(
        utf8_process(string->buffer.data, string->buffer.len, &string->len)
    );

    return 0;
}

__attribute__((format(printf, 3, 4)))
int string_insert_printf(String *string, size_t index, const char *fmt, ...) {
    va_list args;
    int res = 0;

    va_start(args, fmt);
    res = string_insert_vprintf(string, index, fmt, args);
    va_end(args);

    return res;
}

__attribute__((format(printf, 2, 0)))
int string_vprintf(String *string, const char *fmt, va_list args) {
    string_clear(string);
    return string_insert_vprintf(string, 0, fmt, args);
}

__attribute__((format(printf, 2, 3)))
int string_printf(String *string, const char *fmt, ...) {
    va_list args;
    int res = 0;

    va_start(args, fmt);
    res = string_vprintf(string, fmt, args);
    va_end(args);

    return res;
}

__attribute__((format(printf, 2, 0)))
int string_init_vprintf(String *string, const char *fmt, va_list args) {
    string_init(string);
    return string_vprintf(string, fmt, args);
}

__attribute__((format(printf, 2, 3)))
int string_init_printf(String *string, const char *fmt, ...) {
    int res = 0;
    va_list args;

    va_start(args, fmt);
    res = string_init_vprintf(string, fmt, args);
    va_end(args);

    return res;
}

__attribute__((format(printf, 2, 0)))
int string_new_vprintf(String **string, const char *fmt, va_list args) {
    CBASE_PROPAGATE_ERROR(cbmalloc(1, sizeof(String), string));
    CBASE_FREE_AND_PROPAGATE_ERROR(
        string_init_vprintf(*string, fmt, args),
        cbfree,
        *string
    );

    return 0;
}

__attribute__((format(printf, 2, 3)))
int string_new_printf(String **string, const char *fmt, ...) {
    va_list args;
    int res = 0;

    va_start(args, fmt);
    res = string_new_vprintf(string, fmt, args);
    va_end(args);

    return res;
}

__attribute__((format(printf, 2, 0)))
int string_prepend_vprintf(String *string, const char *fmt, va_list args) {
    return string_insert_vprintf(string, 0, fmt, args);
}

__attribute__((format(printf, 2, 3)))
int string_prepend_printf(String *string, const char *fmt, ...) {
    va_list args;
    int res = 0;

    va_start(args, fmt);
    res = string_prepend_vprintf(string, fmt, args);
    va_end(args);

    return res;
}

__attribute__((format(printf, 2, 0)))
int string_append_vprintf(String *string, const char *fmt, va_list args) {
    return string_insert_vprintf(string, string->len, fmt, args);
}

__attribute__((format(printf, 2, 3)))
int string_append_printf(String *string, const char *fmt, ...) {
    va_list args;
    int res = 0;

    va_start(args, fmt);
    res = string_append_vprintf(string, fmt, args);
    va_end(args);

    return res;
}

int string_replace_cstr(String *string, const char *cs,
                                        const char *replacement) {
    char *cursor = NULL;
    size_t cs_len = 0;
    size_t cs_byte_len = 0;
    size_t replacement_len = 0;
    size_t replacement_byte_len = 0;
    size_t index = 0;
    size_t temp_len = string->len;
    size_t temp_byte_len = string->buffer.len;

    /*
     * Find cstr
     * Delete cstr length
     * Insert replacement where cstr was
     * Update string len/byte_len
     */

    CBASE_PROPAGATE_ERROR(
        utf8_process_cstr(cs, &cs_len, &cs_byte_len)
    );

    CBASE_PROPAGATE_ERROR(
        utf8_process_cstr(replacement, &replacement_len, &replacement_byte_len)
    );


    CBASE_PROPAGATE_ERROR(
        strbase_seek_to_cstr(&cursor, &temp_len, &temp_byte_len, cs)
    );

    index = cursor - (char *)string->buffer.data;

    CBASE_PROPAGATE_ERROR(
        string_delete(string, index, cs_len)
    );

    CBASE_PROPAGATE_ERROR(
        buffer_insert_data(&string->buffer, index, replacement,
                                                   replacement_byte_len)
    );

    ssize_t len_diff = (ssize_t)cs_len - (ssize_t)replacement_len;

    string->len += len_diff;

    return 0;
}

/* vi: set et ts=4 sw=4: */

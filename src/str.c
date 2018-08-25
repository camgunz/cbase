#include <stdio.h>

#include "cbase.h"

#define vsnprintf_failed(status) status_failure( \
    status,                                      \
    "string",                                    \
    STRING_VSNPRINTF_FAILED,                     \
    "vsnprintf failed"                           \
)

void string_assign_cstr_full_fast(String *string, const char *cs,
                                                  size_t len,
                                                  size_t byte_len) {
    buffer_assign_data_fast(&string->buffer, cs, byte_len + 1);
    string->len = len;
}

bool string_assign_cstr_full(String *string, const char *cs, size_t len,
                                                             size_t byte_len,
                                                             Status *status) {
    if (!buffer_assign_data(&string->buffer, cs, byte_len + 1, status)) {
        return status_propagate(status);
    }

    string->len = len;

    return status_ok(status);
}

bool string_assign_cstr(String *string, const char *cs, Status *status) {
    size_t len = 0;
    size_t byte_len = 0;

    if (!utf8_process_cstr(cs, &len, &byte_len, status)) {
        return status_propagate(status);
    }

    return string_assign_cstr_full(string, cs, len, byte_len, status);
}

void string_assign_utf8_data_full_fast(String *string, const char *data,
                                                       size_t len,
                                                       size_t byte_len) {
    char terminating_null = '\0';

    buffer_assign_data_fast(&string->buffer, data, byte_len);
    buffer_append_data_fast(&string->buffer, &terminating_null, 1);

    string->len = len;
}

bool string_assign_utf8_data_full(String *string, const char *data,
                                                  size_t len,
                                                  size_t byte_len,
                                                  Status *status) {
    if (!buffer_ensure_capacity(&string->buffer, byte_len + 1, status)) {
        return status_propagate(status);
    }

    string_assign_utf8_data_full_fast(string, data, len, byte_len);

    return status_ok(status);
}

bool string_assign_utf8_data_fast(String *string, const char *data,
                                                  size_t byte_len) {
    size_t len = 0;

    if (data) {
        utf8_len(data, byte_len, &len);
    }

    string_assign_utf8_data_full_fast(string, data, len, byte_len);

    return status_ok(status);
}

bool string_assign_utf8_data(String *string, const char *data,
                                             size_t byte_len,
                                             Status *status) {
    size_t len = 0;

    if (data) {
        utf8_len(data, byte_len, &len);
    }

    return string_assign_utf8_data_full(string, data, len, byte_len, status);
}

void string_assign_sslice_fast(String *string, SSlice *sslice) {
    string_assign_utf8_data_full_fast(string, sslice->data, sslice->len,
                                                            sslice->byte_len);
}

bool string_assign_sslice(String *string, SSlice *sslice, Status *status) {
    return string_assign_utf8_data_full(string, sslice->data, sslice->len,
                                                              sslice->byte_len,
                                                              status);
}

bool string_assign_data_fast(String *string, const char *data,
                                             size_t byte_len,
                                             const char *encoding,
                                             Status *status) {
    Buffer input;

    /*
     * [TODO] Would be better to use *data instead of copying it.
     */

    if (!buffer_init_from_data(&input, data, byte_len, status)) {
        return status_propagate(status);
    }

    if ((!buffer_encode(&string->buffer, encoding, "utf-8", &input, status))) {
        buffer_free(&input);
        return status_propagate(status);
    }
    
    string_assign_utf8_data_fast(
        string, input.array.elements, input.array.len
    );

    buffer_free(&input);
    return status_ok(status);
}

bool string_assign_data(String *string, const char *data,
                                        size_t byte_len,
                                        const char *encoding,
                                        Status *status) {
    Buffer input;

    /* [TODO] Would be better to use *data instead of copying it. */

    if (!buffer_init_from_data(&input, data, byte_len, status)) {
        return status_propagate(status);
    }

    if ((!buffer_encode(&string->buffer, encoding, "utf-8", &input, status)) ||
        (!string_assign_utf8_data(string, input.array.elements,
                                          input.array.len,
                                          status))) {
        buffer_free(&input);
        return status_propagate(status);
    }

    buffer_free(&input);
    return status_ok(status);
}

bool string_assign_slice_fast(String *string, Slice *slice,
                                              const char *encoding,
                                              Status *status) {
    return string_assign_data_fast(
        string, slice->data, slice->len, encoding, status
    );
}

bool string_assign_slice(String *string, Slice *slice, const char *encoding,
                                                       Status *status) {
    return string_assign_data(
        string, slice->data, slice->len, encoding, status
    );
}

void string_assign_utf8_slice_fast(String *string, Slice *slice) {
    string_assign_utf8_data_fast(string, slice->data, slice->len);
}

bool string_assign_utf8_slice(String *string, Slice *slice, Status *status) {
    return string_assign_utf8_data(string, slice->data, slice->len, status);
}

bool string_assign_local_slice_fast(String *string, Slice *slice,
                                                    Status *status) {
    return string_assign_data_fast(string, slice->data,
                                           slice->len,
                                           "wchar_t",
                                           status);
}

bool string_assign_local_slice(String *string, Slice *slice, Status *status) {
    return string_assign_data(string, slice->data, slice->len, "wchar_t",
                                                               status);
}

bool string_assign_buffer_fast(String *string, Buffer *buffer,
                                               const char *encoding,
                                               Status *status) {
    return string_assign_data_fast(string, buffer->array.elements,
                                           buffer->array.len,
                                           encoding,
                                           status);
}

bool string_assign_buffer(String *string, Buffer *buffer, const char *encoding,
                                                          Status *status) {
    return string_assign_data(string, buffer->array.elements,
                                      buffer->array.len,
                                      encoding,
                                      status);
}

void string_assign_utf8_buffer_full_fast(String *string, Buffer *buffer,
                                                         size_t len) {
    string_assign_utf8_data_full_fast(string, buffer->array.elements,
                                              len,
                                              buffer->array.len);
}

bool string_assign_utf8_buffer_full(String *string, Buffer *buffer,
                                                    size_t len,
                                                    Status *status) {
    return string_assign_utf8_data_full(string, buffer->array.elements,
                                                len,
                                                buffer->array.len,
                                                status);
}

void string_assign_utf8_buffer_fast(String *string, Buffer *buffer) {
    string_assign_utf8_data_fast(string, buffer->array.elements,
                                         buffer->array.len);
}

bool string_assign_utf8_buffer(String *string, Buffer *buffer,
                                               Status *status) {
    return string_assign_utf8_data(string, buffer->array.elements,
                                           buffer->array.len,
                                           status);
}

bool string_assign_local_buffer_fast(String *string, Buffer *buffer,
                                                     Status *status) {
    return string_assign_buffer_fast(string, buffer, "wchar_t", status);
}

bool string_assign_local_buffer(String *string, Buffer *buffer,
                                                Status *status) {
    return string_assign_buffer(string, buffer, "wchar_t", status);
}

void string_assign_string_fast(String *dst, String *src) {
    string_assign_utf8_buffer_full_fast(dst, &src->buffer, src->len);
}

bool string_assign_string(String *dst, String *src, Status *status) {
    return string_assign_utf8_buffer_full(dst, &src->buffer, src->len, status);
}

bool string_ensure_capacity(String *string, size_t byte_len, Status *status) {
    return buffer_ensure_capacity(&string->buffer, byte_len + 1, status);
}

void string_init(String *string) {
    buffer_init(&string->buffer);
    string->len = 0;
}

bool string_init_alloc(String *string, size_t alloc, Status *status) {
    if (!buffer_init_alloc(&string->buffer, alloc, status)) {
        return status_propagate(status);
    }

    string->len = 0;

    return status_ok(status);
}

bool string_init_from_cstr(String *string, const char *cs, Status *status) {
    string_init(string);
    return string_assign_cstr(string, cs, status);
}

bool string_init_from_cstr_full(String *string, const char *cs,
                                                size_t len,
                                                size_t byte_len,
                                                Status *status) {
    string_init(string);
    return string_assign_cstr_full(string, cs, len, byte_len, status);
}

bool string_init_from_utf8_data(String *string, const char *data,
                                                size_t byte_len,
                                                Status *status) {
    string_init(string);
    return string_assign_utf8_data(string, data, byte_len, status);
}

bool string_init_from_utf8_data_full(String *string, const char *data,
                                                     size_t len,
                                                     size_t byte_len,
                                                     Status *status) {
    string_init(string);
    return string_assign_utf8_data_full(string, data, len, byte_len, status);
}

bool string_init_from_sslice(String *string, SSlice *sslice, Status *status) {
    string_init(string);
    return string_assign_sslice(string, sslice, status);
}

bool string_init_from_string(String *string, String *input, Status *status) {
    string_init(string);
    return string_assign_string(string, input, status);
}

bool string_init_from_slice(String *string, Slice *slice, const char *encoding,
                                                          Status *status) {
    string_init(string);
    return string_assign_slice(string, slice, encoding, status);
}

bool string_init_from_utf8_slice(String *string, Slice *slice,
                                                 Status *status) {
    string_init(string);
    return string_assign_utf8_slice(string, slice, status);
}

bool string_init_from_local_slice(String *string, Slice *slice, 
                                                  Status *status) {
    string_init(string);
    return string_assign_local_slice(string, slice, status);
}

bool string_init_from_buffer(String *string, Buffer *buffer,
                                             const char *encoding,
                                             Status *status) {
    string_init(string);
    return string_assign_buffer(string, buffer, encoding, status);
}

bool string_init_from_utf8_buffer(String *string, Buffer *buffer,
                                                  Status *status) {
    string_init(string);
    return string_assign_utf8_buffer(string, buffer, status);
}

bool string_init_from_local_buffer(String *string, Buffer *buffer,
                                                   Status *status) {
    string_init(string);
    return string_assign_local_buffer(string, buffer, status);
}

bool string_new(String **string, Status *status) {
    if (!cbmalloc(1, sizeof(String), string, status)) {
        return status_propagate(status);
    }

    string_init(*string);

    return status_ok(status);
}

bool string_new_alloc(String **string, size_t alloc, Status *status) {
    return (
        string_new(string, status) &&
        string_init_alloc(*string, alloc, status)
    );
}

bool string_new_from_cstr(String **string, const char *cs, Status *status) {
    return (
        string_new(string, status) &&
        string_init_from_cstr(*string, cs, status)
    );
}

bool string_new_from_cstr_full(String **string, const char *cs,
                                                size_t len,
                                                size_t byte_len,
                                                Status *status) {
    return (
        string_new(string, status) &&
        string_init_from_cstr_full(*string, cs, len, byte_len, status)
    );
}

bool string_new_from_utf8_data_full(String **string, const char *data,
                                                     size_t len,
                                                     size_t byte_len,
                                                     Status *status) {
    return (
        string_new(string, status) &&
        string_init_from_utf8_data_full(*string, data, len, byte_len, status)
    );
}

bool string_new_from_sslice(String **string, SSlice *sslice, Status *status) {
    return (
        string_new(string, status) &&
        string_init_from_sslice(*string, sslice, status)
    );
}

bool string_new_from_string(String **string, String *input, Status *status) {
    return (
        string_new(string, status) &&
        string_init_from_string(*string, input, status)
    );
}

bool string_new_from_slice(String **string, Slice *slice, const char *encoding,
                                                          Status *status) {
    return (
        string_new(string, status) &&
        string_init_from_slice(*string, slice, encoding, status)
    );
}

bool string_new_from_utf8_slice(String **string, Slice *slice,
                                                 Status *status) {
    return (
        string_new(string, status) &&
        string_init_from_utf8_slice(*string, slice, status)
    );
}

bool string_new_from_local_slice(String **string, Slice *slice, 
                                                  Status *status) {
    return (
        string_new(string, status) &&
        string_init_from_local_slice(*string, slice, status)
    );
}

bool string_new_from_buffer(String **string, Buffer *buffer,
                                             const char *encoding,
                                             Status *status) {
    return (
        string_new(string, status) &&
        string_init_from_buffer(*string, buffer, encoding, status)
    );
}

bool string_new_from_utf8_buffer(String **string, Buffer *buffer,
                                                  Status *status) {
    return (
        string_new(string, status) &&
        string_init_from_utf8_buffer(*string, buffer, status)
    );
}

bool string_new_from_local_buffer(String **string, Buffer *buffer,
                                                   Status *status) {
    return (
        string_new(string, status) &&
        string_init_from_local_buffer(*string, buffer, status)
    );
}

bool string_compact(String *string, Status *status) {
    return buffer_compact(&string->buffer, status);
}

bool string_index_rune(String *string, size_t index, rune *r, Status *status) {
    return utf8_index_rune(
        string->buffer.array.elements,
        string->buffer.array.len,
        index,
        r,
        status
    );
}

bool string_index_rune_reverse(String *string, size_t index, rune *r,
                                                             Status *status) {
    return strbase_index_rune_reverse(
        string->buffer.array.elements,
        string->len,
        index,
        r,
        status
    );
}

bool string_get_first_rune(String *string, rune *r, Status *status) {
    return string_index_rune(string, 0, r, status);
}

bool string_get_last_rune(String *string, rune *r, Status *status) {
    return utf8_get_last_rune(
        string->buffer.array.elements, string->buffer.array.len, r, status
    );
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

bool string_starts_with_rune(String *string, rune r, bool *starts_with,
                                                Status *status) {
    rune r2;

    if (!string_get_first_rune(string, &r2, status)) {
        return status_propagate(status);
    }

    *starts_with = (r2 == r);

    return status_ok(status);
}

bool string_starts_with_cstr_len(String *string, const char *cs,
                                                 size_t byte_len,
                                                 bool *starts_with,
                                                 Status *status) {
    if (!buffer_equals_data_at(&string->buffer, 0, cs, byte_len, starts_with,
                                                                 status)) {
        if (status_match(status, "base", ERROR_OUT_OF_BOUNDS)) {
            status_clear(status);
            *starts_with = false;
        }
        else {
            return status_propagate(status);
        }
    }

    return status_ok(status);
}

bool string_starts_with_cstr(String *string, const char *cs, bool *starts_with,
                                                             Status *status) {
    return string_starts_with_cstr_len(string, cs, strlen(cs), starts_with,
                                                               status);
}

bool string_ends_with_rune(String *string, rune r, bool *ends_with,
                                                   Status *status) {
    rune r2 = 0;

    if (!utf8_get_last_rune(string->buffer.array.elements,
                            string->buffer.array.len,
                            &r2,
                            status)) {
        return status_propagate(status);
    }

    *ends_with = (r2 == r);

    return status_ok(status);
}

bool string_ends_with_utf8_data(String *string, const char *cs,
                                                size_t byte_len,
                                                bool *ends_with,
                                                Status *status) {
    size_t index = string->buffer.array.len - byte_len;

    return buffer_equals_data_at(&string->buffer, index, cs, byte_len,
                                                             ends_with,
                                                             status);
}

bool string_ends_with_cstr(String *string, const char *cs, bool *ends_with,
                                                           Status *status) {
    return string_ends_with_utf8_data(string, cs, strlen(cs) + 1, ends_with,
                                                                  status);
}

void string_slice_fast(String *string, size_t index, size_t len,
                                                     SSlice *sslice) {
    char *start = NULL;
    char *end = NULL;

    utf8_slice_fast(
        string->buffer.array.elements,
        string->buffer.array.len,
        index,
        len,
        &start,
        &end
    );

    sslice_assign_full(sslice, start, len, end - start);
}

bool string_slice(String *string, size_t index, size_t len, SSlice *sslice,
                                                            Status *status) {
    char *start = NULL;
    char *end = NULL;

    if ((index + len) > string->len) {
        return index_out_of_bounds(status);
    }

    utf8_slice_fast(
        string->buffer.array.elements,
        string->buffer.array.len,
        index,
        len,
        &start,
        &end
    );

    sslice_assign_full(sslice, start, len, end - start);

    return status_ok(status);
}

void string_slice_full(String *string, SSlice *sslice) {
    sslice_assign_full(sslice, string->buffer.array.elements,
                               string->len,
                               string->buffer.array.len);
}

void string_delete_fast(String *string, size_t index, size_t rune_count) {
    char *start = string->buffer.array.elements;

    size_t byte_index = 0;
    size_t byte_len = 0;

    if (!rune_count) {
        return;
    }

    if (index) {
        utf8_index_fast(
            string->buffer.array.elements,
            string->buffer.array.len,
            index,
            &start
        );
        byte_index = start - (char *)string->buffer.array.elements;
    }

    size_t temp_len = string->len;
    size_t temp_byte_len = string->buffer.array.len;

    strbase_skip_runes_fast(&start, &temp_len, &temp_byte_len, rune_count);

    buffer_delete_fast(&string->buffer, byte_index, temp_byte_len - byte_len);

    string->len -= rune_count;
}


bool string_delete(String *string, size_t index, size_t rune_count,
                                                 Status *status) {
    char *start = string->buffer.array.elements;

    size_t byte_index = 0;
    size_t byte_len = 0;

    if (!rune_count) {
        return status_ok(status);
    }

    if (index) {
        if (!utf8_index(string->buffer.array.elements,
                        string->buffer.array.len,
                        index,
                        &start,
                        status)) {
            return status_propagate(error);
        }

        byte_index = start - (char *)string->buffer.array.elements;
    }

    size_t temp_len = string->len;
    size_t temp_byte_len = string->buffer.array.len;

    if (!strbase_skip_runes(&start, &temp_len, &temp_byte_len, rune_count,
                                                               status)) {
        return status_propagate(status);
    }

    if (!buffer_delete(&string->buffer, byte_index,
                                        temp_byte_len - byte_len,
                                        status)) {
        return status_propagate(status);
    }

    string->len -= rune_count;

    return status_ok(status);
}

bool string_skip_rune(String *string, Status *status) {
    return string_delete(string, 0, 1, status);
}

bool string_skip_runes(String *string, size_t rune_count, Status *status) {
    return string_delete(string, 0, rune_count, status);
}

bool string_skip_rune_if_equals(String *string, rune r, Status *status) {
    rune r2;

    if (!string_get_first_rune(string, &r2, status)) {
        return status_propagate(status);
    }

    if (r2 != r) {
        return not_equal(status);
    }

    return string_skip_runes(string, 1, status);
}

bool string_pop_rune(String *string, rune *r, Status *status) {
    return (
        string_get_first_rune(string, r, status) &&
        string_delete(string, 0, 1, status)
    );
}

bool string_pop_rune_if_matches(String *string, RuneMatchFunc *matches,
                                                rune *r,
                                                Status *status) {
    rune r2 = 0;
    size_t bytes_read = 0;

    if (!utf8_get_first_rune_len(string->buffer.array.elements, &r2,
                                                                &bytes_read,
                                                                status)) {
        return status_propagate(status);
    }

    if (!matches(r2)) {
        return not_found(status);
    }

    *r = r2;

    return string_delete(string, 0, 1, status);
}

bool string_skip_rune_if_matches(String *string, RuneMatchFunc *matches,
                                                 Status *status) {
    rune r = 0;

    return string_pop_rune_if_matches(string, matches, &r, status);
}

bool string_seek_to_rune(String *string, rune r, Status *status) {
    for (size_t i = 0; i < string->len; i++) {
        char *substring = NULL;
        rune r2;

        if (!utf8_index(string->buffer.array.elements,
                        string->buffer.array.len,
                        i,
                        &substring,
                        status)) {
            return status_propagate(status);
        }

        if (!utf8_get_first_rune(substring, &r2, status)) {
            return status_propagate(status);
        }

        if (r2 == r) {
            return string_delete(string, 0, i, status);
        }
    }

    return not_found(status);
}

bool string_seek_to_cstr(String *string, const char *cs, Status *status) {
    for (size_t i = 0; i < string->len; i++) {
        bool equal = false;
        char *substring = NULL;

        if (!utf8_index(string->buffer.array.elements,
                        string->buffer.array.len,
                        i,
                        &substring,
                        status)) {
            return status_propagate(status);
        }

        if (!utf8_cstr_equal(substring, cs, &equal, status)) {
            return status_propagate(status);
        }

        if (equal) {
            return string_delete(string, 0, i, status);
        }
    }

    return not_found(status);
}

bool string_truncate_runes(String *string, size_t rune_count, Status *status) {
    return string_delete(string, string->len - rune_count, rune_count, status);
}

bool string_truncate_rune(String *string, Status *status) {
    return string_truncate_runes(string, 1, status);
}

char* string_to_cstr(String *string) {
    Status status;
    char *out = NULL;

    if (!cbstrdup(string->buffer.array.elements, &out, &status)) {
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

bool string_insert_cstr_full(String *string, size_t index, const char *cs,
                                                           size_t len,
                                                           size_t byte_len,
                                                           Status *status) {
    if (index > string->len) {
        return index_out_of_bounds(status);
    }

    if (!string_ensure_capacity(string, string->buffer.array.len + byte_len,
                                        status)) {
        return status_propagate(status);
    }

    string_insert_cstr_full_fast(string, index, cs, len, byte_len);

    return status_ok(status);
}

bool string_insert_cstr(String *string, size_t index, const char *cs,
                                                      Status *status) {
    size_t len = 0;
    size_t byte_len = 0;

    if (cs) {
        if (!utf8_process_cstr(cs, &len, &byte_len, status)) {
            return status_propagate(status);
        }
    }

    string_insert_cstr_full(string, index, cs, len, byte_len, status);

    return status_ok(status);
}

void string_insert_utf8_data_full_fast(String *string, size_t index,
                                                       const char *data,
                                                       size_t len,
                                                       size_t byte_len) {
    buffer_insert_data_fast(&string->buffer, index, data, byte_len);
    buffer_insert_data_fast(&string->buffer, index + byte_len, "\0", 1);
    string->len += len;
}

bool string_insert_utf8_data_full(String *string, size_t index,
                                                  const char *data,
                                                  size_t len,
                                                  size_t byte_len,
                                                  Status *status) {
    if (index > string->len) {
        return index_out_of_bounds(status);
    }

    if (!string_ensure_capacity(string,
                                string->buffer.array.len + byte_len,
                                status)) {
        return status_propagate(status);
    }

    string_insert_utf8_data_full_fast(string, index, data, len, byte_len);

    return status_ok(status);
}

void string_insert_utf8_data_fast(String *string, size_t index,
                                                  const char *data,
                                                  size_t byte_len) {
    size_t len = 0;

    if (data) {
        utf8_len(data, byte_len, &len);
    }

    return string_insert_utf8_data_full_fast(
        string, index, data, len, byte_len
    );
}

bool string_insert_utf8_data(String *string, size_t index, const char *data,
                                                           size_t byte_len,
                                                           Status *status) {

    size_t len = 0;

    if (data) {
        utf8_len(data, byte_len, &len);
    }

    return string_insert_utf8_data_full(
        string, index, data, len, byte_len, status
    );
}

void string_insert_sslice_fast(String *string, size_t index, SSlice *sslice) {
    string_insert_utf8_data_full_fast(string, index, sslice->data,
                                                     sslice->len,
                                                     sslice->byte_len);
}

bool string_insert_sslice(String *string, size_t index, SSlice *sslice,
                                                        Status *status) {
    return string_insert_utf8_data_full(string, index, sslice->data,
                                                       sslice->len,
                                                       sslice->byte_len,
                                                       status);
}

void string_insert_string_fast(String *dst, size_t index, String *src) {
    return string_insert_cstr_full_fast(dst, index, src->buffer.array.elements,
                                                    src->len,
                                                    src->buffer.array.len);
}

bool string_insert_string(String *dst, size_t index, String *src,
                                                     Status *status) {
    return string_insert_cstr_full(dst, index, src->buffer.array.elements,
                                               src->len,
                                               src->buffer.array.len,
                                               status);
}

bool string_insert_slice_fast(String *string, size_t index,
                                              Slice *slice,
                                              const char *encoding,
                                              Status *status) {
    Buffer output;

    if (!buffer_init_alloc(&output, 64, status)) {
        return status_propagate(status);
    }

    if (!slice_encode(slice, encoding, "utf-8", &output, status)) {
        buffer_free(&output);
        return status_propagate(status);
    }

    string_insert_utf8_data_fast(string, index, output.array.elements,
                                                output.array.len);

    buffer_free(&output);

    return status_ok(status);
}

bool string_insert_slice(String *string, size_t index, Slice *slice,
                                                       const char *encoding,
                                                       Status *status) {
    Buffer output;

    if (!buffer_init_alloc(&output, 64, status)) {
        return status_propagate(status);
    }

    if ((!slice_encode(slice, encoding, "utf-8", &output, status)) ||
        (!string_insert_utf8_data(string, index, output.array.elements,
                                                 output.array.len,
                                                 status))) {
        buffer_free(&output);
        return status_propagate(status);
    }

    buffer_free(&output);
    return status_ok(status);
}

void string_insert_utf8_slice_fast(String *string, size_t index,
                                                   Slice *slice) {
    return string_insert_utf8_data_fast(
        string, index, slice->data, slice->len
    );
}

bool string_insert_utf8_slice(String *string, size_t index, Slice *slice,
                                                            Status *status) {
    return string_insert_utf8_data(string, index, slice->data, slice->len,
                                                               status);
}

bool string_insert_local_slice_fast(String *string, size_t index,
                                                    Slice *slice,
                                                    Status *status) {
    return string_insert_slice_fast(string, index, slice, "wchar_t", status);
}

bool string_insert_local_slice(String *string, size_t index, Slice *slice,
                                                             Status *status) {
    return string_insert_slice(string, index, slice, "wchar_t", status);
}

bool string_insert_buffer_fast(String *string, size_t index,
                                               Buffer *buffer,
                                               const char *encoding,
                                               Status *status) {
    Buffer output;

    if (!buffer_init_alloc(&output, 64, status)) {
        return status_propagate(status);
    }

    if (!buffer_encode(buffer, encoding, "utf-8", &output, status)) {
        buffer_free(&output);
        return status_propagate(status);
    }

    string_insert_utf8_data_fast(string, index, output.array.elements,
                                                output.array.len);

    buffer_free(&output);

    return status_ok(status);
}

bool string_insert_buffer(String *string, size_t index, Buffer *buffer,
                                                        const char *encoding,
                                                        Status *status) {
    Buffer output;

    if (!buffer_init_alloc(&output, 64, status)) {
        return status_propagate(status);
    }

    if ((!buffer_encode(buffer, encoding, "utf-8", &output, status)) ||
        (!string_insert_utf8_data(string, index, output.array.elements,
                                                 output.array.len,
                                                 status))) {
        buffer_free(&output);
        return status_propagate(status);
    }

    buffer_free(&output);
    return status_ok(status);
}

bool string_insert_utf8_buffer_fast(String *string, size_t index,
                                                    Buffer *buffer,
                                                    Status *status) {
    return string_insert_utf8_data(string, index, buffer->array.elements,
                                                  buffer->array.len,
                                                  status);
}

bool string_insert_utf8_buffer(String *string, size_t index, Buffer *buffer,
                                                             Status *status) {
    return string_insert_utf8_data(string, index, buffer->array.elements,
                                                  buffer->array.len,
                                                  status);
}

bool string_insert_local_buffer_fast(String *string, size_t index,
                                                     Buffer *buffer,
                                                     Status *status) {
    return string_insert_buffer_fast(string, index, buffer, "wchar_t", status);
}

bool string_insert_local_buffer(String *string, size_t index, Buffer *buffer,
                                                              Status *status) {
    return string_insert_buffer(string, index, buffer, "wchar_t", status);
}

bool string_insert_data_fast(String *string, size_t index,
                                             const char *data,
                                             size_t byte_len,
                                             const char *encoding,
                                             Status *status) {
    Slice slice;

    slice.data = (char *)data;
    slice.len = byte_len;

    return string_insert_slice_fast(string, index, &slice, encoding, status);
}

bool string_insert_data(String *string, size_t index, const char *data,
                                                      size_t byte_len,
                                                      const char *encoding,
                                                      Status *status) {
    Slice slice;

    slice.data = (char *)data;
    slice.len = byte_len;

    return string_insert_slice(string, index, &slice, encoding, status);
}

bool string_insert_local_data_fast(String *string, size_t index,
                                                   const char *data,
                                                   size_t byte_len,
                                                   Status *status) {
    return string_insert_data_fast(string, index, data, byte_len, "wchar_t",
                                                                  status);
}

bool string_insert_local_data(String *string, size_t index, const char *data,
                                                            size_t byte_len,
                                                            Status *status) {
    return string_insert_data(string, index, data, byte_len, "wchar_t",
                                                             status);
}

void string_prepend_cstr_full_fast(String *string, const char *cs,
                                                   size_t len,
                                                   size_t byte_len) {
    string_insert_cstr_full_fast(string, 0, cs, len, byte_len);
}

bool string_prepend_cstr_full(String *string, const char *cs, size_t len,
                                                              size_t byte_len,
                                                              Status *status) {
    return string_insert_cstr_full(string, 0, cs, len, byte_len, status);
}

bool string_prepend_cstr(String *string, const char *cs, Status *status) {
    return string_insert_cstr(string, 0, cs, status);
}

void string_prepend_utf8_data_full_fast(String *string, const char *data,
                                                        size_t len,
                                                        size_t byte_len) {
    string_insert_utf8_data_full_fast(string, 0, data, len, byte_len);
}

bool string_prepend_utf8_data_full(String *string, const char *data,
                                                   size_t len,
                                                   size_t byte_len,
                                                   Status *status) {
    return string_insert_utf8_data_full(string, 0, data, len, byte_len,
                                                              status);
}

bool string_prepend_utf8_data(String *string, const char *data,
                                              size_t byte_len,
                                              Status *status) {
    return string_insert_utf8_data(string, 0, data, byte_len, status);
}

void string_prepend_sslice_fast(String *string, SSlice *sslice) {
    string_insert_sslice_fast(string, 0, sslice);
}

bool string_prepend_sslice(String *string, SSlice *sslice, Status *status) {
    return string_insert_sslice(string, 0, sslice, status);
}

void string_prepend_string_fast(String *dst, String *src) {
    string_insert_string_fast(dst, 0, src);
}

bool string_prepend_string(String *dst, String *src, Status *status) {
    return string_insert_string(dst, 0, src, status);
}

bool string_prepend_slice_fast(String *string, Slice *slice,
                                               const char *encoding,
                                               Status *status) {
    return string_insert_slice_fast(string, 0, slice, encoding, status);
}

bool string_prepend_slice(String *string, Slice *slice, const char *encoding,
                                                        Status *status) {
    return string_insert_slice(string, 0, slice, encoding, status);
}

void string_prepend_utf8_slice_fast(String *string, Slice *slice) {
    string_insert_utf8_slice_fast(string, 0, slice);
}

bool string_prepend_utf8_slice(String *string, Slice *slice, Status *status) {
    return string_insert_utf8_slice(string, 0, slice, status);
}

bool string_prepend_local_slice_fast(String *string, Slice *slice,
                                                     Status *status) {
    return string_insert_local_slice_fast(string, 0, slice, status);
}

bool string_prepend_local_slice(String *string, Slice *slice, Status *status) {
    return string_insert_local_slice(string, 0, slice, status);
}

bool string_prepend_buffer_fast(String *string, Buffer *buffer,
                                                const char *encoding,
                                                Status *status) {
    return string_insert_buffer_fast(string, 0, buffer, encoding, status);
}

bool string_prepend_buffer(String *string, Buffer *buffer, const char *encoding,
                                                           Status *status) {
    return string_insert_buffer(string, 0, buffer, encoding, status);
}

bool string_prepend_utf8_buffer_fast(String *string, Buffer *buffer,
                                                     Status *status) {
    return string_insert_utf8_buffer_fast(string, 0, buffer, status);
}

bool string_prepend_utf8_buffer(String *string, Buffer *buffer,
                                                Status *status) {
    return string_insert_utf8_buffer(string, 0, buffer, status);
}

bool string_prepend_local_buffer_fast(String *string, Buffer *buffer,
                                                      Status *status) {
    return string_insert_local_buffer_fast(string, 0, buffer, status);
}

bool string_prepend_local_buffer(String *string, Buffer *buffer,
                                                 Status *status) {
    return string_insert_local_buffer(string, 0, buffer, status);
}

bool string_prepend_data_fast(String *string, const char *data,
                                              size_t byte_len,
                                              const char *encoding,
                                              Status *status) {
    return string_insert_data_fast(
        string, 0, data, byte_len, encoding, status
    );
}

bool string_prepend_data(String *string, const char *data,
                                         size_t byte_len,
                                         const char *encoding,
                                         Status *status) {
    return string_insert_data(string, 0, data, byte_len, encoding, status);
}

bool string_prepend_local_data_fast(String *string, const char *data,
                                                    size_t byte_len,
                                                    Status *status) {
    return string_insert_local_data_fast(string, 0, data, byte_len, status);
}

bool string_prepend_local_data(String *string, const char *data,
                                               size_t byte_len,
                                               Status *status) {
    return string_insert_local_data(string, 0, data, byte_len, status);
}

void string_append_cstr_full_fast(String *string, const char *cs,
                                                  size_t len,
                                                  size_t byte_len) {
    string_insert_cstr_full_fast(string, 0, cs, len, byte_len);
}

bool string_append_cstr_full(String *string, const char *cs, size_t len,
                                                             size_t byte_len,
                                                             Status *status) {
    return string_insert_cstr_full(string, 0, cs, len, byte_len, status);
}

bool string_append_cstr(String *string, const char *cs, Status *status) {
    return string_insert_cstr(string, 0, cs, status);
}

void string_append_utf8_data_full_fast(String *string, const char *data,
                                                       size_t len,
                                                       size_t byte_len) {
    string_insert_utf8_data_full_fast(string, 0, data, len, byte_len);
}

bool string_append_utf8_data_full(String *string, const char *data,
                                                  size_t len,
                                                  size_t byte_len,
                                                  Status *status) {
    return string_insert_utf8_data_full(string, 0, data, len, byte_len,
                                                              status);
}

bool string_append_utf8_data(String *string, const char *data,
                                             size_t byte_len,
                                             Status *status) {
    return string_insert_utf8_data(string, 0, data, byte_len, status);
}

void string_append_sslice_fast(String *string, SSlice *sslice) {
    string_insert_sslice_fast(string, 0, sslice);
}

bool string_append_sslice(String *string, SSlice *sslice, Status *status) {
    return string_insert_sslice(string, 0, sslice, status);
}

void string_append_string_fast(String *dst, String *src) {
    return string_insert_string_fast(dst, 0, src);
}

bool string_append_string(String *dst, String *src, Status *status) {
    return string_insert_string(dst, 0, src, status);
}

bool string_append_slice_fast(String *string, Slice *slice,
                                              const char *encoding,
                                              Status *status) {
    return string_insert_slice_fast(string, 0, slice, encoding, status);
}

bool string_append_slice(String *string, Slice *slice, const char *encoding,
                                                       Status *status) {
    return string_insert_slice(string, 0, slice, encoding, status);
}

void string_append_utf8_slice_fast(String *string, Slice *slice) {
    string_insert_utf8_slice_fast(string, 0, slice);
}

bool string_append_utf8_slice(String *string, Slice *slice, Status *status) {
    return string_insert_utf8_slice(string, 0, slice, status);
}

bool string_append_local_slice_fast(String *string, Slice *slice,
                                                    Status *status) {
    return string_insert_local_slice_fast(string, 0, slice, status);
}

bool string_append_local_slice(String *string, Slice *slice, Status *status) {
    return string_insert_local_slice(string, 0, slice, status);
}

bool string_append_buffer_fast(String *string, Buffer *buffer,
                                               const char *encoding,
                                               Status *status) {
    return string_insert_buffer_fast(string, 0, buffer, encoding, status);
}

bool string_append_buffer(String *string, Buffer *buffer, const char *encoding,
                                                          Status *status) {
    return string_insert_buffer(string, 0, buffer, encoding, status);
}

bool string_append_utf8_buffer_fast(String *string, Buffer *buffer,
                                                    Status *status) {
    return string_insert_utf8_buffer_fast(string, 0, buffer, status);
}

bool string_append_utf8_buffer(String *string, Buffer *buffer,
                                               Status *status) {
    return string_insert_utf8_buffer(string, 0, buffer, status);
}

bool string_append_local_buffer_fast(String *string, Buffer *buffer,
                                                     Status *status) {
    return string_insert_local_buffer_fast(string, 0, buffer, status);
}

bool string_append_local_buffer(String *string, Buffer *buffer,
                                                Status *status) {
    return string_insert_local_buffer(string, 0, buffer, status);
}

bool string_append_data_fast(String *string, const char *data,
                                             size_t byte_len,
                                             const char *encoding,
                                             Status *status) {
    return string_insert_data_fast(string, 0, data, byte_len, encoding,
                                                              status);
}

bool string_append_data(String *string, const char *data,
                                        size_t byte_len,
                                        const char *encoding,
                                        Status *status) {
    return string_insert_data(string, 0, data, byte_len, encoding, status);
}

bool string_append_local_data_fast(String *string, const char *data,
                                                   size_t byte_len,
                                                   Status *status) {
    return string_insert_local_data_fast(string, 0, data, byte_len, status);
}

bool string_append_local_data(String *string, const char *data,
                                              size_t byte_len,
                                              Status *status) {
    return string_insert_local_data(string, 0, data, byte_len, status);
}

bool string_replace_cstr(String *s, const char *cs, const char *replacement,
                                                    Status *status);

bool string_encode(String *string, const char *encoding, Buffer *out,
                                                         Status *status) {
    return strbase_encode(
        string->buffer.array.elements,
        string->buffer.array.len,
        encoding,
        out,
        status
    );
}

bool string_localize(String *string, Buffer *out, Status *status) {
    return strbase_localize(
        string->buffer.array.elements,
        string->buffer.array.len,
        out,
        status
    );
}

void string_clear(String *string) {
    buffer_clear(&string->buffer);
    strbase_clear(&string->len, &string->buffer.array.len);
}

void string_free(String *string) {
    buffer_free(&string->buffer);
    strbase_clear(&string->len, &string->buffer.array.len);
}

bool string_insert_printf(String *string, size_t index, Status *status,
                                                        const char *fmt,
                                                        ...) {
    va_list args;
    bool res;

    va_start(args, fmt);
    res = string_insert_vprintf(string, index, status, fmt, args);
    va_end(args);

    if (!res) {
        return status_propagate(status);
    }

    return status_ok(status);
}

bool string_vprintf(String *string, Status *status, const char *fmt,
                                                    va_list args) {
    string_clear(string);
    return string_insert_vprintf(string, 0, status, fmt, args);
}

bool string_printf(String *string, Status *status, const char *fmt, ...) {
    va_list args;
    bool res;

    va_start(args, fmt);
    res = string_vprintf(string, status, fmt, args);
    va_end(args);

    if (!res) {
        return status_propagate(status);
    }

    return status_ok(status);
}

bool string_init_vprintf(String *string, Status *status, const char *fmt,
                                                         va_list args) {
    string_init(string);
    return string_vprintf(string, status, fmt, args);
}

bool string_init_printf(String *string, Status *status, const char *fmt, ...) {
    bool res;
    va_list args;

    va_start(args, fmt);
    res = string_init_vprintf(string, status, fmt, args);
    va_end(args);

    if (!res) {
        return status_propagate(status);
    }

    return status_ok(status);
}

bool string_new_vprintf(String **string, Status *status, const char *fmt,
                                                         va_list args) {
    return (
        string_new(string, status) &&
        string_init_vprintf(*string, status, fmt, args)
    );
}

bool string_new_printf(String **string, Status *status, const char *fmt, ...) {
    va_list args;
    bool res;

    va_start(args, fmt);
    res = string_new_vprintf(string, status, fmt, args);
    va_end(args);

    if (!res) {
        return status_propagate(status);
    }

    return status_ok(status);
}

bool string_prepend_vprintf(String *string, Status *status, const char *fmt,
                                                            va_list args) {
    return string_insert_vprintf(string, 0, status, fmt, args);
}

bool string_prepend_printf(String *string, Status *status, const char *fmt,
                                                           ...) {
    va_list args;
    bool res;

    va_start(args, fmt);
    res = string_prepend_vprintf(string, status, fmt, args);
    va_end(args);

    if (!res) {
        return status_propagate(status);
    }

    return status_ok(status);
}

bool string_append_vprintf(String *string, Status *status, const char *fmt,
                                                           va_list args) {
    return string_insert_vprintf(string, string->len, status, fmt, args);
}

bool string_append_printf(String *string, Status *status, const char *fmt,
                                                          ...) {
    va_list args;
    bool res;

    va_start(args, fmt);
    res = string_append_vprintf(string, status, fmt, args);
    va_end(args);

    if (!res) {
        return status_propagate(status);
    }

    return status_ok(status);
}

bool string_insert_vprintf(String *string, size_t index, Status *status,
                                                         const char *fmt,
                                                         va_list args) {
    va_list args2;
    int byte_size;

    if (index > string->len) {
        return index_out_of_bounds(status);
    }

    va_copy(args2, args);
    byte_size = vsnprintf(NULL, 0, fmt, args2);
    va_end(args2);

    if (byte_size < 0) {
        return vsnprintf_failed(status);
    }

    if (!string_ensure_capacity(string,
                                string->buffer.array.len + (size_t)byte_size,
                                status)) {
        return status_propagate(status);
    }

    char *cursor = string->buffer.array.elements;
    size_t len = string->len;
    size_t byte_len = string->buffer.array.len;

    if (!strbase_skip_runes(&cursor, &len, &byte_len, index, status)) {
        return status_propagate(status);
    }

    if (!buffer_insert_blank_data_no_zero(
            &string->buffer,
            cursor - (char *)string->buffer.array.elements,
            (size_t)byte_size,
            status)) {
        return status_propagate(status);
    }

    int bytes_written = vsnprintf(cursor, byte_size + 1, fmt, args);

    if (bytes_written != (byte_size - 1)) {
        return vsnprintf_failed(status);
    }

    if (!utf8_process(string->buffer.array.elements, string->buffer.array.len,
                                                     &string->len,
                                                     status)) {
        return status_propagate(status);
    }

    return status_ok(status);
}

bool string_replace_cstr(String *string, const char *cs,
                                         const char *replacement,
                                         Status *status) {
    char *cursor = NULL;
    size_t cs_len = 0;
    size_t cs_byte_len = 0;
    size_t replacement_len = 0;
    size_t replacement_byte_len = 0;
    size_t index = 0;
    size_t temp_len = string->len;
    size_t temp_byte_len = string->buffer.array.len;

    /*
     * Find cstr
     * Delete cstr length
     * Insert replacement where cstr was
     * Update string len/byte_len
     */

    if (!utf8_process_cstr(cs, &cs_len, &cs_byte_len, status)) {
        return status_propagate(status);
    }

    if (!utf8_process_cstr(replacement, &replacement_len,
                                        &replacement_byte_len,
                                        status)) {
        return status_propagate(status);
    }


    if (!strbase_seek_to_cstr(&cursor, &temp_len, &temp_byte_len, cs,
                                                                  status)) {
        return status_propagate(status);
    }

    index = cursor - (char *)string->buffer.array.elements;

    if (!string_delete(string, index, cs_len, status)) {
        return status_propagate(status);
    }

    if (!buffer_insert_data(&string->buffer, index, replacement,
                                                    replacement_byte_len,
                                                    status)) {
        return status_propagate(status);
    }

    ssize_t len_diff = (ssize_t)cs_len - (ssize_t)replacement_len;

    string->len += len_diff;

    return status_ok(status);
}

/* vi: set et ts=4 sw=4: */

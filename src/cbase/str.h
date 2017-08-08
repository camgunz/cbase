#ifndef STR_H__
#define STR_H__

enum {
    STRING_EMPTY = 1,
};

typedef struct StringStruct {
    Buffer buffer;
    size_t len;
    size_t byte_len;
} String;

static inline
void string_assign_full_fast(String *string, const char *data,
                                             size_t len,
                                             size_t byte_len) {
    char terminating_null = '\0';

    buffer_assign_fast(&string->buffer, data, byte_len);
    buffer_append_fast(&string->buffer, &terminating_null, 1);

    string->len = len;
    string->byte_len = byte_len;
}

static inline
bool string_assign_full(String *string, const char *data, size_t len,
                                                          size_t byte_len,
                                                          Status *status) {
    char terminating_null = '\0';

    if (!buffer_ensure_capacity(&string->buffer, byte_len + 1, status)) {
        return false;
    }

    if (!buffer_assign(&string->buffer, data, byte_len)) {
        return false;
    }

    if (!buffer_append_fast(&string->buffer, &terminating_null, 1)) {
        return false;
    }

    string->len = len;
    string->byte_len = byte_len;

    return status_ok(status);
}

static inline
bool string_assign(String *string, const char *data, size_t byte_len,
                                                     Status *status) {
    size_t len = 0;

    if (data) {
        if (!utf8ncmp(data, byte_len, &len, status)) {
            return false;
        }
    }

    return string_assign_full(string, data, len, byte_len, status);
}

static inline
void string_assign_cstr_full_fast(String *string, const char *cs,
                                                  size_t len,
                                                  size_t byte_len) {
    buffer_assign_fast(&string->buffer, cs, byte_len + 1);
    string->len = len;
    string->byte_len = byte_len;
}

static inline
bool string_assign_cstr_full(String *string, const char *cs, size_t len,
                                                             size_t byte_len,
                                                             Status *status) {
    if (!buffer_assign(&string->buffer, cs, byte_len + 1, status)) {
        return false;
    }

    string->len = len;
    string->byte_len = byte_len;
}

static inline
bool string_assign_cstr(String *string, const char *cs, Status *status) {
    size_t len = 0;
    size_t byte_len = 0;

    if (cs) {
        if (!utf8_len_and_byte_len(cs, &len, &byte_len, status)) {
            return false;
        }
    }

    return string_assign_cstr_full(string, cs, len, byte_len, status);
}

static inline
void string_assign_sslice_fast(String *string, SSlice *sslice) {
    string_assign_full_fast(string, sslice->data, sslice->len,
                                                  sslice->byte_len);
}

static inline
bool string_assign_sslice(String *string, SSlice *sslice, Status *status) {
    return string_assign_full_fast(string, sslice->data, sslice->len,
                                                         sslice->byte_len,
                                                         status);
}

bool string_assign_slice(String *s, Slice *slice, const char *encoding,
                                                  Status *status);

static inline
bool string_assign_local_slice(String *s, Slice *slice, Status *status) {
    return string_assign_slice(s, slice, "wchar_t", status);
}

bool string_assign_buffer(String *s, Buffer *buffer, const char *encoding,
                                                     Status *status);

static inline
bool string_assign_local_buffer(String *s, Buffer *buffer, Status *status) {
    return string_assign_buffer(s, buffer, "wchar_t", status);
}

static inline
bool string_ensure_capacity(String *s, size_t byte_len, Status *status) {
    return buffer_ensure_capacity(&s->buffer, byte_len + 1, status);
}

static inline
void string_init(String *string) {
    buffer_init(&string->buffer, sizeof(char));
    string->len = 0;
    string->byte_len = 0;
}

static inline
void string_init_from_data(String *string, char *data, size_t byte_len,
                                                       Status *status) {
    string_init(string);
    return string_assign(string, data, byte_len, status);
}

static inline
bool string_init_from_local_slice(String *s, Slice *slice, Status *status) {
    return string_init_from_slice(s, slice, "wchar_t", status);
}

static inline
bool string_init_from_local_buffer(String *s, Buffer *buffer, Status *status) {
    return string_init_from_buffer(s, buffer, "wchar_t", status);
}

static inline
bool string_new_from_local_slice(String **s, Slice *slice, Status *status) {
    return string_new_from_slice(s, slice, "wchar_t", status);
}

static inline
bool string_new_from_local_buffer(String **s, Buffer *buffer, Status *status) {
    return string_new_from_buffer(s, buffer, "wchar_t", status);
}

static inline
bool string_init_from_cstr(String *string, const char *cs, Status *status) {
    string_init(string);
    return string_assign_cstr(string, cs, status);
}

static inline
bool string_init_from_cstr_full(String *string, const char *cs,
                                                size_t len,
                                                size_t byte_len,
                                                Status *status) {
    string_init(string);
    return string_assign_cstr_full(string, cs, len, byte_len, status);
}

static inline
bool string_init_from_sslice(String *string, SSlice *sslice, Status *status) {
    string_init(string);
    return string_assign_sslice(string, sslice, status);
}

static inline
bool string_init_from_slice(String *string, Slice *slice, const char *encoding,
                                                          Status *status) {
    string_init(string);
    return string_assign_slice(string, slice, encoding, status);
}

static inline
bool string_init_from_buffer(String *string, Buffer *buffer,
                                             const char *encoding,
                                             Status *status) {
    string_init(string);
    return string_assign_buffer(string, buffer, encoding, status);
}

static inline
bool string_new(String **string, Status *status) {
    *string = cbmalloc(1, sizeof(String));

    if (!*string) {
        return alloc_failure(status);
    }

    string_init(*string);

    return status_ok(status);
}

static inline
bool string_new_from_cstr(String **string, const char *cs, Status *status) {
    String *new_string = cbmalloc(1, sizeof(String));

    if (!new_string) {
        return alloc_failure(status);
    }

    if (!string_init_from_cstr(new_string, cs, status)) {
        return false;
    }

    return status_ok(status);
}

bool string_new_from_cstr_full(String *string, const char *cs,
                                                size_t len,
                                                size_t byte_len,
                                                Status *status) {
    String *new_string = cbmalloc(1, sizeof(String));

    if (!new_string) {
        return alloc_failure(status);
    }

    if (!string_init_from_cstr_full(new_string, cs, len, byte_len, status)) {
        return false;
    }

    return status_ok(status);
}

bool string_new_from_sslice(String *string, SSlice *sslice, Status *status) {
    String *new_string = cbmalloc(1, sizeof(String));

    if (!new_string) {
        return alloc_failure(status);
    }

    if (!string_init_from_sslice(new_string, sslice, status)) {
        return false;
    }

    return status_ok(status);
}

bool string_new_from_slice(String *string, Slice *slice, const char *encoding,
                                                         Status *status) {
    String *new_string = cbmalloc(1, sizeof(String));

    if (!new_string) {
        return alloc_failure(status);
    }

    if (!string_init_from_slice(new_string, slice, encoding, status)) {
        return false;
    }

    return status_ok(status);
}

bool string_new_from_buffer(String *string, Buffer *buffer,
                                            const char *encoding,
                                            Status *status) {
    String *new_string = cbmalloc(1, sizeof(String));

    if (!new_string) {
        return alloc_failure(status);
    }

    if (!string_init_from_buffer(new_string, buffer, encoding, status)) {
        return false;
    }

    return status_ok(status);
}

static inline
bool string_compact(String *string, Status *status) {
    return buffer_compact(&string->buffer, status);
}

bool  string_copy(String *dst, String *src, Status *status);

static inline
bool string_slice_fast(String *s, size_t index, size_t len, SSlice *sslice,
                                                            ssize_t *error) {
    char *start = NULL;
    char *end = NULL;

    if (!utf8_slice_fast(s->data, index, len, &start, &end, error)) {
        return false;
    }

    sslice->len = len;
    sslice->byte_len = end - start;
    sslice->data = start;

    return true;
}

static inline
void string_slice_full(String *s, SSlice *sslice) {
    sslice->data = s->data;
    sslice->len = s->len;
    sslice->byte_len = s->byte_len;
}

bool  string_slice(String *s, size_t index, size_t len, SSlice *sslice,
                                                        Status *status);

bool  string_prepend(String *s, SSlice *sslice, Status *status);
bool  string_insert(String *s, size_t pos, SSlice *sslice, Status *status);
bool  string_insert_cstr_full(String *s, size_t pos, const char *data,
                                                     size_t len,
                                                     size_t byte_len,
                                                     Status *status);
bool  string_insert_cstr_fast(String *s, size_t pos, const char *data,
                                                     size_t len,
                                                     size_t byte_len,
                                                     ssize_t *error);
bool  string_append(String *s, SSlice *sslice, Status *status);
bool  string_printf(String *s, Status *status, const char *fmt, ...);
bool  string_vprintf(String *s, Status *status, const char *fmt, va_list args);
bool  string_append_printf(String *s, Status *status, const char *fmt, ...);
bool  string_append_vprintf(String *s, Status *status, const char *fmt,
                                                       va_list args);
bool  string_delete(String *s, size_t index, size_t len, Status *status);
bool  string_delete_fast(String *s, size_t index, size_t len, ssize_t *error);
bool  string_encode(String *s, const char *encoding, Buffer *out,
                                                     Status *status);

void  string_free(String *s);

static inline
void string_prepend_cstr_fast(String *s, const char *data, size_t len,
                                                           size_t byte_len) {
    if (byte_len) {
        memmove(s->data + byte_len, s->data, s->byte_len + 1);
        memmove(s->data, data, byte_len);
    }

    s->len += len;
    s->byte_len += byte_len;
}

static inline
bool string_prepend_cstr_full(String *s, const char *data, size_t len,
                                                           size_t byte_len,
                                                           Status *status) {
    if (!string_ensure_capacity(s, s->byte_len + byte_len, status)) {
        return false;
    }

    string_prepend_cstr_fast(s, data, len, byte_len);

    return status_ok(status);
}

static inline
bool string_prepend_cstr_len(String *s, const char *data, size_t byte_len,
                                                          Status *status) {
    size_t len;

    return utf8len(data, &len, status) &&
           string_prepend_cstr_full(s, data, len, byte_len, status);
}

static inline
bool string_prepend_cstr(String *s, const char *data, Status *status) {
    return string_prepend_cstr_len(s, data, strlen(data), status);
}

static inline
bool string_prepend_str(String *s, String *s2, Status *status) {
    return string_prepend_cstr_full(
        s, s2->data, s2->len, s2->byte_len, status
    );
}

static inline
void string_prepend_str_fast(String *s, String *s2) {
    string_prepend_cstr_fast(s, s2->data, s2->len, s2->byte_len);
}

static inline
void string_prepend_fast(String *s, SSlice *sslice) {
    string_prepend_cstr_fast(s, sslice->data, sslice->len, sslice->byte_len);
}

static inline
bool string_insert_cstr_len(String *s, size_t pos, const char *data,
                                                   size_t byte_len,
                                                   Status *status) {
    size_t len = 0;

    return utf8len(data, &len, status) &&
           string_insert_cstr_full(s, pos, data, len, byte_len, status);
}

static inline
bool string_insert_cstr(String *s, size_t pos, const char *data,
                                               Status *status) {
    return string_insert_cstr_len(s, pos, data, strlen(data), status);
}

static inline
bool string_insert_str(String *s, size_t pos, String *s2, Status *status) {
    return string_insert_cstr_full(
        s, pos, s2->data, s2->len, s2->byte_len, status
    );
}

static inline
bool string_insert_str_fast(String *s, size_t pos, String *s2,
                                                   ssize_t *error) {
    return string_insert_cstr_fast(
        s, pos, s2->data, s2->len, s2->byte_len, error
    );
}

static inline
bool string_insert_fast(String *s, size_t pos, SSlice *sslice, ssize_t *error) {
    char *start = s->data;

    if (pos) {
        if (!utf8_index_fast(s->data, pos, &start, error)) {
            return false;
        }
    }

    size_t byte_offset = (start - s->data) - 1;

    if (s->byte_len && (byte_offset < s->byte_len)) {
        memmove(start + sslice->byte_len, start, s->byte_len - byte_offset);
    }

    memmove(start, sslice->data, sslice->byte_len);

    s->len += sslice->len;
    s->byte_len += sslice->byte_len;

    return true;
}

static inline
void string_append_cstr_fast(String *s, const char *data, size_t len,
                                                          size_t byte_len) {
    if (byte_len) {
        memmove(s->data + s->byte_len, data, byte_len);
    }

    s->len += len;
    s->byte_len += byte_len;
    *(s->data + s->byte_len) = '\0';
}

static inline
bool string_append_cstr_full(String *s, const char *data, size_t len,
                                                          size_t byte_len,
                                                          Status *status) {
    if (!string_ensure_capacity(s, s->byte_len + byte_len, status)) {
        return false;
    }

    string_append_cstr_fast(s, data, len, byte_len);

    return status_ok(status);
}

static inline
bool string_append_cstr_len(String *s, const char *data, size_t byte_len,
                                                         Status *status) {
    size_t len;

    return utf8len(data, &len, status) &&
           string_append_cstr_full(s, data, len, byte_len, status);
}

static inline
bool string_append_cstr(String *s, const char *data, Status *status) {
    return string_append_cstr_len(s, data, strlen(data), status);
}

static inline
bool string_append_str(String *s, String *s2, Status *status) {
    return string_append_cstr_full(s, s2->data, s2->len, s2->byte_len, status);
}

static inline
void string_append_str_fast(String *s, String *s2) {
    string_append_cstr_fast(s, s2->data, s2->len, s2->byte_len);
}

static inline
void string_append_fast(String *s, SSlice *sslice) {
    string_append_cstr_fast(s, sslice->data, sslice->len, sslice->byte_len);
}

static inline
bool string_get_first_rune(String *s, rune *r, Status *status) {
    return sbuffer_get_first_rune(s->data, r, status);
}

static inline
void string_copy_fast(String *dst, String *src) {
    dst->len = src->len;
    dst->byte_len = src->byte_len;

    if (src->byte_len) {
        cbmemmove(dst->data, src->data, src->byte_len + 1);
    }
}

static inline
bool string_skip_runes(String *s, size_t rune_count, Status *status) {
    SSlice sslice;

    string_slice_full(s, &sslice);

    return (
        sslice_skip_runes(s, rune_count, status) &&
        string_assign_sslice(s, &sslice)
    );
}

static inline
bool string_skip_rune_if_equals(String *s, rune r, Status *status) {
    SSlice sslice;

    string_slice_full(s, &sslice);

    return (
        sslice_skip_rune_if_equals(s, r, status) &&
        string_assign_sslice(s, &sslice)
    );
}

static inline
bool string_pop_rune(String *s, rune *r, Status *status) {
    SSlice sslice;

    string_slice_full(s, &sslice);

    return (
        sslice_pop_rune(s, r, status) &&
        string_assign_sslice(s, &sslice)
    );
}

static inline
bool string_seek_to(String *s, rune r, Status *status) {
    SSlice sslice;

    string_slice_full(s, &sslice);

    return (
        sslice_seek_to(s, r, status) &&
        string_assign_sslice(s, &sslice)
    );
}

static inline
bool string_seek_to_cstr(String *s, const char *cs, Status *status) {
    SSlice sslice;

    string_slice_full(s, &sslice);

    return (
        sslice_seek_to_cstr(s, cs, status) &&
        string_assign_sslice(s, &sslice)
    );
}

static inline
bool string_truncate_runes(String *s, size_t rune_count, Status *status) {
    SSlice sslice;

    string_slice_full(s, &sslice);

    return (
        sslice_truncate_runes(s, rune_count, status) &&
        string_assign_sslice(s, &sslice)
    );
}

static inline
bool string_empty(String *s) {
    return sbufer_empty(s->len, s->byte_len);
}

static inline
char* string_to_cstr(String *s) {
    return cbstrdup(s->data);
}

static inline
bool string_contents_equal(String *s1, String *s2) {
    return buffer_equals(&s1->buffer, &s2->buffer);
}

static inline
bool string_equals_cstr_len(String *string, const char *cs, size_t byte_len) {
    return buffer_equals_data(&string->buffer, cs, byte_len);
}

static inline
bool string_equals_cstr(String *string, const char *cs) {
    return buffer_equals_data(&string->buffer, cs, strlen(cs) + 1);
}

static inline
bool string_starts_with_cstr_len(String *string, const char *cs,
                                                 size_t byte_len,
                                                 bool *starts_with,
                                                 Status *status) {
    if (!buffer_equals_data_at(&string->buffer, 0, cs, byte_len, starts_with,
                                                                 status)) {
        if (status_match(status, "base", ERROR_OUT_OF_BOUNDS)) {
            status_clear(&status);
            *starts_with = false;
        }
        else {
            return false;
        }
    }

    return status_ok(status);
}

static inline
bool string_starts_with_cstr(String *string, const char *cs, bool *starts_with,
                                                             Status *status) {
    return string_starts_with_cstr_len(string, cs, strlen(cs), starts_with,
                                                               status);
}

static inline
bool string_ends_with_cstr_len(String *string, const char *cs,
                                               size_t byte_len,
                                               bool *ends_with,
                                               Status *status) {
    size_t index = string->buffer.len - byte_len;

    return buffer_equals_data_at(&string->buffer, index, byte_len, ends_with,
                                                                   status);
}

static inline
bool string_ends_with_cstr(String *string, const char *cs, bool *ends_with,
                                                           Status *status) {
    return string_ends_with_cstr_len(string, cs, strlen(cs) + 1, ends_with,
                                                                 status);
}

static inline
bool string_localize(String *s, Buffer *out, Status *status) {
    return string_encode(s, "wchar_t", out, status);
}

static inline
void string_clear(String *s) {
    buffer_clear_no_zero(&string->buffer);
    sbuffer_clear(&s->len, &s->byte_len);
    if (s->data) {
        *s->data = '\0';
    }
}

#endif

/* vi: set et ts=4 sw=4: */

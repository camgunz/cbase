#ifndef STR_H__
#define STR_H__

typedef struct StringStruct {
    size_t len;
    size_t byte_len;
    size_t alloc;
    char *data;
} String;

/* [TODO] More printfs would be nice */

bool string_init(String *s, const char *data, Status *status);
bool string_init_len(String *s, const char *data, size_t len, Status *status);
bool string_init_full(String *s, const char *data, size_t len,
                                                   size_t byte_len,
                                                   Status *status);
bool string_new(String **s, const char *data, Status *status);
bool string_new_len(String **s, const char *data, size_t byte_len,
                                                  Status *status);
bool string_new_full(String **s, const char *data, size_t len,
                                                   size_t byte_len,
                                                   Status *status);
bool string_init_from_sslice(String *s, SSlice *ss, Status *status);
bool string_ensure_capacity(String *s, size_t byte_len, Status *status);
bool string_assign(String *s, const char *data, Status *status);
bool string_assign_len(String *s, const char *data, size_t byte_len,
                                                    Status *status);
bool string_assign_full(String *s, const char *data, size_t len,
                                                     size_t byte_len,
                                                     Status *status);
bool string_assign_slice(String *s, SSlice *sslice, Status *status);
bool string_shrink(String *s, Status *status);
bool string_copy(String *dst, String *src, Status *status);
bool string_slice(String *s, size_t index, size_t len, SSlice *sslice,
                                                       Status *status);

bool string_prepend(String *s, SSlice *sslice, Status *status);
bool string_insert(String *s, size_t pos, SSlice *sslice, Status *status);
bool string_insert_cstr_full(String *s, size_t pos, const char *data,
                                                    size_t len,
                                                    size_t byte_len,
                                                    Status *status);
bool string_insert_cstr_fast(String *s, size_t pos, const char *data,
                                                    size_t len,
                                                    size_t byte_len,
                                                    ssize_t *error);
bool string_append(String *s, SSlice *sslice, Status *status);
bool string_printf(String *s, Status *status, const char *fmt, ...);
bool string_delete(String *s, size_t index, size_t len, Status *status);
bool string_delete_fast(String *s, size_t index, size_t len, ssize_t *error);
void string_free(String *s);

static inline void string_assign_cstr_full_fast(String *s, const char *data,
                                                           size_t len,
                                                           size_t byte_len) {
    s->len = len;
    s->byte_len = byte_len;
    if (byte_len) {
        memmove(s->data, data, byte_len + 1);
    }
}

static inline void string_assign_fast(String *s, SSlice *sslice) {
    string_assign_cstr_full_fast(s, sslice->data, sslice->len, sslice->byte_len);
}

static inline void string_copy_fast(String *dst, String *src) {
    dst->len = src->len;
    dst->byte_len = src->byte_len;

    if (src->byte_len) {
        memmove(dst->data, src->data, src->byte_len + 1);
    }
}

static inline bool string_slice_fast(String *s, size_t index, size_t len,
                                                              SSlice *sslice,
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

static inline void string_prepend_cstr_fast(String *s, const char *data,
                                                       size_t len,
                                                       size_t byte_len) {
    if (byte_len) {
        memmove(s->data + byte_len, s->data, s->byte_len + 1);
        memmove(s->data, data, byte_len);
    }

    s->len += len;
    s->byte_len += byte_len;
}

static inline bool string_prepend_cstr_full(String *s, const char *data,
                                                       size_t len,
                                                       size_t byte_len,
                                                       Status *status) {
    if (!string_ensure_capacity(s, s->byte_len + byte_len, status)) {
        return false;
    }

    string_prepend_cstr_fast(s, data, len, byte_len);

    return status_ok(status);
}

static inline bool string_prepend_cstr_len(String *s, const char *data,
                                                      size_t byte_len,
                                                      Status *status) {
    size_t len;

    return utf8len(data, &len, status) &&
           string_prepend_cstr_full(s, data, len, byte_len, status);
}

static inline bool string_prepend_cstr(String *s, const char *data,
                                                  Status *status) {
    return string_prepend_cstr_len(s, data, strlen(data), status);
}

static inline bool string_prepend_str(String *s, String *s2, Status *status) {
    return string_prepend_cstr_full(
        s, s2->data, s2->len, s2->byte_len, status
    );
}

static inline void string_prepend_str_fast(String *s, String *s2) {
    string_prepend_cstr_fast(s, s2->data, s2->len, s2->byte_len);
}

static inline void string_prepend_fast(String *s, SSlice *sslice) {
    string_prepend_cstr_fast(s, sslice->data, sslice->len, sslice->byte_len);
}

static inline bool string_insert_cstr_len(String *s, size_t pos,
                                                     const char *data,
                                                     size_t byte_len,
                                                     Status *status) {
    size_t len = 0;

    return utf8len(data, &len, status) &&
           string_insert_cstr_full(s, pos, data, len, byte_len, status);
}

static inline bool string_insert_cstr(String *s, size_t pos, const char *data,
                                                             Status *status) {
    return string_insert_cstr_len(s, pos, data, strlen(data), status);
}

static inline bool string_insert_str(String *s, size_t pos, String *s2,
                                                            Status *status) {
    return string_insert_cstr_full(
        s, pos, s2->data, s2->len, s2->byte_len, status
    );
}

static inline bool string_insert_str_fast(String *s, size_t pos,
                                                     String *s2,
                                                     ssize_t *error) {
    return string_insert_cstr_fast(
        s, pos, s2->data, s2->len, s2->byte_len, error
    );
}

static inline void string_append_cstr_fast(String *s, const char *data,
                                                      size_t len,
                                                      size_t byte_len) {
    if (byte_len) {
        memmove(s->data + s->byte_len, data, byte_len);
    }

    s->len += len;
    s->byte_len += byte_len;
    *(s->data + s->byte_len) = '\0';
}

static inline bool string_append_cstr_full(String *s, const char *data,
                                                      size_t len,
                                                      size_t byte_len,
                                                      Status *status) {
    if (!string_ensure_capacity(s, s->byte_len + byte_len, status)) {
        return false;
    }

    string_append_cstr_fast(s, data, len, byte_len);

    return status_ok(status);
}

static inline bool string_append_cstr_len(String *s, const char *data,
                                                     size_t byte_len,
                                                     Status *status) {
    size_t len;

    return utf8len(data, &len, status) &&
           string_append_cstr_full(s, data, len, byte_len, status);
}

static inline bool string_append_cstr(String *s, const char *data,
                                                 Status *status) {
    return string_append_cstr_len(s, data, strlen(data), status);
}

static inline bool string_append_str(String *s, String *s2, Status *status) {
    return string_append_cstr_full(s, s2->data, s2->len, s2->byte_len, status);
}

static inline void string_append_str_fast(String *s, String *s2) {
    string_append_cstr_fast(s, s2->data, s2->len, s2->byte_len);
}

static inline void string_append_fast(String *s, SSlice *sslice) {
    string_append_cstr_fast(s, sslice->data, sslice->len, sslice->byte_len);
}

static inline bool string_insert_fast(String *s, size_t pos, SSlice *sslice,
                                                             ssize_t *error) {
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

static inline bool string_shift_left_fast(String *s, size_t len, ssize_t *error) {
    return string_delete_fast(s, 0, len, error);
}

static inline bool string_shift_left(String *s, size_t len, Status *status) {
    ssize_t error;

    if (!string_shift_left_fast(s, len, &error)) {
        return utf8_handle_error_code(error, status);
    }

    return status_ok(status);
}

static inline bool string_truncate(String *s, size_t len, Status *status) {
    return string_delete(s, (s->len - len) + 1, len, status);
}

static inline bool string_truncate_fast(String *s, size_t len, ssize_t *error) {
    return string_delete_fast(s, (s->len - len) + 1, len, error);
}

static inline bool string_contents_equal(String *s1, String *s2) {
    return strcmp(s1->data, s2->data) == 0;
}

static inline bool string_equals_cstr(String *s, const char *cs) {
    return utf8ncmp(s->data, cs, s->byte_len);
}

static inline void string_clear(String *s) {
    s->len = 0;
    s->byte_len = 0;
    if (s->data) {
        *s->data = '\0';
    }
}

#endif

/* vi: set et ts=4 sw=4: */

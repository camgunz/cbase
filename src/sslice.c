#include "cbase.h"

#define empty(status) status_failure( \
    status,                           \
    "sslice",                         \
    SSLICE_EMPTY,                     \
    "SSlice is empty"                 \
)

#define not_subslice(status) status_failure( \
    status,                                  \
    "sslice",                                \
    SSLICE_NOT_SUBSLICE,                     \
    "SSlice is not a subslice"               \
)

bool sslice_assign_cstr(SSlice *sslice, char *cs, Status *status) {
    if (!cs) {
        sslice->len = 0;
        sslice->byte_len = 0;
    }
    else if (!utf8_process_cstr(cs, &sslice->len, &sslice->byte_len, status)) {
        return false;
    }

    sslice->data = cs;

    return status_ok(status);
}

void sslice_assign_full(SSlice *sslice, char *data, size_t len,
                                                    size_t byte_len) {
    sslice->data = data;
    sslice->len = len;
    sslice->byte_len = byte_len;
}

void sslice_assign_sslice(SSlice *dst, SSlice *src) {
    strbase_copy(
        &dst->data, &dst->len, &dst->byte_len,
        src->data, src->len, src->byte_len
    );
}

bool sslice_new_from_cstr(SSlice **sslice, char *cs, Status *status) {
    if (!cbmalloc(1, sizeof(SSlice), sslice, status)) {
        return false;
    }

    if (!sslice_assign_cstr(*sslice, cs, status)) {
        cbfree(*sslice);
        return false;
    }

    return status_ok(status);
}

bool sslice_new_full(SSlice **sslice, char *data, size_t len,
                                                  size_t byte_len,
                                                  Status *status) {
    if (!cbmalloc(1, sizeof(SSlice), sslice, status)) {
        return false;
    }

    sslice_assign_full(*sslice, data, len, byte_len);

    return status_ok(status);
}

bool sslice_index_rune(SSlice *sslice, size_t index, rune *r, Status *status) {
    return strbase_index_rune(
        sslice->data, sslice->byte_len, index, r, status
    );
}

bool sslice_empty(SSlice *sslice) {
    return strbase_empty(sslice->data, sslice->len, sslice->byte_len);
}

bool sslice_get_first_rune(SSlice *sslice, rune *r, Status *status) {
    return sslice_index_rune(sslice, 0, r, status);
}

bool sslice_get_last_rune(SSlice *sslice, rune *r, Status *status) {
    return sslice_index_rune(sslice, sslice->len - 1, r, status);
}

bool sslice_equals_cstr(SSlice *sslice, const char *cs) {
    return utf8_cstr_equal_fast(cs, sslice->data);
}

bool sslice_equals_utf8_data(SSlice *sslice, const char *data, size_t len) {
    return (
        (len == sslice->byte_len) &&
        utf8_cstr_equal_fast(sslice->data, data)
    );
}

bool sslice_equals_sslice(SSlice *s1, SSlice *s2) {
    return (
        (s1->len == s2->len) &&
        (s1->byte_len == s2->byte_len) &&
        (memcmp(s1->data, s2->data, s1->byte_len) == 0)
    );
}

bool sslice_equals_utf8_slice(SSlice *sslice, Slice *slice) {
    return sslice_equals_utf8_data(sslice, slice->data, slice->len);
}

bool sslice_equals_utf8_buffer(SSlice *sslice, Buffer *buffer) {
    return sslice_equals_utf8_data(sslice, buffer->array.elements,
                                           buffer->array.len);
}

bool sslice_starts_with_rune(SSlice *sslice, rune r, bool *starts_with,
                                                     Status *status) {
    return utf8_starts_with_rune(sslice->data, r, starts_with, status);
}

bool sslice_starts_with_cstr(SSlice *sslice, const char *cs, bool *starts_with,
                                                             Status *status) {
    return utf8_starts_with_cstr(sslice->data, sslice->byte_len, cs,
                                                                 starts_with,
                                                                 status);
}

bool sslice_starts_with_sslice(SSlice *sslice1, SSlice *sslice2,
                                                bool *starts_with,
                                                Status *status) {
    return utf8_starts_with_data(sslice1->data, sslice1->byte_len,
                                 sslice2->data, sslice2->byte_len,
                                                starts_with,
                                                status);
}

bool sslice_ends_with_rune(SSlice *sslice, rune r, bool *ends_with,
                                                   Status *status) {
    return utf8_ends_with_rune(sslice->data, sslice->byte_len, r, ends_with,
                                                                  status);
}

bool sslice_ends_with_cstr(SSlice *sslice, const char *cs, bool *ends_with,
                                                           Status *status) {
    return utf8_ends_with_cstr(sslice->data, sslice->byte_len, cs, ends_with,
                                                                   status);
}

bool sslice_ends_with_sslice(SSlice *sslice1, SSlice *sslice2,
                                              bool *ends_with,
                                              Status *status) {
    return utf8_ends_with_data(sslice1->data, sslice1->byte_len,
                               sslice2->data, sslice2->byte_len,
                                              ends_with,
                                              status);
}

bool sslice_skip_runes(SSlice *sslice, size_t rune_count, Status *status) {
    return strbase_skip_runes(
        &sslice->data, &sslice->len, &sslice->byte_len, rune_count, status
    );
}

bool sslice_skip_rune_if_equals(SSlice *sslice, rune r, Status *status) {
    rune r2;
    size_t bytes_read;

    if (!utf8_get_first_rune_len(sslice->data, &r2, &bytes_read, status)) {
        return false;
    }

    if (r2 != r) {
        return not_equal(status);
    }

    sslice->len = sslice->len - 1;
    sslice->byte_len -= bytes_read;
    sslice->data += bytes_read;

    return status_ok(status);
}

bool sslice_pop_rune(SSlice *sslice, rune *r, Status *status) {
    return strbase_pop_rune(
        &sslice->data, &sslice->len, &sslice->byte_len, r, status
    );
}

bool sslice_pop_rune_if_matches(SSlice *sslice, RuneMatchFunc *matches,
                                                rune *r,
                                                Status *status) {
    return strbase_pop_rune_if_matches(
        &sslice->data, &sslice->len, &sslice->byte_len, matches, r, status
    );
}

bool sslice_pop_rune_if_alpha(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_alpha, r, status);
}

bool sslice_pop_rune_if_hex_digit(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_hex_digit, r, status);
}

bool sslice_pop_rune_if_digit(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_digit, r, status);
}

bool sslice_pop_rune_if_oct_digit(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_oct_digit, r, status);
}

bool sslice_pop_rune_if_bin_digit(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_bin_digit, r, status);
}

bool sslice_pop_rune_if_alnum(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_alnum, r, status);
}

bool sslice_pop_rune_if_whitespace(SSlice *sslice, rune *r, Status *status) {
    return sslice_pop_rune_if_matches(sslice, rune_is_whitespace, r, status);
}

bool sslice_seek_to_rune(SSlice *sslice, rune r, Status *status) {
    return strbase_seek_to_rune(
        &sslice->data, &sslice->len, &sslice->byte_len, r, status
    );
}

bool sslice_seek_to_cstr(SSlice *sslice, const char *cs, Status *status) {
    return strbase_seek_to_cstr(
        &sslice->data, &sslice->len, &sslice->byte_len, cs, status
    );
}

bool sslice_seek_to_whitespace(SSlice *sslice, Status *status) {
    return strbase_seek_to_whitespace(
        &sslice->data, &sslice->len, &sslice->byte_len, status
    );
}

bool sslice_seek_to_subslice(SSlice *sslice, SSlice *subslice,
                                             Status *status) {
    if (subslice->data < sslice->data) {
        return not_subslice(status);
    }

    if (subslice->data >= (sslice->data + sslice->byte_len)) {
        return index_out_of_bounds(status);
    }

    if (sslice->data == subslice->data) {
        return status_ok(status);
    }

    size_t start_byte_len = subslice->data - sslice->data;
    size_t start_len;

    utf8_len(sslice->data, sslice->byte_len, &start_len);

    sslice->len -= start_len;
    sslice->byte_len -= start_byte_len;
    sslice->data = subslice->data;

    return status_ok(status);
}

bool sslice_seek_past_subslice(SSlice *sslice, SSlice *subslice,
                                               Status *status) {
    size_t start_len = 0;
    char *start = subslice->data + subslice->byte_len;
    char *current_end = sslice->data + sslice->byte_len;

    if (start < sslice->data) {
        return not_subslice(status);
    }

    if (start >= current_end) {
        sslice_clear(sslice);
        return status_ok(status);
    }

    size_t start_byte_len = subslice->data - sslice->data;

    if (start_byte_len) {
        utf8_len(sslice->data, start_byte_len, &start_len);
    }

    sslice->len -= (start_len + subslice->len);
    sslice->byte_len -= (start_byte_len + subslice->len);
    sslice->data = start;

    return status_ok(status);
}

bool sslice_seek_past_whitespace(SSlice *sslice, Status *status) {
    return strbase_seek_past_whitespace(
        &sslice->data, &sslice->len, &sslice->byte_len, status
    );
}

bool sslice_truncate_whitespace(SSlice *sslice, Status *status) {
    return strbase_truncate_whitespace(
        sslice->data, &sslice->len, &sslice->byte_len, status
    );
}

bool sslice_truncate_at_rune(SSlice *sslice, rune r, Status *status) {
    return strbase_truncate_at_rune(
        sslice->data, &sslice->len, &sslice->byte_len, r, status
    );
}

bool sslice_truncate_at_whitespace(SSlice *sslice, Status *status) {
    return strbase_truncate_at_whitespace(
        sslice->data, &sslice->len, &sslice->byte_len, status
    );
}

bool sslice_truncate_runes(SSlice *sslice, size_t rune_count, Status *status) {
    return strbase_truncate_runes(
        sslice->data, &sslice->len, &sslice->byte_len, rune_count, status
    );
}

bool sslice_truncate_at_subslice(SSlice *sslice, SSlice *subslice,
                                                 Status *status) {
    if (subslice->data < sslice->data) {
        return not_subslice(status);
    }

    if (((size_t)(subslice->data - sslice->data)) >= sslice->len) {
        return not_subslice(status);
    }

    sslice->byte_len = subslice->data - sslice->data;
    utf8_len(sslice->data, sslice->byte_len, &sslice->len);

    return status_ok(status);
}

void sslice_clear(SSlice *s) {
    strbase_clear(&s->len, &s->byte_len);
}

bool sslice_skip_rune(SSlice *sslice, Status *status) {
    return sslice_skip_runes(sslice, 1, status);
}

bool sslice_truncate_rune(SSlice *sslice, Status *status) {
    return sslice_truncate_runes(sslice, 1, status);
}


void sslice_seek_to_end(SSlice *sslice) {
    sslice->data += sslice->byte_len;
    sslice->len = 0;
    sslice->byte_len = 0;
}

bool sslice_to_cstr(SSlice *sslice, char **cs, Status *status) {
    return cbstrndup(sslice->data, sslice->byte_len, cs, status);
}

/* vi: set et ts=4 sw=4: */

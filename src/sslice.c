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

static inline
bool sslice_pop_rune(SSlice *sslice, rune *r, Status *status) {
    return strbase_pop_rune(&sslice->data, r, status);
}

bool sslice_pop_rune_if_matches(SSlice *sslice, RuneMatchFunc *matches,
                                                rune *r,
                                                Status *status) {
    return strbase_pop_rune_if_matches(
        &sslice->data, &sslice->len, &sslice->byte_len, matches, r, status
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

bool sslice_truncate_at_subslice(SSlice *sslice, SSlice *subslice, Status *status) {
    if (subslice->data < s->data) {
        return not_subslice(status);
    }

    if (((size_t)(subslice->data - s->data)) >= s->len) {
        return not_subslice(status);
    }

    s->byte_len = subslice->data - s->data;
    if (!utf8nlen(s->data, s->byte_len, &s->len, status)) {
        return false;
    }

    return status_ok(status);
}

/* vi: set et ts=4 sw=4: */

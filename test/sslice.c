#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_sslice(void **state) {
    String *alpha;
    String *hex;
    String *dec;
    String *oct;
    String *bin;
    String *whitespace;
    String *alnum;
    String *s;
    SSlice ss;
    SSlice ss2;
    Status status;
    rune r;
    bool starts_with;

    (void)state;

    status_init(&status);

    assert_true(string_new_from_cstr(&alpha, "1abc", &status));
    assert_true(string_new_from_cstr(
        &hex, "g0123456789aAbBcCdDeEfF", &status
    ));
    assert_true(string_new_from_cstr(&dec, "a123", &status));
    assert_true(string_new_from_cstr(&oct, "801234567", &status));
    assert_true(string_new_from_cstr(&bin, "201", &status));
    assert_true(string_new_from_cstr(&whitespace, "a \t\r\n", &status));
    assert_true(string_new_from_cstr(&alnum, " 1a", &status));
    assert_true(string_new_from_cstr(&s, "", &status));
    assert_true(string_ensure_capacity(
        s,
        alpha->buffer.array.len +
        hex->buffer.array.len +
        dec->buffer.array.len +
        oct->buffer.array.len +
        bin->buffer.array.len +
        whitespace->buffer.array.len +
        alnum->buffer.array.len +
        6,
        &status
    ));

    assert_true(string_append_string(s, alpha, &status));
    assert_true(string_append_cstr(s, " ", &status));
    assert_true(string_append_string(s, hex, &status));
    assert_true(string_append_cstr(s, " ", &status));
    assert_true(string_append_string(s, dec, &status));
    assert_true(string_append_cstr(s, " ", &status));
    assert_true(string_append_string(s, oct, &status));
    assert_true(string_append_cstr(s, " ", &status));
    assert_true(string_append_string(s, bin, &status));
    assert_true(string_append_cstr(s, " ", &status));
    assert_true(string_append_string(s, whitespace, &status));
    assert_true(string_append_cstr(s, " ", &status));
    assert_true(string_append_string(s, alnum, &status));

    assert_true(string_slice(s, 0, s->len, &ss, &status));
    assert_true(string_slice(s, 34, 3, &ss2, &status));

    assert_int_equal(ss.len, 57);
    assert_int_equal(ss.byte_len, 57);
    assert_true(sslice_starts_with_cstr(&ss, "1abc", &starts_with, &status));
    assert_true(starts_with);

    assert_true(sslice_get_first_rune(&ss, &r, &status));
    assert_int_equal(r, '1');

    assert_true(sslice_skip_rune(&ss, &status));
    assert_true(sslice_get_first_rune(&ss, &r, &status));
    assert_int_equal(r, 'a');
    assert_int_equal(ss.len, 56);
    assert_int_equal(ss.byte_len, 56);

    assert_true(sslice_skip_runes(&ss, 2, &status));
    assert_true(sslice_get_first_rune(&ss, &r, &status));
    assert_int_equal(r, 'c');
    assert_int_equal(ss.len, 54);
    assert_int_equal(ss.byte_len, 54);

    assert_false(sslice_skip_rune_if_equals(&ss, 'd', &status));
    assert_int_equal(status.code, ERROR_NOT_EQUAL);
    assert_string_equal(status.domain, "base");

    status_init(&status);

    assert_true(sslice_skip_rune_if_equals(&ss, 'c', &status));
    assert_true(sslice_get_first_rune(&ss, &r, &status));
    assert_int_equal(r, ' ');
    assert_int_equal(ss.len, 53);
    assert_int_equal(ss.byte_len, 53);

    assert_true(sslice_pop_rune(&ss, &r, &status));
    assert_int_equal(r, ' ');
    assert_true(sslice_starts_with_rune(&ss, 'g', &starts_with, &status));
    assert_true(starts_with);
    assert_int_equal(ss.len, 52);
    assert_int_equal(ss.byte_len, 52);

    assert_false(sslice_seek_to_rune(&ss, 'q', &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    status_init(&status);

    assert_true(sslice_seek_to_rune(&ss, 'a', &status));
    assert_int_equal(ss.len, 41);
    assert_int_equal(ss.byte_len, 41);

    assert_false(sslice_seek_to_cstr(&ss, "cD", &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    status_init(&status);

    assert_true(sslice_seek_to_cstr(&ss, "Cd", &status));
    assert_int_equal(ss.len, 36);
    assert_int_equal(ss.byte_len, 36);

    assert_true(sslice_get_first_rune(&ss, &r, &status));
    assert_int_equal(r, 'C');

    assert_true(sslice_seek_to_whitespace(&ss, &status));
    assert_true(sslice_starts_with_rune(&ss, ' ', &starts_with, &status));
    assert_true(starts_with);
    assert_int_equal(ss.len, 29);
    assert_int_equal(ss.byte_len, 29);

    assert_true(sslice_seek_past_whitespace(&ss, &status));
    assert_true(sslice_starts_with_rune(&ss, 'a', &starts_with, &status));
    assert_true(starts_with);
    assert_int_equal(ss.len, 28);
    assert_int_equal(ss.byte_len, 28);

    assert_true(sslice_truncate_runes(&ss, 2, &status));
    assert_int_equal(ss.len, 26);
    assert_int_equal(ss.byte_len, 26);
    assert_true(sslice_equals_cstr(&ss, "a123 801234567 201 a \t\r\n  "));

    assert_true(sslice_truncate_whitespace(&ss, &status));
    assert_int_equal(ss.len, 20);
    assert_int_equal(ss.byte_len, 20);
    assert_true(sslice_equals_cstr(&ss, "a123 801234567 201 a"));

    assert_true(sslice_truncate_at_rune(&ss, '2', &status));
    assert_int_equal(ss.len, 16);
    assert_int_equal(ss.byte_len, 16);
    assert_true(sslice_equals_cstr(&ss, "a123 801234567 2"));

    assert_true(sslice_seek_to_subslice(&ss, &ss2, &status));
    assert_int_equal(ss.len, 11);
    assert_int_equal(ss.byte_len, 11);
    assert_true(sslice_equals_cstr(&ss, "801234567 2"));

    assert_true(sslice_skip_rune(&ss2, &status));

    assert_true(sslice_seek_past_subslice(&ss, &ss2, &status));
    assert_int_equal(ss.len, 8);
    assert_int_equal(ss.byte_len, 8);
    assert_true(sslice_equals_cstr(&ss, "234567 2"));

    char *dup = NULL;
        
    assert_true(sslice_to_cstr(&ss, &dup, &status));
    assert_non_null(dup);
    assert_int_equal(strcmp("234567 2", dup), 0);
    cbfree(dup);

    assert_true(sslice_truncate_runes(&ss, 100, &status));
    assert_int_equal(ss.len, 0);
    assert_int_equal(ss.byte_len, 0);

    assert_true(string_slice(alpha, 0, alpha->len, &ss, &status));

    assert_false(sslice_pop_rune_if_alpha(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_skip_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_alpha(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_slice(hex, 0, hex->len, &ss, &status));

    assert_false(sslice_pop_rune_if_hex_digit(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_skip_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_hex_digit(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_slice(dec, 0, dec->len, &ss, &status));

    assert_false(sslice_pop_rune_if_digit(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_skip_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_digit(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_slice(oct, 0, oct->len, &ss, &status));

    assert_false(sslice_pop_rune_if_oct_digit(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_skip_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_oct_digit(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_slice(bin, 0, bin->len, &ss, &status));

    assert_false(sslice_pop_rune_if_bin_digit(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_skip_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_bin_digit(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_slice(whitespace, 0, whitespace->len, &ss, &status));

    assert_false(sslice_pop_rune_if_whitespace(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_skip_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_whitespace(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_slice(alnum, 0, alnum->len, &ss, &status));

    assert_false(sslice_pop_rune_if_alnum(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_skip_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_alnum(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_assign_cstr(s, "token1, token2, token3", &status));
    assert_true(string_slice(s, 0, s->len, &ss, &status));
    assert_true(string_slice(s, 8, s->len - 8, &ss2, &status));
    assert_true(sslice_equals_cstr(&ss2, "token2, token3"));
    assert_true(sslice_truncate_at_whitespace(&ss, &status));
    assert_true(sslice_equals_cstr(&ss, "token1, token2, "));
    assert_true(sslice_truncate_at_subslice(&ss, &ss2, &status));
    assert_true(sslice_equals_cstr(&ss, "token1, "));

    assert_true(sslice_seek_past_subslice(&ss, &ss2, &status));
    assert_int_equal(ss.len, 0);
    assert_int_equal(ss.byte_len, 0);

    string_free(alpha);
    cbfree(alpha);
    string_free(hex);
    cbfree(hex);
    string_free(dec);
    cbfree(dec);
    string_free(oct);
    cbfree(oct);
    string_free(bin);
    cbfree(bin);
    string_free(whitespace);
    cbfree(whitespace);
    string_free(alnum);
    cbfree(alnum);
    string_free(s);
    cbfree(s);
}

/* vi: set et ts=4 sw=4: */

#include <setjmp.h>

#include "cbase/str.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_string(void **state) {
    String *s;
    String *s2;
    SSlice ss;
    bool starts_with;

    (void)state;

    assert_int_equal(string_new_from_cstr(&s, "We are great"), 0);
    assert_non_null(s->data);
    assert_int_equal(s->len, 12);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 13), 12);
    string_free(s);
    cbfree(s);

    assert_int_equal(string_new_from_cstr(&s, "We are great"), 0);

    assert_int_equal(string_starts_with_cstr(s, "We are", &starts_with), 0);
    assert_true(starts_with);

    assert_int_equal(
        string_starts_with_cstr(s, "We are great", &starts_with),
        0
    );
    assert_true(starts_with);

    assert_int_equal(string_starts_with_cstr(s, "We sre", &starts_with), 0);
    assert_false(starts_with);

    assert_int_equal(
        string_starts_with_cstr(s, "We are great because we are good",
                                   &starts_with),
        0
    );
    assert_false(starts_with);

    string_free(s);
    cbfree(s);

    assert_int_equal(string_new_from_cstr_full(&s, "We are great", 12, 13), 0);
    assert_non_null(s->data);
    assert_int_equal(s->len, 12);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 13), 12);
    string_free(s);
    cbfree(s);

    assert_int_equal(string_new_from_cstr_full(&s, "We are great", 12, 12), 0);
    assert_non_null(s->data);
    assert_int_equal(s->len, 12);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 13), 12);
    assert_true(string_equals_cstr(s, "We are great"));

    assert_int_equal(string_new_from_cstr(&s2, "because we are good"), 0);
    assert_non_null(s2->data);
    assert_int_equal(s2->len, 19);
    assert_int_equal(s2->alloc, 20);
    assert_int_equal(strnlen(s2->data, 20), 19);
    assert_true(string_equals_cstr(s2, "because we are good"));

    assert_int_equal(string_slice(s2, 15, 4, &ss), 0);
    assert_int_equal(ss.len, 4);
    assert_true(sslice_equals_cstr(&ss, "good"));

    assert_int_equal(string_assign_sslice(s, &ss), 0);
    assert_int_equal(s->len, 4);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 5), 4);
    assert_true(string_equals_cstr(s, "good"));

    assert_int_equal(string_slice(s2, 0, s2->len, &ss), 0);
    assert_int_equal(ss.len, 19);
    assert_true(sslice_equals_cstr(&ss, "because we are good"));

    assert_int_equal(string_assign_sslice(s, &ss), 0);
    assert_int_equal(s->len, 19);
    assert_int_equal(s->alloc, 20);
    assert_int_equal(strnlen(s->data, 20), 19);
    assert_true(string_equals_cstr(s, "because we are good"));

    assert_int_equal(string_assign_sslice(s, &ss), 0);
    assert_int_equal(s->len, 19);
    assert_int_equal(s->alloc, 20);
    assert_int_equal(strnlen(s->data, 20), 19);
    assert_true(string_equals_cstr(s, "because we are good"));

    assert_int_equal(string_assign_cstr(s, "We are great"), 0);
    assert_int_equal(s->len, 12);
    assert_int_equal(s->alloc, 20);
    assert_int_equal(strnlen(s->data, 13), 12);
    assert_true(string_equals_cstr(s, "We are great"));

    assert_int_equal(string_compact(s), 0);
    assert_int_equal(s->len, 12);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 13), 12);
    assert_true(string_equals_cstr(s, "We are great"));

    assert_int_equal(string_assign_string(s2, s), 0);
    assert_int_equal(s2->len, 12);
    assert_int_equal(s2->alloc, 20);
    assert_int_equal(strnlen(s2->data, 13), 12);
    assert_true(string_equals_cstr(s2, "We are great"));

    assert_int_equal(string_slice(s, 0, s->len, &ss), 0);
    assert_int_equal(ss.len, s->len);
    assert_true(sslice_equals_cstr(&ss, "We are great"));

    assert_int_equal(string_assign_cstr(s2, "because we are good"), 0);
    assert_int_equal(s2->len, 19);
    assert_int_equal(s2->alloc, 20);
    assert_int_equal(strnlen(s2->data, 20), 19);
    assert_true(string_equals_cstr(s2, "because we are good"));

    assert_int_equal(string_prepend_slice(s2, &ss), 0);
    assert_int_equal(s2->len, 31);
    assert_int_equal(s2->alloc, 32);
    assert_int_equal(strnlen(s2->data, 32), 31);
    assert_true(string_equals_cstr(s2, "We are greatbecause we are good"));

    ss.data = (char *)" ";
    ss.len = 1;

    assert_int_equal(string_insert_sslice(s2, 13, &ss), 0);
    assert_int_equal(s2->len, 32);
    assert_int_equal(s2->alloc, 33);
    assert_int_equal(strnlen(s2->data, 33), 32);
    assert_true(string_equals_cstr(s2, "We are great because we are good"));

    assert_int_equal(string_delete(s2, 13, 1), 0);
    assert_int_equal(s2->len, 31);
    assert_int_equal(s2->alloc, 33);
    assert_int_equal(strnlen(s2->data, 32), 31);
    assert_true(string_equals_cstr(s2, "We are greatbecause we are good"));

    assert_int_equal(string_insert_cstr(s2, 13, " "), 0);
    assert_int_equal(s2->len, 32);
    assert_int_equal(s2->alloc, 33);
    assert_int_equal(strnlen(s2->data, 33), 32);
    assert_true(string_equals_cstr(s2, "We are great because we are good"));

    assert_int_equal(string_assign_cstr(s2, "because we are good"), 0);
    assert_int_equal(s2->len, 19);
    assert_int_equal(s2->alloc, 33);
    assert_int_equal(strnlen(s2->data, 20), 19);
    assert_true(string_equals_cstr(s2, "because we are good"));

    assert_int_equal(string_slice(s2, 0, s2->len, &ss), 0);
    assert_int_equal(ss.len, s2->len);
    assert_true(sslice_equals_cstr(&ss, "because we are good"));

    assert_int_equal(string_append_cstr(s, " "), 0);
    assert_int_equal(s->len, 13);
    assert_int_equal(s->alloc, 14);
    assert_true(string_equals_cstr(s, "We are great "));

    assert_int_equal(string_append_sslice(s, &ss), 0);
    assert_int_equal(s->len, 32);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 33), 32);
    assert_true(string_equals_cstr(s, "We are great because we are good"));

    assert_int_equal(string_skip_runes(s, 3), 0);
    assert_int_equal(s->len, 29);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 30), 29);
    assert_true(string_equals_cstr(s, "are great because we are good"));

    assert_int_equal(string_truncate_runes(s, 1), 0);
    assert_int_equal(s->len, 28);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 29), 28);
    assert_true(string_equals_cstr(s, "are great because we are goo"));

    assert_int_equal(string_truncate_runes(s, 11), 0);
    assert_int_equal(s->len, 17);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 18), 17);
    assert_true(string_equals_cstr(s, "are great because"));

    assert_int_equal(string_prepend_cstr(s, "We "), 0);
    assert_int_equal(s->len, 20);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 21), 20);
    assert_true(string_equals_cstr(s, "We are great because"));

    assert_int_equal(string_append_cstr(s, " we are good"), 0);
    assert_int_equal(s->len, 32);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 33), 32);
    assert_true(string_equals_cstr(s, "We are great because we are good"));

    string_clear(s);

    assert_true(string_printf(s, &status, "We are %s because we are %s\n",
        "great",
        "good"
    ));

    assert_true(string_equals_cstr(s, "We are great because we are good\n"));

    assert_int_equal(string_slice(s, 0, s->len, &ss), 0);

    string_clear(s2);
    assert_int_equal(string_init_from_sslice(s2, &ss), 0);
    assert_true(string_equals_string(s, s2));

    string_free(s);
    cbfree(s);

    string_free(s2);
    cbfree(s2);
}

/* vi: set et ts=4 sw=4: */

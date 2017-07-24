#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_string(void **state) {
    String *s;
    String *s2;
    SSlice ss;
    Status status;
    ssize_t error;

    (void)state;

    status_init(&status);

    assert_true(string_new(&s, "We are great", &status));
    assert_non_null(s->data);
    assert_int_equal(s->len, 12);
    assert_int_equal(s->byte_len, 12);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 13), 12);
    string_free(s);
    cbfree(s);

    assert_true(string_new(&s, "We are great", &status));
    assert_true(string_starts_with_cstr(s, "We are"));
    assert_true(string_starts_with_cstr(s, "We are great"));
    assert_false(string_starts_with_cstr(s, "We sre"));
    assert_false(string_starts_with_cstr(
        s, "We are great because we are good"
    ));
    string_free(s);
    cbfree(s);

    assert_true(string_new_len(&s, "We are great", 12, &status));
    assert_non_null(s->data);
    assert_int_equal(s->len, 12);
    assert_int_equal(s->byte_len, 12);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 13), 12);
    string_free(s);
    cbfree(s);

    assert_true(string_new_full(&s, "We are great", 12, 12, &status));
    assert_non_null(s->data);
    assert_int_equal(s->len, 12);
    assert_int_equal(s->byte_len, 12);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 13), 12);
    assert_true(string_equals_cstr(s, "We are great"));

    assert_true(string_new(&s2, "because we are good", &status));
    assert_non_null(s2->data);
    assert_int_equal(s2->len, 19);
    assert_int_equal(s2->byte_len, 19);
    assert_int_equal(s2->alloc, 20);
    assert_int_equal(strnlen(s2->data, 20), 19);
    assert_true(string_equals_cstr(s2, "because we are good"));

    assert_true(string_slice(s2, 15, 4, &ss, &status));
    assert_int_equal(ss.len, 4);
    assert_int_equal(ss.byte_len, 4);
    assert_true(sslice_equals_cstr(&ss, "good"));

    assert_true(string_assign_sslice(s, &ss, &status));
    assert_int_equal(s->len, 4);
    assert_int_equal(s->byte_len, 4);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 5), 4);
    assert_true(string_equals_cstr(s, "good"));

    assert_true(string_slice(s2, 0, s2->len, &ss, &status));
    assert_int_equal(ss.len, 19);
    assert_int_equal(ss.byte_len, 19);
    assert_true(sslice_equals_cstr(&ss, "because we are good"));

    assert_true(string_assign_sslice(s, &ss, &status));
    assert_int_equal(s->len, 19);
    assert_int_equal(s->byte_len, 19);
    assert_int_equal(s->alloc, 20);
    assert_int_equal(strnlen(s->data, 20), 19);
    assert_true(string_equals_cstr(s, "because we are good"));

    assert_true(string_assign_sslice(s, &ss, &status));
    assert_int_equal(s->len, 19);
    assert_int_equal(s->byte_len, 19);
    assert_int_equal(s->alloc, 20);
    assert_int_equal(strnlen(s->data, 20), 19);
    assert_true(string_equals_cstr(s, "because we are good"));

    assert_true(string_assign(s, "We are great", &status));
    assert_int_equal(s->len, 12);
    assert_int_equal(s->byte_len, 12);
    assert_int_equal(s->alloc, 20);
    assert_int_equal(strnlen(s->data, 13), 12);
    assert_true(string_equals_cstr(s, "We are great"));

    assert_true(string_shrink(s, &status));
    assert_int_equal(s->len, 12);
    assert_int_equal(s->byte_len, 12);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 13), 12);
    assert_true(string_equals_cstr(s, "We are great"));

    assert_true(string_copy(s2, s, &status));
    assert_int_equal(s2->len, 12);
    assert_int_equal(s2->byte_len, 12);
    assert_int_equal(s2->alloc, 20);
    assert_int_equal(strnlen(s2->data, 13), 12);
    assert_true(string_equals_cstr(s2, "We are great"));

    assert_true(string_slice(s, 0, s->len, &ss, &status));
    assert_int_equal(ss.len, s->len);
    assert_int_equal(ss.byte_len, s->byte_len);
    assert_true(sslice_equals_cstr(&ss, "We are great"));

    assert_true(string_assign(s2, "because we are good", &status));
    assert_int_equal(s2->len, 19);
    assert_int_equal(s2->byte_len, 19);
    assert_int_equal(s2->alloc, 20);
    assert_int_equal(strnlen(s2->data, 20), 19);
    assert_true(string_equals_cstr(s2, "because we are good"));

    assert_true(string_prepend(s2, &ss, &status));
    assert_int_equal(s2->len, 31);
    assert_int_equal(s2->byte_len, 31);
    assert_int_equal(s2->alloc, 32);
    assert_int_equal(strnlen(s2->data, 32), 31);
    assert_true(string_equals_cstr(s2, "We are greatbecause we are good"));

    ss.data = " ";
    ss.len = 1;
    ss.byte_len = 1;

    assert_true(string_insert(s2, 13, &ss, &status));
    assert_int_equal(s2->len, 32);
    assert_int_equal(s2->byte_len, 32);
    assert_int_equal(s2->alloc, 33);
    assert_int_equal(strnlen(s2->data, 33), 32);
    assert_true(string_equals_cstr(s2, "We are great because we are good"));

    assert_true(string_delete(s2, 13, 1, &status));
    assert_int_equal(s2->len, 31);
    assert_int_equal(s2->byte_len, 31);
    assert_int_equal(s2->alloc, 33);
    assert_int_equal(strnlen(s2->data, 32), 31);
    assert_true(string_equals_cstr(s2, "We are greatbecause we are good"));

    assert_true(string_insert_cstr(s2, 13, " ", &status));
    assert_int_equal(s2->len, 32);
    assert_int_equal(s2->byte_len, 32);
    assert_int_equal(s2->alloc, 33);
    assert_int_equal(strnlen(s2->data, 33), 32);
    assert_true(string_equals_cstr(s2, "We are great because we are good"));

    assert_true(string_assign(s2, "because we are good", &status));
    assert_int_equal(s2->len, 19);
    assert_int_equal(s2->byte_len, 19);
    assert_int_equal(s2->alloc, 33);
    assert_int_equal(strnlen(s2->data, 20), 19);
    assert_true(string_equals_cstr(s2, "because we are good"));

    assert_true(string_slice(s2, 0, s2->len, &ss, &status));
    assert_int_equal(ss.len, s2->len);
    assert_int_equal(ss.byte_len, s2->byte_len);
    assert_true(sslice_equals_cstr(&ss, "because we are good"));

    assert_true(string_append_cstr(s, " ", &status));
    assert_int_equal(s->len, 13);
    assert_int_equal(s->byte_len, 13);
    assert_int_equal(s->alloc, 14);
    assert_true(string_equals_cstr(s, "We are great "));

    assert_true(string_append(s, &ss, &status));
    assert_int_equal(s->len, 32);
    assert_int_equal(s->byte_len, 32);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 33), 32);
    assert_true(string_equals_cstr(s, "We are great because we are good"));

    assert_true(string_shift_left(s, 3, &status));
    assert_int_equal(s->len, 29);
    assert_int_equal(s->byte_len, 29);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 30), 29);
    assert_true(string_equals_cstr(s, "are great because we are good"));

    assert_true(string_truncate_fast(s, 1, &error));
    assert_int_equal(s->len, 28);
    assert_int_equal(s->byte_len, 28);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 29), 28);
    assert_true(string_equals_cstr(s, "are great because we are goo"));

    assert_true(string_truncate(s, 11, &status));
    assert_int_equal(s->len, 17);
    assert_int_equal(s->byte_len, 17);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 18), 17);
    assert_true(string_equals_cstr(s, "are great because"));

    assert_true(string_prepend_cstr(s, "We ", &status));
    assert_int_equal(s->len, 20);
    assert_int_equal(s->byte_len, 20);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 21), 20);
    assert_true(string_equals_cstr(s, "We are great because"));

    assert_true(string_append_cstr(s, " we are good", &status));
    assert_int_equal(s->len, 32);
    assert_int_equal(s->byte_len, 32);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 33), 32);
    assert_true(string_equals_cstr(s, "We are great because we are good"));

    string_clear(s);

    assert_true(string_printf(s, &status, "We are %s because we are %s\n",
        "great",
        "good"
    ));

    assert_true(string_equals_cstr(s, "We are great because we are good\n"));

    assert_true(string_slice(s, 0, s->len, &ss, &status));

    string_clear(s2);
    assert_true(string_init_from_sslice(s2, &ss, &status));
    assert_true(string_contents_equal(s, s2));

    string_free(s);
    cbfree(s);

    string_free(s2);
    cbfree(s2);
}

/* vi: set et ts=4 sw=4: */

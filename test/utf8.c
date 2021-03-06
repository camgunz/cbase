#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_utf8(void **state) {
    const char *s = "年暮れぬ\n笠きて草鞋\nはきながら";
    char *cursor = NULL;
    char *start = NULL;
    char *end = NULL;
    rune ki = 0x00006728;
    char *ki_string = NULL;
    Status status;
    size_t len;
    size_t byte_len;

    (void)state;

    assert_true(utf8_cstr_validate_len(s, &len, &byte_len, &status));
    assert_int_equal(len, 19);
    assert_int_equal(byte_len, 47);
    assert_true(utf8_index(s, 6, byte_len, &cursor, &status));
    assert_int_equal(strcmp(cursor, "笠きて草鞋\nはきながら"), 0);

    assert_true(utf8_slice(s, byte_len, 5, 5, &start, &end, &status));
    assert_int_equal(end - start, len - 4);
    assert_int_equal(strncmp(start, "笠きて草鞋", end - start), 0);
    assert_true(rune_to_string(ki, &ki_string, &status));
    assert_string_equal(ki_string, "木");
}

/* vi: set et ts=4 sw=4: */

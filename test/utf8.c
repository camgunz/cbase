#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#include "cbase/utf8.h"
#include "cbase/utf8_cstr.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_utf8(void **state) {
    const char *s = "年暮れぬ\n笠きて草鞋\nはきながら";
    char *cursor = NULL;
    char *start = NULL;
    char *end = NULL;
    rune ki = 0x00006728;
    char *ki_string = NULL;
    size_t len;

    (void)state;

    assert_int_equal(utf8_cstr_validate_len(s, &len), 0);
    assert_int_equal(len, 16);
    assert_int_equal(utf8_cstr_index(s, 6, &cursor), 0);
    assert_int_equal(strcmp(cursor, "きて草鞋\nはきながら"), 0);

    assert_int_equal(utf8_cstr_slice(s, 5, 5, &start, &end), 0);
    assert_int_equal(end - start, 15);
    assert_int_equal(utf8_validate_len(start, end - start, &len), 0);
    assert_int_equal(len, 5);
    assert_int_equal(strncmp(start, "笠きて草鞋", end - start), 0);

    assert_int_equal(rune_to_cstr(ki, &ki_string), 0);
    assert_string_equal(ki_string, "木");
}

/* vi: set et ts=4 sw=4: */

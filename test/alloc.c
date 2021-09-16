#include <setjmp.h>
#include <stdarg.h>

#include "cbase/alloc.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_alloc(void **state) {
    const char *s = "Hillary Clinton";
    char *s2 = NULL;

    (void)state;

    assert_int_equal(cbstrdup(s, &s2), 0);
    assert_non_null(s2);

    assert_string_equal(s, s2);

    cbfree(s2);
}

/* vi: set et ts=4 sw=4: */

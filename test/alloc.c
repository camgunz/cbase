#include <setjmp.h>
#include <stdarg.h>

#include "cbase/alloc.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_alloc(void **state) {
    const char *s = "Hillary Clinton";
    char *s2 = NULL;

    (void)state;

    assert_int_equal(cb_strdup(s, &s2), 0);
    assert_non_null(s2);

    assert_string_equal(s, s2);

    cb_free(s2);
}

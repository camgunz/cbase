#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_alloc(void **state) {
    Status status;
    const char *s = "Hillary Clinton";
    char *s2 = NULL;

    (void)state;

    assert_true(cbstrdup(s, &s2, &status));
    assert_non_null(s2);

    assert_string_equal(s, s2);

    cbfree(s2);
}

/* vi: set et ts=4 sw=4: */

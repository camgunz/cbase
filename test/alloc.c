#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_alloc(void **state) {
    const char *s = "Hillary Clinton";
    char *s2 = cbstrdup(s);

    (void)state;

    assert_string_equal(s, s2);

    cbfree(s2);
}

/* vi: set et ts=4 sw=4: */

#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_path(void **state) {
    Path p;
    SSlice ss;
    Status status;

    (void)state;

    status_clear(&status);

    assert_true(path_init_non_local_from_cstr(
        &p,
        "C:\\Program Files (x86)\\SuperApp\\config.ini",
        &status
    ));

    assert_true(path_dirname(&p, &ss, &status));
    assert_true(sslice_equals_cstr(&ss, "/C/Program Files (x86)/SuperApp"));
    assert_true(path_basename(&p, &ss, &status));
    assert_true(sslice_equals_cstr(&ss, "config.ini"));
    assert_true(path_extension(&p, &ss, &status));
    assert_true(sslice_equals_cstr(&ss, "ini"));
}

/* vi: set et ts=4 sw=4: */

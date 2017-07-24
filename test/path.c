#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

#define TEST_PATH "C:\\Program Files (x86)\\SuperApp\\config.ini"

void test_path(void **state) {
    Path p;
    Path dirname;
    SSlice ss;
    Status status;

    (void)state;

    status_clear(&status);

    assert_true(path_init_from_cstr(&p, TEST_PATH, &status));

    printf("%s\n", p.normal_path.data);

    assert_true(string_equals_cstr(
        &p.normal_path,
        "C:/Program Files (x86)/SuperApp/config.ini"
    ));

    (void)ss;
    (void)dirname;

    /*
    assert_true(path_dirname(&p, &ss, &status));
    assert_true(sslice_equals_cstr(&ss, "C:/Program Files (x86)/SuperApp"));
    assert_true(path_basename(&p, &ss, &status));
    assert_true(sslice_equals_cstr(&ss, "config.ini"));
    assert_true(path_extension(&p, &ss, &status));
    assert_true(sslice_equals_cstr(&ss, "ini"));
    */
}

/* vi: set et ts=4 sw=4: */

#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

#define TEST_PATH "C:\\Program Files (x86)\\SuperApp\\config.ini"

void test_path(void **state) {
    Path p;
    SSlice ss;
    Status status;

    (void)state;

    status_clear(&status);

#if 0
    if (!path_init_non_local_from_cstr(&p, TEST_PATH, &status)) {
        printf("\n\npath_init_non_local_from_cstr failed: (%s-%d) %s [%s:%d]\n\n",
            status.domain,
            status.code,
            status.message,
            status.file,
            status.line
        );
    }
#endif

    assert_true(path_init_non_local_from_cstr(
        &p,
        "C:\\Program Files (x86)\\SuperApp\\config.ini",
        &status
    ));

    printf("%s\n", p.normal_path.data);

    assert_true(string_equals_cstr(
        &p.normal_path,
        "C:/Program Files (x86)/SuperApp/config.ini"
    ));
    assert_true(path_dirname(&p, &ss, &status));
    assert_true(sslice_equals_cstr(&ss, "/C/Program Files (x86)/SuperApp"));
    assert_true(path_basename(&p, &ss, &status));
    assert_true(sslice_equals_cstr(&ss, "config.ini"));
    assert_true(path_extension(&p, &ss, &status));
    assert_true(sslice_equals_cstr(&ss, "ini"));
}

/* vi: set et ts=4 sw=4: */

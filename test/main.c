#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#include <cmocka.h>

void test_alloc(void **state);
void test_array(void **state);
void test_charset(void **state);
void test_dlist(void **state);
void test_list(void **state);
void test_parray(void **state);
void test_path(void **state);
void test_sslice(void **state);
void test_status(void **state);
void test_string(void **state);
void test_table(void **state);
void test_utf8(void **state);

int main(void) {
    int failed_test_count = 0;

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_alloc),
        cmocka_unit_test(test_array),
        cmocka_unit_test(test_charset),
        cmocka_unit_test(test_dlist),
        cmocka_unit_test(test_list),
        cmocka_unit_test(test_parray),
        cmocka_unit_test(test_path),
        cmocka_unit_test(test_sslice),
        cmocka_unit_test(test_status),
        cmocka_unit_test(test_string),
        cmocka_unit_test(test_table),
        cmocka_unit_test(test_utf8),
    };

    failed_test_count = cmocka_run_group_tests(tests, NULL, NULL);

    if (failed_test_count > 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* vi: set et ts=4 sw=4: */

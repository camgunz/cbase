#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

static void test_status_handler(StatusHandler *status_handler,
                                Status *status) {
    int *ptr = (int *)status_handler->data;

    *ptr = status->code;
}

void test_status(void **state) {
    int test_code = 0;
    Status status;
    Status *status2;

    (void)state;

    status_init(&status);
    assert_true(status_is_ok(&status));

    assert_true(_status_new(
        STATUS_DEBUG, "test", 1, "", __FILE__, __LINE__, &status2, &status
    ));
    assert_true(status_is_ok(&status));

    status_init(status2);
    assert_true(status_is_ok(status2));

    _status_debug(
        &status, "test", 1, "This is a debug status\n", __FILE__, __LINE__
    );
    _status_info(
        &status, "test", 1, "This is a info status\n", __FILE__, __LINE__
    );
    _status_warning(
        &status, "test", 1, "This is a warning status\n", __FILE__, __LINE__
    );
    _status_failure(
        &status, "test", 1, "This is a failure status\n", __FILE__, __LINE__
    );
    _status_error(
        &status, "test", 1, "This is a error status\n", __FILE__, __LINE__
    );
    _status_critical(
        &status, "test", 1, "This is a critical status\n", __FILE__, __LINE__
    );
    _status_fatal(
        &status, "test", 1, "This is a fatal status\n", __FILE__, __LINE__
    );
    _status_set(
        &status,
        STATUS_DEBUG,
        "test",
        1,
        "This is a debug status\n",
        __FILE__,
        __LINE__
    );

    _status_debug(
        NULL, "test", 1, "This is a debug status\n", __FILE__, __LINE__
    );
    _status_info(
        NULL, "test", 1, "This is a info status\n", __FILE__, __LINE__
    );
    _status_warning(
        NULL, "test", 1, "This is a warning status\n", __FILE__, __LINE__
    );
    _status_failure(
        NULL, "test", 1, "This is a failure status\n", __FILE__, __LINE__
    );
    _status_error(
        NULL, "test", 1, "This is a error status\n", __FILE__, __LINE__
    );
    _status_critical(
        NULL, "test", 1, "This is a critical status\n", __FILE__, __LINE__
    );
    _status_fatal(
        NULL, "test", 1, "This is a fatal status\n", __FILE__, __LINE__
    );
    assert_true(status_set_handler(
        "test",
        28,
        (void *)&test_code,
        test_status_handler,
        &status
    ));

    assert_true(status_set_handler(
        NULL,
        28,
        (void *)&test_code,
        test_status_handler,
        &status
    ));

    status.domain = "test";
    status.code = 28;
    status_handle(&status);
    assert_int_equal(test_code, 28);

    status_clear_handler("test", 28);
    test_code = 0;
    status_handle(&status);
    assert_int_equal(test_code, 0);

    assert_true(status_match(&status, "test", 28));

    status_copy(status2, &status);
    assert_int_equal(status.level, status2->level);
    assert_string_equal(status.domain, status2->domain);
    assert_string_equal(status.message, status2->message);
    assert_int_equal(status.code, status2->code);
    assert_string_equal(status.file, status2->file);
    assert_int_equal(status.line, status2->line);

    status.domain = NULL;
    assert_true(status_match(&status, NULL, 28));
    status_handle(&status);
    assert_int_equal(test_code, 28);

    status_clear_handler(NULL, 28);
    test_code = 0;
    status_handle(&status);
    assert_int_equal(test_code, 0);

    cbfree(status2);
}

/* vi: set et ts=4 sw=4: */

#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_list(void **state) {
    List *list = NULL;
    ListNode *node = NULL;
    size_t i;
    Person *person = NULL;
    Status status;

    (void)state;

    status_init(&status);

    assert_true(list_new(&list, sizeof(Person), &status));
    list_free(list);

    assert_true(list_new_alloc(&list, sizeof(Person), 10, &status));

    assert_true(list_push(list, (void **)&person, &status));
    person->name = "John";
    person->age = 43;

    assert_true(list_push(list, (void **)&person, &status));
    person->name = "Lyndon";
    person->age = 55;

    assert_true(list_push(list, (void **)&person, &status));
    person->name = "James";
    person->age = 53;

    assert_true(list_push(list, (void **)&person, &status));
    person->name = "William";
    person->age = 47;

    assert_true(list_push(list, (void **)&person, &status));
    person->name = "Barack";
    person->age = 46;

    i = 0;
    while (list_iterate(list, &node, (void **)&person)) {
        switch (i) {
            case 0:
                assert_string_equal(person->name, "Barack");
                assert_int_equal(person->age, 46);
                break;
            case 1:
                assert_string_equal(person->name, "William");
                assert_int_equal(person->age, 47);
                break;
            case 2:
                assert_string_equal(person->name, "James");
                assert_int_equal(person->age, 53);
                break;
            case 3:
                assert_string_equal(person->name, "Lyndon");
                assert_int_equal(person->age, 55);
                break;
            case 4:
                assert_string_equal(person->name, "John");
                assert_int_equal(person->age, 43);
                break;
        }
        i++;
    }

    person = NULL;

    assert_true(list_pop(list, (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(list_pop(list, (void **)&person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(list_pop(list, (void **)&person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(list_pop(list, (void **)&person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(list_pop(list, (void **)&person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    list_free(list);
    cbfree(list);
}

/* vi: set et ts=4 sw=4: */

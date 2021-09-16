#include <setjmp.h>

#include "cbase/list.h"

#include "cbase_test.h"
#include "./list.h"

#include <cmocka.h>

void test_list(void **state) {
    PersonList *list = NULL;
    PersonListNode *node = NULL;
    size_t i;
    Person *person = NULL;

    (void)state;

    assert_int_equal(person_list_new(&list), 0);
    person_list_free(list);

    assert_int_equal(person_list_new_alloc(&list, 10), 0);

    assert_int_equal(person_list_push_slot(list, &person), 0);
    assert_int_equal(list->len, 1);
    person->name = "John";
    person->age = 43;

    assert_int_equal(person_list_push_slot(list, &person), 0);
    assert_int_equal(list->len, 2);
    person->name = "Lyndon";
    person->age = 55;

    assert_int_equal(person_list_push_slot(list, &person), 0);
    assert_int_equal(list->len, 3);
    person->name = "James";
    person->age = 53;

    assert_int_equal(person_list_push_slot(list, &person), 0);
    assert_int_equal(list->len, 4);
    person->name = "William";
    person->age = 47;

    assert_int_equal(person_list_push_slot(list, &person), 0);
    assert_int_equal(list->len, 5);
    person->name = "Barack";
    person->age = 46;

    i = 0;
    while (person_list_iterate(list, &node, &person)) {
        switch (i) {
            case 0:
                assert_string_equal(person->name, "Barack");
                assert_int_equal(person->age, 46);
                assert_int_equal(list->len, 5);
                break;
            case 1:
                assert_string_equal(person->name, "William");
                assert_int_equal(person->age, 47);
                assert_int_equal(list->len, 5);
                break;
            case 2:
                assert_string_equal(person->name, "James");
                assert_int_equal(person->age, 53);
                assert_int_equal(list->len, 5);
                break;
            case 3:
                assert_string_equal(person->name, "Lyndon");
                assert_int_equal(person->age, 55);
                assert_int_equal(list->len, 5);
                break;
            case 4:
                assert_string_equal(person->name, "John");
                assert_int_equal(person->age, 43);
                assert_int_equal(list->len, 5);
                break;
        }
        i++;
    }

    assert_int_equal(list->len, 5);
    assert_int_equal(i, 5);

    person = NULL;

    assert_int_equal(person_list_pop(list, &person), 0);
    assert_int_equal(list->len, 4);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(person_list_pop(list, &person), 0);
    assert_int_equal(list->len, 3);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_int_equal(person_list_pop(list, &person), 0);
    assert_int_equal(list->len, 2);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_int_equal(person_list_pop(list, &person), 0);
    assert_int_equal(list->len, 1);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_list_pop(list, &person), 0);
    assert_int_equal(list->len, 0);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    person_list_destroy(&list);
    assert_null(list);
}

/* vi: set et ts=4 sw=4: */

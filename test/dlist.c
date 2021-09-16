#include <setjmp.h>

#include "cbase/dlist.h"

#include "cbase_test.h"
#include "./dlist.h"

#include <cmocka.h>

void test_dlist(void **state) {
    PersonList *dlist = NULL;
    PersonListNode *node = NULL;
    size_t i;
    Person *person = NULL;

    (void)state;

    assert_int_equal(person_list_new(&dlist), 0);
    person_list_free(dlist);

    assert_int_equal(person_list_new_alloc(&dlist, 10), 0);

    assert_int_equal(person_list_push_head_slot(dlist, &person), 0);
    assert_int_equal(dlist->len, 1);
    person->name = "James";
    person->age = 53;

    assert_int_equal(person_list_push_tail_slot(dlist, &person), 0);
    assert_int_equal(dlist->len, 2);
    person->name = "William";
    person->age = 47;

    assert_int_equal(person_list_push_head_slot(dlist, &person), 0);
    assert_int_equal(dlist->len, 3);
    person->name = "Lyndon";
    person->age = 55;

    assert_int_equal(person_list_push_tail_slot(dlist, &person), 0);
    assert_int_equal(dlist->len, 4);
    person->name = "Barack";
    person->age = 46;

    assert_int_equal(person_list_push_head_slot(dlist, &person), 0);
    assert_int_equal(dlist->len, 5);
    person->name = "John";
    person->age = 43;

    i = 0;
    while (person_list_iterate(dlist, &node, &person)) {
        switch (i) {
            case 0:
                assert_string_equal(person->name, "John");
                assert_int_equal(person->age, 43);
                assert_int_equal(dlist->len, 5);
                break;
            case 1:
                assert_string_equal(person->name, "Lyndon");
                assert_int_equal(person->age, 55);
                assert_int_equal(dlist->len, 5);
                break;
            case 2:
                assert_string_equal(person->name, "James");
                assert_int_equal(person->age, 53);
                assert_int_equal(dlist->len, 5);
                break;
            case 3:
                assert_string_equal(person->name, "William");
                assert_int_equal(person->age, 47);
                assert_int_equal(dlist->len, 5);
                break;
            case 4:
                assert_string_equal(person->name, "Barack");
                assert_int_equal(person->age, 46);
                assert_int_equal(dlist->len, 5);
                break;
        }
        i++;
    }

    assert_int_equal(dlist->len, 5);
    assert_int_equal(i, 5);

    person = NULL;

    assert_int_equal(person_list_pop_tail(dlist, &person), 0);
    assert_int_equal(dlist->len, 4);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(person_list_pop_head(dlist, &person), 0);
    assert_int_equal(dlist->len, 3);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_int_equal(person_list_pop_tail(dlist, &person), 0);
    assert_int_equal(dlist->len, 2);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_int_equal(person_list_pop_head(dlist, &person), 0);
    assert_int_equal(dlist->len, 1);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_list_pop_head(dlist, &person), 0);
    assert_int_equal(dlist->len, 0);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    person_list_destroy(&dlist);
    assert_null(dlist);
}

/* vi: set et ts=4 sw=4: */

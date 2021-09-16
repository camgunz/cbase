#include <setjmp.h>

#include "cbase/internal.h"
#include "cbase_test.h"
#include "./array.h"

#include <cmocka.h>

void test_array(void **state) {
    IntArray    *int_array;
    PersonArray *person_array;
    PersonArray *person_array2;
    PersonArray  stack_person_array;
    PersonArray  stack_person_array2;

    /*
    int     int_val;
    */
    Person *person;
    Person *person2;
    Person *person3;
    Person **pperson = &person3;
    Person *john = NULL;
    Person *lyndon = NULL;
    Person *james = NULL;
    Person *william = NULL;
    Person *barack = NULL;
    Person  stack_person;
    Person  bill;

    (void)state;

    assert_int_equal(cbmalloc(1, sizeof(Person), &john), 0);
    assert_int_equal(cbmalloc(1, sizeof(Person), &lyndon), 0);
    assert_int_equal(cbmalloc(1, sizeof(Person), &james), 0);
    assert_int_equal(cbmalloc(1, sizeof(Person), &william), 0);
    assert_int_equal(cbmalloc(1, sizeof(Person), &barack), 0);

    john->name = "John";
    john->age = 43;

    lyndon->name = "Lyndon";
    lyndon->age = 55;

    james->name = "James";
    james->age = 53;

    william->name = "William";
    william->age = 47;

    barack->name = "Barack";
    barack->age = 46;

    assert_int_equal(int_array_new_alloc(&int_array, 4), 0);
    assert_int_equal(int_array->len, 0);
    assert_int_equal(int_array->alloc, 4);

    assert_int_equal(person_array_new_alloc(&person_array, 3), 0);
    assert_non_null(person_array);
    assert_non_null(person_array->data);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 3);

    assert_int_equal(person_array_new(&person_array2), 0);
    assert_non_null(person_array2);
    assert_null(person_array2->data);
    assert_int_equal(person_array2->len, 0);
    assert_int_equal(person_array2->alloc, 0);

    /*
    int_val = 14;
    assert_int_equal(array_append(int_array, (char **)&int_val), 0);

    int_val = 22;
    assert_int_equal(array_append(int_array, (char **)&int_val), 0);

    int_val = 95;
    assert_int_equal(array_append(int_array, (char **)&int_val), 0);

    assert_int_equal(int_array->len, 3);
    assert_int_equal(int_array->alloc, 4);

    assert_int_equal(array_index(int_array, 0, (char **)&int_val), 0);
    assert_int_equal(int_val, 14);

    assert_int_equal(array_index(int_array, 1, (char **)&int_val), 0);
    assert_int_equal(int_val, 22);

    assert_int_equal(array_index(int_array, 2, (char **)&int_val), 0);
    assert_int_equal(int_val, 95);
    */

    assert_int_equal(person_array_append_slot(person_array, &person), 0);
    person->name = "John";
    person->age = 43;
    assert_int_equal(person_array->len, 1);
    assert_int_equal(person_array->alloc, 3);

    person = NULL;
    assert_null(person);

    assert_int_equal(person_array->len, 1);
    assert_int_equal(person_array_index(person_array, 0, &person), 0);
    assert_non_null(person);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_int_equal(person_array_append_slot(person_array, &person), 0);
    person->name = "Lyndon";
    person->age = 55;
    assert_int_equal(person_array->len, 2);
    assert_int_equal(person_array->alloc, 3);

    assert_int_equal(person_array_append_slot(person_array2, &person), 0);
    person->name = "James";
    person->age = 53;
    assert_int_equal(person_array2->len, 1);
    assert_int_equal(person_array2->alloc, 1);

    assert_int_equal(person_array_append_slot(person_array2, &person), 0);
    person->name = "William";
    person->age = 47;
    assert_int_equal(person_array2->len, 2);
    assert_int_equal(person_array2->alloc, 2);

    assert_int_equal(person_array_append_slot(person_array, &person), 0);
    person->name = "Barack";
    person->age = 46;

    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 3);

    assert_int_equal(
        person_array_insert_person_array(person_array, 2, person_array2),
        0
    );

    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 5);

    assert_int_equal(person_array2->len, 2);
    assert_int_equal(person_array2->alloc, 2);

    assert_int_equal(person_array_index(person_array, 0, &person), 0);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_int_equal(person_array_index(person_array, 1, &person), 0);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_array_index(person_array, 2, &person), 0);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_int_equal(person_array_index(person_array, 3, &person), 0);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_int_equal(person_array_index(person_array, 4, &person), 0);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(person_array_set_size(person_array, 20), 0);
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 20);

    assert_int_equal(person_array_index(person_array, 0, &person), 0);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_int_equal(person_array_index(person_array, 1, &person), 0);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_array_index(person_array, 2, &person), 0);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_int_equal(person_array_index(person_array, 3, &person), 0);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_int_equal(person_array_index(person_array, 4, &person), 0);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(person_array_set_size(person_array, 3), 0);
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 3);

    assert_int_equal(person_array_index(person_array, 0, &person), 0);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_int_equal(person_array_index(person_array, 1, &person), 0);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_array_index(person_array, 2, &person), 0);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    person_array_destroy(&person_array);

    person_array_destroy(&person_array2);

    assert_int_equal(person_array_new_alloc_zero(&person_array, 3), 0);
    assert_non_null(person_array);
    assert_non_null(person_array->data);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 3);

    assert_int_equal(person_array_ensure_capacity(person_array, 2), 0);
    assert_non_null(person_array->data);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 3);

    assert_int_equal(person_array_ensure_capacity(person_array, 4), 0);
    assert_non_null(person_array->data);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 4);

    assert_int_equal(person_array_append_slot(person_array, &person), 0);
    person->name = "Lyndon";
    person->age = 55;
    assert_int_equal(person_array->len, 1);
    assert_int_equal(person_array->alloc, 4);

    assert_int_equal(person_array_append_slot(person_array, &person), 0);
    person->name = "James";
    person->age = 53;
    assert_int_equal(person_array->len, 2);
    assert_int_equal(person_array->alloc, 4);

    assert_int_equal(person_array_append_slot(person_array, &person), 0);
    person->name = "Barack";
    person->age = 46;
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 4);

    assert_int_equal(person_array_insert_slot(person_array, 2, &person), 0);
    person->name = "William";
    person->age = 47;
    assert_int_equal(person_array->len, 4);
    assert_int_equal(person_array->alloc, 4);

    assert_int_equal(person_array_prepend_slot(person_array, &person), 0);
    person->name = "John";
    person->age = 43;
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 5);

    assert_int_equal(person_array_index(person_array, 0, &person), 0);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_int_equal(person_array_index(person_array, 1, &person), 0);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_array_index(person_array, 2, &person), 0);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_int_equal(person_array_index(person_array, 3, &person), 0);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_int_equal(person_array_index(person_array, 4, &person), 0);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(person_array_delete_unordered(person_array, 1), 0);
    assert_int_equal(person_array->len, 4);
    assert_int_equal(person_array->alloc, 5);

    assert_int_equal(person_array_index(person_array, 1, &person), 0);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(person_array_delete(person_array, 1), 0);
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 5);

    assert_int_equal(person_array_index(person_array, 1, &person), 0);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_int_equal(person_array_compact(person_array), 0);
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 3);

    assert_int_equal(person_array_index(person_array, 0, &person), 0);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_int_equal(person_array_index(person_array, 1, &person), 0);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_int_equal(person_array_index(person_array, 2, &person), 0);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_int_equal(person_array_copy_element(person_array, 2, &bill), 0);
    assert_string_equal(bill.name, "William");
    assert_int_equal(bill.age, 47);

    assert_int_equal(person_array_init_alloc_zero(&stack_person_array, 5), 0);

    assert_int_equal(stack_person_array.len, 0);
    assert_int_equal(stack_person_array.alloc, 5);

    assert_int_equal(person_array_init_alloc_zero(&stack_person_array2, 3), 0);

    assert_int_equal(stack_person_array2.len, 0);
    assert_int_equal(stack_person_array2.alloc, 3);

    assert_int_equal(person_array_append_slot(&stack_person_array, &person), 0);
    person->name = "Lyndon";
    person->age = 55;
    assert_int_equal(stack_person_array.len, 1);
    assert_int_equal(stack_person_array.alloc, 5);

    assert_int_equal(person_array_append_slot(&stack_person_array, &person), 0);
    person->name = "Barack";
    person->age = 46;
    assert_int_equal(stack_person_array.len, 2);
    assert_int_equal(stack_person_array.alloc, 5);

    assert_int_equal(person_array_index(&stack_person_array, 0, &person), 0);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_array_index(&stack_person_array, 1, &person), 0);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(
        person_array_assign_person_array(
            &stack_person_array2,
            &stack_person_array
        ),
        0
    );

    assert_int_equal(stack_person_array2.len, 2);
    assert_int_equal(stack_person_array2.alloc, 3);
    assert_int_equal(stack_person_array.len, 2);
    assert_int_equal(stack_person_array.alloc, 5);

    assert_int_equal(person_array_index(&stack_person_array2, 0, &person), 0);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_array_index(&stack_person_array2, 1, &person), 0);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    person_array_free(&stack_person_array2);

    assert_int_equal(
        person_array_append_person_array(person_array, &stack_person_array),
        0
    );
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 5);
    assert_int_equal(stack_person_array.len, 2);
    assert_int_equal(stack_person_array.alloc, 5);

    assert_int_equal(
        person_array_append_person_array(person_array, &stack_person_array),
        0
    );
    assert_int_equal(person_array->len, 7);
    assert_int_equal(person_array->alloc, 7);
    assert_int_equal(stack_person_array.len, 2);
    assert_int_equal(stack_person_array.alloc, 5);

    person_array_free(&stack_person_array);

    assert_int_equal(
        person_array_truncate_no_zero(person_array, person_array->len - 1),
        0
    );
    assert_int_equal(person_array->len, 6);
    assert_int_equal(person_array->alloc, 7);

    assert_int_equal(
        person_array_truncate(person_array, person_array->len - 1),
        0
    );
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 7);

    assert_int_equal(
        person_array_zero_element(person_array, person_array->len - 1),
        0
    );

    assert_int_equal(person_array_pop_right(person_array, &stack_person), 0);
    assert_ptr_equal(stack_person.name, NULL);
    assert_int_equal(stack_person.age, 0);

    assert_int_equal(person_array_pop_left(person_array, &stack_person), 0);
    assert_string_equal(stack_person.name, "John");
    assert_int_equal(stack_person.age, 43);

    assert_int_equal(
        person_array_pop_unordered(person_array, 0, &stack_person),
        0
    );
    assert_string_equal(stack_person.name, "James");
    assert_int_equal(stack_person.age, 53);

    assert_int_equal(person_array_index(person_array, 0, &person), 0);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    person_array_free(person_array);
    assert_ptr_equal(person_array->data, NULL);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 0);

    cbfree(person_array);

    assert_int_equal(person_array_new(&person_array), 0);
    assert_int_equal(person_array_ensure_capacity(person_array, 2), 0);
    assert_non_null(person_array->data);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 2);

    assert_int_equal(person_array_ensure_capacity(person_array, 4), 0);
    assert_non_null(person_array->data);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 4);

    assert_int_equal(person_array_append(person_array, lyndon), 0);
    assert_int_equal(person_array->len, 1);
    assert_int_equal(person_array->alloc, 4);

    assert_int_equal(person_array_append(person_array, james), 0);
    assert_int_equal(person_array->len, 2);
    assert_int_equal(person_array->alloc, 4);

    assert_int_equal(person_array_append(person_array, barack), 0);
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 4);

    assert_int_equal(person_array_index(person_array, 2, &person), 0);
    assert_non_null(person);
    assert_string_equal(person->name, barack->name);
    assert_int_equal(person->age, barack->age);

    assert_int_equal(person_array_insert(person_array, 2, william), 0);
    assert_int_equal(person_array->len, 4);
    assert_int_equal(person_array->alloc, 4);

    assert_int_equal(person_array_prepend(person_array, john), 0);
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 5);

    assert_int_equal(person_array_new(&person_array2), 0);

    assert_int_equal(
        person_array_assign_person_array(person_array2, person_array),
        0
    );
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 5);
    assert_int_equal(person_array2->len, 5);
    assert_int_equal(person_array2->alloc, 5);

    assert_int_equal(person_array_index(person_array2, 0, &person), 0);
    assert_non_null(person);
    assert_string_equal(john->name, "John");
    assert_int_equal(john->age, 43);

    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_int_equal(person_array_index(person_array, 1, &person), 0);
    assert_non_null(person);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_array_index(person_array, 2, &person), 0);
    assert_non_null(person);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_int_equal(person_array_index(person_array, 3, &person), 0);
    assert_non_null(person);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_int_equal(person_array_index(person_array, 4, &person), 0);
    assert_non_null(person);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(person_array_index(person_array2, 0, &person), 0);
    assert_non_null(person);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_int_equal(person_array_index(person_array2, 1, &person), 0);
    assert_non_null(person);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_array_index(person_array2, 2, &person), 0);
    assert_non_null(person);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_int_equal(person_array_index(person_array2, 3, &person), 0);
    assert_non_null(person);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_int_equal(person_array_index(person_array2, 4, &person), 0);
    assert_non_null(person);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(person_array2->len, 5);
    assert_int_equal(person_array_delete(person_array2, 4), 0);
    assert_int_equal(person_array2->len, 4);
    assert_int_equal(person_array2->alloc, 5);

    assert_int_equal(person_array_delete(person_array2, 3), 0);
    assert_int_equal(person_array2->len, 3);
    assert_int_equal(person_array2->alloc, 5);

    assert_int_equal(person_array_set_size(person_array2, 3), 0);
    assert_int_equal(person_array2->len, 3);
    assert_int_equal(person_array2->alloc, 3);

    assert_int_equal(person_array_set_size(person_array2, 4), 0);
    assert_int_equal(person_array2->len, 3);
    assert_int_equal(person_array2->alloc, 4);

    assert_int_equal(person_array_set_size(person_array2, 3), 0);
    assert_int_equal(person_array2->len, 3);
    assert_int_equal(person_array2->alloc, 3);

    assert_int_equal(person_array_zero_element(person_array2, 2), 0);
    person = person_array_index_fast(person_array2, 2);
    assert_non_null(person);
    assert_null(person->name);
    assert_int_equal(person->age, 0);
    assert_int_equal(person_array2->len, 3);
    assert_int_equal(person_array2->alloc, 3);

    assert_int_equal(person_array_delete_unordered(person_array, 1), 0);
    assert_int_equal(person_array->len, 4);
    assert_int_equal(person_array->alloc, 5);

    assert_int_equal(person_array_index(person_array, 1, &person), 0);
    assert_non_null(person);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(person_array_delete(person_array, 1), 0);
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 5);

    assert_int_equal(person_array_index(person_array, 1, &person), 0);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_int_equal(person_array_compact(person_array), 0);
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 3);

    assert_int_equal(person_array_index(person_array, 0, &person), 0);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_int_equal(person_array_index(person_array, 1, &person), 0);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_int_equal(person_array_index(person_array, 2, &person), 0);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_int_equal(person_array_init_alloc(&stack_person_array2, 3), 0);

    assert_int_equal(person_array_append(&stack_person_array2, lyndon), 0);
    assert_int_equal(stack_person_array2.len, 1);
    assert_int_equal(stack_person_array2.alloc, 3);

    assert_int_equal(person_array_append(&stack_person_array2, barack), 0);
    assert_int_equal(stack_person_array2.len, 2);
    assert_int_equal(stack_person_array2.alloc, 3);

    assert_int_equal(person_array_index(&stack_person_array2, 0, pperson), 0);
    assert_string_equal((*pperson)->name, "Lyndon");
    assert_int_equal((*pperson)->age, 55);

    assert_int_equal(person_array_index(&stack_person_array2, 1, pperson), 0);
    assert_string_equal((*pperson)->name, "Barack");
    assert_int_equal((*pperson)->age, 46);

    person_array_free(&stack_person_array2);

    assert_int_equal(person_array_init_alloc(&stack_person_array, 3), 0);

    assert_int_equal(person_array_append(&stack_person_array, lyndon), 0);
    assert_int_equal(stack_person_array.len, 1);
    assert_int_equal(stack_person_array.alloc, 3);

    assert_int_equal(person_array_append(&stack_person_array, barack), 0);
    assert_int_equal(stack_person_array.len, 2);
    assert_int_equal(stack_person_array.alloc, 3);

    assert_int_equal(
        person_array_append_person_array(person_array, &stack_person_array),
        0
    );
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 5);
    assert_int_equal(stack_person_array.len, 2);
    assert_int_equal(stack_person_array.alloc, 3);

    assert_int_equal(
        person_array_append_person_array(person_array, &stack_person_array),
        0
    );
    assert_int_equal(person_array->len, 7);
    assert_int_equal(person_array->alloc, 7);

    person_array_clear(&stack_person_array);
    assert_int_equal(stack_person_array.len, 0);
    assert_int_equal(stack_person_array.alloc, 3);

    person_array_free(&stack_person_array);

    assert_int_equal(person_array_index(person_array, 0, &person), 0);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_int_equal(person_array_index(person_array, 1, &person), 0);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_int_equal(person_array_index(person_array, 2, &person), 0);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_int_equal(person_array_index(person_array, 3, &person), 0);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_array_index(person_array, 4, &person), 0);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(person_array_index(person_array, 5, &person), 0);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_int_equal(person_array_index(person_array, 6, &person), 0);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(
        person_array_truncate(person_array, person_array->len - 2),
        0
    );
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 7);

    assert_int_equal(cbcalloc(1, sizeof(Person), &person2), 0);

    assert_int_equal(person_array_pop_right(person_array, person2), 0);
    assert_string_equal(person2->name, "Barack");
    assert_int_equal(person2->age, 46);

    assert_int_equal(person_array_pop_left(person_array, person2), 0);
    assert_string_equal(person2->name, "John");
    assert_int_equal(person2->age, 43);

    assert_int_equal(person_array_insert(person_array, 0, person2), 0);

    assert_int_equal(person_array_set(person_array, 0, james), 0);
    assert_int_equal(person_array_index(person_array, 0, &person), 0);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    person_array_free(person_array);
    assert_ptr_equal(person_array->data, NULL);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 0);

    cbfree(person_array);

    person_array_destroy(&person_array2);
    assert_null(person_array2);

    cbfree(john);
    cbfree(lyndon);
    cbfree(james);
    cbfree(william);
    cbfree(barack);
}

/* vi: set et ts=4 sw=4: */

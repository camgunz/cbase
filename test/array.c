#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_array(void **state) {
    Array *int_array;
    Array *person_array;
    Array *person_array2;
    Array  stack_person_array;
    Array  stack_person_array2;

    Status  status;
    /*
    int     int_val;
    */
    Person *person;
    Person *person2;
    Person **pperson;
    Person *john = NULL;
    Person *lyndon = NULL;
    Person *james = NULL;
    Person *william = NULL;
    Person *barack = NULL;
    Person  stack_person;
    Person  bill;

    (void)state;

    status_init(&status);

    assert_true(cbmalloc(1, sizeof(Person), &john, &status));
    assert_true(cbmalloc(1, sizeof(Person), &lyndon, &status));
    assert_true(cbmalloc(1, sizeof(Person), &james, &status));
    assert_true(cbmalloc(1, sizeof(Person), &william, &status));
    assert_true(cbmalloc(1, sizeof(Person), &barack, &status));

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

    assert_true(array_new_alloc(&int_array, 4, sizeof(int), &status));
    assert_int_equal(int_array->len, 0);
    assert_int_equal(int_array->alloc, 4);
    assert_int_equal(int_array->element_size, sizeof(int));

    assert_true(array_new_alloc(&person_array, 3, sizeof(Person), &status));
    assert_non_null(person_array);
    assert_non_null(person_array->elements);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 3);
    assert_int_equal(person_array->element_size, sizeof(Person));

    assert_true(array_new(&person_array2, sizeof(Person), &status));
    assert_non_null(person_array2);
    assert_null(person_array2->elements);
    assert_int_equal(person_array2->len, 0);
    assert_int_equal(person_array2->alloc, 0);
    assert_int_equal(person_array2->element_size, sizeof(Person));

    /*
    int_val = 14;
    assert_true(array_append(int_array, (void **)&int_val, &status));

    int_val = 22;
    assert_true(array_append(int_array, (void **)&int_val, &status));

    int_val = 95;
    assert_true(array_append(int_array, (void **)&int_val, &status));

    assert_int_equal(int_array->len, 3);
    assert_int_equal(int_array->alloc, 4);

    assert_true(array_index(int_array, 0, (void **)&int_val, &status));
    assert_int_equal(int_val, 14);

    assert_true(array_index(int_array, 1, (void **)&int_val, &status));
    assert_int_equal(int_val, 22);

    assert_true(array_index(int_array, 2, (void **)&int_val, &status));
    assert_int_equal(int_val, 95);
    */

    assert_true(array_append_slot(person_array, &person, &status));
    person->name = "John";
    person->age = 43;
    assert_int_equal(person_array->len, 1);
    assert_int_equal(person_array->alloc, 3);

    person = NULL;
    assert_null(person);
    assert_true(array_index(person_array, 0, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_append_slot(person_array, &person, &status));
    person->name = "Lyndon";
    person->age = 55;
    assert_int_equal(person_array->len, 2);
    assert_int_equal(person_array->alloc, 3);

    assert_true(array_append_slot(person_array2, &person, &status));
    person->name = "James";
    person->age = 53;
    assert_int_equal(person_array2->len, 1);
    assert_int_equal(person_array2->alloc, 1);

    assert_true(array_append_slot(person_array2, &person, &status));
    person->name = "William";
    person->age = 47;
    assert_int_equal(person_array2->len, 2);
    assert_int_equal(person_array2->alloc, 2);

    assert_true(array_append_slot(person_array, &person, &status));
    person->name = "Barack";
    person->age = 46;

    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 3);

    assert_true(array_insert_array(person_array, 2, person_array2, &status));

    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 5);

    assert_int_equal(person_array2->len, 2);
    assert_int_equal(person_array2->alloc, 2);

    assert_true(array_index(person_array, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(person_array, 1, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(person_array, 2, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(person_array, 3, &person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(person_array, 4, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_set_size(person_array, 20, &status));
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 20);

    assert_true(array_index(person_array, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(person_array, 1, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(person_array, 2, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(person_array, 3, &person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(person_array, 4, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_set_size(person_array, 3, &status));
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 3);

    assert_true(array_index(person_array, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(person_array, 1, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(person_array, 2, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    array_destroy(&person_array);

    array_destroy(&person_array2);

    assert_true(array_new_alloc_zero(
        &person_array, 3, sizeof(Person), &status
    ));
    assert_non_null(person_array);
    assert_non_null(person_array->elements);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 3);

    assert_true(array_ensure_capacity(person_array, 2, &status));
    assert_non_null(person_array->elements);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 3);

    assert_true(array_ensure_capacity(person_array, 4, &status));
    assert_non_null(person_array->elements);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 4);

    assert_true(array_append_slot(person_array, &person, &status));
    person->name = "Lyndon";
    person->age = 55;
    assert_int_equal(person_array->len, 1);
    assert_int_equal(person_array->alloc, 4);

    assert_true(array_append_slot(person_array, &person, &status));
    person->name = "James";
    person->age = 53;
    assert_int_equal(person_array->len, 2);
    assert_int_equal(person_array->alloc, 4);

    assert_true(array_append_slot(person_array, &person, &status));
    person->name = "Barack";
    person->age = 46;
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 4);

    assert_true(array_insert_slot(person_array, 2, &person, &status));
    person->name = "William";
    person->age = 47;
    assert_int_equal(person_array->len, 4);
    assert_int_equal(person_array->alloc, 4);

    assert_true(array_prepend_slot(person_array, &person, &status));
    person->name = "John";
    person->age = 43;
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 5);

    assert_true(array_index(person_array, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(person_array, 1, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(person_array, 2, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(person_array, 3, &person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(person_array, 4, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_delete_unordered(person_array, 1, &status));
    assert_int_equal(person_array->len, 4);
    assert_int_equal(person_array->alloc, 5);

    assert_true(array_index(person_array, 1, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_delete(person_array, 1, &status));
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 5);

    assert_true(array_index(person_array, 1, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_compact(person_array, &status));
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 3);

    assert_true(array_index(person_array, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(person_array, 1, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(person_array, 2, &person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_copy_element(person_array, 2, (void *)&bill, &status));
    assert_string_equal(bill.name, "William");
    assert_int_equal(bill.age, 47);

    assert_true(array_init_alloc_zero(
        &stack_person_array, 5, sizeof(Person), &status
    ));

    assert_int_equal(stack_person_array.len, 0);
    assert_int_equal(stack_person_array.alloc, 5);
    assert_int_equal(stack_person_array.element_size, sizeof(Person));

    assert_true(array_init_alloc_zero(
        &stack_person_array2, 3, sizeof(Person), &status
    ));

    assert_int_equal(stack_person_array2.len, 0);
    assert_int_equal(stack_person_array2.alloc, 3);
    assert_int_equal(stack_person_array2.element_size, sizeof(Person));

    assert_true(array_append_slot(&stack_person_array, &person, &status));
    person->name = "Lyndon";
    person->age = 55;
    assert_int_equal(stack_person_array.len, 1);
    assert_int_equal(stack_person_array.alloc, 5);

    assert_true(array_append_slot(&stack_person_array, &person, &status));
    person->name = "Barack";
    person->age = 46;
    assert_int_equal(stack_person_array.len, 2);
    assert_int_equal(stack_person_array.alloc, 5);

    assert_true(array_index(&stack_person_array, 0, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(&stack_person_array, 1, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_assign_array(
        &stack_person_array2, &stack_person_array, &status
    ));

    assert_int_equal(stack_person_array2.len, 2);
    assert_int_equal(stack_person_array2.alloc, 3);
    assert_int_equal(stack_person_array.len, 2);
    assert_int_equal(stack_person_array.alloc, 5);

    assert_true(array_index(&stack_person_array2, 0, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(&stack_person_array2, 1, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    array_free(&stack_person_array2);

    assert_true(array_append_array(
        person_array, &stack_person_array, &status
    ));
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 5);
    assert_int_equal(stack_person_array.len, 2);
    assert_int_equal(stack_person_array.alloc, 5);

    assert_true(array_append_array(
        person_array, &stack_person_array, &status
    ));
    assert_int_equal(person_array->len, 7);
    assert_int_equal(person_array->alloc, 7);
    assert_int_equal(stack_person_array.len, 2);
    assert_int_equal(stack_person_array.alloc, 5);

    array_free(&stack_person_array);

    assert_true(array_truncate_no_zero(
        person_array, person_array->len - 1, &status
    ));
    assert_int_equal(person_array->len, 6);
    assert_int_equal(person_array->alloc, 7);

    assert_true(array_truncate(person_array, person_array->len - 1, &status));
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 7);

    assert_true(array_zero_element(
        person_array, person_array->len - 1, &status
    ));

    assert_true(array_pop_right(person_array, &stack_person, &status));
    assert_ptr_equal(stack_person.name, NULL);
    assert_int_equal(stack_person.age, 0);

    assert_true(array_pop_left(person_array, &stack_person, &status));
    assert_string_equal(stack_person.name, "John");
    assert_int_equal(stack_person.age, 43);

    assert_true(array_pop_unordered(person_array, 0, &stack_person, &status));
    assert_string_equal(stack_person.name, "James");
    assert_int_equal(stack_person.age, 53);

    assert_true(array_index(person_array, 0, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    array_free(person_array);
    assert_ptr_equal(person_array->elements, NULL);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 0);
    assert_int_equal(person_array->element_size, sizeof(Person));

    cbfree(person_array);

    assert_true(array_new(&person_array, sizeof(Person), &status));
    assert_true(array_ensure_capacity(person_array, 2, &status));
    assert_non_null(person_array->elements);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 2);

    assert_true(array_ensure_capacity(person_array, 4, &status));
    assert_non_null(person_array->elements);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 4);

    assert_true(array_append(person_array, lyndon, &status));
    assert_int_equal(person_array->len, 1);
    assert_int_equal(person_array->alloc, 4);

    assert_true(array_append(person_array, james, &status));
    assert_int_equal(person_array->len, 2);
    assert_int_equal(person_array->alloc, 4);

    assert_true(array_append(person_array, barack, &status));
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 4);

    assert_true(array_index(person_array, 2, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, barack->name);
    assert_int_equal(person->age, barack->age);

    assert_true(array_insert(person_array, 2, william, &status));
    assert_int_equal(person_array->len, 4);
    assert_int_equal(person_array->alloc, 4);

    assert_true(array_prepend(person_array, john, &status));
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 5);

    assert_true(array_new(&person_array2, sizeof(Person), &status));

    assert_true(array_assign_array(person_array2, person_array, &status));
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 5);
    assert_int_equal(person_array2->len, 5);
    assert_int_equal(person_array2->alloc, 5);

    assert_true(array_index(person_array2, 0, &person, &status));
    assert_non_null(person);
    assert_string_equal(john->name, "John");
    assert_int_equal(john->age, 43);

    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(person_array, 1, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(person_array, 2, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(person_array, 3, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(person_array, 4, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_index(person_array2, 0, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(person_array2, 1, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(person_array2, 2, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(person_array2, 3, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(person_array2, 4, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(person_array2->len, 5);
    assert_true(array_delete(person_array2, 4, &status));
    assert_int_equal(person_array2->len, 4);
    assert_int_equal(person_array2->alloc, 5);

    assert_true(array_delete(person_array2, 3, &status));
    assert_int_equal(person_array2->len, 3);
    assert_int_equal(person_array2->alloc, 5);

    assert_true(array_set_size(person_array2, 3, &status));
    assert_int_equal(person_array2->len, 3);
    assert_int_equal(person_array2->alloc, 3);

    assert_true(array_set_size(person_array2, 4, &status));
    assert_int_equal(person_array2->len, 3);
    assert_int_equal(person_array2->alloc, 4);

    assert_true(array_set_size(person_array2, 3, &status));
    assert_int_equal(person_array2->len, 3);
    assert_int_equal(person_array2->alloc, 3);

    assert_true(array_zero_element(person_array2, 2, &status));
    person = array_index_fast(person_array2, 2);
    assert_non_null(person);
    assert_null(person->name);
    assert_int_equal(person->age, 0);
    assert_int_equal(person_array2->len, 3);
    assert_int_equal(person_array2->alloc, 3);

    assert_true(array_delete_unordered(person_array, 1, &status));
    assert_int_equal(person_array->len, 4);
    assert_int_equal(person_array->alloc, 5);

    assert_true(array_index(person_array, 1, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_delete(person_array, 1, &status));
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 5);

    assert_true(array_index(person_array, 1, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_compact(person_array, &status));
    assert_int_equal(person_array->len, 3);
    assert_int_equal(person_array->alloc, 3);

    assert_true(array_index(person_array, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(person_array, 1, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(person_array, 2, &person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    (void)pperson;

    assert_true(array_init_alloc(
        &stack_person_array2, 3, sizeof(Person*), &status)
    );

    assert_true(array_append(&stack_person_array2, &lyndon, &status));
    assert_int_equal(stack_person_array2.len, 1);
    assert_int_equal(stack_person_array2.alloc, 3);

    assert_true(array_append(&stack_person_array2, &barack, &status));
    assert_int_equal(stack_person_array2.len, 2);
    assert_int_equal(stack_person_array2.alloc, 3);

    assert_true(array_index(&stack_person_array2, 0, &pperson, &status));
    assert_string_equal((*pperson)->name, "Lyndon");
    assert_int_equal((*pperson)->age, 55);

    assert_true(array_index(&stack_person_array2, 1, &pperson, &status));
    assert_string_equal((*pperson)->name, "Barack");
    assert_int_equal((*pperson)->age, 46);

    array_free(&stack_person_array2);

    assert_true(array_init_alloc(
        &stack_person_array, 3, sizeof(Person), &status)
    );

    assert_true(array_append(&stack_person_array, lyndon, &status));
    assert_int_equal(stack_person_array.len, 1);
    assert_int_equal(stack_person_array.alloc, 3);

    assert_true(array_append(&stack_person_array, barack, &status));
    assert_int_equal(stack_person_array.len, 2);
    assert_int_equal(stack_person_array.alloc, 3);

    assert_true(array_append_array(
        person_array, &stack_person_array, &status
    ));
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 5);
    assert_int_equal(stack_person_array.len, 2);
    assert_int_equal(stack_person_array.alloc, 3);

    assert_true(array_append_array(
        person_array, &stack_person_array, &status
    ));
    assert_int_equal(person_array->len, 7);
    assert_int_equal(person_array->alloc, 7);

    array_clear(&stack_person_array);
    assert_int_equal(stack_person_array.len, 0);
    assert_int_equal(stack_person_array.alloc, 3);

    array_free(&stack_person_array);

    assert_true(array_index(person_array, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(person_array, 1, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(person_array, 2, &person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(person_array, 3, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(person_array, 4, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_index(person_array, 5, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(person_array, 6, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_truncate(person_array, person_array->len - 2, &status));
    assert_int_equal(person_array->len, 5);
    assert_int_equal(person_array->alloc, 7);

    assert_true(cbcalloc(1, sizeof(Person), &person2, &status));

    assert_true(array_pop_right(person_array, person2, &status));
    assert_string_equal(person2->name, "Barack");
    assert_int_equal(person2->age, 46);

    assert_true(array_pop_left(person_array, person2, &status));
    assert_string_equal(person2->name, "John");
    assert_int_equal(person2->age, 43);

    assert_true(array_insert(person_array, 0, person2, &status));

    assert_true(array_set(person_array, 0, james, &status));
    assert_true(array_index(person_array, 0, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    array_free(person_array);
    assert_ptr_equal(person_array->elements, NULL);
    assert_int_equal(person_array->len, 0);
    assert_int_equal(person_array->alloc, 0);

    cbfree(person_array);

    array_destroy(&person_array2);
    assert_null(person_array2);

    cbfree(john);
    cbfree(lyndon);
    cbfree(james);
    cbfree(william);
    cbfree(barack);
}

/* vi: set et ts=4 sw=4: */

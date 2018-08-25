#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_array(void **state) {
    Array *array;
    Array *array2;
    Status status;
    Person *person;

    (void)state;

    status_init(&status);

    assert_true(array_new_alloc(&array, sizeof(Person), 3, &status));
    assert_true(array_ensure_capacity_zero(array, 5, &status));
    assert_true(array_new(&array2, sizeof(Person), &status));

    assert_true(array_append(array, (void **)&person, &status));
    person->name = "John";
    person->age = 43;

    assert_true(array_append(array, (void **)&person, &status));
    person->name = "Lyndon";
    person->age = 55;

    assert_true(array_append(array2, (void **)&person, &status));
    person->name = "James";
    person->age = 53;

    assert_true(array_append(array2, (void **)&person, &status));
    person->name = "William";
    person->age = 47;

    assert_true(array_append(array, (void **)&person, &status));
    person->name = "Barack";
    person->age = 46;

    assert_int_equal(array->len, 3);
    assert_int_equal(array->alloc, 5);

    assert_true(array_insert_array(array, 2, array2, &status));

    assert_int_equal(array->len, 5);
    assert_int_equal(array->alloc, 5);

    assert_int_equal(array2->len, 2);
    assert_int_equal(array2->alloc, 2);

    assert_true(array_index(array, 0, (void **)&person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(array, 1, (void **)&person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(array, 2, (void **)&person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(array, 3, (void **)&person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(array, 4, (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_set_size(array, 20, &status));
    assert_int_equal(array->len, 5);
    assert_int_equal(array->alloc, 20);

    assert_true(array_index(array, 0, (void **)&person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(array, 1, (void **)&person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(array, 2, (void **)&person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(array, 3, (void **)&person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(array, 4, (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_set_size(array, 3, &status));
    assert_int_equal(array->len, 3);
    assert_int_equal(array->alloc, 3);

    assert_true(array_index(array, 0, (void **)&person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(array, 1, (void **)&person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(array, 2, (void **)&person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    array_free(array);
    cbfree(array);

    array_free(array2);
    cbfree(array2);

    assert_true(array_new_alloc_zero(&array, sizeof(Person), 3, &status));
    assert_non_null(array);
    assert_non_null(array->elements);
    assert_int_equal(array->len, 0);
    assert_int_equal(array->alloc, 3);

    assert_true(array_ensure_capacity(array, 2, &status));
    assert_non_null(array->elements);
    assert_int_equal(array->len, 0);
    assert_int_equal(array->alloc, 3);

    assert_true(array_ensure_capacity(array, 4, &status));
    assert_non_null(array->elements);
    assert_int_equal(array->len, 0);
    assert_int_equal(array->alloc, 4);

    assert_true(array_append(array, (void **)&person, &status));
    person->name = "Lyndon";
    person->age = 55;
    assert_int_equal(array->len, 1);
    assert_int_equal(array->alloc, 4);

    assert_true(array_append(array, (void **)&person, &status));
    person->name = "James";
    person->age = 53;
    assert_int_equal(array->len, 2);
    assert_int_equal(array->alloc, 4);

    assert_true(array_append(array, (void **)&person, &status));
    person->name = "Barack";
    person->age = 46;
    assert_int_equal(array->len, 3);
    assert_int_equal(array->alloc, 4);

    assert_true(array_insert(array, 2, (void **)&person, &status));
    person->name = "William";
    person->age = 47;
    assert_int_equal(array->len, 4);
    assert_int_equal(array->alloc, 4);

    assert_true(array_prepend(array, (void **)&person, &status));
    person->name = "John";
    person->age = 43;
    assert_int_equal(array->len, 5);
    assert_int_equal(array->alloc, 5);

    assert_true(array_index(array, 0, (void **)&person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(array, 1, (void **)&person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(array, 2, (void **)&person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(array, 3, (void **)&person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(array, 4, (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_delete_unordered(array, 1, &status));
    assert_int_equal(array->len, 4);
    assert_int_equal(array->alloc, 5);

    assert_true(array_index(array, 1, (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_delete(array, 1, &status));
    assert_int_equal(array->len, 3);
    assert_int_equal(array->alloc, 5);

    assert_true(array_index(array, 1, (void **)&person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_compact(array, &status));
    assert_int_equal(array->len, 3);
    assert_int_equal(array->alloc, 3);

    assert_true(array_index(array, 0, (void **)&person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(array, 1, (void **)&person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(array, 2, (void **)&person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    Person bill;

    assert_true(array_copy_element(array, 2, (void *)&bill, &status));
    assert_string_equal(bill.name, "William");
    assert_int_equal(bill.age, 47);

    Array stack_array;
    Array stack_array2;

    assert_true(array_init_alloc_zero(&stack_array2, sizeof(Person), 3, &status));

    assert_true(array_init_alloc(&stack_array, sizeof(Person), 3, &status));

    assert_true(array_append(&stack_array, (void **)&person, &status));
    person->name = "Lyndon";
    person->age = 55;
    assert_int_equal(stack_array.len, 1);
    assert_int_equal(stack_array.alloc, 3);

    assert_true(array_append(&stack_array, (void **)&person, &status));
    person->name = "Barack";
    person->age = 46;
    assert_int_equal(stack_array.len, 2);
    assert_int_equal(stack_array.alloc, 3);

    assert_true(array_index(&stack_array, 0, (void **)&person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(&stack_array, 1, (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_assign_array(&stack_array2, &stack_array, &status));
    array_free(&stack_array2);

    assert_true(array_append_array(array, &stack_array, &status));
    assert_int_equal(array->len, 5);
    assert_int_equal(array->alloc, 5);
    assert_int_equal(stack_array.len, 2);
    assert_int_equal(stack_array.alloc, 3);

    assert_true(array_append_array(array, &stack_array, &status));
    assert_int_equal(array->len, 7);
    assert_int_equal(array->alloc, 7);
    assert_int_equal(stack_array.len, 0);
    assert_int_equal(stack_array.alloc, 3);

    array_free(&stack_array);

    assert_true(array_truncate_no_zero(array, array->len - 1, &status));
    assert_int_equal(array->len, 6);
    assert_int_equal(array->alloc, 7);

    assert_true(array_truncate(array, array->len - 1, &status));
    assert_int_equal(array->len, 5);
    assert_int_equal(array->alloc, 7);

    assert_true(array_zero_element(array, array->len - 1, &status));

    Person stack_person;
    
    assert_true(array_pop_right(array, &stack_person, &status));
    assert_ptr_equal(stack_person.name, NULL);
    assert_int_equal(stack_person.age, 0);

    assert_true(array_pop_left(array, &stack_person, &status));
    assert_string_equal(stack_person.name, "John");
    assert_int_equal(stack_person.age, 43);

    assert_true(array_pop_unordered(array, 0, &stack_person, &status));
    assert_string_equal(stack_person.name, "James");
    assert_int_equal(stack_person.age, 53);

    assert_true(array_index(array, 0, (void **)&person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    array_free(array);
    assert_ptr_equal(array->elements, NULL);
    assert_int_equal(array->len, 0);
    assert_int_equal(array->alloc, 0);
    assert_int_equal(array->element_size, sizeof(Person));

    cbfree(array);
}

/* vi: set et ts=4 sw=4: */

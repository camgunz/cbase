#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_array(void **state) {
    Array *array;
    Array *array2;
    Array *parray;
    Array *parray2;
    Array  stack_array;
    Array  stack_array2;
    Array  stack_parray;

    Status  status;
    Person *person;
    Person *person2;
    Person *john = NULL;
    Person *lyndon = NULL;
    Person *james = NULL;
    Person *william = NULL;
    Person *barack = NULL;
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

    assert_true(array_new_alloc(&array, 3, sizeof(Person), &status));
    assert_int_equal(array->len, 0);
    assert_int_equal(array->alloc, 3);
    assert_int_equal(array->element_size, sizeof(Person));

    assert_true(array_ensure_capacity_zero(array, 5, &status));
    assert_int_equal(array->len, 0);
    assert_int_equal(array->alloc, 5);
    assert_int_equal(array->element_size, sizeof(Person));

    assert_true(array_new(&array2, sizeof(Person), &status));
    assert_int_equal(array2->len, 0);
    assert_int_equal(array2->alloc, 0);
    assert_int_equal(array2->element_size, sizeof(Person));

    assert_true(array_new_alloc(&parray, 3, sizeof(Person *), &status));
    assert_non_null(parray);
    assert_non_null(parray->elements);
    assert_int_equal(parray->len, 0);
    assert_int_equal(parray->alloc, 3);

    assert_true(array_new(&parray2, sizeof(Person *), &status));
    assert_non_null(parray2);
    assert_null(parray2->elements);
    assert_int_equal(parray2->len, 0);
    assert_int_equal(parray2->alloc, 0);

    assert_true(array_append_slot(array, &person, &status));
    person->name = "John";
    person->age = 43;
    assert_int_equal(array->len, 1);
    assert_int_equal(array->alloc, 5);

    assert_true(array_append_slot(array, &person, &status));
    person->name = "Lyndon";
    person->age = 55;
    assert_int_equal(array->len, 2);
    assert_int_equal(array->alloc, 5);

    assert_true(array_append_slot(array2, &person, &status));
    person->name = "James";
    person->age = 53;
    assert_int_equal(array2->len, 1);
    assert_int_equal(array2->alloc, 1);

    assert_true(array_append_slot(array2, &person, &status));
    person->name = "William";
    person->age = 47;
    assert_int_equal(array2->len, 2);
    assert_int_equal(array2->alloc, 2);

    assert_true(array_append_slot(array, &person, &status));
    person->name = "Barack";
    person->age = 46;

    assert_int_equal(array->len, 3);
    assert_int_equal(array->alloc, 5);

    assert_true(array_insert_array(array, 2, array2, &status));

    assert_int_equal(array->len, 5);
    assert_int_equal(array->alloc, 5);

    assert_int_equal(array2->len, 2);
    assert_int_equal(array2->alloc, 2);

    assert_true(array_index(array, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(array, 1, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(array, 2, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(array, 3, &person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(array, 4, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_set_size(array, 20, &status));
    assert_int_equal(array->len, 5);
    assert_int_equal(array->alloc, 20);

    assert_true(array_index(array, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(array, 1, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(array, 2, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(array, 3, &person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(array, 4, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_set_size(array, 3, &status));
    assert_int_equal(array->len, 3);
    assert_int_equal(array->alloc, 3);

    assert_true(array_index(array, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(array, 1, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(array, 2, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    array_free(array);
    cbfree(array);

    array_free(array2);
    cbfree(array2);

    assert_true(array_new_alloc_zero(&array, 3, sizeof(Person), &status));
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

    assert_true(array_append_slot(array, &person, &status));
    person->name = "Lyndon";
    person->age = 55;
    assert_int_equal(array->len, 1);
    assert_int_equal(array->alloc, 4);

    assert_true(array_append_slot(array, &person, &status));
    person->name = "James";
    person->age = 53;
    assert_int_equal(array->len, 2);
    assert_int_equal(array->alloc, 4);

    assert_true(array_append_slot(array, &person, &status));
    person->name = "Barack";
    person->age = 46;
    assert_int_equal(array->len, 3);
    assert_int_equal(array->alloc, 4);

    assert_true(array_insert_slot(array, 2, &person, &status));
    person->name = "William";
    person->age = 47;
    assert_int_equal(array->len, 4);
    assert_int_equal(array->alloc, 4);

    assert_true(array_prepend_slot(array, &person, &status));
    person->name = "John";
    person->age = 43;
    assert_int_equal(array->len, 5);
    assert_int_equal(array->alloc, 5);

    assert_true(array_index(array, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(array, 1, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(array, 2, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(array, 3, &person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(array, 4, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_delete_unordered(array, 1, &status));
    assert_int_equal(array->len, 4);
    assert_int_equal(array->alloc, 5);

    assert_true(array_index(array, 1, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_delete(array, 1, &status));
    assert_int_equal(array->len, 3);
    assert_int_equal(array->alloc, 5);

    assert_true(array_index(array, 1, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_compact(array, &status));
    assert_int_equal(array->len, 3);
    assert_int_equal(array->alloc, 3);

    assert_true(array_index(array, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(array, 1, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(array, 2, &person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_copy_element(array, 2, (void *)&bill, &status));
    assert_string_equal(bill.name, "William");
    assert_int_equal(bill.age, 47);

    assert_true(array_init_alloc_zero(
        &stack_array2, 3, sizeof(Person), &status
    ));

    assert_true(array_init_alloc(&stack_array, 3, sizeof(Person), &status));

    assert_true(array_append_slot(&stack_array, &person, &status));
    person->name = "Lyndon";
    person->age = 55;
    assert_int_equal(stack_array.len, 1);
    assert_int_equal(stack_array.alloc, 3);

    assert_true(array_append_slot(&stack_array, &person, &status));
    person->name = "Barack";
    person->age = 46;
    assert_int_equal(stack_array.len, 2);
    assert_int_equal(stack_array.alloc, 3);

    assert_true(array_index(&stack_array, 0, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(&stack_array, 1, &person, &status));
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
    assert_int_equal(stack_array.len, 2);
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

    assert_true(array_index(array, 0, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    array_free(array);
    assert_ptr_equal(array->elements, NULL);
    assert_int_equal(array->len, 0);
    assert_int_equal(array->alloc, 0);
    assert_int_equal(array->element_size, sizeof(Person));

    cbfree(array);

    assert_true(array_ensure_capacity(parray, 2, &status));
    assert_non_null(parray->elements);
    assert_int_equal(parray->len, 0);
    assert_int_equal(parray->alloc, 3);

    assert_true(array_ensure_capacity(parray, 4, &status));
    assert_non_null(parray->elements);
    assert_int_equal(parray->len, 0);
    assert_int_equal(parray->alloc, 4);

    assert_true(array_append(parray, lyndon, &status));
    assert_int_equal(parray->len, 1);
    assert_int_equal(parray->alloc, 4);

    assert_true(array_append(parray, james, &status));
    assert_int_equal(parray->len, 2);
    assert_int_equal(parray->alloc, 4);

    assert_true(array_append(parray, barack, &status));
    assert_int_equal(parray->len, 3);
    assert_int_equal(parray->alloc, 4);

    assert_true(array_insert(parray, 2, william, &status));
    assert_int_equal(parray->len, 4);
    assert_int_equal(parray->alloc, 4);

    assert_true(array_prepend(parray, john, &status));
    assert_int_equal(parray->len, 5);
    assert_int_equal(parray->alloc, 5);

    assert_true(array_assign_array(parray2, parray, &status));
    assert_int_equal(parray->len, 5);
    assert_int_equal(parray->alloc, 5);

    assert_true(array_index(parray, 0, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(parray, 1, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(parray, 2, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(parray, 3, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(parray, 4, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_index(parray2, 0, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(parray2, 1, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(parray2, 2, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(parray2, 3, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_index(parray2, 4, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(parray2->len, 5);
    assert_true(array_delete(parray2, 4, &status));
    assert_int_equal(parray2->len, 4);
    assert_int_equal(parray2->alloc, 5);

    assert_true(array_delete(parray2, 3, &status));
    assert_int_equal(parray2->len, 3);
    assert_int_equal(parray2->alloc, 5);

    assert_true(array_set_size(parray2, 3, &status));
    assert_int_equal(parray2->len, 3);
    assert_int_equal(parray2->alloc, 3);

    assert_true(array_set_size(parray2, 4, &status));
    assert_int_equal(parray2->len, 3);
    assert_int_equal(parray2->alloc, 4);

    assert_true(array_set_size(parray2, 3, &status));
    assert_int_equal(parray2->len, 3);
    assert_int_equal(parray2->alloc, 3);

    assert_true(array_zero_element(parray2, 2, &status));
    assert_null(array_index_fast(parray2, 2));
    assert_int_equal(parray2->len, 3);
    assert_int_equal(parray2->alloc, 3);

    assert_true(array_delete_unordered(parray, 1, &status));
    assert_int_equal(parray->len, 4);
    assert_int_equal(parray->alloc, 5);

    assert_true(array_index(parray, 1, &person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_delete(parray, 1, &status));
    assert_int_equal(parray->len, 3);
    assert_int_equal(parray->alloc, 5);

    assert_true(array_index(parray, 1, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_compact(parray, &status));
    assert_int_equal(parray->len, 3);
    assert_int_equal(parray->alloc, 3);

    assert_true(array_index(parray, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(array_index(parray, 1, &person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(array_index(parray, 2, &person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(array_init_alloc(&stack_parray, 3, sizeof(void*), &status));

    assert_true(array_append(&stack_parray, lyndon, &status));
    assert_int_equal(stack_parray.len, 1);
    assert_int_equal(stack_parray.alloc, 3);

    assert_true(array_append(&stack_parray, barack, &status));
    assert_int_equal(stack_parray.len, 2);
    assert_int_equal(stack_parray.alloc, 3);

    assert_true(array_index(&stack_parray, 0, &person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(array_index(&stack_parray, 1, &person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(array_append_array(parray, &stack_parray, &status));
    assert_int_equal(parray->len, 5);
    assert_int_equal(parray->alloc, 5);
    assert_int_equal(stack_parray.len, 2);
    assert_int_equal(stack_parray.alloc, 3);

    assert_true(array_append_array(parray, &stack_parray, &status));
    assert_int_equal(parray->len, 7);
    assert_int_equal(parray->alloc, 7);

    array_clear(&stack_parray);
    assert_int_equal(stack_parray.len, 0);
    assert_int_equal(stack_parray.alloc, 3);

    array_free(&stack_parray);

    assert_true(array_truncate(parray, parray->len - 2, &status));
    assert_int_equal(parray->len, 5);
    assert_int_equal(parray->alloc, 7);

    assert_true(array_pop_right(parray, &person2, &status));
    assert_string_equal(person2->name, "Barack");
    assert_int_equal(person2->age, 46);

    assert_true(array_pop_left(parray, &person2, &status));
    assert_string_equal(person2->name, "John");
    assert_int_equal(person2->age, 43);

    assert_true(array_insert(parray, 0, person2, &status));

    assert_true(array_set(parray, 0, &person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    array_free(parray);
    assert_ptr_equal(parray->elements, NULL);
    assert_int_equal(parray->len, 0);
    assert_int_equal(parray->alloc, 0);

    cbfree(parray);

    array_free(parray2);
    cbfree(parray2);

    cbfree(john);
    cbfree(lyndon);
    cbfree(james);
    cbfree(william);
    cbfree(barack);
}

/* vi: set et ts=4 sw=4: */

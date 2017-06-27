#include <setjmp.h>

#include "cbase.h"
#include "cbase_test.h"

#include <cmocka.h>

void test_parray(void **state) {
    PArray *parray;
    PArray *parray2;
    Status status;
    Person *person = NULL;
    Person *john = cbmalloc(1, sizeof(Person));
    Person *lyndon = cbmalloc(1, sizeof(Person));
    Person *james = cbmalloc(1, sizeof(Person));
    Person *william = cbmalloc(1, sizeof(Person));
    Person *barack = cbmalloc(1, sizeof(Person));

    (void)state;

    status_init(&status);

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

    assert_true(parray_new_alloc(&parray, 3, &status));
    assert_non_null(parray);
    assert_non_null(parray->elements);
    assert_int_equal(parray->len, 0);
    assert_int_equal(parray->alloc, 3);

    assert_true(parray_new(&parray2, &status));
    assert_non_null(parray2);
    assert_null(parray2->elements);
    assert_int_equal(parray2->len, 0);
    assert_int_equal(parray2->alloc, 0);

    assert_true(parray_ensure_capacity(parray, 2, &status));
    assert_non_null(parray->elements);
    assert_int_equal(parray->len, 0);
    assert_int_equal(parray->alloc, 3);

    assert_true(parray_ensure_capacity(parray, 4, &status));
    assert_non_null(parray->elements);
    assert_int_equal(parray->len, 0);
    assert_int_equal(parray->alloc, 4);

    assert_true(parray_append(parray, lyndon, &status));
    assert_int_equal(parray->len, 1);
    assert_int_equal(parray->alloc, 4);

    assert_true(parray_append(parray, james, &status));
    assert_int_equal(parray->len, 2);
    assert_int_equal(parray->alloc, 4);

    assert_true(parray_append(parray, barack, &status));
    assert_int_equal(parray->len, 3);
    assert_int_equal(parray->alloc, 4);

    assert_true(parray_insert(parray, 2, william, &status));
    assert_int_equal(parray->len, 4);
    assert_int_equal(parray->alloc, 4);

    assert_true(parray_prepend(parray, john, &status));
    assert_int_equal(parray->len, 5);
    assert_int_equal(parray->alloc, 5);

    assert_true(parray_copy(parray2, parray, &status));
    assert_int_equal(parray->len, 5);
    assert_int_equal(parray->alloc, 5);

    assert_true(parray_index(parray, 0, (void **)&person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(parray_index(parray, 1, (void **)&person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(parray_index(parray, 2, (void **)&person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(parray_index(parray, 3, (void **)&person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(parray_index(parray, 4, (void **)&person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(parray_index(parray2, 0, (void **)&person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(parray_index(parray2, 1, (void **)&person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(parray_index(parray2, 2, (void **)&person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(parray_index(parray2, 3, (void **)&person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(parray_index(parray2, 4, (void **)&person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_int_equal(parray2->len, 5);
    assert_true(parray_delete(parray2, 4, &status));
    assert_int_equal(parray2->len, 4);
    assert_int_equal(parray2->alloc, 5);

    assert_true(parray_delete(parray2, 3, &status));
    assert_int_equal(parray2->len, 3);
    assert_int_equal(parray2->alloc, 5);

    assert_true(parray_set_size(parray2, 3, &status));
    assert_int_equal(parray2->len, 3);
    assert_int_equal(parray2->alloc, 3);

    assert_true(parray_set_size(parray2, 4, &status));
    assert_int_equal(parray2->len, 3);
    assert_int_equal(parray2->alloc, 4);

    assert_true(parray_set_size(parray2, 3, &status));
    assert_int_equal(parray2->len, 3);
    assert_int_equal(parray2->alloc, 3);

    assert_true(parray_delete_leave_null(parray2, 2, &status));
    assert_null(parray_index_fast(parray2, 2));
    assert_int_equal(parray2->len, 3);
    assert_int_equal(parray2->alloc, 3);

    assert_true(parray_pop_leave_null(parray2, 1, (void **)&person, &status));
    assert_null(parray_index_fast(parray2, 1));
    assert_int_equal(parray2->len, 3);
    assert_int_equal(parray2->alloc, 3);
    assert_non_null(person);
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(parray_delete_unordered(parray, 1, &status));
    assert_int_equal(parray->len, 4);
    assert_int_equal(parray->alloc, 5);

    assert_true(parray_index(parray, 1, (void **)&person, &status));
    assert_non_null(person);
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(parray_delete(parray, 1, &status));
    assert_int_equal(parray->len, 3);
    assert_int_equal(parray->alloc, 5);

    assert_true(parray_index(parray, 1, (void **)&person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(parray_shrink(parray, &status));
    assert_int_equal(parray->len, 3);
    assert_int_equal(parray->alloc, 3);

    assert_true(parray_index(parray, 0, (void **)&person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(parray_index(parray, 1, (void **)&person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(parray_index(parray, 2, (void **)&person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    PArray stack_parray;
    assert_true(parray_init_alloc(&stack_parray, 3, &status));

    assert_true(parray_append(&stack_parray, lyndon, &status));
    assert_int_equal(stack_parray.len, 1);
    assert_int_equal(stack_parray.alloc, 3);

    assert_true(parray_append(&stack_parray, barack, &status));
    assert_int_equal(stack_parray.len, 2);
    assert_int_equal(stack_parray.alloc, 3);

    assert_true(parray_index(&stack_parray, 0, (void **)&person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(parray_index(&stack_parray, 1, (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(parray_concat_no_clear(parray, &stack_parray, &status));
    assert_int_equal(parray->len, 5);
    assert_int_equal(parray->alloc, 5);
    assert_int_equal(stack_parray.len, 2);
    assert_int_equal(stack_parray.alloc, 3);

    assert_true(parray_concat(parray, &stack_parray, &status));
    assert_int_equal(parray->len, 7);
    assert_int_equal(parray->alloc, 7);
    assert_int_equal(stack_parray.len, 0);
    assert_int_equal(stack_parray.alloc, 3);

    parray_free(&stack_parray);

    assert_true(parray_truncate(parray, parray->len - 2, &status));
    assert_int_equal(parray->len, 5);
    assert_int_equal(parray->alloc, 7);

    Person *person2;
    
    assert_true(parray_pop_right(parray, (void **)&person2, &status));
    assert_string_equal(person2->name, "Barack");
    assert_int_equal(person2->age, 46);

    assert_true(parray_pop_left(parray, (void **)&person2, &status));
    assert_string_equal(person2->name, "John");
    assert_int_equal(person2->age, 43);

    assert_true(parray_set(parray, 0, person2, &status));

    assert_true(parray_index(parray, 0, (void **)&person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    parray_free(parray);
    assert_ptr_equal(parray->elements, NULL);
    assert_int_equal(parray->len, 0);
    assert_int_equal(parray->alloc, 0);

    cbfree(parray);

    parray_free(parray2);
    cbfree(parray2);

    cbfree(john);
    cbfree(lyndon);
    cbfree(james);
    cbfree(william);
    cbfree(barack);
}

/* vi: set et ts=4 sw=4: */

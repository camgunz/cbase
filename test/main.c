#include <stdio.h>
#include <setjmp.h>

#include "cbase.h"

#include <cmocka.h>

typedef struct {
    const char *name;
    int age;
} Person;

typedef struct {
    const char *name;
    const char *class;
} Character;

static size_t key_to_hash(const void *key, size_t seed) {
    return hash64(key, strlen((const char *)key), seed);
}

static void* person_to_key(const void *obj) {
    return (void *)((Person *)obj)->name;
}

static void* character_to_key(const void *obj) {
    return (void *)((Character *)obj)->name;
}

static bool key_equal(const void *key1, const void *key2) {
    return key1 == key2;
}

static void test_array(void **state) {
    Array *array;
    Status status;
    Person *person;

    (void)state;

    status_init(&status);

    assert_true(array_new_alloc(&array, sizeof(Person), 3, &status));
    array_free(array);
    cbfree(array);

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

    assert_true(array_shrink(array, &status));
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

    assert_true(array_deep_copy(&stack_array2, &stack_array, &status));
    array_free(&stack_array2);

    assert_true(array_concat_no_clear(array, &stack_array, &status));
    assert_int_equal(array->len, 5);
    assert_int_equal(array->alloc, 5);
    assert_int_equal(stack_array.len, 2);
    assert_int_equal(stack_array.alloc, 3);

    assert_true(array_concat(array, &stack_array, &status));
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

static void test_parray(void **state) {
    PArray *parray;
    PArray *parray2;
    Status status;
    Person *person = NULL;
    Person *john = cbmalloc(sizeof(Person));
    Person *lyndon = cbmalloc(sizeof(Person));
    Person *james = cbmalloc(sizeof(Person));
    Person *william = cbmalloc(sizeof(Person));
    Person *barack = cbmalloc(sizeof(Person));

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
    assert_ptr_equal(person2->name, "Barack");
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

static void test_string(void **state) {
    String *s;
    String *s2;
    SSlice ss;
    Status status;
    ssize_t error;

    (void)state;

    status_init(&status);

    assert_true(string_new(&s, "We are great", &status));
    assert_non_null(s->data);
    assert_int_equal(s->len, 12);
    assert_int_equal(s->byte_len, 12);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 13), 12);
    string_free(s);
    cbfree(s);

    assert_true(string_new_len(&s, "We are great", 12, &status));
    assert_non_null(s->data);
    assert_int_equal(s->len, 12);
    assert_int_equal(s->byte_len, 12);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 13), 12);
    string_free(s);
    cbfree(s);

    assert_true(string_new_full(&s, "We are great", 12, 12, &status));
    assert_non_null(s->data);
    assert_int_equal(s->len, 12);
    assert_int_equal(s->byte_len, 12);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 13), 12);
    assert_true(string_equals_cstr(s, "We are great"));

    assert_true(string_new(&s2, "because we are good", &status));
    assert_non_null(s2->data);
    assert_int_equal(s2->len, 19);
    assert_int_equal(s2->byte_len, 19);
    assert_int_equal(s2->alloc, 20);
    assert_int_equal(strnlen(s2->data, 20), 19);
    assert_true(string_equals_cstr(s2, "because we are good"));

    assert_true(string_slice(s2, 15, 4, &ss, &status));
    assert_int_equal(ss.len, 4);
    assert_int_equal(ss.byte_len, 4);
    assert_true(sslice_equals_cstr(&ss, "good"));

    assert_true(string_assign_slice(s, &ss, &status));
    assert_int_equal(s->len, 4);
    assert_int_equal(s->byte_len, 4);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 5), 4);
    assert_true(string_equals_cstr(s, "good"));

    assert_true(string_slice(s2, 0, s2->len, &ss, &status));
    assert_int_equal(ss.len, 19);
    assert_int_equal(ss.byte_len, 19);
    assert_true(sslice_equals_cstr(&ss, "because we are good"));

    assert_true(string_assign_slice(s, &ss, &status));
    assert_int_equal(s->len, 19);
    assert_int_equal(s->byte_len, 19);
    assert_int_equal(s->alloc, 20);
    assert_int_equal(strnlen(s->data, 20), 19);
    assert_true(string_equals_cstr(s, "because we are good"));

    assert_true(string_assign_slice(s, &ss, &status));
    assert_int_equal(s->len, 19);
    assert_int_equal(s->byte_len, 19);
    assert_int_equal(s->alloc, 20);
    assert_int_equal(strnlen(s->data, 20), 19);
    assert_true(string_equals_cstr(s, "because we are good"));

    assert_true(string_assign(s, "We are great", &status));
    assert_int_equal(s->len, 12);
    assert_int_equal(s->byte_len, 12);
    assert_int_equal(s->alloc, 20);
    assert_int_equal(strnlen(s->data, 13), 12);
    assert_true(string_equals_cstr(s, "We are great"));

    assert_true(string_shrink(s, &status));
    assert_int_equal(s->len, 12);
    assert_int_equal(s->byte_len, 12);
    assert_int_equal(s->alloc, 13);
    assert_int_equal(strnlen(s->data, 13), 12);
    assert_true(string_equals_cstr(s, "We are great"));

    assert_true(string_copy(s2, s, &status));
    assert_int_equal(s2->len, 12);
    assert_int_equal(s2->byte_len, 12);
    assert_int_equal(s2->alloc, 20);
    assert_int_equal(strnlen(s2->data, 13), 12);
    assert_true(string_equals_cstr(s2, "We are great"));

    assert_true(string_slice(s, 0, s->len, &ss, &status));
    assert_int_equal(ss.len, s->len);
    assert_int_equal(ss.byte_len, s->byte_len);
    assert_true(sslice_equals_cstr(&ss, "We are great"));

    assert_true(string_assign(s2, "because we are good", &status));
    assert_int_equal(s2->len, 19);
    assert_int_equal(s2->byte_len, 19);
    assert_int_equal(s2->alloc, 20);
    assert_int_equal(strnlen(s2->data, 20), 19);
    assert_true(string_equals_cstr(s2, "because we are good"));

    assert_true(string_prepend(s2, &ss, &status));
    assert_int_equal(s2->len, 31);
    assert_int_equal(s2->byte_len, 31);
    assert_int_equal(s2->alloc, 32);
    assert_int_equal(strnlen(s2->data, 32), 31);
    assert_true(string_equals_cstr(s2, "We are greatbecause we are good"));

    ss.data = " ";
    ss.len = 1;
    ss.byte_len = 1;

    assert_true(string_insert(s2, 13, &ss, &status));
    assert_int_equal(s2->len, 32);
    assert_int_equal(s2->byte_len, 32);
    assert_int_equal(s2->alloc, 33);
    assert_int_equal(strnlen(s2->data, 33), 32);
    assert_true(string_equals_cstr(s2, "We are great because we are good"));

    assert_true(string_delete(s2, 13, 1, &status));
    assert_int_equal(s2->len, 31);
    assert_int_equal(s2->byte_len, 31);
    assert_int_equal(s2->alloc, 33);
    assert_int_equal(strnlen(s2->data, 32), 31);
    assert_true(string_equals_cstr(s2, "We are greatbecause we are good"));

    assert_true(string_insert_cstr(s2, 13, " ", &status));
    assert_int_equal(s2->len, 32);
    assert_int_equal(s2->byte_len, 32);
    assert_int_equal(s2->alloc, 33);
    assert_int_equal(strnlen(s2->data, 33), 32);
    assert_true(string_equals_cstr(s2, "We are great because we are good"));

    assert_true(string_assign(s2, "because we are good", &status));
    assert_int_equal(s2->len, 19);
    assert_int_equal(s2->byte_len, 19);
    assert_int_equal(s2->alloc, 33);
    assert_int_equal(strnlen(s2->data, 20), 19);
    assert_true(string_equals_cstr(s2, "because we are good"));

    assert_true(string_slice(s2, 0, s2->len, &ss, &status));
    assert_int_equal(ss.len, s2->len);
    assert_int_equal(ss.byte_len, s2->byte_len);
    assert_true(sslice_equals_cstr(&ss, "because we are good"));

    assert_true(string_append_cstr(s, " ", &status));
    assert_int_equal(s->len, 13);
    assert_int_equal(s->byte_len, 13);
    assert_int_equal(s->alloc, 14);
    assert_true(string_equals_cstr(s, "We are great "));

    assert_true(string_append(s, &ss, &status));
    assert_int_equal(s->len, 32);
    assert_int_equal(s->byte_len, 32);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 33), 32);
    assert_true(string_equals_cstr(s, "We are great because we are good"));

    assert_true(string_shift_left(s, 3, &status));
    assert_int_equal(s->len, 29);
    assert_int_equal(s->byte_len, 29);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 30), 29);
    assert_true(string_equals_cstr(s, "are great because we are good"));

    assert_true(string_truncate_fast(s, 1, &error));
    assert_int_equal(s->len, 28);
    assert_int_equal(s->byte_len, 28);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 29), 28);
    assert_true(string_equals_cstr(s, "are great because we are goo"));

    assert_true(string_truncate(s, 11, &status));
    assert_int_equal(s->len, 17);
    assert_int_equal(s->byte_len, 17);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 18), 17);
    assert_true(string_equals_cstr(s, "are great because"));

    assert_true(string_prepend_cstr(s, "We ", &status));
    assert_int_equal(s->len, 20);
    assert_int_equal(s->byte_len, 20);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 21), 20);
    assert_true(string_equals_cstr(s, "We are great because"));

    assert_true(string_append_cstr(s, " we are good", &status));
    assert_int_equal(s->len, 32);
    assert_int_equal(s->byte_len, 32);
    assert_int_equal(s->alloc, 33);
    assert_int_equal(strnlen(s->data, 33), 32);
    assert_true(string_equals_cstr(s, "We are great because we are good"));

    string_clear(s);

    string_free(s);
    cbfree(s);

    string_free(s2);
    cbfree(s2);
}

static void test_sslice(void **state) {
    String *alpha;
    String *hex;
    String *dec;
    String *oct;
    String *bin;
    String *whitespace;
    String *alnum;
    String *s;
    SSlice ss;
    SSlice ss2;
    Status status;
    rune r;

    (void)state;

    status_init(&status);

    assert_true(string_new(&alpha, "1abc", &status));
    assert_true(string_new(&hex, "g0123456789aAbBcCdDeEfF", &status));
    assert_true(string_new(&dec, "a123", &status));
    assert_true(string_new(&oct, "801234567", &status));
    assert_true(string_new(&bin, "201", &status));
    assert_true(string_new(&whitespace, "a \t\r\n", &status));
    assert_true(string_new(&alnum, " 1a", &status));
    assert_true(string_new(&s, "", &status));
    assert_true(string_ensure_capacity(
        s,
        alpha->byte_len +
        hex->byte_len +
        dec->byte_len +
        oct->byte_len +
        bin->byte_len +
        whitespace->byte_len +
        alnum->byte_len +
        6,
        &status
    ));

    assert_true(string_append_str(s, alpha, &status));
    assert_true(string_append_cstr(s, " ", &status));
    assert_true(string_append_str(s, hex, &status));
    assert_true(string_append_cstr(s, " ", &status));
    assert_true(string_append_str(s, dec, &status));
    assert_true(string_append_cstr(s, " ", &status));
    assert_true(string_append_str(s, oct, &status));
    assert_true(string_append_cstr(s, " ", &status));
    assert_true(string_append_str(s, bin, &status));
    assert_true(string_append_cstr(s, " ", &status));
    assert_true(string_append_str(s, whitespace, &status));
    assert_true(string_append_cstr(s, " ", &status));
    assert_true(string_append_str(s, alnum, &status));

    assert_true(string_slice(s, 0, s->len, &ss, &status));
    assert_true(string_slice(s, 34, 3, &ss2, &status));

    assert_int_equal(ss.len, 57);
    assert_int_equal(ss.byte_len, 57);
    assert_true(sslice_starts_with_cstr(&ss, "1abc"));

    assert_true(sslice_get_first_rune(&ss, &r, &status));
    assert_int_equal(r, '1');

    assert_true(sslice_advance_rune(&ss, &status));
    assert_true(sslice_get_first_rune(&ss, &r, &status));
    assert_int_equal(r, 'a');
    assert_int_equal(ss.len, 56);
    assert_int_equal(ss.byte_len, 56);

    assert_true(sslice_advance_runes(&ss, 2, &status));
    assert_true(sslice_get_first_rune(&ss, &r, &status));
    assert_int_equal(r, 'c');
    assert_int_equal(ss.len, 54);
    assert_int_equal(ss.byte_len, 54);

    assert_false(sslice_advance_rune_if_equals(&ss, 'd', &status));
    assert_int_equal(status.code, SSLICE_NOT_EQUAL);
    assert_string_equal(status.domain, "sslice");

    status_init(&status);

    assert_true(sslice_advance_rune_if_equals(&ss, 'c', &status));
    assert_true(sslice_get_first_rune(&ss, &r, &status));
    assert_int_equal(r, ' ');
    assert_int_equal(ss.len, 53);
    assert_int_equal(ss.byte_len, 53);

    assert_true(sslice_pop_rune(&ss, &r, &status));
    assert_int_equal(r, ' ');
    assert_true(sslice_first_rune_equals(&ss, 'g', &status));
    assert_int_equal(ss.len, 52);
    assert_int_equal(ss.byte_len, 52);

    assert_false(sslice_seek_to(&ss, 'q', &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    status_init(&status);

    assert_true(sslice_seek_to(&ss, 'a', &status));
    assert_int_equal(ss.len, 40);
    assert_int_equal(ss.byte_len, 40);

    assert_false(sslice_seek_to_cstr(&ss, "cD", &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    status_init(&status);

    assert_true(sslice_seek_to_cstr(&ss, "Cd", &status));
    assert_int_equal(ss.len, 36);
    assert_int_equal(ss.byte_len, 36);

    assert_true(sslice_get_first_rune(&ss, &r, &status));
    assert_int_equal(r, 'C');

    assert_true(sslice_seek_to_whitespace(&ss, &status));
    assert_true(sslice_first_rune_equals(&ss, ' ', &status));
    assert_int_equal(ss.len, 29);
    assert_int_equal(ss.byte_len, 29);

    assert_true(sslice_seek_past_whitespace(&ss, &status));
    assert_true(sslice_first_rune_equals(&ss, 'a', &status));
    assert_int_equal(ss.len, 28);
    assert_int_equal(ss.byte_len, 28);

    assert_true(sslice_truncate_runes(&ss, 2, &status));
    assert_int_equal(ss.len, 26);
    assert_int_equal(ss.byte_len, 26);
    assert_true(sslice_equals_cstr(&ss, "a123 801234567 201 a \t\r\n  "));

    assert_true(sslice_truncate_whitespace(&ss, &status));
    assert_int_equal(ss.len, 20);
    assert_int_equal(ss.byte_len, 20);
    assert_true(sslice_equals_cstr(&ss, "a123 801234567 201 a"));

    assert_true(sslice_truncate_at(&ss, '2', &status));
    assert_int_equal(ss.len, 16);
    assert_int_equal(ss.byte_len, 16);
    assert_true(sslice_equals_cstr(&ss, "a123 801234567 2"));

    assert_true(sslice_seek_to_subslice(&ss, &ss2, &status));
    assert_int_equal(ss.len, 11);
    assert_int_equal(ss.byte_len, 11);
    assert_true(sslice_equals_cstr(&ss, "801234567 2"));

    assert_true(sslice_advance_rune(&ss2, &status));

    assert_true(sslice_seek_past_subslice(&ss, &ss2, &status));
    assert_int_equal(ss.len, 8);
    assert_int_equal(ss.byte_len, 8);
    assert_true(sslice_equals_cstr(&ss, "234567 2"));

    char *dup = sslice_to_cstr(&ss);
    assert_non_null(dup);
    assert_int_equal(strcmp("234567 2", dup), 0);
    free(dup);

    assert_true(sslice_truncate_runes(&ss, 100, &status));
    assert_int_equal(ss.len, 0);
    assert_int_equal(ss.byte_len, 0);

    assert_true(string_slice(alpha, 0, alpha->len, &ss, &status));

    assert_false(sslice_pop_rune_if_alpha(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_advance_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_alpha(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_slice(hex, 0, hex->len, &ss, &status));

    assert_false(sslice_pop_rune_if_hex_digit(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_advance_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_hex_digit(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_slice(dec, 0, dec->len, &ss, &status));

    assert_false(sslice_pop_rune_if_digit(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_advance_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_digit(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_slice(oct, 0, oct->len, &ss, &status));

    assert_false(sslice_pop_rune_if_oct_digit(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_advance_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_oct_digit(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_slice(bin, 0, bin->len, &ss, &status));

    assert_false(sslice_pop_rune_if_bin_digit(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_advance_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_bin_digit(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_slice(whitespace, 0, whitespace->len, &ss, &status));

    assert_false(sslice_pop_rune_if_whitespace(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_advance_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_whitespace(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    assert_true(string_slice(alnum, 0, alnum->len, &ss, &status));

    assert_false(sslice_pop_rune_if_alnum(&ss, &r, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.domain, "base");

    assert_true(sslice_advance_rune(&ss, &status));
    while (ss.len) {
        size_t len = ss.len;

        assert_true(sslice_pop_rune_if_alnum(&ss, &r, &status));
        assert_int_equal(ss.len, len - 1);
    }

    string_free(alpha);
    cbfree(alpha);
    string_free(hex);
    cbfree(hex);
    string_free(dec);
    cbfree(dec);
    string_free(oct);
    cbfree(oct);
    string_free(bin);
    cbfree(bin);
    string_free(whitespace);
    cbfree(whitespace);
    string_free(alnum);
    cbfree(alnum);
    string_free(s);
    cbfree(s);
}

static void test_table(void **state) {
    Table table;
    Status status;

    (void)state;

    status_init(&status);

    assert_true(table_init(
        &table, key_to_hash, person_to_key, key_equal, 0, &status
    ));

    Person john;
    Person lyndon;
    Person james;
    Person william;
    Person barack;
    Person *person;

    john.name = "John";
    john.age = 43;

    lyndon.name = "Lyndon";
    lyndon.age = 55;

    james.name = "James";
    james.age = 53;

    william.name = "William";
    william.age = 47;

    barack.name = "Barack";
    barack.age = 46;

    assert_true(table_insert(&table, &john, &status));
    assert_true(table_insert(&table, &lyndon, &status));
    assert_true(table_insert(&table, &james, &status));
    assert_true(table_insert(&table, &william, &status));
    assert_true(table_insert(&table, &barack, &status));
    assert_int_equal(table.len, 5);

    assert_true(table_insert(&table, &barack, &status));
    assert_int_equal(table.len, 6);

    assert_true(table_lookup(&table, "John", (void **)&person, &status));
    assert_string_equal(person->name, "John");
    assert_int_equal(person->age, 43);

    assert_true(table_lookup(&table, "Lyndon", (void **)&person, &status));
    assert_string_equal(person->name, "Lyndon");
    assert_int_equal(person->age, 55);

    assert_true(table_lookup(&table, "James", (void **)&person, &status));
    assert_string_equal(person->name, "James");
    assert_int_equal(person->age, 53);

    assert_true(table_lookup(&table, "William", (void **)&person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);

    assert_true(table_lookup(&table, "Barack", (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);

    assert_true(table_remove(&table, "William", (void **)&person, &status));
    assert_string_equal(person->name, "William");
    assert_int_equal(person->age, 47);
    assert_int_equal(table.len, 5);

    assert_true(table_remove(&table, "Barack", (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);
    assert_int_equal(table.len, 4);

    assert_true(table_remove(&table, "Barack", (void **)&person, &status));
    assert_string_equal(person->name, "Barack");
    assert_int_equal(person->age, 46);
    assert_int_equal(table.len, 3);

    table_free(&table);
    assert_ptr_equal(table.buckets.elements, NULL);
    assert_int_equal(table.buckets.len, 0);
    assert_int_equal(table.buckets.alloc, 0);
    assert_int_equal(table.bucket_bit, 0);
    assert_int_equal(table.bucket_max, 0);
    assert_int_equal(table.bucket_mask, 0);
    assert_int_equal(table.len, 0);

    assert_true(table_init(
        &table, key_to_hash, character_to_key, key_equal, 0, &status
    ));

    Character banon = {"Banon", "Oracle"};
    Character celes = {"Celes Chere", "Rune Knight"};
    Character cyan = {"Cyan Garamonde", "Samurai"};
    Character edgar = {"Edgar Figaro", "Machinist"};
    Character gau = {"Gau", "Feral Youth"};
    Character ghost = {"Ghost", "Ghost"};
    Character gogo = {"Gogo", "Mime"};
    Character leo = {"Leo Cristophe", "General"};
    Character locke = {"Locke Cole", "Adventurer"};
    Character mog = {"Mog", "Moogle"};
    Character relm = {"Relm Arrowny", "Pictomancer"};
    Character sabin = {"Sabin Figaro", "Monk"};
    Character setzer = {"Setzer Gabbiani", "Gambler"};
    Character shadow = {"Shadow", "Assassin"};
    Character strago = {"Strago Magus", "Blue Mage"};
    Character terra = {"Terra Branford", "Magitek Elite"};
    Character umaro = {"Umaro", "Berserker"};
    Character *cha = NULL;

    assert_true(table_insert(&table, (void **)&banon, &status));
    assert_true(table_insert(&table, (void **)&celes, &status));
    assert_true(table_insert(&table, (void **)&cyan, &status));
    assert_true(table_insert(&table, (void **)&edgar, &status));
    assert_true(table_insert(&table, (void **)&gau, &status));
    assert_true(table_insert(&table, (void **)&ghost, &status));
    assert_true(table_insert(&table, (void **)&gogo, &status));
    assert_true(table_insert(&table, (void **)&leo, &status));
    assert_true(table_insert(&table, (void **)&locke, &status));
    assert_true(table_insert(&table, (void **)&mog, &status));
    assert_true(table_insert(&table, (void **)&relm, &status));
    assert_true(table_insert(&table, (void **)&sabin, &status));
    assert_true(table_insert(&table, (void **)&setzer, &status));
    assert_true(table_insert(&table, (void **)&shadow, &status));
    assert_int_equal(table.len, 14);

    assert_true(table_insert(&table, (void **)&strago, &status));

    assert_int_equal(table.len, 15);
    assert_int_equal(table.bucket_bit, 5);
    assert_int_equal(table.bucket_max, 32);
    assert_int_equal(table.bucket_mask, 0x1F);

    assert_true(table_insert(&table, (void **)&terra, &status));
    assert_true(table_insert(&table, (void **)&umaro, &status));
    assert_true(table_insert(&table, (void **)&umaro, &status));
    assert_true(table_insert(&table, (void **)&umaro, &status));
    assert_int_equal(table.len, 19);

    size_t i;
    size_t count = 0;
    cha = NULL;

    while ((cha = table_iterate(&table, &i, cha))) {
        count++;
    }

    cha = NULL;

    assert_int_equal(count, table.len);

    assert_true(table_remove(&table, (void *)umaro.name, NULL, &status));
    assert_int_equal(table.len, 18);

    assert_true(table_remove(&table, (void *)umaro.name, NULL, &status));
    assert_int_equal(table.len, 17);

    assert_true(table_remove(&table, (void *)gogo.name, NULL, &status));
    assert_true(table_remove(&table, (void *)leo.name, NULL, &status));
    assert_true(table_remove(&table, (void *)locke.name, NULL, &status));
    assert_true(table_remove(&table, (void *)mog.name, NULL, &status));
    assert_true(table_remove(&table, (void *)relm.name, NULL, &status));
    assert_true(table_remove(&table, (void *)sabin.name, NULL, &status));
    assert_true(table_remove(&table, (void *)setzer.name, NULL, &status));
    assert_true(table_remove(&table, (void *)shadow.name, NULL, &status));
    assert_true(table_remove(&table, (void *)strago.name, NULL, &status));
    assert_true(table_remove(&table, (void *)terra.name, NULL, &status));

    assert_int_equal(table.len, 7);

    assert_true(table_remove(&table, (void *)umaro.name, NULL, &status));

    assert_int_equal(table.len, 6);
    assert_int_equal(table.bucket_bit, 4);
    assert_int_equal(table.bucket_max, 16);
    assert_int_equal(table.bucket_mask, 0xF);

    assert_false(table_remove(&table, (void *)strago.name, NULL, &status));
    assert_int_equal(status.code, ERROR_NOT_FOUND);
    assert_string_equal(status.message, "search term not found");

    status_clear(&status);

    assert_true(table_remove(&table, (void *)banon.name, (void **)&cha, &status));

    assert_non_null(cha);
    assert_string_equal(cha->name, "Banon");
    assert_string_equal(cha->class, "Oracle");

    assert_true(table_remove(&table, (void *)celes.name, NULL, &status));
    assert_true(table_remove(&table, (void *)cyan.name, NULL, &status));
    assert_true(table_remove(&table, (void *)edgar.name, NULL, &status));
    assert_true(table_remove(&table, (void *)gau.name, NULL, &status));
    assert_true(table_remove(&table, (void *)ghost.name, NULL, &status));

    table_free(&table);

    assert_null(table.key_to_hash);
    assert_null(table.obj_to_key);
    assert_null(table.key_equal);
    assert_int_equal(table.seed, 0);
    assert_int_equal(table.bucket_bit, 0);
    assert_int_equal(table.bucket_max, 0);
    assert_int_equal(table.bucket_mask, 0);
    assert_int_equal(table.len, 0);
}

static void test_utf8(void **state) {
    const char *s = "年暮れぬ\n笠きて草鞋\nはきながら";
    char *cursor = NULL;
    char *start = NULL;
    char *end = NULL;
    Status status;

    (void)state;

    assert_true(utf8_index(s, 6, &cursor, &status));
    assert_int_equal(strcmp(cursor, "笠きて草鞋\nはきながら"), 0);

    assert_true(utf8_slice(s, 5, 5, &start, &end, &status));
    assert_int_equal(end - start, 15);
    assert_int_equal(strncmp(start, "笠きて草鞋", end - start), 0);
}

static void test_list(void **state) {
    List *list = NULL;
    Person john;
    Person lyndon;
    Person james;
    Person william;
    Person barack;
    Person *person;

    Status status;

    (void)state;

    status_init(&status);

    john.name = "John";
    john.age = 43;

    lyndon.name = "Lyndon";
    lyndon.age = 55;

    james.name = "James";
    james.age = 53;

    william.name = "William";
    william.age = 47;

    barack.name = "Barack";
    barack.age = 46;

    assert_true(list_new_alloc(&list, 10, &status));

    assert_true(list_push(list, &john, &status));
    assert_true(list_push(list, &lyndon, &status));
    assert_true(list_push(list, &james, &status));
    assert_true(list_push(list, &william, &status));
    assert_true(list_push(list, &barack, &status));

    list_free(list);
    free(list);
}

static void test_alloc(void **state) {
    const char *s = "Hillary Clinton";
    char *s2 = __cbstrdup(s);

    (void)state;

    assert_string_equal(s, s2);

    free(s2);
}

int main(void) {
    int failed_test_count = 0;

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_alloc),
        cmocka_unit_test(test_array),
        cmocka_unit_test(test_list),
        cmocka_unit_test(test_parray),
        cmocka_unit_test(test_sslice),
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

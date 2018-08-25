#pragma once

#ifndef ARRAY_H__
#define ARRAY_H__

enum {
    ARRAY_ELEMENT_SIZE_MISMATCH = 1,
};

typedef struct ArrayStruct {
    size_t len;
    size_t alloc;
    size_t element_size;
    void *elements;
} Array;

bool array_ensure_capacity(Array *array, size_t len, Status *status);

bool array_ensure_capacity_zero(Array *array, size_t len, Status *status);

bool array_set_size(Array *array, size_t len, Status *status);

bool array_compact(Array *array, Status *status);

void array_init(Array *array, size_t element_size);

bool array_init_alloc(Array *array, size_t element_count, size_t element_size,
                                                          Status *status);

bool array_init_alloc_zero(Array *array, size_t element_count,
                                         size_t element_size,
                                         Status *status);

bool array_new(Array **array, size_t element_size, Status *status);

bool array_new_alloc(Array **array, size_t element_count, size_t element_size,
                                                          Status *status);

bool array_new_alloc_zero(Array **array, size_t element_count,
                                         size_t element_size,
                                         Status *status);

void* array_index_fast(Array *array, size_t index);

bool  array_index(Array *array, size_t index, void **element, Status *status);

void* array_insert_fast(Array *array, size_t index);

bool  array_insert(Array *array, size_t index, void **new_element,
                                               Status *status);

bool  array_insert_no_zero(Array *array, size_t index, void **new_element,
                                                       Status *status);

void  array_insert_many_fast(Array *array, size_t index, const void *elements,
                                                         size_t element_count);

bool  array_insert_many(Array *array, size_t index, const void *elements,
                                                    size_t element_count,
                                                    Status *status);

void  array_shift_elements_down_fast_no_zero(Array *array,
                                             size_t index,
                                             size_t element_count);

void  array_shift_elements_down_fast(Array *array, size_t index,
                                                   size_t element_count);

bool  array_shift_elements_down_no_zero(Array *array, size_t index,
                                                      size_t element_count,
                                                      Status *status);

bool  array_shift_elements_down(Array *array, size_t index,
                                              size_t element_count,
                                              Status *status);

void  array_insert_array_same_fast(Array *dst, size_t index, Array *src);

bool  array_insert_array_same(Array *dst, size_t index, Array *src,
                                                        Status *status);

bool  array_insert_array_fast(Array *dst, size_t index, Array *src,
                                                        Status *status);

bool  array_insert_array(Array *dst, size_t index, Array *src, Status *status);

void* array_prepend_fast(Array *array);

bool  array_prepend(Array *array, void **element, Status *status);

bool  array_prepend_no_zero(Array *array, void **element, Status *status);

bool  array_prepend_many(Array *array, const void *elements,
                                       size_t element_count,
                                       Status *status);

void  array_prepend_many_fast(Array *array, const void *elements,
                                            size_t element_count);

void  array_prepend_array_same_fast(Array *dst, Array *src);

bool  array_prepend_array_same(Array *dst, Array *src, Status *status);

bool  array_prepend_array_fast(Array *dst, Array *src, Status *status);

bool  array_prepend_array(Array *dst, Array *src, Status *status);

void* array_append_fast(Array *array);

bool  array_append(Array *array, void **element, Status *status);

bool  array_append_no_zero(Array *array, void **element, Status *status);

void  array_append_many_fast(Array *array, const void *elements,
                                           size_t element_count);

bool  array_append_many(Array *array, const void *elements,
                                      size_t element_count,
                                      Status *status);

void  array_append_array_same_fast(Array *dst, Array *src);

bool  array_append_array_same(Array *dst, Array *src, Status *status);

bool  array_append_array_fast(Array *dst, Array *src, Status *status);

bool  array_append_array(Array *dst, Array *src, Status *status);

void  array_overwrite_fast(Array *array, size_t index,
                                         const void *element);

bool  array_overwrite(Array *array, size_t index, const void *element,
                                                  Status *status);

void  array_overwrite_many_fast(Array *array, size_t index,
                                              const void *elements,
                                              size_t element_count);

bool  array_overwrite_many(Array *array, size_t index, const void *elements,
                                                       size_t element_count,
                                                       Status *status);

void  array_overwrite_array_same_fast(Array *dst, size_t index, Array *src);

bool  array_overwrite_array_same(Array *dst, size_t index, Array *src,
                                                           Status *status);

bool  array_overwrite_array_fast(Array *dst, size_t index, Array *src,
                                                           Status *status);

bool  array_overwrite_array(Array *dst, size_t index, Array *src,
                                                      Status *status);

void  array_zero_elements_fast(Array *array, size_t index, size_t count);

bool  array_zero_elements(Array *array, size_t index, size_t count,
                                                      Status *status);

void  array_zero_element_fast(Array *array, size_t index);

bool  array_zero_element(Array *array, size_t index, Status *status);

void  array_truncate_fast(Array *array, size_t len);

bool  array_truncate(Array *array, size_t len, Status *status);

bool  array_truncate_no_zero(Array *array, size_t len, Status *status);

void  array_assign_fast(Array *array, const void *elements,
                                     size_t element_count);

bool  array_assign(Array *array, const void *elements, size_t element_count,
                                                       Status *status);

void  array_assign_array_same_fast(Array *dst, Array *src);

bool  array_assign_array_same(Array *dst, Array *src, Status *status);

bool  array_assign_array_fast(Array *dst, Array *src, Status *status);

bool  array_assign_array(Array *dst, Array *src, Status *status);

void  array_delete_many_fast(Array *array, size_t index, size_t count);

bool  array_delete_many(Array *array, size_t index, size_t count,
                                                    Status *status);

void  array_delete_fast(Array *array, size_t index);

bool  array_delete(Array *array, size_t index, Status *status);

void  array_delete_unordered_fast(Array *array, size_t index);

bool  array_delete_unordered(Array *array, size_t index, Status *status);

void  array_copy_element_fast(Array *array, size_t index, void *element);

bool  array_copy_element(Array *array, size_t index, void *element,
                                                     Status *status);

void  array_copy_elements_fast(Array *array, size_t index, size_t count,
                                                           void *elements);

bool  array_copy_elements(Array *array, size_t index, size_t count,
                                                      void *elements,
                                                      Status *status);

void  array_pop_fast(Array *array, size_t index, void *element);

bool  array_pop(Array *array, size_t index, void *element, Status *status);

void  array_pop_unordered_fast(Array *array, size_t index, void *element);

bool  array_pop_unordered(Array *array, size_t index, void *element,
                                                      Status *status);

void  array_pop_left_fast(Array *array, void *element);

bool  array_pop_left(Array *array, void *element, Status *status);

void  array_pop_left_unordered_fast(Array *array, void *element);

bool  array_pop_left_unordered(Array *array, void *element, Status *status);

void  array_pop_right_fast(Array *array, void *element);

bool  array_pop_right(Array *array, void *element, Status *status);

void  array_pop_right_unordered_fast(Array *array, void *element);

bool  array_pop_right_unordered(Array *array, void *element, Status *status);

void  array_clear_no_zero(Array *array);

void  array_clear(Array *array);

void  array_free(Array *array);

#endif

/* vi: set et ts=4 sw=4: */

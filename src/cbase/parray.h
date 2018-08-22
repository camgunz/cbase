#pragma once

#ifndef PARRAY_H__
#define PARRAY_H__

typedef struct PArrayStruct {
    Array array;
} PArray;

bool parray_ensure_capacity(PArray *parray, size_t len, Status *status);

bool parray_set_size(PArray *parray, size_t len, Status *status);

bool parray_compact(PArray *parray, Status *status);

void parray_init(PArray *parray);

bool parray_init_alloc(PArray *parray, size_t alloc, Status *status);

bool parray_new(PArray **parray, Status *status);

bool parray_new_alloc(PArray **parray, size_t alloc, Status *status);

void* parray_index_fast(PArray *parray, size_t index);

bool parray_index(PArray *parray, size_t index, void **element,
                                                Status *status);

void parray_insert_fast(PArray *parray, size_t index, void *element);

bool parray_insert(PArray *parray, size_t index, void *element,
                                                 Status *status);

void parray_insert_many_fast(PArray *parray, size_t index,
                                             void **elements,
                                             size_t element_count);

bool parray_insert_many(PArray *parray, size_t index, void **elements,
                                                      size_t element_count,
                                                      Status *status);

void parray_shift_elements_down_fast(PArray *parray, size_t index,
                                                     size_t element_count);

void parray_shift_elements_down_fast_no_zero(PArray *parray,
                                             size_t index,
                                             size_t element_count);

bool parray_shift_elements_down(PArray *parray, size_t index,
                                                size_t element_count,
                                                Status *status);

bool parray_shift_elements_down_no_zero(PArray *parray, size_t index,
                                                        size_t element_count,
                                                        Status *status);

void parray_insert_parray_fast(PArray *dst, size_t index, PArray *src);

bool parray_insert_parray(PArray *dst, size_t index, PArray *src,
                                                     Status *status);

void parray_prepend_fast(PArray *parray, void *element);

bool parray_prepend(PArray *parray, void *element, Status *status);

void parray_prepend_many_fast(PArray *parray, void **elements,
                                              size_t element_count);

bool parray_prepend_many(PArray *parray, void **elements, size_t element_count,
                                                          Status *status);

void parray_prepend_parray_fast(PArray *dst, PArray *src);

bool parray_prepend_parray(PArray *dst, PArray *src, Status *status);

void parray_append_fast(PArray *parray, void *element);

bool parray_append(PArray *parray, void *element, Status *status);

void parray_append_many_fast(PArray *parray, void **elements,
                                             size_t element_count);

bool parray_append_many(PArray *parray, void **elements, size_t element_count,
                                                         Status *status);

void parray_append_parray_fast(PArray *dst, PArray *src);

bool parray_append_parray(PArray *dst, PArray *src, Status *status);

void parray_overwrite_fast(PArray *parray, size_t index, void *element);

bool parray_overwrite(PArray *parray, size_t index, void *element,
                                                    Status *status);

void parray_overwrite_many_fast(PArray *parray, size_t index,
                                                void **elements,
                                                size_t element_count);

bool parray_overwrite_many(PArray *parray, size_t index, void **elements,
                                                         size_t element_count,
                                                         Status *status);

void parray_overwrite_parray_fast(PArray *dst, size_t index, PArray *src);

bool parray_overwrite_parray(PArray *dst, size_t index, PArray *src,
                                                        Status *status);

void parray_assign_fast(PArray *parray, void **elements,
                                        size_t element_count);

bool parray_assign(PArray *parray, void **elements, size_t element_count,
                                                    Status *status);

void parray_assign_parray_fast(PArray *dst, PArray *src);

bool parray_assign_parray(PArray *dst, PArray *src, Status *status);

void parray_zero_elements_fast(PArray *parray, size_t index, size_t count);

bool parray_zero_elements(PArray *parray, size_t index, size_t count,
                                                        Status *status);

void parray_zero_element_fast(PArray *parray, size_t index);

bool parray_zero_element(PArray *parray, size_t index, Status *status);

void parray_delete_fast(PArray *parray, size_t index);

bool parray_delete(PArray *parray, size_t index, Status *status);

void parray_delete_unordered_fast(PArray *parray, size_t index);

bool parray_delete_unordered(PArray *parray, size_t index, Status *status);

void parray_delete_leave_null_fast(PArray *parray, size_t index);

bool parray_delete_leave_null(PArray *parray, size_t index, Status *status);

void parray_truncate_fast(PArray *parray, size_t len);

bool parray_truncate(PArray *parray, size_t len, Status *status);

void* parray_pop_fast(PArray *parray, size_t index);

bool parray_pop(PArray *parray, size_t index, void **element, Status *status);

void* parray_pop_unordered_fast(PArray *parray, size_t index);

bool parray_pop_unordered(PArray *parray, size_t index, void **element,
                                                        Status *status);

void parray_pop_left_fast(PArray *parray, void **element);

bool parray_pop_left(PArray *parray, void **element, Status *status);

void* parray_pop_left_unordered_fast(PArray *parray);

bool parray_pop_left_unordered(PArray *parray, void **element,
                                               Status *status);

void* parray_pop_right_fast(PArray *parray);

bool parray_pop_right(PArray *parray, void **element, Status *status);

void* parray_pop_right_unordered_fast(PArray *parray);

bool parray_pop_right_unordered(PArray *parray, void **element,
                                                Status *status);

void parray_pop_leave_null_fast(PArray *parray, size_t index, void **element);

bool parray_pop_leave_null(PArray *parray, size_t index, void **element,
                                                         Status *status);

void parray_clear_no_null(PArray *parray);

void parray_clear(PArray *parray);

void parray_free(PArray *parray);

#endif

/* vi: set et ts=4 sw=4: */

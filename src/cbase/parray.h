#ifndef PARRAY_H__
#define PARRAY_H__

typedef struct {
    Array array;
} PArray;

static inline
bool parray_ensure_capacity(PArray *parray, size_t len, Status *status) {
    return array_ensure_capacity(&parray->array, len, status);
}

static inline
bool parray_set_size(PArray *parray, size_t len, Status *status) {
    return array_set_size(&parray->array, len, status);
}

static inline
bool parray_compact(PArray *parray, Status *status) {
    return array_compact(&parray->array, status);
}

static inline
void parray_init(PArray *parray) {
    return array_init(&parray->array, sizeof(void *));
}

static inline
void parray_init_alloc(PArray *parray, size_t alloc, Status *status) {
    return array_init_alloc(&parray->array, sizeof(void *), alloc, status);
}

static inline
bool parray_new(PArray **parray, Status *status) {
    if (!cbmalloc(1, sizeof(PArray), (void **)parray, status)) {
        return false;
    }

    parray_init(new_parray);

    return status_ok(status);
}

static inline
bool parray_new_alloc(PArray **parray, size_t alloc, Status *status) {
    return (
        parray_new(parray, status) &&
        parray_ensure_capacity(*parray, alloc, status)
    );
}

static inline
void* parray_index_fast(PArray *parray, size_t index) {
    return array_index_fast(&parray->array, index);
}

static inline
bool parray_index(PArray *parray, size_t index, void **element,
                                                Status *status) {
    return array_index(&parray->array, index, element, status);
}

static inline
void parray_insert_fast(PArray *parray, size_t index, void *element) {
    void **element2 = array_insert_fast(&parray->array, index);

    *element2 = element;
}

static inline
bool parray_insert(PArray *parray, size_t index, void *element,
                                                 Status *status) {
    return array_insert(&parray->array, index, &element, status);
}

static inline
void parray_insert_many_fast(PArray *parray, size_t index,
                                             void **elements,
                                             size_t element_count) {
    array_insert_many_fast(&parray->array, index, elements, element_count);
}

static inline
bool parray_insert_many(PArray *parray, size_t index, void **elements,
                                                      size_t element_count,
                                                      Status *status) {
    return array_insert_many(&parray->array, index, elements, element_count,
                                                              status);
}

static inline
void parray_shift_elements_down_fast(PArray *parray, size_t index,
                                                     size_t element_count) {
    array_shift_elements_down_fast(&parray->array, index, element_count);
}

static inline
void parray_shift_elements_down_fast_no_zero(PArray *parray,
                                             size_t index,
                                             size_t element_count) {
    array_shift_elements_down_fast_no_zero(&parray->array, index,
                                                           element_count);
}

static inline
bool parray_shift_elements_down(PArray *parray, size_t index,
                                                size_t element_count,
                                                Status *status) {
    return array_shift_elements_down(&parray->array, index, element_count,
                                                            status);
}

static inline
bool parray_shift_elements_down_no_zero(PArray *parray, size_t index,
                                                        size_t element_count,
                                                        Status *status) {
    return array_shift_elements_down_no_zero(&parray->array, index,
                                                             element_count,
                                                             status);
}

static inline
void parray_insert_parray_fast(PArray *dst, size_t index, PArray *src) {
    array_insert_array_same_fast(&dst->array, index, &src->array);
}

static inline
bool parray_insert_parray(PArray *dst, size_t index, PArray *src,
                                                     Status *status) {
    return array_insert_same_array(&dst->array, index, &src->array, status);
}

static inline
void parray_prepend_fast(PArray *parray, void *element) {
    void **element2 = array_prepend_fast(&parray->array);

    *element2 = element;
}

static inline
bool parray_prepend(PArray *parray, void *element, Status *status) {
    return array_prepend(&parray->array, &element, status);
}

static inline
void parray_prepend_many_fast(PArray *parray, void **elements,
                                              size_t element_count) {
    array_prepend_many_fast(&parray->array, elements, element_count);
}

static inline
bool parray_prepend_many(PArray *parray, void **elements, size_t element_count,
                                                          Status *status) {
    return array_prepend_many(&parray->array, elements, element_count, status);
}

static inline
void parray_prepend_parray_fast(PArray *dst, size_t index, PArray *src) {
    array_prepend_array_same_fast(&dst->array, index, &src->array);
}

static inline
bool parray_prepend_parray(PArray *dst, size_t index, PArray *src,
                                                      Status *status) {
    return array_prepend_same_array(&dst->array, index, &src->array, status);
}

static inline
void parray_append_fast(PArray *parray, void *element) {
    void **element2 = array_append_fast(&parray->array);

    *element2 = element;
}

static inline
bool parray_append(PArray *parray, void *element, Status *status) {
    return array_append(&parray->array, &element, status);
}

static inline
void parray_append_many_fast(PArray *parray, void **elements,
                                             size_t element_count) {
    array_append_many_fast(&parray->array, elements, element_count);
}

static inline
bool parray_append_many(PArray *parray, void **elements, size_t element_count,
                                                         Status *status) {
    return array_append_many(&parray->array, elements, element_count, status);
}

static inline
void parray_append_parray_fast(PArray *dst, size_t index, PArray *src) {
    array_append_array_same_fast(&dst->array, index, &src->array);
}

static inline
bool parray_append_parray(PArray *dst, size_t index, PArray *src,
                                                     Status *status) {
    return array_append_same_array(&dst->array, index, &src->array, status);
}

static inline
void parray_overwrite_fast(PArray *parray, size_t index, void *element) {
    void **element2 = array_overwrite_fast(&parray->array);

    *element2 = element;
}

static inline
bool parray_overwrite(PArray *parray, size_t index, void *element,
                                                    Status *status) {
    return array_overwrite(&parray->array, index, element, status);
}

static inline
void parray_overwrite_many_fast(PArray *parray, size_t index,
                                                void **elements,
                                                size_t element_count) {
    array_overwrite_many_fast(&parray->array, index, elements, element_count);
}

static inline
bool parray_overwrite_many(PArray *parray, size_t index, void **elements,
                                                         size_t element_count,
                                                         Status *status) {
    return array_overwrite_many(&parray->array, index, elements,
                                                       element_count,
                                                       status);
}

static inline
void parray_overwrite_parray_fast(PArray *dst, size_t index, PArray *src) {
    array_overwrite_array_fast(&dst->array, index, &src->array);
}

static inline
bool parray_overwrite_parray(PArray *dst, size_t index, PArray *src,
                                                        Status *status) {
    return array_overwrite_array(&dst->array, index, &src->array, status);
}

static inline
void parray_assign_fast(PArray *parray, void **elements,
                                        size_t element_count) {
    array_assign_fast(&parray->array, elements, element_count);
}

static inline
bool parray_assign(PArray *parray, void **elements, size_t element_count,
                                                    Status *status) {
    return array_assign(&parray->array, elements, element_count, status);
}

static inline
void parray_assign_parray_fast(PArray *dst, PArray *src) {
    array_assign_array_same_fast(&dst->array, &src->array);
}

static inline
bool parray_assign_parray(PArray *dst, PArray *src, Status *status) {
    return array_assign_array_same(&dst->array, &src->array, status);
}

static inline
bool parray_zero_elements_fast(PArray *parray, size_t index, size_t count,
                                                             Status *status) {
    return array_zero_elements_fast(&parray->array, index, count, status);
}

static inline
bool parray_zero_elements(PArray *parray, size_t index, size_t count,
                                                        Status *status) {
    return array_zero_elements(&parray->array, index, count, status);
}

static inline
bool parray_zero_element_fast(PArray *parray, size_t index, size_t count,
                                                            Status *status) {
    return array_zero_element_fast(&parray->array, index, count, status);
}

static inline
bool parray_zero_element(PArray *parray, size_t index, Status *status) {
    return array_zero_element(&parray->array, index, status);
}

static inline
void parray_delete_fast(PArray *parray, size_t index) {
    return array_delete_fast(&parray->array, index);
}

static inline
bool parray_delete(PArray *parray, size_t index, Status *status) {
    return array_delete(&parray->array, index, status);
}

static inline
void parray_delete_unordered_fast(PArray *parray, size_t index) {
    array_delete_unordered_fast(&parray->array, index);
}

static inline
bool parray_delete_unordered(PArray *parray, size_t index, Status *status) {
    return array_delete_unordered(&parray->array, index, status);
}

static inline
void parray_delete_leave_null_fast(PArray *parray, size_t index) {
    void *element = NULL;

    parray_overwrite_fast(parray, index, &element);
}

static inline
bool parray_delete_leave_null(PArray *parray, size_t index, Status *status) {
    if (index >= parray->len) {
        return index_out_of_bounds(status);
    }

    parray_delete_leave_null_fast(parray, index);

    return status_ok(status);
}

static inline
void parray_truncate_fast(PArray *parray, size_t len) {
    array_truncate_fast(&parray->array, len);
}

static inline
bool parray_truncate(PArray *parray, size_t len, Status *status) {
    return array_truncate(&parray->array, len, status);
}

static inline
void* parray_pop_fast(PArray *parray, size_t index) {
    void *element = NULL;
    
    array_pop_fast(&parray->array, index, &element);

    return element;
}

static inline
bool parray_pop(PArray *parray, size_t index, void **element, Status *status) {
    return array_pop(&parray->array, index, element, status);
}

static inline
void* parray_pop_unordered_fast(PArray *parray, size_t index) {
    void *element = NULL;

    array_pop_unordered_fast(&parray->array, index, &element);

    return element;
}

static inline
bool *parray_pop_unordered(PArray *parray, size_t index, void **element,
                                                         Status *status) {
    return array_pop_unordered(&parray->array, index, element, status);
}

static inline
void parray_pop_left_fast(PArray *parray, void **element) {
    array_pop_left_fast(&parray->array, element);
}

static inline
bool parray_pop_left(PArray *parray, void **element, Status *status) {
    return array_pop_left(&parray->array, element, status);
}

static inline
void* parray_pop_left_unordered_fast(PArray *parray) {
    void *element = NULL;

    array_pop_left_unordered_fast(&parray->array, &element);

    return element;
}

static inline
bool parray_pop_left_unordered(PArray *parray, void **element,
                                               Status *status) {
    return array_pop_left_unordered(&parray->array, element, status);
}

static inline
void* parray_pop_right_fast(PArray *parray) {
    void *element = NULL;

    array_pop_right_fast(&parray->array, &element);

    return element;
}

static inline
bool parray_pop_right(PArray *parray, void **element, Status *status) {
    return array_pop_right(&parray->array, element, status);
}

static inline
void* parray_pop_right_unordered_fast(PArray *parray) {
    void *element = NULL;

    array_pop_right_unordered_fast(&parray->array, &element);

    return element;
}

static inline
bool parray_pop_right_unordered(PArray *parray, void **element,
                                                Status *status) {
    return array_pop_right_unordered(&parray->array, element, status);
}

static inline
void parray_pop_leave_null_fast(PArray *parray, size_t index, void **element) {
    *element = parray_index_fast(parray, index);
    parray_delete_leave_null_fast(parray, index);
}

static inline
bool parray_pop_leave_null(PArray *parray, size_t index, void **element,
                                                         Status *status) {
    if (index >= parray->len) {
        return index_out_of_bounds(status);
    }

    parray_pop_leave_null_fast(parray, index, element);

    return status_ok(status);
}

static inline
void parray_clear_no_null(PArray *parray) {
    array_clear_no_zero(&parray->array);
}

static inline
bool parray_clear(PArray *parray, Status *status) {
    return array_clear(&parray->array, status);
}

static inline
void parray_free(PArray *parray) {
    array_free(&parray->array);
}

#endif

/* vi: set et ts=4 sw=4: */

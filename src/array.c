#include "cbase.h"

/* [TODO] Add checks for element_size when running array/array functions */

#define array_element_size_mismatch(status) status_failure( \
    status,                                                 \
    "array",                                                \
    ARRAY_ELEMENT_SIZE_MISMATCH,                            \
    "Array element sizes do not match"                      \
)

bool array_ensure_capacity(Array *array, size_t len, Status *status) {
    if (array->alloc < len) {
        if (!cbrealloc(len, array->element_size, &array->elements, status)) {
            return false;
        }

        array->alloc = len;
    }

    return status_ok(status);
}

bool array_ensure_capacity_zero(Array *array, size_t len, Status *status) {
    if (array->alloc < len) {
        if (!array->elements) {
            if (!cbcalloc(len, array->element_size, &array->elements,
                                                    status)) {
                return false;
            }

        }
        else if (!cbrealloc(len, array->element_size, &array->elements,
                                                      status)) {
            return false;
        }

        array->alloc = len;
    }

    return status_ok(status);
}

bool array_set_size(Array *array, size_t len, Status *status) {
    if (array->alloc < len) {
        return array_ensure_capacity(array, len, status);
    }

    if (array->alloc > len) {
        if (!cbrealloc(len, array->element_size, &array->elements, status)) {
            return false;
        }

        array->alloc = len;
        array->len = array->alloc;
    }

    return status_ok(status);
}

inline
bool array_compact(Array *array, Status *status) {
    return array_set_size(array, array->len, status);
}

inline
void array_init(Array *array, size_t element_size) {
    array->element_size = element_size;
    array->elements = NULL;
    array->len = 0;
    array->alloc = 0;
}

inline
bool array_init_alloc(Array *array, size_t element_count, size_t element_size,
                                                          Status *status) {
    array_init(array, element_size);
    return array_ensure_capacity(array, element_count, status);
}

inline
bool array_init_alloc_zero(Array *array, size_t element_count,
                                         size_t element_size,
                                         Status *status) {
    array_init(array, element_size);
    return array_ensure_capacity_zero(array, element_count, status);
}

inline
bool array_new(Array **array, size_t element_size, Status *status) {
    if (!cbmalloc(1, sizeof(Array), (void **)array, status)) {
        return false;
    }

    array_init(*array, element_size);

    return status_ok(status);
}

inline
bool array_new_alloc(Array **array, size_t element_count, size_t element_size,
                                                          Status *status) {
    return (
        array_new(array, element_size, status) &&
        array_ensure_capacity(*array, element_count, status)
    );
}

inline
bool array_new_alloc_zero(Array **array, size_t element_count,
                                         size_t element_size,
                                         Status *status) {
    return (
        array_new(array, element_size, status) &&
        array_ensure_capacity_zero(*array, element_count, status)
    );
}

inline
void* array_index_fast(Array *array, size_t index) {
    return (void *)(((char *)array->elements) + (array->element_size * index));
}

inline
bool array_index(Array *array, size_t index, void **element, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    *element = array_index_fast(array, index);

    return status_ok(status);
}

inline
void* array_insert_fast(Array *array, size_t index) {
    if (index < array->len) {
        cbbase_memmove(array_index_fast(array, index + 1),
                       array_index_fast(array, index),
                       array->len - index * array->element_size);
    }

    array->len++;

    return array_index_fast(array, index);
}

inline
bool array_insert(Array *array, size_t index, void **new_element,
                                              Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    if (!array_ensure_capacity_zero(array, array->len + 1, status)) {
        return false;
    }

    *new_element = array_insert_fast(array, index);

    return status_ok(status);
}

inline
bool array_insert_no_zero(Array *array, size_t index, void **new_element,
                                                      Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    if (!array_ensure_capacity(array, array->len + 1, status)) {
        return false;
    }

    *new_element = array_insert_fast(array, index);

    return status_ok(status);
}

inline
void array_insert_many_fast(Array *array, size_t index, const void *elements,
                                                        size_t element_count) {
    if (index < array->len) {
        cbbase_memmove(array_index_fast(array, index + element_count),
                       array_index_fast(array, index),
                       array->len - index * array->element_size);
    }

    cbbase_memmove(array_index_fast(array, index),
                   elements,
                   element_count * array->element_size);

    array->len += element_count;
}

inline
bool array_insert_many(Array *array, size_t index, const void *elements,
                                                   size_t element_count,
                                                   Status *status) {
    if (element_count == 0) {
        return status_ok(status);
    }

    if (!array_ensure_capacity(array, array->len + element_count, status)) {
        return false;
    }

    array_insert_many_fast(array, index, elements, element_count);

    return status_ok(status);
}

inline
void array_shift_elements_down_fast_no_zero(Array *array,
                                            size_t index,
                                            size_t element_count) {
    if (index < array->len) {
        cbbase_memmove(array_index_fast(array, index + element_count),
                       array_index_fast(array, index),
                       array->len - index * array->element_size);
    }

    array->len += element_count;
}

inline
void array_shift_elements_down_fast(Array *array, size_t index,
                                                  size_t element_count) {
    array_shift_elements_down_fast_no_zero(array, index, element_count);

    zero_buf_fast(array_index_fast(array, index),
                  element_count * array->element_size);
}

inline
bool array_shift_elements_down_no_zero(Array *array, size_t index,
                                                     size_t element_count,
                                                     Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    if (!array_ensure_capacity(array, array->len + element_count, status)) {
        return false;
    }

    array_shift_elements_down_fast_no_zero(array, index, element_count);

    return status_ok(status);
}

inline
bool array_shift_elements_down(Array *array, size_t index, size_t element_count,
                                                           Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    if (!array_ensure_capacity(array, array->len + element_count, status)) {
        return false;
    }

    array_shift_elements_down_fast(array, index, element_count);

    return status_ok(status);
}

inline
void array_insert_array_same_fast(Array *dst, size_t index, Array *src) {
    array_insert_many_fast(dst, index, src->elements, src->len);
}

inline
bool array_insert_array_same(Array *dst, size_t index, Array *src,
                                                       Status *status) {
    return array_insert_many(dst, index, src->elements, src->len, status);
}

bool array_insert_array_fast(Array *dst, size_t index, Array *src,
                                                       Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    array_insert_array_same_fast(dst, index, src);

    return status_ok(status);
}

bool array_insert_array(Array *dst, size_t index, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_insert_array_same(dst, index, src, status);
}

inline
void* array_prepend_fast(Array *array) {
    return array_insert_fast(array, 0);
}

inline
bool array_prepend(Array *array, void **element, Status *status) {
    return array_insert(array, 0, element, status);
}

inline
bool array_prepend_no_zero(Array *array, void **element, Status *status) {
    return array_insert_no_zero(array, 0, element, status);
}

inline
bool array_prepend_many(Array *array, const void *elements,
                                      size_t element_count,
                                      Status *status) {
    return array_insert_many(array, 0, elements, element_count, status);
}

inline
void array_prepend_many_fast(Array *array, const void *elements,
                                           size_t element_count) {
    array_insert_many_fast(array, 0, elements, element_count);
}

inline
void array_prepend_array_same_fast(Array *dst, Array *src) {
    array_insert_array_same_fast(dst, 0, src);
}

inline
bool array_prepend_array_same(Array *dst, Array *src, Status *status) {
    return array_insert_array_same(dst, 0, src, status);
}

bool array_prepend_array_fast(Array *dst, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    array_prepend_array_same_fast(dst, src);

    return status_ok(status);
}

bool array_prepend_array(Array *dst, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_prepend_array_same(dst, src, status);
}

inline
void* array_append_fast(Array *array) {
    return array_insert_fast(array, array->len);
}

inline
bool array_append(Array *array, void **element, Status *status) {
    return array_insert(array, array->len, element, status);
}

inline
bool array_append_no_zero(Array *array, void **element, Status *status) {
    return array_insert_no_zero(array, array->len, element, status);
}

inline
void array_append_many_fast(Array *array, const void *elements,
                                          size_t element_count) {
    array_insert_many_fast(array, array->len, elements, element_count);
}

inline
bool array_append_many(Array *array, const void *elements,
                                     size_t element_count,
                                     Status *status) {
    return array_insert_many(array, array->len, elements, element_count,
                                                          status);
}

inline
void array_append_array_same_fast(Array *dst, Array *src) {
    array_insert_array_same_fast(dst, dst->len, src);
}

inline
bool array_append_array_same(Array *dst, Array *src, Status *status) {
    return array_insert_array_same(dst, dst->len, src, status);
}

bool array_append_array_fast(Array *dst, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    array_append_array_same_fast(dst, src);

    return status_ok(status);
}

bool array_append_array(Array *dst, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_append_array_same(dst, src, status);
}

inline
void array_overwrite_fast(Array *array, size_t index,
                                        const void *element) {
    cbbase_memmove(array_index_fast(array, index), element,
                                                   array->element_size);
}

inline
bool array_overwrite(Array *array, size_t index, const void *element,
                                                 Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_overwrite_fast(array, index, element);

    return status_ok(status);
}

inline
void array_overwrite_many_fast(Array *array, size_t index,
                                             const void *elements,
                                             size_t element_count) {
    cbbase_memmove(array_index_fast(array, index),
                   elements,
                   element_count * array->element_size);
}

inline
bool array_overwrite_many(Array *array, size_t index, const void *elements,
                                                      size_t element_count,
                                                      Status *status) {
    if (!array_ensure_capacity(array, index + element_count, status)) {
        return false;
    }

    array_overwrite_many_fast(array, index, elements, element_count);

    return status_ok(status);
}

inline
void array_overwrite_array_same_fast(Array *dst, size_t index, Array *src) {
    array_overwrite_many_fast(dst, index, src->elements, src->len);
}

inline
bool array_overwrite_array_same(Array *dst, size_t index, Array *src,
                                                          Status *status) {
    return array_overwrite_many(dst, index, src->elements, src->len, status);
}

bool array_overwrite_array_fast(Array *dst, size_t index, Array *src,
                                                          Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    array_overwrite_array_same_fast(dst, index, src);

    return status_ok(status);
}

bool array_overwrite_array(Array *dst, size_t index, Array *src,
                                                     Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_overwrite_array_same(dst, index, src, status);
}

inline
void array_zero_elements_fast(Array *array, size_t index, size_t count) {
    zero_buf_fast(array_index_fast(array, index), count * array->element_size);
}

inline
bool array_zero_elements(Array *array, size_t index, size_t count,
                                                     Status *status) {
    if ((index + count) > array->len) {
        return index_out_of_bounds(status);
    }

    return zero_buf(array_index_fast(array, index), count, array->element_size,
                                                           status);
}

inline
void array_zero_element_fast(Array *array, size_t index) {
    array_zero_elements_fast(array, index, 1);
}

inline
bool array_zero_element(Array *array, size_t index, Status *status) {
    return array_zero_elements(array, index, 1, status);
}

inline
void array_truncate_fast(Array *array, size_t len) {
    array->len = len;
}

inline
bool array_truncate(Array *array, size_t len, Status *status) {
    if (len > array->len) {
        return index_out_of_bounds(status);
    }

    if (array->len == len) {
        return status_ok(status);
    }

    if (!array_zero_elements(array, len, array->len - len, status)) {
        return false;
    }

    array_truncate_fast(array, len);

    return status_ok(status);
}

inline
bool array_truncate_no_zero(Array *array, size_t len, Status *status) {
    if (len > array->len) {
        return index_out_of_bounds(status);
    }

    if (array->len != len) {
        return status_ok(status);
    }

    array_truncate_fast(array, len);

    return status_ok(status);
}

inline
void array_assign_fast(Array *array, const void *elements,
                                     size_t element_count) {
    array_overwrite_many_fast(array, 0, elements, element_count);
    array_truncate_fast(array, element_count);
}

inline
bool array_assign(Array *array, const void *elements, size_t element_count,
                                                      Status *status) {
    if (!array_overwrite_many(array, 0, elements, element_count, status)) {
        return false;
    }

    array_truncate_fast(array, element_count);

    return true;
}

inline
void array_assign_array_same_fast(Array *dst, Array *src) {
    array_assign_fast(dst, src->elements, src->len);
}

inline
bool array_assign_array_same(Array *dst, Array *src, Status *status) {
    return (
        array_assign(dst, src->elements, src->len, status) &&
        array_truncate(dst, src->len, status)
    );
}

bool array_assign_array_fast(Array *dst, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    array_assign_array_same_fast(dst, src);

    return status_ok(status);
}

bool array_assign_array(Array *dst, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_assign_array_same(dst, src, status);
}

inline
void array_delete_many_fast(Array *array, size_t index, size_t count) {
    cbbase_memmove(array_index_fast(array, index),
                   array_index_fast(array, index + count),
                   ((array->len - index) - count) * array->element_size);

    array->len -= count;
}

inline
bool array_delete_many(Array *array, size_t index, size_t count,
                                                   Status *status) {
    if ((index + count) > array->len) {
        return index_out_of_bounds(status);
    }

    array_delete_many_fast(array, index, count);

    return status_ok(status);
}

inline
void array_delete_fast(Array *array, size_t index) {
    array_delete_many_fast(array, index, 1);
}

inline
bool array_delete(Array *array, size_t index, Status *status) {
    return array_delete_many(array, index, 1, status);
}

inline
void array_delete_unordered_fast(Array *array, size_t index) {
    if (index < (array->len - 1)) {
        cbbase_memmove(array_index_fast(array, index),
                       array_index_fast(array, array->len - 1),
                       array->element_size);
    }

    array->len--;
}

inline
bool array_delete_unordered(Array *array, size_t index, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_delete_unordered_fast(array, index);

    return status_ok(status);
}

inline
void array_copy_element_fast(Array *array, size_t index, void *element) {
    cbbase_memmove(element, array_index_fast(array, index),
                            array->element_size);
}

inline
bool array_copy_element(Array *array, size_t index, void *element,
                                                    Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_copy_element_fast(array, index, element);

    return status_ok(status);
}

inline
void array_copy_elements_fast(Array *array, size_t index, size_t count,
                                                          void *elements) {
    cbbase_memmove(elements, array_index_fast(array, index),
                             count * array->element_size);
}

inline
bool array_copy_elements(Array *array, size_t index, size_t count,
                                                     void *elements,
                                                     Status *status) {
    if ((index + count) > array->len) {
        return index_out_of_bounds(status);
    }

    if (count == 0) {
        return status_ok(status);
    }

    return cbmemmove(elements, array_index_fast(array, index),
                               count,
                               array->element_size,
                               status);
}

inline
void array_pop_fast(Array *array, size_t index, void *element) {
    array_copy_element_fast(array, index, element);
    array_delete_fast(array, index);
}

inline
bool array_pop(Array *array, size_t index, void *element, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_pop_fast(array, index, element);

    return status_ok(status);
}

inline
void array_pop_unordered_fast(Array *array, size_t index, void *element) {
    array_copy_element_fast(array, index, element);
    array_delete_unordered_fast(array, index);
}

inline
bool array_pop_unordered(Array *array, size_t index, void *element,
                                                     Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_pop_unordered_fast(array, index, element);

    return status_ok(status);
}

inline
void array_pop_left_fast(Array *array, void *element) {
    array_pop_fast(array, 0, element);
}

inline
bool array_pop_left(Array *array, void *element, Status *status) {
    return array_pop(array, 0, element, status);
}

inline
void array_pop_left_unordered_fast(Array *array, void *element) {
    array_pop_unordered_fast(array, 0, element);
}

inline
bool array_pop_left_unordered(Array *array, void *element, Status *status) {
    return array_pop_unordered(array, 0, element, status);
}

inline
void array_pop_right_fast(Array *array, void *element) {
    array_pop_fast(array, array->len - 1, element);
}

inline
bool array_pop_right(Array *array, void *element, Status *status) {
    return array_pop(array, array->len - 1, element, status);
}

inline
void array_pop_right_unordered_fast(Array *array, void *element) {
    array_pop_unordered_fast(array, array->len - 1, element);
}

inline
bool array_pop_right_unordered(Array *array, void *element, Status *status) {
    return array_pop_unordered(array, array->len - 1, element, status);
}

inline
void array_clear_no_zero(Array *array) {
    array->len = 0;
}

inline
void array_clear(Array *array) {
    array_zero_elements_fast(array, 0, array->len);
    array_clear_no_zero(array);
}

inline
void array_free(Array *array) {
    cbfree(array->elements);
    array_init(array, array->element_size);
}

/* vi: set et ts=4 sw=4: */

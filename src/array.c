#include "cbase.h"

#define array_element_size_mismatch(status) status_failure( \
    status,                                                 \
    "array",                                                \
    ARRAY_ELEMENT_SIZE_MISMATCH,                            \
    "Array element sizes do not match"                      \
)

bool array_ensure_capacity(Array *array, size_t len, Status *status) {
    if (array->alloc < len) {
        if (!cbrealloc(len, array->element_size, &array->elements, status)) {
            return status_propagate(status);
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
                return status_propagate(status);
            }

        }
        else if (!cbrealloc(len, array->element_size, &array->elements,
                                                      status)) {
            return status_propagate(status);
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
            return status_propagate(status);
        }

        array->alloc = len;
        array->len = array->alloc;
    }

    return status_ok(status);
}

bool array_compact(Array *array, Status *status) {
    return array_set_size(array, array->len, status);
}

void array_init(Array *array, size_t element_size) {
    array->element_size = element_size;
    array->elements = NULL;
    array->len = 0;
    array->alloc = 0;
}

bool array_init_alloc(Array *array, size_t element_count, size_t element_size,
                                                          Status *status) {
    array_init(array, element_size);
    return array_ensure_capacity(array, element_count, status);
}

bool array_init_alloc_zero(Array *array, size_t element_count,
                                         size_t element_size,
                                         Status *status) {
    array_init(array, element_size);
    return array_ensure_capacity_zero(array, element_count, status);
}

bool array_new(Array **array, size_t element_size, Status *status) {
    if (!cbmalloc(1, sizeof(Array), array, status)) {
        return status_propagate(status);
    }

    array_init(*array, element_size);

    return status_ok(status);
}

bool array_new_alloc(Array **array, size_t element_count, size_t element_size,
                                                          Status *status) {
    return (
        array_new(array, element_size, status) &&
        array_ensure_capacity(*array, element_count, status)
    );
}

bool array_new_alloc_zero(Array **array, size_t element_count,
                                         size_t element_size,
                                         Status *status) {
    return (
        array_new(array, element_size, status) &&
        array_ensure_capacity_zero(*array, element_count, status)
    );
}

void* array_index_fast(Array *array, size_t index) {
    return (void *)(((char *)array->elements) + (array->element_size * index));
}

bool _array_index(Array *array, size_t index, void **element, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    *element = array_index_fast(array, index);

    return status_ok(status);
}

void array_set_fast(Array *array, size_t index, void *element) {
    void *new_slot = array_index_fast(array, index);

    cbbase_memmove(new_slot, element, array->element_size);
}

bool array_set(Array *array, size_t index, void *element, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_set_fast(array, index, element);

    return status_ok(status);
}

bool array_insert(Array *array, size_t index, void *element, Status *status) {
    if (index > array->len) {
        return index_out_of_bounds(status);
    }

    if (!array_shift_elements_down_no_zero(array, index, 1, status)) {
        return status_propagate(status);
    }

    array_set_fast(array, index, element);

    return status_ok(status);
}

void* array_insert_slot_fast(Array *array, size_t index) {
    array_shift_elements_down_fast_no_zero(array, index, 1);
    return array_index_fast(array, index);
}

bool _array_insert_slot(Array *array, size_t index, void **new_slot,
                                                    Status *status) {
    if (index > array->len) {
        return index_out_of_bounds(status);
    }

    if (!array_ensure_capacity_zero(array, array->len + 1, status)) {
        return status_propagate(status);
    }

    *new_slot = array_insert_slot_fast(array, index);

    return status_ok(status);
}

bool _array_insert_slot_no_zero(Array *array, size_t index, void **new_slot,
                                                            Status *status) {
    if (index > array->len) {
        return index_out_of_bounds(status);
    }

    if (!array_ensure_capacity(array, array->len + 1, status)) {
        return status_propagate(status);
    }

    *new_slot = array_insert_slot_fast(array, index);

    return status_ok(status);
}

void array_insert_many_fast(Array *array, size_t index, const void *elements,
                                                        size_t element_count) {
    array_shift_elements_down_fast_no_zero(array, index, element_count);

    cbbase_memmove(array_index_fast(array, index),
                   elements,
                   element_count * array->element_size);
}

bool array_insert_many(Array *array, size_t index, const void *elements,
                                                   size_t element_count,
                                                   Status *status) {
    if (element_count == 0) {
        return status_ok(status);
    }

    if (!array_ensure_capacity(array, array->len + element_count, status)) {
        return status_propagate(status);
    }

    array_insert_many_fast(array, index, elements, element_count);

    return status_ok(status);
}

void array_shift_elements_down_fast_no_zero(Array *array,
                                            size_t index,
                                            size_t element_count) {
    cbbase_memmove(array_index_fast(array, index + element_count),
                   array_index_fast(array, index),
                   (array->len - index) * array->element_size);

    array->len += element_count;
}

void array_shift_elements_down_fast(Array *array, size_t index,
                                                  size_t element_count) {
    array_shift_elements_down_fast_no_zero(array, index, element_count);

    zero_buf_fast(array_index_fast(array, index),
                  element_count * array->element_size);
}

bool array_shift_elements_down_no_zero(Array *array, size_t index,
                                                     size_t element_count,
                                                     Status *status) {
    bool has_existing_elements = array->len > 0;

    if (index > array->len) {
        return index_out_of_bounds(status);
    }

    if (!array_ensure_capacity(array, array->len + element_count, status)) {
        return status_propagate(status);
    }

    if (has_existing_elements) {
        array_shift_elements_down_fast_no_zero(array, index, element_count);
    }
    else {
        array->len += element_count;
    }

    return status_ok(status);
}

bool array_shift_elements_down(Array *array, size_t index, size_t element_count,
                                                           Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    if (!array_ensure_capacity(array, array->len + element_count, status)) {
        return status_propagate(status);
    }

    array_shift_elements_down_fast(array, index, element_count);

    return status_ok(status);
}

void array_insert_array_same_fast(Array *dst, size_t index, Array *src) {
    array_insert_many_fast(dst, index, src->elements, src->len);
}

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

void array_prepend_fast(Array *array, void *element) {
    array_set_fast(array, 0, element);
    array->len++;
}

bool array_prepend(Array *array, void *element, Status *status) {
    return array_insert(array, 0, element, status);
}

void* array_prepend_slot_fast(Array *array) {
    return array_insert_slot_fast(array, 0);
}

bool _array_prepend_slot(Array *array, void **new_slot, Status *status) {
    return array_insert_slot(array, 0, new_slot, status);
}

bool _array_prepend_slot_no_zero(Array *array, void **new_slot,
                                               Status *status) {
    return array_insert_slot_no_zero(array, 0, new_slot, status);
}

bool array_prepend_many(Array *array, const void *elements,
                                      size_t element_count,
                                      Status *status) {
    return array_insert_many(array, 0, elements, element_count, status);
}

void array_prepend_many_fast(Array *array, const void *elements,
                                           size_t element_count) {
    array_insert_many_fast(array, 0, elements, element_count);
}

void array_prepend_array_same_fast(Array *dst, Array *src) {
    array_insert_array_same_fast(dst, 0, src);
}

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

void array_append_fast(Array *array, void *element) {
    array_set_fast(array, array->len, element);
    array->len++;
}

bool array_append(Array *array, void *element, Status *status) {
    return array_insert(array, array->len, element, status);
}

void* array_append_slot_fast(Array *array) {
    return array_insert_slot_fast(array, array->len);
}

bool _array_append_slot(Array *array, void **new_slot, Status *status) {
    return array_insert_slot(array, array->len, new_slot, status);
}

bool _array_append_slot_no_zero(Array *array, void **new_slot,
                                              Status *status) {
    return array_insert_slot_no_zero(array, array->len, new_slot, status);
}

void array_append_many_fast(Array *array, const void *elements,
                                          size_t element_count) {
    array_insert_many_fast(array, array->len, elements, element_count);
}

bool array_append_many(Array *array, const void *elements,
                                     size_t element_count,
                                     Status *status) {
    return array_insert_many(
        array, array->len, elements, element_count, status
    );
}

void array_append_array_same_fast(Array *dst, Array *src) {
    array_insert_array_same_fast(dst, dst->len, src);
}

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

void array_overwrite_fast(Array *array, size_t index,
                                        const void *element) {
    cbbase_memmove(array_index_fast(array, index), element,
                                                   array->element_size);
}

bool array_overwrite(Array *array, size_t index, const void *element,
                                                 Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_overwrite_fast(array, index, element);

    return status_ok(status);
}

void array_overwrite_many_fast(Array *array, size_t index,
                                             const void *elements,
                                             size_t element_count) {
    cbbase_memmove(array_index_fast(array, index),
                   elements,
                   element_count * array->element_size);
}

bool array_overwrite_many(Array *array, size_t index, const void *elements,
                                                      size_t element_count,
                                                      Status *status) {
    if (!array_ensure_capacity(array, index + element_count, status)) {
        return status_propagate(status);
    }

    array_overwrite_many_fast(array, index, elements, element_count);

    return status_ok(status);
}

void array_overwrite_array_same_fast(Array *dst, size_t index, Array *src) {
    array_overwrite_many_fast(dst, index, src->elements, src->len);
}

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

void array_zero_elements_fast(Array *array, size_t index, size_t count) {
    zero_buf_fast(array_index_fast(array, index), count * array->element_size);
}

bool array_zero_elements(Array *array, size_t index, size_t count,
                                                     Status *status) {
    if ((index + count) > array->len) {
        return index_out_of_bounds(status);
    }

    return zero_buf(array_index_fast(array, index), count, array->element_size,
                                                           status);
}

void array_zero_element_fast(Array *array, size_t index) {
    array_zero_elements_fast(array, index, 1);
}

bool array_zero_element(Array *array, size_t index, Status *status) {
    return array_zero_elements(array, index, 1, status);
}

void array_truncate_fast(Array *array, size_t len) {
    array->len = len;
}

bool array_truncate_no_zero(Array *array, size_t len, Status *status) {
    if (len > array->len) {
        return index_out_of_bounds(status);
    }

    if (array->len == len) {
        return status_ok(status);
    }

    array_truncate_fast(array, len);

    return status_ok(status);
}

bool array_truncate(Array *array, size_t len, Status *status) {
    if (len > array->len) {
        return index_out_of_bounds(status);
    }

    if (array->len == len) {
        return status_ok(status);
    }

    if (!array_zero_elements(array, len, array->len - len, status)) {
        return status_propagate(status);
    }

    array_truncate_fast(array, len);

    return status_ok(status);
}

void array_assign_fast(Array *array, const void *elements,
                                     size_t element_count) {
    array_overwrite_many_fast(array, 0, elements, element_count);
    array_truncate_fast(array, element_count);
}

bool array_assign(Array *array, const void *elements, size_t element_count,
                                                      Status *status) {
    if (!array_overwrite_many(array, 0, elements, element_count, status)) {
        return status_propagate(status);
    }

    array_truncate_fast(array, element_count);

    return true;
}

void array_assign_array_same_fast(Array *dst, Array *src) {
    array_assign_fast(dst, src->elements, src->len);
}

bool array_assign_array_same(Array *dst, Array *src, Status *status) {
    return array_assign(dst, src->elements, src->len, status);
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

void array_delete_many_fast(Array *array, size_t index, size_t count) {
    if ((index + count) < array->len) {
        cbbase_memmove(array_index_fast(array, index),
                       array_index_fast(array, index + count),
                       ((array->len - index) - count) * array->element_size);
    }

    array->len -= count;
}

bool array_delete_many_no_zero(Array *array, size_t index, size_t count,
                                                           Status *status) {
    if ((index + count) > array->len) {
        return index_out_of_bounds(status);
    }

    array_delete_many_fast(array, index, count);

    return status_ok(status);
}

bool array_delete_many(Array *array, size_t index, size_t count,
                                                   Status *status) {
    if ((index + count) > array->len) {
        return index_out_of_bounds(status);
    }

    array_delete_many_fast(array, index, count);
    array_zero_elements_fast(array, array->len, count);

    return status_ok(status);
}

void array_delete_fast(Array *array, size_t index) {
    array_delete_many_fast(array, index, 1);
}

bool array_delete_no_zero(Array *array, size_t index, Status *status) {
    return array_delete_many_no_zero(array, index, 1, status);
}

bool array_delete(Array *array, size_t index, Status *status) {
    return array_delete_many(array, index, 1, status);
}

void array_delete_unordered_fast(Array *array, size_t index) {
    if (index < (array->len - 1)) {
        cbbase_memmove(array_index_fast(array, index),
                       array_index_fast(array, array->len - 1),
                       array->element_size);
    }

    array->len--;
}

bool array_delete_unordered_no_zero(Array *array, size_t index, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_delete_unordered_fast(array, index);

    return status_ok(status);
}

bool array_delete_unordered(Array *array, size_t index, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_delete_unordered_fast(array, index);
    array_zero_element_fast(array, array->len);

    return status_ok(status);
}

void array_copy_element_fast(Array *array, size_t index, void *element) {
    cbbase_memmove(element, array_index_fast(array, index),
                            array->element_size);
}

bool array_copy_element(Array *array, size_t index, void *element,
                                                    Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_copy_element_fast(array, index, element);

    return status_ok(status);
}

void array_copy_elements_fast(Array *array, size_t index, size_t count,
                                                          void *elements) {
    cbbase_memmove(elements, array_index_fast(array, index),
                             count * array->element_size);
}

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

void array_pop_fast(Array *array, size_t index, void *element) {
    array_copy_element_fast(array, index, element);
    array_delete_fast(array, index);
}

bool array_pop_no_zero(Array *array, size_t index, void *element, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_copy_element_fast(array, index, element);
    array_delete_fast(array, index);

    return status_ok(status);
}

bool array_pop(Array *array, size_t index, void *element, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_copy_element_fast(array, index, element);
    array_zero_element_fast(array, index);
    array_delete_fast(array, index);

    return status_ok(status);
}

void array_pop_unordered_fast(Array *array, size_t index, void *element) {
    array_copy_element_fast(array, index, element);
    array_delete_unordered_fast(array, index);
}

bool array_pop_unordered_no_zero(Array *array, size_t index, void *element,
                                                             Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_copy_element_fast(array, index, element);
    array_delete_unordered_fast(array, index);

    return status_ok(status);
}

bool array_pop_unordered(Array *array, size_t index, void *element,
                                                     Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_copy_element_fast(array, index, element);
    array_zero_element_fast(array, index);
    array_delete_unordered_fast(array, index);

    return status_ok(status);
}

void array_pop_left_fast(Array *array, void *element) {
    array_pop_fast(array, 0, element);
}

bool array_pop_left(Array *array, void *element, Status *status) {
    return array_pop(array, 0, element, status);
}

void array_pop_left_unordered_fast(Array *array, void *element) {
    array_pop_unordered_fast(array, 0, element);
}

bool array_pop_left_unordered(Array *array, void *element, Status *status) {
    return array_pop_unordered(array, 0, element, status);
}

void array_pop_right_fast(Array *array, void *element) {
    array_pop_fast(array, array->len - 1, element);
}

bool array_pop_right(Array *array, void *element, Status *status) {
    return array_pop(array, array->len - 1, element, status);
}

void array_pop_right_unordered_fast(Array *array, void *element) {
    array_pop_unordered_fast(array, array->len - 1, element);
}

bool array_pop_right_unordered(Array *array, void *element, Status *status) {
    return array_pop_unordered(array, array->len - 1, element, status);
}

void array_clear_no_zero(Array *array) {
    array_truncate_fast(array, 0);
}

void array_clear(Array *array) {
    array_zero_elements_fast(array, 0, array->len);
    array_clear_no_zero(array);
}

void array_free_no_zero(Array *array) {
    cbfree(array->elements);
    array_init(array, array->element_size);
}

void array_free(Array *array) {
    array_zero_elements_fast(array, 0, array->len);
    array_free_no_zero(array);
}

void array_destroy_no_zero(Array **array) {
    array_free_no_zero(*array);
    cbfree(*array);
    *array = NULL;
}

void array_destroy(Array **array) {
    array_free(*array);
    cbfree(*array);
    *array = NULL;
}

/* vi: set et ts=4 sw=4: */

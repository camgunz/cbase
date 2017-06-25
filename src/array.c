#include "cbase.h"

/* [TODO] Add checks for element_size when running array/array functions */

#define array_element_size_mismatch(status) status_failure( \
    status,                                                 \
    "array",                                                \
    ARRAY_ELEMENT_SIZE_MISMATCH,                            \
    "Array element sizes do not match"                      \
)

void array_init(Array *array, size_t element_size) {
    array->element_size = element_size;
    array->elements = NULL;
    array->len = 0;
    array->alloc = 0;
}

bool array_init_alloc(Array *array, size_t element_size, size_t alloc,
                                                         Status *status) {
    array_init(array, element_size);
    return array_ensure_capacity(array, alloc, status);
}

bool array_init_alloc_zero(Array *array, size_t element_size, size_t alloc,
                                                              Status *status) {
    array_init(array, element_size);
    return array_ensure_capacity_zero(array, alloc, status);
}

bool array_new(Array **array, size_t element_size, Status *status) {
    Array *new_array = cbmalloc(1, sizeof(Array));

    if (!new_array) {
        return alloc_failure(status);
    }

    array_init(new_array, element_size);

    *array = new_array;

    return status_ok(status);
}

bool array_new_alloc(Array **array, size_t element_size,
                                    size_t alloc,
                                    Status *status) {
    return array_new(array, element_size, status) &&
           array_ensure_capacity(*array, alloc, status);
}

bool array_new_alloc_zero(Array **array, size_t element_size,
                                         size_t alloc,
                                         Status *status) {
    return array_new(array, element_size, status) &&
           array_ensure_capacity_zero(*array, alloc, status);
}

bool array_ensure_capacity(Array *array, size_t length, Status *status) {
    if (array->alloc < length) {
        void *new_elements = cbrealloc(
            array->elements,
            array->element_size,
            length
        );

        if (!new_elements) {
            return alloc_failure(status);
        }

        array->elements = new_elements;

        array->alloc = length;
    }

    return status_ok(status);
}

bool array_ensure_capacity_zero(Array *array, size_t length, Status *status) {
    if (array->alloc < length) {
        void *new_elements = NULL;

        if (!array->elements) {
            new_elements = calloc(array->element_size, length);

            if (!new_elements) {
                return alloc_failure(status);
            }

            array->elements = new_elements;
            array->alloc = length;
        }
        else {
            new_elements = cbrealloc(
                array->elements, array->element_size, length
            );

            if (!new_elements) {
                return alloc_failure(status);
            }

            array->elements = new_elements;

            memset(
                array_index_fast(array, array->alloc),
                0,
                array->element_size * (length - array->alloc)
            );

            array->alloc = length;
        }
    }

    return status_ok(status);
}

bool array_set_size(Array *array, size_t length, Status *status) {
    if (array->alloc < length) {
        return array_ensure_capacity(array, length, status);
    }

    if (array->alloc == length) {
        return status_ok(status);
    }

    void *new_elements = cbrealloc(
        array->elements,
        array->element_size,
        length
    );


    if (!new_elements) {
        return alloc_failure(status);
    }

    array->elements = new_elements;
    array->alloc = length;

    if (array->len > array->alloc) {
        array->len = array->alloc;
    }

    return status_ok(status);
}

bool array_shrink(Array *array, Status *status) {
    if (array->alloc > array->len) {
        void *new_elements = cbrealloc(
            array->elements,
            array->element_size,
            array->len
        );

        if (!new_elements) {
            return alloc_failure(status);
        }

        array->elements = new_elements;
        array->alloc = array->len;
    }

    return status_ok(status);
}

bool array_index(Array *array, size_t index, void **element, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    *element = array_index_fast(array, index);

    return status_ok(status);
}

bool array_zero_elements(Array *array, size_t index, size_t count,
                                                     Status *status) {
    if ((index + count) > array->len) {
        return index_out_of_bounds(status);
    }

    array_zero_elements_fast(array, index, count);

    return status_ok(status);
}

bool array_insert(Array *array, size_t index, void **new_element,
                                              Status *status) {
    if (!array_insert_no_zero(array, index, new_element, status)) {
        return false;
    }

    array_zero_element_fast(array, index);

    return status_ok(status);
}

bool array_insert_no_zero(Array *array, size_t index, void **new_element,
                                                      Status *status) {
    if (!array_ensure_capacity(array, array->len + 1, status)) {
        return false;
    }

    *new_element = array_insert_fast(array, index);

    return status_ok(status);
}

bool array_insert_array(Array *dst, Array *src, size_t index, Status *status) {
    if (!array_ensure_capacity(dst, dst->len + src->len, status)) {
        return false;
    }

    array_insert_array_fast(dst, src, index);

    return status_ok(status);
}

bool array_delete(Array *array, size_t index, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_delete_fast(array, index);

    return status_ok(status);
}

bool array_delete_unordered(Array *array, size_t index, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_delete_unordered_fast(array, index);

    return status_ok(status);
}

bool array_truncate(Array *array, size_t length, Status *status) {
    if (length >= array->len) {
        return index_out_of_bounds(status);
    }

    memset(
        array_index_fast(array, length),
        0,
        array->element_size * (array->len - length)
    );

    array_truncate_fast(array, length);

    return status_ok(status);
}

bool array_truncate_no_zero(Array *array, size_t length, Status *status) {
    if (length >= array->len) {
        return index_out_of_bounds(status);
    }

    array_truncate_fast(array, length);

    return status_ok(status);
}

bool array_copy_element(Array *array, size_t index,
                                      void *element,
                                      Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_copy_element_fast(array, index, element);

    return status_ok(status);
}

bool array_pop(Array *array, size_t index, void *element, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_pop_fast(array, index, element);

    return status_ok(status);
}

bool array_pop_unordered(Array *array, size_t index, void *element, Status *status) {
    if (index >= array->len) {
        return index_out_of_bounds(status);
    }

    array_pop_unordered_fast(array, index, element);

    return status_ok(status);
}

bool array_deep_copy(Array *dst, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    if (!array_ensure_capacity(dst, src->len, status)) {
        return false;
    }

    memmove(dst->elements, src->elements, src->element_size * src->len);
    dst->len = src->len;

    return status_ok(status);
}

bool array_concat(Array *dst, Array *src, Status *status) {
    if (!array_ensure_capacity(dst, dst->len + src->len, status)) {
        return false;
    }

    array_concat_fast(dst, src);
    array_clear(src);

    return status_ok(status);
}

bool array_concat_no_clear(Array *dst, Array *src, Status *status) {
    if (!array_ensure_capacity(dst, dst->len + src->len, status)) {
        return false;
    }

    array_concat_fast(dst, src);

    return status_ok(status);
}

void array_clear(Array *array) {
    memset(array->elements, 0, array->len * array->element_size);
    array->len = 0;
}

void array_free(Array *array) {
    cbfree(array->elements);
    array_init(array, array->element_size);
}

/* vi: set et ts=4 sw=4: */

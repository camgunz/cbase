#include "cbase.h"

/* [TODO] Add checks for element_size when running array/array functions */

#define array_element_size_mismatch(status) status_failure( \
    status,                                                 \
    "array",                                                \
    ARRAY_ELEMENT_SIZE_MISMATCH,                            \
    "Array element sizes do not match"                      \
)

bool array_ensure_capacity(Array *array, size_t length, Status *status) {
    if (array->alloc < length) {
        void *new_elements = cbrealloc(array->elements, array->element_size,
                                                        length);

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
            new_elements = cbrealloc(array->elements, array->element_size,
                                                      length);

            if (!new_elements) {
                return alloc_failure(status);
            }

            array->elements = new_elements;

            if (!array_zero_elements_fast(array, array->alloc,
                                                 length - array->alloc)) {
                return false;
            }

            array->alloc = length;
        }
    }

    return status_ok(status);
}

bool array_set_size(Array *array, size_t length, Status *status) {
    void *new_elements = NULL;

    if (array->alloc < length) {
        return array_ensure_capacity(array, length, status);
    }

    if (array->alloc == length) {
        return status_ok(status);
    }

    new_elements = cbrealloc(array->elements, array->element_size, length);

    if (!new_elements) {
        return alloc_failure(status);
    }

    array->elements = new_elements;
    array->alloc = length;
    array->len = array->alloc;

    return status_ok(status);
}

bool array_insert_array_fast(Array *dst, size_t index, Array *src,
                                                       Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_insert_array_same_fast(dst, index, src, status);
}

bool array_insert_array(Array *dst, size_t index, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_insert_array_same(dst, index, src, status);
}

bool array_prepend_array_fast(Array *dst, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_prepend_array_same_fast(dst, src, status);
}

bool array_prepend_array(Array *dst, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_prepend_array_same(dst, src, status);
}

bool array_append_array_fast(Array *dst, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_append_array_same_fast(dst, src, status);
}

bool array_append_array(Array *dst, Array *src, Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_append_array_same(dst, src, status);
}

bool array_overwrite_array_fast(Array *dst, size_t index, Array *src,
                                                          Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_overwrite_array_same_fast(dst, index, src, status);
}

bool array_overwrite_array(Array *dst, size_t index, Array *src,
                                                     Status *status) {
    if (dst->element_size != src->element_size) {
        return array_element_size_mismatch(status);
    }

    return array_overwrite_array_same(dst, index, src, status);
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

/* vi: set et ts=4 sw=4: */

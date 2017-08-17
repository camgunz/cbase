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

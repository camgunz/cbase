#include "cbase.h"

void parray_init(PArray *parray) {
    parray->elements = NULL;
    parray->len = 0;
    parray->alloc = 0;
}

bool parray_init_alloc(PArray *parray, size_t alloc, Status *status) {
    parray_init(parray);
    return parray_ensure_capacity(parray, alloc, status);
}

bool parray_new(PArray **parray, Status *status) {
    PArray *new_parray = cbmalloc(1, sizeof(PArray));

    if (!new_parray) {
        return alloc_failure(status);
    }

    parray_init(new_parray);

    *parray = new_parray;

    return status_ok(status);
}

bool parray_new_alloc(PArray **parray, size_t alloc, Status *status) {
    return parray_new(parray, status) &&
           parray_ensure_capacity(*parray, alloc, status);
}

bool parray_ensure_capacity(PArray *parray, size_t length, Status *status) {
    if (parray->alloc < length) {
        void **new_elements = cbrealloc(
            parray->elements,
            length,
            sizeof(void *)
        );

        if (!new_elements) {
            return alloc_failure(status);
        }

        parray->elements = new_elements;
        parray->alloc = length;
    }

    return status_ok(status);
}

bool parray_set_size(PArray *parray, size_t length, Status *status) {
    if (parray->alloc < length) {
        return parray_ensure_capacity(parray, length, status);
    }

    if (parray->alloc == length) {
        return status_ok(status);
    }

    void **new_elements = cbrealloc(parray->elements, length, sizeof(void *));

    if (!new_elements) {
        return alloc_failure(status);
    }

    parray->elements = new_elements;
    parray->alloc = length;

    return status_ok(status);
}

bool parray_shrink(PArray *parray, Status *status) {
    if (parray->alloc > parray->len) {
        void *new_elements = cbrealloc(
            parray->elements,
            parray->len,
            sizeof(void *)
        );

        if (!new_elements) {
            return alloc_failure(status);
        }

        parray->elements = new_elements;
        parray->alloc = parray->len;
    }

    return status_ok(status);
}

bool parray_copy(PArray *dst, PArray *src, Status *status) {
    parray_clear(dst);

    if (!parray_ensure_capacity(dst, src->len, status)) {
        return false;
    }

    for (size_t i = 0; i < src->len; i++) {
        parray_append_fast(dst, parray_index_fast(src, i));
    }

    return status_ok(status);
}

bool parray_set(PArray *parray, size_t index, void *element, Status *status) {
    if (index >= parray->len) {
        return index_out_of_bounds(status);
    }

    parray_set_fast(parray, index, element);

    return status_ok(status);
}

bool parray_index(PArray *parray, size_t index, void **element, Status *status) {
    if (index >= parray->len) {
        return index_out_of_bounds(status);
    }

    *element = parray_index_fast(parray, index);

    return status_ok(status);
}

bool parray_insert(PArray *parray, size_t index, void *element,
                                                 Status *status) {
    if (!parray_ensure_capacity(parray, parray->len + 1, status)) {
        return false;
    }

    parray_insert_fast(parray, index, element);

    return status_ok(status);
}

bool parray_delete(PArray *parray, size_t index, Status *status) {
    if (index >= parray->len) {
        return index_out_of_bounds(status);
    }

    parray_delete_fast(parray, index);

    return status_ok(status);
}

bool parray_delete_unordered(PArray *parray, size_t index, Status *status) {
    if (index >= parray->len) {
        return index_out_of_bounds(status);
    }

    parray_delete_unordered_fast(parray, index);

    return status_ok(status);
}

bool parray_delete_leave_null(PArray *parray, size_t index, Status *status) {
    if (index >= parray->len) {
        return index_out_of_bounds(status);
    }

    parray_delete_leave_null_fast(parray, index);

    return status_ok(status);
}

bool parray_truncate(PArray *parray, size_t length, Status *status) {
    if (length >= parray->len) {
        return index_out_of_bounds(status);
    }

    parray_truncate_fast(parray, length);
    parray->len = length;

    return status_ok(status);
}

bool parray_pop(PArray *parray, size_t index, void **element, Status *status) {
    if (index >= parray->len) {
        return index_out_of_bounds(status);
    }

    parray_pop_fast(parray, index, element);

    return status_ok(status);
}

bool parray_pop_leave_null(PArray *parray, size_t index, void **element,
                                                         Status *status) {
    if (index >= parray->len) {
        return index_out_of_bounds(status);
    }

    parray_pop_leave_null_fast(parray, index, element);

    return status_ok(status);
}

bool parray_concat(PArray *dst, PArray *src, Status *status) {
    if (!parray_ensure_capacity(dst, dst->len + src->len, status)) {
        return false;
    }

    parray_concat_fast(dst, src);
    parray_clear(src);

    return status_ok(status);
}

bool parray_concat_no_clear(PArray *dst, PArray *src, Status *status) {
    if (!parray_ensure_capacity(dst, dst->len + src->len, status)) {
        return false;
    }

    parray_concat_fast(dst, src);

    return status_ok(status);
}

void parray_clear(PArray *parray) {
    memset(parray->elements, 0, sizeof(void *) * parray->len);
    parray->len = 0;
}

void parray_free(PArray *parray) {
    cbfree(parray->elements);
    parray_init(parray);
}

/* vi: set et ts=4 sw=4: */

#ifndef PARRAY_H__
#define PARRAY_H__

typedef struct {
    size_t len;
    size_t alloc;
    void **elements;
} PArray;

void parray_init(PArray *parray);
bool parray_init_alloc(PArray *parray, size_t alloc, Status *status);
bool parray_new(PArray **parray, Status *status);
bool parray_new_alloc(PArray **parray, size_t alloc, Status *status);
bool parray_ensure_capacity(PArray *parray, size_t length, Status *status);
bool parray_set_size(PArray *parray, size_t length, Status *status);
bool parray_compact(PArray *parray, Status *status);
bool parray_copy(PArray *dst, PArray *src, Status *status);
bool parray_index(PArray *parray, size_t index, void **element,
                                                Status *status);
bool parray_set(PArray *parray, size_t index, void *element, Status *status);
bool parray_insert(PArray *parray, size_t index, void *element,
                                                 Status *status);
bool parray_delete(PArray *parray, size_t index, Status *status);
bool parray_delete_unordered(PArray *parray, size_t index, Status *status);
bool parray_delete_leave_null(PArray *parray, size_t index, Status *status);
bool parray_truncate(PArray *parray, size_t length, Status *status);
bool parray_pop(PArray *parray, size_t index, void **element, Status *status);
bool parray_pop_leave_null(PArray *parray, size_t index, void **element,
                                                         Status *status);
bool parray_concat(PArray *dst, PArray *src, Status *status);
bool parray_concat_no_clear(PArray *dst, PArray *src, Status *status);
void parray_clear(PArray *parray);
void parray_free(PArray *parray);

static inline void* parray_index_fast(PArray *parray, size_t index) {
    return *(parray->elements + index);
}

static inline void parray_insert_fast(PArray *parray, size_t index,
                                                      void *element) {
    if (index < parray->len) {
        cbmemmove(
            parray->elements + index + 1,
            parray->elements + index,
            sizeof(void *) * (parray->len - index)
        );
    }

    *(parray->elements + index) = element;

    if (index > parray->len) {
        parray->len = index + 1;
    }
    else {
        parray->len++;
    }
}

static inline bool parray_prepend(PArray *parray, void *element,
                                                  Status *status) {
    return parray_insert(parray, 0, element, status);
}

static inline void parray_prepend_fast(PArray *parray, void *element) {
    parray_insert_fast(parray, 0, element);
}

static inline bool parray_append(PArray *parray, void *element,
                                                 Status *status) {
    return parray_insert(parray, parray->len, element, status);
}

static inline void parray_append_fast(PArray *parray, void *element) {
    parray_insert_fast(parray, parray->len, element);
}

static inline void parray_set_fast(PArray *parray, size_t index,
                                                   void *element) {
    *(parray->elements + index) = element;
}

static inline void parray_delete_fast(PArray *parray, size_t index) {
    cbmemmove(
        parray->elements + index,
        parray->elements + index + 1,
        sizeof(void *) * (parray->len - index - 1)
    );

    parray->len--;
}

static inline void parray_delete_unordered_fast(PArray *parray, size_t index) {
    cbmemmove(
        parray->elements + index,
        parray->elements + (parray->len - 1),
        sizeof(void *)
    );

    parray->len--;
}

static inline void parray_truncate_fast(PArray *parray, size_t length) {
    parray->len = length;
}

static inline void parray_delete_leave_null_fast(PArray *parray,
                                                 size_t index) {
    *(parray->elements + index) = NULL;
}

static inline void parray_pop_leave_null_fast(PArray *parray, size_t index,
                                                              void **element) {
    *element = parray_index_fast(parray, index);
    parray_delete_leave_null_fast(parray, index);
}

static inline void parray_pop_fast(PArray *parray, size_t index,
                                                   void **element) {
    *element = parray_index_fast(parray, index);
    parray_delete_fast(parray, index);
}

static inline void parray_pop_unordered_fast(PArray *parray, size_t index,
                                                             void **element) {
    *element = parray_index_fast(parray, index);
    parray_delete_unordered_fast(parray, index);
}

static inline bool parray_pop_left(PArray *parray, void **element,
                                                   Status *status) {
    return parray_pop(parray, 0, element, status);
}

static inline void parray_pop_left_fast(PArray *parray, void **element) {
    parray_pop_fast(parray, 0, element);
}

static inline void parray_pop_left_unordered_fast(PArray *parray,
                                                  void **element) {
    parray_pop_unordered_fast(parray, 0, element);
}

static inline bool parray_pop_right(PArray *parray, void **element,
                                                   Status *status) {
    return parray_pop(parray, parray->len - 1, element, status);
}

static inline void parray_pop_right_fast(PArray *parray, void **element) {
    parray_pop_fast(parray, parray->len - 1, element);
}

static inline void parray_pop_right_unordered_fast(PArray *parray,
                                                  void **element) {
    parray_pop_unordered_fast(parray, parray->len - 1, element);
}

static inline void parray_concat_fast(PArray *dst, PArray *src) {
    cbmemmove(
        dst->elements + dst->len,
        src->elements,
        sizeof(void *) * src->len
    );

    dst->len += src->len;
}

#endif

/* vi: set et ts=4 sw=4: */

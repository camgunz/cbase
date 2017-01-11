#ifndef ARRAY_H__
#define ARRAY_H__

enum {
    ARRAY_ELEMENT_SIZE_MISMATCH = 1,
};

typedef struct {
    size_t len;
    size_t element_size;
    size_t alloc;
    void *elements;
} Array;

void array_init(Array *array, size_t element_size);
bool array_init_alloc(Array *array, size_t element_size, size_t alloc,
                                                         Status *status);
bool array_init_alloc_zero(Array *array, size_t element_size, size_t alloc,
                                                              Status *status);
bool array_new(Array **array, size_t element_size, Status *status);
bool array_new_alloc(Array **array, size_t element_size, size_t alloc,
                                                         Status *status);
bool array_new_alloc_zero(Array **array, size_t element_size, size_t alloc,
                                                              Status *status);
bool array_ensure_capacity(Array *array, size_t length, Status *status);
bool array_ensure_capacity_zero(Array *array, size_t length, Status *status);
bool array_set_size(Array *array, size_t length, Status *status);
bool array_shrink(Array *array, Status *status);
bool array_index(Array *array, size_t index, void **element, Status *status);
bool array_zero_elements(Array *array, size_t index, size_t count,
                                                     Status *status);
bool array_insert(Array *array, size_t index, void **new_element,
                                              Status *status);
bool array_insert_no_zero(Array *array, size_t index, void **new_element,
                                                      Status *status);
bool array_delete(Array *array, size_t index, Status *status);
bool array_delete_unordered(Array *array, size_t index, Status *status);
bool array_truncate(Array *array, size_t length, Status *status);
bool array_truncate_no_zero(Array *array, size_t length, Status *status);
bool array_copy_element(Array *array, size_t index,
                                      void *element,
                                      Status *status);
bool array_pop(Array *array, size_t index, void *element, Status *status);
bool array_pop_unordered(Array *array, size_t index, void *element,
                                                     Status *status);
bool array_deep_copy(Array *dst, Array *src, Status *status);
bool array_concat(Array *dst, Array *src, Status *status);
bool array_concat_no_clear(Array *dst, Array *src, Status *status);
void array_clear(Array *array);
void array_free(Array *array);

static inline void* array_index_fast(Array *array, size_t index) {
    return (void *)(((char *)array->elements) + (array->element_size * index));
}

static inline bool array_zero_element(Array *array, size_t index,
                                                    Status *status) {
    return array_zero_elements(array, index, 1, status);
}

static inline void array_zero_elements_fast(Array *array, size_t index,
                                                          size_t count) {
    memset(array_index_fast(array, index), 0, array->element_size * count);
}

static inline void array_zero_element_fast(Array *array, size_t index) {
    array_zero_elements_fast(array, index, 1);
}

static inline void* array_insert_fast(Array *array, size_t index) {
    if (index < array->len) {
        memmove(
            array_index_fast(array, index + 1),
            array_index_fast(array, index),
            array->element_size * (array->len - index)
        );
    }

    if (index > array->len) {
        array->len = index + 1;
    }
    else {
        array->len++;
    }

    return array_index_fast(array, index);
}

static inline bool array_prepend(Array *array, void **element, Status *status) {
    return array_insert(array, 0, element, status);
}

static inline bool array_prepend_no_zero(Array *array, void **element,
                                                      Status *status) {
    return array_insert_no_zero(array, 0, element, status);
}

static inline void* array_prepend_fast(Array *array) {
    return array_insert_fast(array, 0);
}

static inline bool array_append(Array *array, void **element, Status *status) {
    return array_insert(array, array->len, element, status);
}

static inline bool array_append_no_zero(Array *array, void **element,
                                                      Status *status) {
    return array_insert_no_zero(array, array->len, element, status);
}

static inline void* array_append_fast(Array *array) {
    return array_insert_fast(array, array->len);
}

static inline void array_delete_fast(Array *array, size_t index) {
    memmove(
        array_index_fast(array, index),
        array_index_fast(array, index + 1),
        array->element_size * (array->len - index)
    );

    array->len--;
}

static inline void array_delete_unordered_fast(Array *array, size_t index) {
    memmove(
        array_index_fast(array, index),
        array_index_fast(array, array->len - 1),
        array->element_size
    );

    array->len--;
}

static inline void array_truncate_fast(Array *array, size_t length) {
    array->len = length;
}

static inline void array_copy_element_fast(Array *array, size_t index,
                                                         void **element) {
    memmove(element, array_index_fast(array, index), array->element_size);
}

static inline void array_pop_fast(Array *array, size_t index, void *element) {
    array_copy_element_fast(array, index, element);
    array_delete_fast(array, index);
}

static inline void array_pop_unordered_fast(Array *array, size_t index, void *element) {
    array_copy_element_fast(array, index, element);
    array_delete_unordered_fast(array, index);
}

static inline bool array_pop_left(Array *array, void *element,
                                                Status *status) {
    return array_pop(array, 0, element, status);
}

static inline void array_pop_left_fast(Array *array, void *element) {
    array_pop_fast(array, 0, element);
}

static inline void array_pop_left_unordered_fast(Array *array, void *element) {
    array_pop_unordered_fast(array, 0, element);
}

static inline bool array_pop_right(Array *array, void *element,
                                                 Status *status) {
    return array_pop(array, array->len - 1, element, status);
}

static inline void array_pop_right_fast(Array *array, void *element) {
    array_pop_fast(array, array->len - 1, element);
}

static inline void array_pop_right_unordered_fast(Array *array, void *element) {
    array_pop_unordered_fast(array, array->len - 1, element);
}

static inline void array_concat_fast(Array *dst, Array *src) {
    memmove(
        array_index_fast(dst, dst->len),
        src->elements,
        src->element_size * src->len
    );

    dst->len += src->len;
}

#endif

/* vi: set et ts=4 sw=4: */

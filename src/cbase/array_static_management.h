#pragma once

#ifndef _CBASE_ARRAY_STATIC_MANAGEMENT_H__
#define _CBASE_ARRAY_STATIC_MANAGEMENT_H__

#define CBASE_ARRAY_STATIC_MANAGEMENT_IMPL_DECL(_api, _dname, _aname, _atype) \
    _api int _aname##_ensure_capacity_no_zero_no_check(_atype *array,         \
                                                       size_t cap);           \
                                                                              \
    _api int _aname##_ensure_capacity_no_zero(_atype *array, size_t cap);     \
                                                                              \
    _api int _aname##_ensure_capacity_no_check(_atype *array, size_t cap);    \
                                                                              \
    _api int _aname##_ensure_capacity(_atype *array, size_t cap);             \
                                                                              \
    _api int _aname##_set_length_no_zero_no_check(_atype *array, size_t len); \
                                                                              \
    _api int _aname##_set_length_no_zero(_atype *array, size_t len);          \
                                                                              \
    _api int _aname##_set_length_no_check(_atype *array, size_t len);         \
                                                                              \
    _api int _aname##_set_length(_atype *array, size_t len);                  \
                                                                              \
    _api void _aname##_init_no_check(_atype *array);                          \
                                                                              \
    _api int _aname##_init(_atype *array);                                    \
                                                                              \
    _api int _aname##_init_length_no_zero_no_check(_atype *array,             \
                                                   size_t len);               \
                                                                              \
    _api int _aname##_init_length_no_zero(_atype *array, size_t len)          \
                                                                              \
    _api int _aname##_init_length_no_check(_atype *array, size_t len)         \
                                                                              \
    _api int _aname##_init_length(_atype *array, size_t len)                  \
                                                                              \
    _api int _aname##_init_from_data_no_check(_atype *array,                  \
                                              const _etype *elements,         \
                                              size_t element_count);          \
                                                                              \
    _api int _aname##_init_from_data(_atype *array,                           \
                                     const _etype *elements,                  \
                                     size_t element_count);                   \
                                                                              \
    _api void _aname##_free_no_zero_no_check(_atype *array);                  \
                                                                              \
    _api int _aname##_free_no_zero(_atype *array);                            \
                                                                              \
    _api void _aname##_free_no_check(_atype *array);                          \
                                                                              \
    _api int _aname##_free(_atype *array);                                    \
                                                                              \
    _api void _aname##_destroy_no_zero_no_check(_atype *array);               \
                                                                              \
    _api int _aname##_destroy_no_zero(_atype *array);                         \
                                                                              \
    _api void _aname##_destroy_no_check(_atype *array);                       \
                                                                              \
    _api int _aname##_destroy(_atype *array);

#define CBASE_ARRAY_STATIC_MANAGEMENT_IMPL(_api, _dname, _aname, _atype)      \
    _api int _aname##_ensure_capacity_no_zero(_atype *array, size_t cap) {    \
        CBASE_DELEGATE(_dname##_ensure_capacity_no_zero(&array->data,         \
                                                        &array->len,          \
                                                        cap));                \
    }                                                                         \
                                                                              \
    _api int _aname##_ensure_capacity(_atype *array, size_t cap) {            \
        CBASE_DELEGATE(                                                       \
            _dname##_ensure_capacity(&array->data, &array->len, cap));        \
    }                                                                         \
                                                                              \
    _api int _aname##_set_length_no_zero_no_check(_atype *array,              \
                                                  size_t len) {               \
        CBASE_DELEGATE(_dname##_set_length_no_zero_no_check(&array->data,     \
                                                            &array->len,      \
                                                            len));            \
    }                                                                         \
                                                                              \
    _api int _aname##_set_length_no_zero(_atype *array, size_t len) {         \
        CBASE_DELEGATE(                                                       \
            _dname##_set_length_no_zero(&array->data, &array->len, len));     \
    }                                                                         \
                                                                              \
    _api int _aname##_set_length_no_check(_atype *array, size_t len) {        \
        CBASE_DELEGATE(                                                       \
            _dname##_set_length_no_check(&array->data, &array->len, len));    \
    }                                                                         \
                                                                              \
    _api int _aname##_set_length(_atype *array, size_t len) {                 \
        CBASE_DELEGATE(_dname##_set_length(&array->data, &array->len, len));  \
    }                                                                         \
                                                                              \
    _api void _aname##_init_no_check(_atype *array) {                         \
        _dname##_init_no_check(&array->len);                                  \
    }                                                                         \
                                                                              \
    _api int _aname##_init(_atype *array) {                                   \
        CBASE_DELEGATE(_dname##_init(&array->len));                           \
    }                                                                         \
                                                                              \
    _api int _aname##_init_length_no_zero_no_check(_atype *array,             \
                                                   size_t len) {              \
        CBASE_DELEGATE(_dname##_init_length_no_zero_no_check(&array->data,    \
                                                             &array->len,     \
                                                             len));           \
    }                                                                         \
                                                                              \
    _api int _aname##_init_length_no_zero(_atype *array, size_t len) {        \
        CBASE_DELEGATE(                                                       \
            _dname##_init_length_no_zero(&array->data, &array->len, len));    \
    }                                                                         \
                                                                              \
    _api int _aname##_init_length_no_check(_atype *array, size_t len) {       \
        CBASE_DELEGATE(                                                       \
            _dname##_init_length_no_zero(&array->data, &array->len, len));    \
    }                                                                         \
                                                                              \
    _api int _aname##_init_length(_atype *array, size_t len) {                \
        CBASE_DELEGATE(_dname##_init_length(&array->data, &array->len, len)); \
    }                                                                         \
                                                                              \
    _api int _aname##_init_from_data_no_check(_atype *array,                  \
                                              const _etype *elements,         \
                                              size_t element_count) {         \
        CBASE_DELEGATE(_dname##_init_from_data_no_check(&array->data,         \
                                                        &array->len,          \
                                                        elements,             \
                                                        element_count));      \
    }                                                                         \
                                                                              \
    _api int _aname##_init_from_data(_atype *array,                           \
                                     const _etype *elements,                  \
                                     size_t element_count) {                  \
        CBASE_DELEGATE(_dname##init_from_data(&array->data,                   \
                                              &array->len,                    \
                                              elements,                       \
                                              element_count));                \
    }                                                                         \
                                                                              \
    _api void _aname##_free_no_zero_no_check(_atype *array) {                 \
        _dname##_free_no_zero_no_check(&array->data, &array->len);            \
    }                                                                         \
                                                                              \
    _api int _aname##_free_no_zero(_atype *array) {                           \
        CBASE_DELEGATE(_dname##_free_no_zero(&array->data, &array->len));     \
    }                                                                         \
                                                                              \
    _api void _aname##_free_no_check(_atype *array) {                         \
        CBASE_DELEGATE(_dname##_free_no_check(&array->data, &array->len));    \
    }                                                                         \
                                                                              \
    _api int _aname##_free(_atype *array) {                                   \
        CBASE_DELEGATE(_dname##_free(&array->data, &array->len));             \
    }                                                                         \
                                                                              \
    _api void _aname##_destroy_no_zero_no_check(_atype **array) {             \
        _dname##_destroy_no_zero_no_check(&(*array)->data, &(*array)->len);   \
        *array = NULL;                                                        \
    }                                                                         \
                                                                              \
    _api int _aname##_destroy_no_zero(_atype **array) {                       \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_destroy_no_zero(&(*array)->data, &(*array)->len));       \
        *array = NULL;                                                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _aname##_destroy_no_check(_atype **array) {                     \
        _dname##_destroy_no_check(&(*array)->data, &(*array)->len);           \
        *array = NULL;                                                        \
    }                                                                         \
                                                                              \
    _api int _aname##_destroy(_atype **array) {                               \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_destroy(&(*array)->data, &(*array)->len));               \
        *array = NULL;                                                        \
                                                                              \
        return 0;                                                             \
    }

#endif

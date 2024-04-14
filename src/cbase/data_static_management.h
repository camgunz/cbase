#pragma once

#ifndef _CBASE_DATA_STATIC_MANAGEMENT_H__
#define _CBASE_DATA_STATIC_MANAGEMENT_H__

#define _CBASE_TRY_EXPAND_STATIC_DATA_IF_NEEDED_NO_ZERO(_dname,               \
                                                        _data,                \
                                                        _dcap,                \
                                                        _excap)               \
    do {                                                                      \
        size_t _slot_count = 0;                                               \
        CBASE_PROPAGATE_ERROR(                                                \
            cb_safe_add_size((*(_dcap)), (_excap), &_slot_count));            \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_ensure_capacity_no_zero_no_check(&(_data),               \
                                                      (_dcap),                \
                                                      _slot_count));          \
    } while (0)

#define _CBASE_TRY_EXPAND_STATIC_DATA_IF_NEEDED(_dname, _data, _dcap, _excap) \
    do {                                                                      \
        size_t _slot_count = 0;                                               \
        CBASE_PROPAGATE_ERROR(                                                \
            cb_safe_add_size((*(_dcap)), (_excap), &_slot_count));            \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_ensure_capacity_no_zero_no_check(&(_data),               \
                                                      (_dcap),                \
                                                      _slot_count));          \
    } while (0)

#define CBASE_DATA_STATIC_MANAGEMENT_IMPL_DECL(_api,                          \
                                               _dname,                        \
                                               _dtype,                        \
                                               _dmaxcap)                      \
    _api int _dname##_set_length_no_zero_no_check(_dtype *data,               \
                                                  size_t *dlen,               \
                                                  size_t len);                \
                                                                              \
    _api int _dname##_set_length_no_zero(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         size_t len);                         \
                                                                              \
    _api int _dname##_set_length_no_check(_dtype *data,                       \
                                          size_t *dlen,                       \
                                          size_t len);                        \
                                                                              \
    _api int _dname##_set_length(_dtype *data, size_t *dlen, size_t len);     \
                                                                              \
    _api void _dname##_init_no_check(size_t *dlen);                           \
                                                                              \
    _api int _dname##_init(size_t *dlen);                                     \
                                                                              \
    _api int _dname##_init_length_no_zero_no_check(_dtype *data,              \
                                                   size_t *dlen,              \
                                                   size_t dlen2);             \
                                                                              \
    _api int _dname##_init_length_no_zero(_dtype *data,                       \
                                          size_t *dlen,                       \
                                          size_t dlen2);                      \
                                                                              \
    _api int _dname##_init_length_no_check(_dtype *data,                      \
                                           size_t *dlen,                      \
                                           size_t dlen2);                     \
                                                                              \
    _api int _dname##_init_length(_dtype *data, size_t *dlen, size_t dlen2);  \
                                                                              \
    _api int _dname##_init_from_data_no_check(_dtype *data,                   \
                                              size_t *dlen,                   \
                                              const _dtype *data2,            \
                                              size_t dlen2);                  \
                                                                              \
    _api int _dname##_init_from_data(_dtype *data,                            \
                                     size_t *dlen,                            \
                                     const _dtype *data2,                     \
                                     size_t dlen2);                           \
                                                                              \
    _api void _dname##_free_no_zero_no_check(size_t *dlen);                   \
                                                                              \
    _api int _dname##_free_no_zero(size_t *dlen);                             \
                                                                              \
    _api void _dname##_free_no_check(_dtype *data, size_t *dlen);             \
                                                                              \
    _api int _dname##_free(_dtype *data, size_t *dlen);

#define CBASE_DATA_STATIC_MANAGEMENT_IMPL(_api, _dname, _dtype, _dmaxcap)     \
    _api int _dname##_ensure_capacity_no_zero_no_check(_dtype **data,         \
                                                       size_t *dcap,          \
                                                       size_t cap) {          \
        CBASE_ERROR_IF((cap > _dmaxcap), CBASE_ERROR_OUT_OF_BOUNDS);          \
                                                                              \
        (void)data;                                                           \
                                                                              \
        (*dcap) = cap;                                                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_ensure_capacity_no_check(_dtype **data,                 \
                                               size_t *dcap,                  \
                                               size_t cap) {                  \
        CBASE_ERROR_IF((cap > _dmaxcap), CBASE_ERROR_OUT_OF_BOUNDS);          \
                                                                              \
        _dname##_zero_no_check((*data), (*dcap), cap - (*dcap));              \
                                                                              \
        (*dcap) = cap;                                                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_length_no_zero_no_check(_dtype *data,               \
                                                  size_t *dlen,               \
                                                  size_t len) {               \
        if (len < (*dlen)) {                                                  \
            (*dlen) = len;                                                    \
        }                                                                     \
        else {                                                                \
            _CBASE_TRY_EXPAND_STATIC_DATA_IF_NEEDED_NO_ZERO(_dname,           \
                                                            data,             \
                                                            dlen,             \
                                                            len);             \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_length_no_zero(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         size_t len) {                        \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_set_length_no_zero_no_check(data, dlen, len));           \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_length_no_check(_dtype *data,                       \
                                          size_t *dlen,                       \
                                          size_t len) {                       \
        if (len < (*dlen)) {                                                  \
            _dname##_zero_no_check(data, (*dlen), len - (*dlen));             \
            (*dlen) = len;                                                    \
        }                                                                     \
        else {                                                                \
            _CBASE_TRY_EXPAND_STATIC_DATA_IF_NEEDED(_dname, data, dlen, len); \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_length(_dtype *data, size_t *dlen, size_t len) {    \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(_dname##_set_length_no_check(data, dlen, len)); \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_init_no_check(size_t *dlen) {                          \
        (*dlen) = 0;                                                          \
    }                                                                         \
                                                                              \
    _api int _dname##_init(size_t *dlen) {                                    \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
                                                                              \
        _dname##_init_no_check(dlen);                                         \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_length_no_zero_no_check(_dtype *data,              \
                                                   size_t *dlen,              \
                                                   size_t len) {              \
        _dname##_init_no_check(dlen);                                         \
        _CBASE_TRY_EXPAND_STATIC_DATA_IF_NEEDED_NO_ZERO(_dname,               \
                                                        data,                 \
                                                        dlen,                 \
                                                        len);                 \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_length_no_zero(_dtype *data,                       \
                                          size_t *dlen,                       \
                                          size_t len) {                       \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_length_no_zero_no_check(data, dlen, len));          \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_length_no_check(_dtype *data,                      \
                                           size_t *dlen,                      \
                                           size_t len) {                      \
        _dname##_init_no_check(dlen);                                         \
        _CBASE_TRY_EXPAND_STATIC_DATA_IF_NEEDED(_dname, data, dlen, len);     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_length(_dtype *data, size_t *dlen, size_t len) {   \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_length_no_check(data, dlen, len));                  \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_from_data_no_check(_dtype *data,                   \
                                              size_t *dlen,                   \
                                              const _dtype *data2,            \
                                              size_t dlen2) {                 \
        _dname##_init_no_check(dlen);                                         \
        _CBASE_TRY_EXPAND_STATIC_DATA_IF_NEEDED(_dname, data, dlen, dlen2);   \
        _dname##_set_no_check(data, 0, data2, dlen2);                         \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_from_data(_dtype *data,                            \
                                     size_t *dlen,                            \
                                     const _dtype *data2,                     \
                                     size_t dlen2) {                          \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(data2);                                  \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_from_data_no_check(data, dlen, data2, dlen2));      \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_free_no_zero_no_check(size_t *dlen) {                  \
        _dname##_init_no_check(dlen);                                         \
    }                                                                         \
                                                                              \
    _api int _dname##_free_no_zero(size_t *dlen) {                            \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
                                                                              \
        _dname##_free_no_zero_no_check(dlen);                                 \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_free_no_check(_dtype *data, size_t *dlen) {            \
        _dname##_zero_no_check(data, 0, (*dlen));                             \
        _dname##_init_no_check(dlen);                                         \
    }                                                                         \
                                                                              \
    _api int _dname##_free(_dtype *data, size_t *dlen) {                      \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
                                                                              \
        _dname##_free_no_check(data, dlen);                                   \
                                                                              \
        return 0;                                                             \
    }

#endif

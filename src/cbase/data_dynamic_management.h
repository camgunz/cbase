#pragma once

#ifndef _CBASE_DATA_DYNAMIC_MANAGEMENT_H__
#define _CBASE_DATA_DYNAMIC_MANAGEMENT_H__

/* [TODO] Look at aligned allocation */

#define _CBASE_TRY_EXPAND_DYNAMIC_DATA_IF_NEEDED_NO_ZERO(_dname,              \
                                                         _data,               \
                                                         _dlen,               \
                                                         _dcap,               \
                                                         _excap)              \
    do {                                                                      \
        size_t _slot_count = 0;                                               \
        CBASE_PROPAGATE_ERROR(                                                \
            cb_safe_add_size((_dlen), (_excap), &_slot_count));               \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_ensure_capacity_no_zero_no_check((_data),                \
                                                      (_dcap),                \
                                                      _slot_count));          \
    } while (0)

#define _CBASE_TRY_EXPAND_DYNAMIC_DATA_IF_NEEDED(_dname,                      \
                                                 _data,                       \
                                                 _dlen,                       \
                                                 _dcap,                       \
                                                 _excap)                      \
    do {                                                                      \
        size_t _slot_count = 0;                                               \
        CBASE_PROPAGATE_ERROR(                                                \
            cb_safe_add_size((_dlen), (_excap), &_slot_count));               \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_ensure_capacity_no_zero_no_check((_data),                \
                                                      (_dcap),                \
                                                      _slot_count));          \
    } while (0)

#define CBASE_DATA_DYNAMIC_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)         \
    _api int _dname##_set_length_no_zero_no_check(_dtype **data,              \
                                                  size_t *dlen,               \
                                                  size_t *dcap,               \
                                                  size_t len);                \
                                                                              \
    _api int _dname##_set_length_no_zero(_dtype **data,                       \
                                         size_t *dlen,                        \
                                         size_t *dcap,                        \
                                         size_t len);                         \
                                                                              \
    _api int _dname##_set_length_no_check(_dtype **data,                      \
                                          size_t *dlen,                       \
                                          size_t *dcap,                       \
                                          size_t len);                        \
                                                                              \
    _api int _dname##_set_length(_dtype **data,                               \
                                 size_t *dlen,                                \
                                 size_t *dcap,                                \
                                 size_t len);                                 \
                                                                              \
    _api int _dname##_set_capacity_no_zero_no_check(_dtype **data,            \
                                                    size_t *dlen,             \
                                                    size_t *dcap,             \
                                                    size_t cap);              \
                                                                              \
    _api int _dname##_set_capacity_no_zero(_dtype **data,                     \
                                           size_t *dlen,                      \
                                           size_t *dcap,                      \
                                           size_t cap);                       \
                                                                              \
    _api int _dname##_set_capacity_no_check(_dtype **data,                    \
                                            size_t *dlen,                     \
                                            size_t *dcap,                     \
                                            size_t cap);                      \
                                                                              \
    _api int _dname##_set_capacity(_dtype **data,                             \
                                   size_t *dlen,                              \
                                   size_t *dcap,                              \
                                   size_t cap);                               \
                                                                              \
    _api void _dname##_init_no_check(size_t *dlen, size_t *dcap);             \
                                                                              \
    _api int _dname##_init(size_t *dlen, size_t *dcap);                       \
                                                                              \
    _api int _dname##_init_length_no_zero_no_check(_dtype **data,             \
                                                   size_t *dlen,              \
                                                   size_t *dcap,              \
                                                   size_t dlen2);             \
                                                                              \
    _api int _dname##_init_length_no_zero(_dtype **data,                      \
                                          size_t *dlen,                       \
                                          size_t *dcap,                       \
                                          size_t dlen2);                      \
                                                                              \
    _api int _dname##_init_length_no_check(_dtype **data,                     \
                                           size_t *dlen,                      \
                                           size_t *dcap,                      \
                                           size_t dlen2);                     \
                                                                              \
    _api int _dname##_init_length(_dtype **data,                              \
                                  size_t *dlen,                               \
                                  size_t *dcap,                               \
                                  size_t dlen2);                              \
                                                                              \
    _api int _dname##_init_capacity_no_check(_dtype **data,                   \
                                             size_t *dlen,                    \
                                             size_t *dcap,                    \
                                             size_t cap);                     \
                                                                              \
    _api int _dname##_init_capacity(_dtype **data,                            \
                                    size_t *dlen,                             \
                                    size_t *dcap,                             \
                                    size_t cap);                              \
                                                                              \
    _api int _dname##_init_from_data_no_check(_dtype **data,                  \
                                              size_t *dlen,                   \
                                              size_t *dcap,                   \
                                              const _dtype *data2,            \
                                              size_t len2);                   \
                                                                              \
    _api int _dname##_init_from_data(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     size_t *dcap,                            \
                                     const _dtype *data2,                     \
                                     size_t len2);                            \
                                                                              \
    _api void _dname##_free_no_zero_no_check(_dtype *data,                    \
                                             size_t *dlen,                    \
                                             size_t *dcap);                   \
                                                                              \
    _api int _dname##_free_no_zero(_dtype *data, size_t *dlen, size_t *dcap); \
                                                                              \
    _api void _dname##_free_no_check(_dtype *data,                            \
                                     size_t *dlen,                            \
                                     size_t *dcap);                           \
                                                                              \
    _api int _dname##_free(_dtype *data, size_t *dlen, size_t *dcap);         \
                                                                              \
    _api void _dname##_destroy_no_zero_no_check(_dtype **data,                \
                                                size_t *dlen,                 \
                                                size_t *dcap);                \
                                                                              \
    _api int _dname##_destroy_no_zero(_dtype **data,                          \
                                      size_t *dlen,                           \
                                      size_t *dcap);                          \
                                                                              \
    _api void _dname##_destroy_no_check(_dtype **data,                        \
                                        size_t *dlen,                         \
                                        size_t *dcap);                        \
                                                                              \
    _api int _dname##_destroy(_dtype **data, size_t *dlen, size_t *dcap);

#define CBASE_DATA_DYNAMIC_MANAGEMENT_IMPL(_api, _dname, _dtype)              \
    _api int _dname##_ensure_capacity_no_zero_no_check(_dtype **data,         \
                                                       size_t *dcap,          \
                                                       size_t cap) {          \
        if ((*dcap) < cap) {                                                  \
            if (!(*data)) {                                                   \
                CBASE_PROPAGATE_ERROR(cb_malloc(cap, sizeof(_dtype), data));  \
            }                                                                 \
            else {                                                            \
                CBASE_PROPAGATE_ERROR(cb_realloc(cap, sizeof(_dtype), data)); \
            }                                                                 \
                                                                              \
            (*dcap) = cap;                                                    \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_ensure_capacity_no_check(_dtype **data,                 \
                                               size_t *dcap,                  \
                                               size_t cap) {                  \
        if ((*dcap) < cap) {                                                  \
            if (!(*data)) {                                                   \
                CBASE_PROPAGATE_ERROR(cb_calloc(cap, sizeof(_dtype), data));  \
            }                                                                 \
            else {                                                            \
                CBASE_PROPAGATE_ERROR(cb_realloc(cap, sizeof(_dtype), data)); \
                _dname##_zero_no_check((*data), (*dcap), cap - (*dcap));      \
            }                                                                 \
                                                                              \
            (*dcap) = cap;                                                    \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_capacity_no_zero_no_check(_dtype **data,            \
                                                    size_t *dlen,             \
                                                    size_t *dcap,             \
                                                    size_t cap) {             \
        if (cap < (*dcap)) {                                                  \
            (*dcap) = cap;                                                    \
            if (cap < (*dlen)) {                                              \
                (*dlen) = cap;                                                \
            }                                                                 \
        }                                                                     \
        else {                                                                \
            _CBASE_TRY_EXPAND_DYNAMIC_DATA_IF_NEEDED_NO_ZERO(_dname,          \
                                                             data,            \
                                                             (*dlen),         \
                                                             dcap,            \
                                                             cap);            \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_capacity_no_zero(_dtype **data,                     \
                                           size_t *dlen,                      \
                                           size_t *dcap,                      \
                                           size_t cap) {                      \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_set_capacity_no_zero_no_check(data, dlen, dcap, cap));   \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_capacity_no_check(_dtype **data,                    \
                                            size_t *dlen,                     \
                                            size_t *dcap,                     \
                                            size_t cap) {                     \
        if (cap < (*dcap)) {                                                  \
            _dname##_zero_no_check((*data), (*dcap), cap - (*dcap));          \
            (*dcap) = cap;                                                    \
            if (cap < (*dlen)) {                                              \
                (*dlen) = cap;                                                \
            }                                                                 \
        }                                                                     \
        else {                                                                \
            _CBASE_TRY_EXPAND_DYNAMIC_DATA_IF_NEEDED(_dname,                  \
                                                     data,                    \
                                                     (*dlen),                 \
                                                     dcap,                    \
                                                     cap);                    \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_capacity(_dtype **data,                             \
                                   size_t *dlen,                              \
                                   size_t *dcap,                              \
                                   size_t cap) {                              \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_set_capacity_no_check(data, dlen, dcap, cap));           \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_length_no_zero_no_check(_dtype **data,              \
                                                  size_t *dlen,               \
                                                  size_t *dcap,               \
                                                  size_t len) {               \
        if ((*dcap) < len) {                                                  \
            _CBASE_TRY_EXPAND_DYNAMIC_DATA_IF_NEEDED_NO_ZERO(_dname,          \
                                                             data,            \
                                                             (*dlen),         \
                                                             dcap,            \
                                                             len - (*dcap));  \
        }                                                                     \
                                                                              \
        (*dlen) = len;                                                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_length_no_zero(_dtype **data,                       \
                                         size_t *dlen,                        \
                                         size_t *dcap,                        \
                                         size_t len) {                        \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_set_length_no_zero_no_check(data, dlen, dcap, len));     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_length_no_check(_dtype **data,                      \
                                          size_t *dlen,                       \
                                          size_t *dcap,                       \
                                          size_t len) {                       \
        if ((*dcap) < len) {                                                  \
            _CBASE_TRY_EXPAND_DYNAMIC_DATA_IF_NEEDED(_dname,                  \
                                                     data,                    \
                                                     (*dlen),                 \
                                                     dcap,                    \
                                                     len - (*dcap));          \
        }                                                                     \
        else {                                                                \
            _dname##_zero_no_check((*data), len, (*dlen) - len);              \
        }                                                                     \
                                                                              \
        (*dlen) = len;                                                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_length(_dtype **data,                               \
                                 size_t *dlen,                                \
                                 size_t *dcap,                                \
                                 size_t len) {                                \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_set_length_no_check(data, dlen, dcap, len));             \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_init_no_check(size_t *dlen, size_t *dcap) {            \
        (*dlen) = 0;                                                          \
        (*dcap) = 0;                                                          \
    }                                                                         \
                                                                              \
    _api int _dname##_init(size_t *dlen, size_t *dcap) {                      \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
        CBASE_CHECK_LENGTH_BOUNDS((*dcap), (*dlen));                          \
                                                                              \
        _dname##_init_no_check(dlen, dcap);                                   \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_length_no_zero_no_check(_dtype **data,             \
                                                   size_t *dlen,              \
                                                   size_t *dcap,              \
                                                   size_t len) {              \
        _dname##_init_no_check(dlen, dcap);                                   \
        _CBASE_TRY_EXPAND_DYNAMIC_DATA_IF_NEEDED_NO_ZERO(_dname,              \
                                                         data,                \
                                                         (*dlen),             \
                                                         dcap,                \
                                                         len);                \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_length_no_zero(_dtype **data,                      \
                                          size_t *dlen,                       \
                                          size_t *dcap,                       \
                                          size_t len) {                       \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_length_no_zero_no_check(data, dlen, dcap, len));    \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_length_no_check(_dtype **data,                     \
                                           size_t *dlen,                      \
                                           size_t *dcap,                      \
                                           size_t len) {                      \
        _dname##_init_no_check(dlen, dcap);                                   \
        _CBASE_TRY_EXPAND_DYNAMIC_DATA_IF_NEEDED(_dname,                      \
                                                 data,                        \
                                                 (*dlen),                     \
                                                 dcap,                        \
                                                 len);                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_length(_dtype **data,                              \
                                  size_t *dlen,                               \
                                  size_t *dcap,                               \
                                  size_t len) {                               \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_length_no_check(data, dlen, dcap, len));            \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_capacity_no_zero_no_check(_dtype **data,           \
                                                     size_t *dlen,            \
                                                     size_t *dcap,            \
                                                     size_t cap) {            \
        _dname##_init_no_check(dlen, dcap);                                   \
                                                                              \
        _CBASE_TRY_EXPAND_DYNAMIC_DATA_IF_NEEDED_NO_ZERO(_dname,              \
                                                         data,                \
                                                         (*dlen),             \
                                                         dcap,                \
                                                         cap);                \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_capacity_no_zero(_dtype **data,                    \
                                            size_t *dlen,                     \
                                            size_t *dcap,                     \
                                            size_t cap) {                     \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_capacity_no_zero_no_check(data, dlen, dcap, cap));  \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_capacity_no_check(_dtype **data,                   \
                                             size_t *dlen,                    \
                                             size_t *dcap,                    \
                                             size_t cap) {                    \
        _dname##_init_no_check(dlen, dcap);                                   \
                                                                              \
        _CBASE_TRY_EXPAND_DYNAMIC_DATA_IF_NEEDED(_dname,                      \
                                                 data,                        \
                                                 (*dlen),                     \
                                                 dcap,                        \
                                                 cap);                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_capacity(_dtype **data,                            \
                                    size_t *dlen,                             \
                                    size_t *dcap,                             \
                                    size_t cap) {                             \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_capacity_no_check(data, dlen, dcap, cap));          \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_length_capacity_no_zero_no_check(_dtype **data,    \
                                                            size_t *dlen,     \
                                                            size_t *dcap,     \
                                                            size_t len,       \
                                                            size_t cap) {     \
        if (cap <= len) {                                                     \
            CBASE_DELEGATE(_dname##_init_length_no_zero_no_check(data,        \
                                                                 dlen,        \
                                                                 dcap,        \
                                                                 len));       \
        }                                                                     \
                                                                              \
        _dname##_init_no_check(dlen, dcap);                                   \
                                                                              \
        _CBASE_TRY_EXPAND_DYNAMIC_DATA_IF_NEEDED_NO_ZERO(_dname,              \
                                                         data,                \
                                                         (*dlen),             \
                                                         dcap,                \
                                                         cap);                \
                                                                              \
        (*dlen) = len;                                                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_length_capacity_no_zero(_dtype **data,             \
                                                   size_t *dlen,              \
                                                   size_t *dcap,              \
                                                   size_t len,                \
                                                   size_t cap) {              \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_length_capacity_no_zero_no_check(data,              \
                                                           dlen,              \
                                                           dcap,              \
                                                           len,               \
                                                           cap));             \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_length_capacity_no_check(_dtype **data,            \
                                                    size_t *dlen,             \
                                                    size_t *dcap,             \
                                                    size_t len,               \
                                                    size_t cap) {             \
        if (cap <= len) {                                                     \
            CBASE_DELEGATE(                                                   \
                _dname##_init_length_no_check(data, dlen, dcap, len));        \
        }                                                                     \
                                                                              \
        _dname##_init_no_check(dlen, dcap);                                   \
                                                                              \
        _CBASE_TRY_EXPAND_DYNAMIC_DATA_IF_NEEDED(_dname,                      \
                                                 data,                        \
                                                 (*dlen),                     \
                                                 dcap,                        \
                                                 cap);                        \
                                                                              \
        (*dlen) = len;                                                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_length_capacity(_dtype **data,                     \
                                           size_t *dlen,                      \
                                           size_t *dcap,                      \
                                           size_t len,                        \
                                           size_t cap) {                      \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        CBASE_PROPAGATE_ERROR(_dname##_init_length_capacity_no_check(data,    \
                                                                     dlen,    \
                                                                     dcap,    \
                                                                     len,     \
                                                                     cap));   \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_from_data_no_check(_dtype **data,                  \
                                              size_t *dlen,                   \
                                              size_t *dcap,                   \
                                              const _dtype *data2,            \
                                              size_t len2) {                  \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_capacity_no_check(data, dlen, dcap, len2));         \
                                                                              \
        _dname##_set_no_check((*data), 0, data2, len2);                       \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_init_from_data(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     size_t *dcap,                            \
                                     const _dtype *data2,                     \
                                     size_t len2) {                           \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_init_capacity(data, dlen, dcap, len2));                  \
                                                                              \
        _dname##_set_no_check((*data), 0, data2, len2);                       \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_free_no_zero_no_check(_dtype *data,                    \
                                             size_t *dlen,                    \
                                             size_t *dcap) {                  \
        cb_free(data);                                                        \
        _dname##_init_no_check(dlen, dcap);                                   \
    }                                                                         \
                                                                              \
    _api int _dname##_free_no_zero(_dtype *data,                              \
                                   size_t *dlen,                              \
                                   size_t *dcap) {                            \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        _dname##_free_no_zero_no_check(data, dlen, dcap);                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_free_no_check(_dtype *data,                            \
                                     size_t *dlen,                            \
                                     size_t *dcap) {                          \
        _dname##_zero_no_check(data, 0, (*dlen));                             \
        _dname##_free_no_zero_no_check(data, dlen, dcap);                     \
    }                                                                         \
                                                                              \
    _api int _dname##_free(_dtype *data, size_t *dlen, size_t *dcap) {        \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        _dname##_free_no_check(data, dlen, dcap);                             \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_destroy_no_zero_no_check(_dtype **data,                \
                                                size_t *dlen,                 \
                                                size_t *dcap) {               \
        _dname##_free((*data), dlen, dcap);                                   \
        *data = NULL;                                                         \
    }                                                                         \
                                                                              \
    _api int _dname##_destroy_no_zero(_dtype **data,                          \
                                      size_t *dlen,                           \
                                      size_t *dcap) {                         \
        CBASE_CHECK_DOUBLE_POINTER_ARGUMENT(data);                            \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        _dname##_destroy_no_zero_no_check(data, dlen, dcap);                  \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_destroy_no_check(_dtype **data,                        \
                                        size_t *dlen,                         \
                                        size_t *dcap) {                       \
        _dname##_zero_no_check(*data, 0, (*dlen));                            \
        _dname##_destroy_no_zero(data, dlen, dcap);                           \
    }                                                                         \
                                                                              \
    _api int _dname##_destroy(_dtype **data, size_t *dlen, size_t *dcap) {    \
        CBASE_CHECK_DOUBLE_POINTER_ARGUMENT(data);                            \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        _dname##_destroy_no_check(data, dlen, dcap);                          \
                                                                              \
        return 0;                                                             \
    }

#endif

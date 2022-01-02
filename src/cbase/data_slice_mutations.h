#pragma once

#ifndef _CBASE_DATA_SLICE_MUTATIONS_H__
#define _CBASE_DATA_SLICE_MUTATIONS_H__

/*
 * [TODO]
 * - truncate_at (uses find_*_reverse)
 */

#define CBASE_DATA_SLICE_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)            \
    _api void _dname##_skip_no_check(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     size_t count);                           \
                                                                              \
    _api int _dname##_skip(_dtype **data, size_t *dlen, size_t count);        \
                                                                              \
    _api void _dname##_seek_no_check(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     const _dtype *data2,                     \
                                     size_t dlen2);                           \
                                                                              \
    _api int _dname##_seek(_dtype **data,                                     \
                           size_t *dlen,                                      \
                           const _dtype *data2,                               \
                           size_t dlen2);                                     \
                                                                              \

#define CBASE_DATA_SLICE_MUTATIONS_IMPL(_api, _dname, _dtype)                 \
    _api void _dname##_skip_no_check(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     size_t count) {                          \
        (*data) += count;                                                     \
        (*dlen) -= count;                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_skip(_dtype **data, size_t *dlen, size_t count) {       \
        CBASE_CHECK_DOUBLE_POINTER_ARGUMENT(data);                            \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_LENGTH_BOUNDS(*dlen, count);                              \
                                                                              \
        (*data) += count;                                                     \
        (*dlen) -= count;                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_seek_no_check(_dtype **data,                           \
                                     size_t *dlen,                            \
                                     const _dtype *data2,                     \
                                     size_t dlen2) {                          \
        _dtype *saved_data = (*data);                                         \
                                                                              \
        _dname##_find_no_check((*data), (*dlen), 0, data2, dlen2, data);      \
                                                                              \
        (*dlen) -= (data - saved_data);                                       \
    }                                                                         \
                                                                              \
    _api int _dname##_seek(_dtype **data,                                     \
                           size_t *dlen,                                      \
                           const _dtype *data2,                               \
                           size_t dlen2) {                                    \
        _dtype *saved_data = (*data);                                         \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_find((*data), dlen, 0, data2, dlen2, data)               \
        );                                                                    \
                                                                              \
        CBASE_DELEGATE(cb_safe_ptrdiff((*data), saved_data, (*dlen)))         \
    }

#endif

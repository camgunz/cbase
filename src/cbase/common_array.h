#pragma once

#ifndef _CBASE_COMMON_ARRAY_H__
#define _CBASE_COMMON_ARRAY_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/common_data.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#define CBASE_COMMON_ARRAY_IMPL_DECL(_api, _aname, _atype, _etype)            \
    _api const _etype *_aname##_index_no_check(const _atype *array,           \
                                               size_t index);                 \
                                                                              \
    _api int _aname##_index(const _atype *array,                              \
                            size_t index,                                     \
                            _etype const **element);                          \
                                                                              \
    _api void _aname##_slice_no_check(const _atype *array,                    \
                                      size_t index,                           \
                                      size_t count,                           \
                                      _dtype **data,                          \
                                      size_t *dlen);                          \
                                                                              \
    _api int _aname##_slice(const _atype *array,                              \
                            size_t index,                                     \
                            size_t count,                                     \
                            _dtype **data,                                    \
                            size_t *dlen);                                    \
                                                                              \
    _api void _aname##_copy_no_check(const _atype *array,                     \
                                     size_t index,                            \
                                     size_t count,                            \
                                     _etype *data);                           \
                                                                              \
    _api int _aname##_copy(const _atype *array,                               \
                           size_t index,                                      \
                           size_t count,                                      \
                           _etype *data,                                      \
                           size_t dlen);                                      \
                                                                              \
    _api void _aname##_truncate_no_zero_no_check(_atype *array,               \
                                                 size_t new_length);          \
                                                                              \
    _api int _aname##_truncate_no_zero(_atype *array, size_t new_length);     \
                                                                              \
    _api bool _aname##_equals_no_check(const _atype *array,                   \
                                       size_t index,                          \
                                       const _etype *data,                    \
                                       size_t dlen);                          \
                                                                              \
    _api int _aname##_equals(const _atype *array,                             \
                             size_t index,                                    \
                             const _etype *data,                              \
                             size_t dlen,                                     \
                             bool *equal);                                    \
                                                                              \
    _api bool _aname##_starts_with_no_check(const _atype *array,              \
                                            const _etype *data,               \
                                            size_t dlen);                     \
                                                                              \
    _api int _aname##_starts_with(const _atype *array,                        \
                                  const _etype *data,                         \
                                  size_t dlen,                                \
                                  bool *equal);                               \
                                                                              \
    _api bool _aname##_ends_with_no_check(const _atype *array,                \
                                          const _etype *data,                 \
                                          size_t dlen);                       \
                                                                              \
    _api int _aname##_ends_with(const _atype *array,                          \
                                const _etype *data,                           \
                                size_t dlen,                                  \
                                bool *equal);                                 \
                                                                              \
    _api void _aname##_find_no_check(const _atype *array,                     \
                                     size_t index,                            \
                                     const _etype *data,                      \
                                     size_t dlen,                             \
                                     _etype **cursor);                        \
                                                                              \
    _api int _aname##_find(const _atype *array,                               \
                           size_t index,                                      \
                           const _etype *data,                                \
                           size_t dlen,                                       \
                           _etype **cursor);                                  \
                                                                              \
    _api void _aname##_find_index_no_check(const _atype *array,               \
                                           size_t index,                      \
                                           const _etype *data,                \
                                           size_t dlen,                       \
                                           size_t *location);                 \
                                                                              \
    _api int _aname##_find_index(const _atype *array,                         \
                                 size_t index,                                \
                                 const _etype *data,                          \
                                 size_t dlen,                                 \
                                 size_t *location);                           \
                                                                              \
    _api void _aname##_clear_no_zero_no_check(_atype *array);                 \
                                                                              \
    _api int _aname##_clear_no_zero(_atype *array);

#define CBASE_COMMON_ARRAY_IMPL_DEPS(_api, _dname, _etype)                    \
    CBASE_COMMON_DATA_IMPL(_api, _dname, _etype)

#define CBASE_COMMON_ARRAY_IMPL_NO_DEPS(_api, _dname, _aname, _atype, _etype) \
    _api const _etype *_aname##_index_no_check(const _atype *array,           \
                                               size_t index) {                \
        CBASE_DELEGATE(_dname##_index_no_check(array->data, index));          \
    }                                                                         \
                                                                              \
    _api int _aname##_index(_atype *array,                                    \
                            size_t index,                                     \
                            _etype const **element) {                         \
        CBASE_DELEGATE(                                                       \
            _dname##_index(array->data, array->len, index, element));         \
    }                                                                         \
                                                                              \
    _api void _aname##_slice_no_check(const _atype *array,                    \
                                      size_t index,                           \
                                      size_t count,                           \
                                      _dtype **data,                          \
                                      size_t *dlen) {                         \
        _dname##_slice_no_check(array->data,                                  \
                                array->len,                                   \
                                index,                                        \
                                count,                                        \
                                data,                                         \
                                dlen);                                        \
    }                                                                         \
                                                                              \
    _api int _aname##_slice(const _atype *array,                              \
                            size_t index,                                     \
                            size_t len,                                       \
                            _dtype **data,                                    \
                            size_t *dlen) {                                   \
        CBASE_DELEGATE(_dname##_slice(array->data,                            \
                                      array->len,                             \
                                      index,                                  \
                                      count,                                  \
                                      data,                                   \
                                      dlen));                                 \
    }                                                                         \
                                                                              \
    _api void _aname##_copy_no_check(const _atype *array,                     \
                                     size_t index,                            \
                                     size_t count,                            \
                                     _etype *data) {                          \
        _dname##_copy_no_check(array->data, index, count, data);              \
    }                                                                         \
                                                                              \
    _api int _aname##_copy(const _atype *array,                               \
                           size_t index,                                      \
                           size_t count,                                      \
                           _etype *data,                                      \
                           size_t dlen) {                                     \
        CBASE_DELEGATE(_dname##_copy(array->data,                             \
                                     array->len,                              \
                                     index,                                   \
                                     count,                                   \
                                     data,                                    \
                                     dlen));                                  \
    }                                                                         \
                                                                              \
    _api void _aname##_truncate_no_zero_no_check(_atype *array,               \
                                                 size_t new_length) {         \
        _dname##_truncate_no_zero_no_check(&array->len, new_length);          \
    }                                                                         \
                                                                              \
    _api int _aname##_truncate_no_zero(_atype *array, size_t new_length) {    \
        CBASE_DELEGATE(_dname##_truncate_no_zero(&array->len, new_length));   \
    }                                                                         \
                                                                              \
    _api bool _aname##_equals_no_check(const _atype *array,                   \
                                       size_t index,                          \
                                       const _etype *data,                    \
                                       size_t dlen) {                         \
        return _dname##_equals_no_check(array->data,                          \
                                        array->len,                           \
                                        index,                                \
                                        data,                                 \
                                        dlen);                                \
    }                                                                         \
                                                                              \
    _api int _aname##_equals(const _atype *array,                             \
                             size_t index,                                    \
                             const _etype *data,                              \
                             size_t dlen,                                     \
                             bool *equal) {                                   \
        CBASE_DELEGATE(_dname##_equals(array->data,                           \
                                       array->len,                            \
                                       index,                                 \
                                       data,                                  \
                                       dlen,                                  \
                                       equal));                               \
    }                                                                         \
                                                                              \
    _api bool _aname##_starts_with_no_check(const _atype *array,              \
                                            const _etype *data,               \
                                            size_t dlen) {                    \
        return _dname##_starts_with_no_check(array->data,                     \
                                             array->len,                      \
                                             data,                            \
                                             dlen);                           \
    }                                                                         \
                                                                              \
    _api int _aname##_starts_with(const _atype *array,                        \
                                  const _etype *data,                         \
                                  size_t dlen,                                \
                                  bool *equal) {                              \
        CBASE_DELEGATE(_dname##_starts_with(array->data,                      \
                                            array->len,                       \
                                            data,                             \
                                            dlen,                             \
                                            equal));                          \
    }                                                                         \
                                                                              \
    _api bool _aname##_ends_with_no_check(const _atype *array,                \
                                          const _etype *data,                 \
                                          size_t dlen) {                      \
        return _dname##_ends_with_no_check(array->data,                       \
                                           array->len,                        \
                                           data,                              \
                                           dlen);                             \
    }                                                                         \
                                                                              \
    _api int _aname##_ends_with(const _atype *array,                          \
                                const _etype *data,                           \
                                size_t dlen,                                  \
                                bool *equal) {                                \
        CBASE_DELEGATE(                                                       \
            _dname##_ends_with(array->data, array->len, data, dlen, equal));  \
    }                                                                         \
                                                                              \
    _api void _aname##_find_no_check(const _atype *array,                     \
                                     size_t index,                            \
                                     const _etype *data,                      \
                                     size_t dlen,                             \
                                     _etype **cursor) {                       \
        _dname##_find_no_check(array->data,                                   \
                               array->len,                                    \
                               index,                                         \
                               data,                                          \
                               dlen,                                          \
                               cursor);                                       \
    }                                                                         \
                                                                              \
    _api int _aname##_find(const _atype *array,                               \
                           size_t index,                                      \
                           const _etype *data,                                \
                           size_t dlen,                                       \
                           _etype **cursor) {                                 \
        CBASE_DELEGATE(_dname##_find(array->data,                             \
                                     array->len,                              \
                                     index,                                   \
                                     data,                                    \
                                     dlen,                                    \
                                     cursor));                                \
    }                                                                         \
                                                                              \
    _api void _aname##_find_index_no_check(const _atype *array,               \
                                           size_t index,                      \
                                           const _etype *data,                \
                                           size_t dlen,                       \
                                           size_t *location) {                \
        _dname##_find_index_no_check(array->data,                             \
                                     array->len,                              \
                                     index,                                   \
                                     data,                                    \
                                     dlen,                                    \
                                     location);                               \
    }                                                                         \
                                                                              \
    _api int _aname##_find_index(const _atype *array,                         \
                                 size_t index,                                \
                                 const _etype *data,                          \
                                 size_t dlen,                                 \
                                 size_t *location) {                          \
        CBASE_DELEGATE(_dname##_find_index(array->data,                       \
                                           array->len,                        \
                                           index,                             \
                                           data,                              \
                                           dlen,                              \
                                           location));                        \
    }                                                                         \
                                                                              \
    _api void _aname##_clear_no_zero_no_check(_atype *array) {                \
        _dname##_clear_no_zero_no_check(&array->len);                         \
    }                                                                         \
                                                                              \
    _api int _aname##_clear_no_zero(_atype *array) {                          \
        CBASE_DELEGATE(_dname##_clear_no_zero(&array->len));                  \
    }

#define CBASE_COMMON_ARRAY_IMPL(_api, _dname, _aname, _atype, _etype)         \
    CBASE_COMMON_ARRAY_IMPL_DEPS(_api, _dname, _etype)                        \
    CBASE_COMMON_ARRAY_IMPL_NO_DEPS(_api, _dname, _aname, _atype, _etype)

#endif

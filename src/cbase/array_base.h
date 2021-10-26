#pragma once

#ifndef _CBASE_ARRAY_BASE_H__
#define _CBASE_ARRAY_BASE_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "cbase/data_base.h"

#define CBASE_ARRAY_BASE_IMPL_DECL(_api, _dname, _etype, _aname, _atype)      \
    _api const _etype *_aname##_index_no_check(const _atype *array,           \
                                               size_t index);                 \
                                                                              \
    _api int _aname##_index(_atype *array,                                    \
                            size_t index,                                     \
                            _etype const **element);                          \
                                                                              \
    _api void _aname##_slice_no_check(const _atype *array,                    \
                                      size_t index,                           \
                                      size_t len,                             \
                                      _etype **data,                          \
                                      size_t *dlen);                          \
                                                                              \
    _api int _aname##_slice(const _atype *array,                              \
                            size_t index,                                     \
                            size_t len,                                       \
                            _etype **data,                                    \
                            size_t *dlen);                                    \
                                                                              \
    _api void _aname##_copy_no_check(const _atype *array,                     \
                                     size_t index,                            \
                                     size_t count,                            \
                                     _atype *array2);                         \
                                                                              \
    _api int _aname##_copy(const _atype *array,                               \
                           size_t index,                                      \
                           size_t count,                                      \
                           _atype *array2)                                    \
                                                                              \
        _api bool _aname##_equals_no_check(const _atype *array,               \
                                           size_t index,                      \
                                           const _atype *array2);             \
                                                                              \
    _api int _aname##_equals(const _atype *array,                             \
                             size_t index,                                    \
                             const _atype *array2,                            \
                             bool *equal);                                    \
                                                                              \
    _api bool _aname##_starts_with_no_check(const _atype *array,              \
                                            const _atype *array2);            \
                                                                              \
    _api int _aname##_starts_with(const _atype *array,                        \
                                  const _atype *array2,                       \
                                  bool *equal);                               \
                                                                              \
    _api bool _aname##_ends_with_no_check(const _atype *array,                \
                                          const _atype *array2);              \
                                                                              \
    _api int _aname##_ends_with(const _atype *array,                          \
                                const _atype *array2,                         \
                                bool *equal);                                 \
                                                                              \
    _api void _aname##_find_no_check(const _atype *array,                     \
                                     size_t index,                            \
                                     const _atype *array2,                    \
                                     _etype **cursor);                        \
                                                                              \
    _api int _aname##_find(const _atype *array,                               \
                           size_t index,                                      \
                           const _atype *array2,                              \
                           _etype **cursor);                                  \
                                                                              \
    _api void _aname##_find_index_no_check(const _atype *array,               \
                                           size_t index,                      \
                                           const _atype *array2,              \
                                           size_t *location);                 \
                                                                              \
    _api int _aname##_find_index(const _atype *array,                         \
                                 size_t index,                                \
                                 const _atype *array2,                        \
                                 size_t *location);

#define CBASE_ARRAY_BASE_IMPL(_api, _dname, _etype, _aname, atype)            \
    _api const _etype *_aname##_index_no_check(const _atype *array,           \
                                               size_t index) {                \
        CBASE_DELEGATE(_dname##_index_no_check(array->data, index));          \
    }                                                                         \
                                                                              \
    _api int _aname##_index(_atype *array,                                    \
                            size_t index,                                     \
                            _etype const **element) {                         \
        CBASE_DELEGATE(_dname##_index(array->data, array->len, element));     \
    }                                                                         \
                                                                              \
    _api void _aname##_slice_no_check(const _atype *array,                    \
                                      size_t index,                           \
                                      size_t len,                             \
                                      _etype **data,                          \
                                      size_t *dlen) {                         \
        _dname##_slice_no_check(array->data, index, len, data, dlen);         \
    }                                                                         \
                                                                              \
    _api int _aname##_slice(const _atype *array,                              \
                            size_t index,                                     \
                            size_t len,                                       \
                            _etype **data,                                    \
                            size_t *dlen) {                                   \
        CBASE_DELEGATE(_dname##_slice(array->data, index, len, data, dlen));  \
    }                                                                         \
                                                                              \
    _api void _aname##_copy_no_check(const _atype *array,                     \
                                     size_t index,                            \
                                     size_t count,                            \
                                     _atype *array2) {                        \
        _dname##_copy_no_check(array->data, index, count, array2->data);      \
    }                                                                         \
                                                                              \
    _api int _aname##_copy(const _atype *array,                               \
                           size_t index,                                      \
                           size_t count,                                      \
                           _atype *array2) {                                  \
        CBASE_DELEGATE(_dname##_copy(array->data,                             \
                                     array->len,                              \
                                     index,                                   \
                                     count,                                   \
                                     array2->data,                            \
                                     array2->len));                           \
    }                                                                         \
                                                                              \
    _api int _aname##_equals(const _atype *array,                             \
                             size_t index,                                    \
                             const _atype *array2,                            \
                             bool *equal) {                                   \
        CBASE_DELEGATE(_dname##_equals(array->data,                           \
                                       array->len,                            \
                                       index,                                 \
                                       array2->data,                          \
                                       array2->len,                           \
                                       equal));                               \
    }                                                                         \
                                                                              \
    _api bool _aname##_starts_with_no_check(const _atype *array,              \
                                            const _atype *array2) {           \
        CBASE_DELEGATE(_dname##_starts_with_no_check(array->data,             \
                                                     array->len,              \
                                                     array2->data,            \
                                                     array2->len));           \
    }                                                                         \
                                                                              \
    _api int _aname##_starts_with(const _atype *array,                        \
                                  const _atype *array2,                       \
                                  bool *equal) {                              \
        CBASE_DELEGATE(_dname##_starts_with(array->data,                      \
                                            array->len,                       \
                                            array2->data,                     \
                                            array2->len,                      \
                                            equal));                          \
    }                                                                         \
                                                                              \
    _api bool _aname##_ends_with_no_check(const _atype *array,                \
                                          const _atype *array2) {             \
        CBASE_DELEGATE(_dname##_ends_with_no_check(array->data,               \
                                                   array->len,                \
                                                   array2->data,              \
                                                   array2->len));             \
    }                                                                         \
                                                                              \
    _api int _aname##_ends_with(const _atype *array,                          \
                                const _atype *array2,                         \
                                bool *equal) {                                \
        CBASE_DELEGATE(_dname##_ends_with(array->data,                        \
                                          array->len,                         \
                                          array2->data,                       \
                                          array2->len,                        \
                                          equal));                            \
    }                                                                         \
                                                                              \
    _api void _aname##_find_no_check(const _atype *array,                     \
                                     size_t index,                            \
                                     const _atype *array2,                    \
                                     _etype **cursor) {                       \
        _dname##_find_no_check(array->data,                                   \
                               array->len,                                    \
                               index,                                         \
                               array2->data,                                  \
                               array2->len,                                   \
                               cursor);                                       \
    }                                                                         \
                                                                              \
    _api int _aname##_find(const _atype *array,                               \
                           size_t index,                                      \
                           const _atype *array2,                              \
                           _etype **cursor) {                                 \
        CBASE_DELEGATE(_dname##_find(array->data,                             \
                                     array->len,                              \
                                     index,                                   \
                                     array2->data,                            \
                                     array2->len,                             \
                                     cursor));                                \
    }                                                                         \
                                                                              \
    _api void _aname##_find_index_no_check(const _atype *array,               \
                                           size_t index,                      \
                                           const _atype *array2,              \
                                           size_t *location) {                \
        _dname##_find_index_no_check(array->data,                             \
                                     array->len,                              \
                                     index,                                   \
                                     array2->data,                            \
                                     array2->len,                             \
                                     location);                               \
    }                                                                         \
                                                                              \
    _api int _aname##_find_index(const _atype *array,                         \
                                 size_t index,                                \
                                 const _atype *array2,                        \
                                 size_t *location) {                          \
        CBASE_DELEGATE(_dname##_find_index(array->data,                       \
                                           array->len,                        \
                                           index,                             \
                                           array2->data,                      \
                                           array2->len,                       \
                                           location));                        \
    }

#endif

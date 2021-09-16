#pragma once

#ifndef SLICE_H__
#define SLICE_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>

#include "cbase/errors.h"
#include "cbase/alloc.h"
#include "cbase/util.h"

#define _SLICE_CHECK_INDEX_BOUNDS(_slice, _index) \
    CBASE_ERROR_IF((_index) >= (_slice)->len, CBASE_ERROR_OUT_OF_BOUNDS)

#define _SLICE_CHECK_LENGTH_BOUNDS(_slice, _len) \
    CBASE_ERROR_IF((_len) > (_slice)->len, CBASE_ERROR_OUT_OF_BOUNDS)

#define CBASE_SLICE_DECL(_stype, _etype) \
    typedef struct _stype ## Struct {    \
        size_t len;                      \
        _etype *data;                    \
    } _stype;

#define CBASE_SLICE_IMPL_DECL(_stype, _sname, _etype)                         \
    void _sname ## _assign(_stype *slice, _etype *data, size_t len);          \
                                                                              \
    void _sname ## _assign_ ## _sname(_stype *dst, _stype *src);              \
                                                                              \
    void _sname ## _truncate_fast(_stype *slice, size_t len);                 \
                                                                              \
    int _sname ## _truncate(_stype *slice, size_t len);                       \
                                                                              \
    void _sname ## _skip_fast(_stype *slice, size_t count);                   \
                                                                              \
    int _sname ## _skip(_stype *slice, size_t count);                         \
                                                                              \
    _etype* _sname ## _index_fast(_stype *slice, size_t index);               \
                                                                              \
    int _sname ## _index(_stype *slice, size_t index, _etype **element);      \
                                                                              \
    bool _sname ## _equals_data_fast(_stype *slice, size_t index,             \
                                                    const _etype *data,       \
                                                    size_t len);              \
                                                                              \
    int _sname ## _equals_data(_stype *slice, size_t index,                   \
                                              const _etype *data,             \
                                              size_t len,                     \
                                              bool *equal);                   \
                                                                              \
    bool _sname ## _starts_with_data_fast(_stype *slice, const _etype *data,  \
                                                         size_t len);         \
                                                                              \
    int  _sname ## _starts_with_data(_stype *slice, const _etype *data,       \
                                                    size_t len,               \
                                                    bool *equal);             \
                                                                              \
    bool _sname ## _ends_with_data_fast(_stype *slice, const _etype *data,    \
                                                       size_t len);           \
                                                                              \
    int _sname ## _ends_with_data(_stype *slice, const _etype *data,          \
                                                 size_t len,                  \
                                                 bool *equal);                \
                                                                              \
    void _sname ## _find_data_fast(_stype *slice, size_t index,               \
                                                  const _etype *data,         \
                                                  size_t len,                 \
                                                  size_t *location);          \
                                                                              \
    int _sname ## _find_data(_stype *slice, size_t index, const _etype *data, \
                                                          size_t len,         \
                                                          size_t *location);  \
                                                                              \
    int _sname ## _seek_to_data(_stype *slice, size_t index,                  \
                                               const _etype *data,            \
                                               size_t len);                   \
                                                                              \
    void _sname ## _copy_data_fast(_stype *slice, size_t index,               \
                                                  size_t count,               \
                                                  _etype *data);              \
                                                                              \
    int _sname ## _copy_data(_stype *slice, size_t index,                     \
                                            size_t count,                     \
                                            _etype *data);                    \
                                                                              \
    void _sname ## _copy_element_fast(_stype *slice, size_t index,            \
                                                     _etype *element);        \
                                                                              \
    int _sname ## _copy_element(_stype *slice, size_t index,                  \
                                               _etype *element);              \
                                                                              \
    void _sname ## _pop_left_fast(_stype *slice, _etype *element);            \
                                                                              \
    int _sname ## _pop_left(_stype *slice, _etype *element);                  \
                                                                              \
    void _sname ## _pop_right_fast(_stype *slice, _etype *element);           \
                                                                              \
    int _sname ## _pop_right(_stype *slice, _etype *element);                 \
                                                                              \
    void _sname ## _clear(_stype *slice);

#define CBASE_SLICE_BASE_IMPL(_scope, _stype, _sname, _etype)                 \
    _scope                                                                    \
    void _sname ## _assign(_stype *slice, _etype *data, size_t len) {         \
        slice->data = data;                                                   \
        slice->len = len;                                                     \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    void _sname ## _assign_ ## _sname(_stype *dst, _stype *src) {             \
        dst->data = src->data;                                                \
        dst->len = src->len;                                                  \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    _etype* _sname ## _index_fast(_stype *slice, size_t index) {              \
        return slice->data + index;                                           \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    int _sname ## _index(_stype *slice, size_t index, _etype **element) {     \
        _SLICE_CHECK_INDEX_BOUNDS(slice, index);                              \
                                                                              \
        *element = _sname ## _index_fast(slice, index);                       \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    void _sname ## _skip_fast(_stype *slice, size_t count) {                  \
        slice->data += count;                                                 \
        slice->len -= count;                                                  \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    int _sname ## _skip(_stype *slice, size_t count) {                        \
        _SLICE_CHECK_LENGTH_BOUNDS(slice, count);                             \
                                                                              \
        _sname ## _skip_fast(slice, count);                                   \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    void _sname ## _truncate_fast(_stype *slice, size_t len) {                \
        slice->len = len;                                                     \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    int _sname ## _truncate(_stype *slice, size_t len) {                      \
        _SLICE_CHECK_LENGTH_BOUNDS(slice, len);                               \
                                                                              \
        _sname ## _truncate_fast(slice, len);                                 \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    bool _sname ## _equals_data_fast(_stype *slice, size_t index,             \
                                                    const _etype *data,       \
                                                    size_t len) {             \
        return (                                                              \
            (slice->len - index == len) &&                                    \
            memcmp(_sname ## _index_fast(slice, index), data, len) == 0       \
        );                                                                    \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    int _sname ## _equals_data(_stype *slice, size_t index,                   \
                                              const _etype *data,             \
                                              size_t len,                     \
                                              bool *equal) {                  \
        _SLICE_CHECK_INDEX_BOUNDS(slice, index);                              \
        _SLICE_CHECK_LENGTH_BOUNDS(slice, (index + len));                     \
                                                                              \
        *equal = _sname ## _equals_data_fast(slice, index, data, len);        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    bool _sname ## _starts_with_data_fast(_stype *slice, const _etype *data,  \
                                                         size_t len) {        \
        return _sname ## _equals_data_fast(slice, 0, data, len);              \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    int  _sname ## _starts_with_data(_stype *slice, const _etype *data,       \
                                                    size_t len,               \
                                                    bool *equal) {            \
        CBASE_PROPAGATE_ERROR(                                                \
            _sname ## _equals_data(slice, 0, data, len, equal);               \
        );                                                                    \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    bool _sname ## _ends_with_data_fast(_stype *slice, const _etype *data,    \
                                                       size_t len) {          \
        return _sname ## _equals_data_fast(slice, slice->len - len, data,     \
                                                                    len);     \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    int _sname ## _ends_with_data(_stype *slice, const _etype *data,          \
                                                 size_t len,                  \
                                                 bool *equal) {               \
        _SLICE_CHECK_LENGTH_BOUNDS(slice, len);                               \
                                                                              \
        *equal = _sname ## _ends_with_data_fast(slice, data, len);            \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    void _sname ## _find_data_fast(_stype *slice, size_t index,               \
                                                  const _etype *data,         \
                                                  size_t len,                 \
                                                  size_t *location) {         \
        _etype *cursor = NULL;                                                \
                                                                              \
        cbmemmem_fast(slice->data + index, slice->len - index,                \
                                           data,                              \
                                           len,                               \
                                           (void **)&cursor);                 \
                                                                              \
        *location = positive_ptrdiff(cursor, slice->data);                    \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    int _sname ## _find_data(_stype *slice, size_t index, const _etype *data, \
                                                          size_t len,         \
                                                          size_t *location) { \
        _SLICE_CHECK_INDEX_BOUNDS(slice, index);                              \
        _SLICE_CHECK_LENGTH_BOUNDS(slice, (index + len));                     \
                                                                              \
        _etype *cursor = NULL;                                                \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            cbmemmem(slice->data + index, slice->len - index,                 \
                                          data,                               \
                                          len,                                \
                                          (void **)&cursor)                   \
        );                                                                    \
                                                                              \
        *location = positive_ptrdiff(cursor, slice->data);                    \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    int _sname ## _seek_to_data(_stype *slice, size_t index,                  \
                                               const _etype *data,            \
                                               size_t len) {                  \
        size_t location = 0;                                                  \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _sname ## _find_data(slice, index, data, len, &location)          \
        );                                                                    \
                                                                              \
        _sname ## _skip_fast(slice, index + location);                        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    void _sname ## _copy_data_fast(_stype *slice, size_t index,               \
                                                  size_t count,               \
                                                  _etype *data) {             \
        cbbase_memmove(data, _sname ## _index_fast(slice, index),             \
                              count * sizeof(_etype));                        \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    int _sname ## _copy_data(_stype *slice, size_t index,                     \
                                            size_t count,                     \
                                            _etype *data) {                   \
        _SLICE_CHECK_INDEX_BOUNDS(slice, index);                              \
        _SLICE_CHECK_LENGTH_BOUNDS(slice, (index + count));                   \
                                                                              \
        if (count == 0) {                                                     \
            return 0;                                                         \
        }                                                                     \
                                                                              \
        _sname ## _copy_data_fast(slice, index, count, data);                 \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    void _sname ## _copy_element_fast(_stype *slice, size_t index,            \
                                                     _etype *element) {       \
        _sname ## _copy_data_fast(slice, index, 1, element);                  \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    int _sname ## _copy_element(_stype *slice, size_t index,                  \
                                               _etype *element) {             \
        _SLICE_CHECK_INDEX_BOUNDS(slice, index);                              \
                                                                              \
        _sname ## _copy_data_fast(slice, index, 1, element);                  \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    void _sname ## _pop_left_fast(_stype *slice, _etype *element) {           \
        _sname ## _copy_element_fast(slice, 0, element);                      \
        _sname ## _skip_fast(slice, 1);                                       \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    int _sname ## _pop_left(_stype *slice, _etype *element) {                 \
        CBASE_PROPAGATE_ERROR(_sname ## _copy_element(slice, 0, element));    \
        CBASE_PROPAGATE_ERROR(_sname ## _skip(slice, 1));                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    void _sname ## _pop_right_fast(_stype *slice, _etype *element) {          \
        _sname ## _copy_element_fast(slice, slice->len - 1, element);         \
        _sname ## _truncate_fast(slice, slice->len - 1);                      \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    int _sname ## _pop_right(_stype *slice, _etype *element) {                \
        CBASE_PROPAGATE_ERROR(                                                \
            _sname ## _copy_element(slice, slice->len - 1, element)           \
        );                                                                    \
        CBASE_PROPAGATE_ERROR(_sname ## _truncate(slice, slice->len - 1));    \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _scope                                                                    \
    void _sname ## _clear(_stype *slice) {                                    \
        slice->data = NULL;                                                   \
        slice->len = 0;                                                       \
    }

#define CBASE_SLICE_EXTERN_IMPL(_stype, _sname, _etype) \
    CBASE_SLICE_BASE_IMPL(CBASE_IMPL_EXTERN, _stype, _sname, _etype)

#define CBASE_SLICE_STATIC_IMPL(_stype, _sname, _etype) \
    CBASE_SLICE_BASE_IMPL(CBASE_IMPL_STATIC, _stype, _sname, _etype)

#define CBASE_SLICE_STATIC_DEF(_stype, _sname, _etype) \
    CBASE_SLICE_DECL(_stype, _etype)                   \
    CBASE_SLICE_STATIC_IMPL(_stype, _sname, _etype)

#endif

/* vi: set et ts=4 sw=4: */

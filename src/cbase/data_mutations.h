#pragma once

#ifndef _CBASE_DATA_MUTATIONS_H__
#define _CBASE_DATA_MUTATIONS_H__

#define CBASE_DATA_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)                  \
    _api _dtype *_dname##_mutable_index_no_check(_dtype *data, size_t index); \
                                                                              \
    _api int _dname##_mutable_index(_dtype *data,                             \
                                    size_t dlen,                              \
                                    size_t index,                             \
                                    _dtype **element);                        \
                                                                              \
    _api void _dname##_zero_no_check(_dtype *data,                            \
                                     size_t index,                            \
                                     size_t count);                           \
                                                                              \
    _api int _dname##_zero(_dtype *data,                                      \
                           size_t dlen,                                       \
                           size_t index,                                      \
                           size_t count);                                     \
                                                                              \
    _api void _dname##_compact_no_check(size_t dlen, size_t *dcap);           \
                                                                              \
    _api int _dname##_compact(size_t dlen, size_t *dcap);                     \
                                                                              \
    _api void _dname##_set_no_check(_dtype *data,                             \
                                    size_t index,                             \
                                    const _dtype *data2,                      \
                                    size_t count);                            \
                                                                              \
    _api int _dname##_set(_dtype *data,                                       \
                          size_t dlen,                                        \
                          size_t index,                                       \
                          const _dtype *data2,                                \
                          size_t count);                                      \
                                                                              \
    _api void _dname##_move_left_no_zero_no_check(_dtype *data,               \
                                                  size_t *dlen,               \
                                                  size_t index,               \
                                                  size_t count);              \
                                                                              \
    _api int _dname##_move_left_no_zero(_dtype *data,                         \
                                        size_t *dlen,                         \
                                        size_t index,                         \
                                        size_t count);                        \
                                                                              \
    _api void _dname##_move_left_no_check(_dtype *data,                       \
                                          size_t *dlen,                       \
                                          size_t index,                       \
                                          size_t count);                      \
                                                                              \
    _api int _dname##_move_left(_dtype *data,                                 \
                                size_t *dlen,                                 \
                                size_t index,                                 \
                                size_t count);                                \
                                                                              \
    _api void _dname##_delete_no_zero_no_check(_dtype *data,                  \
                                               size_t *dlen,                  \
                                               size_t index,                  \
                                               size_t count);                 \
                                                                              \
    _api int _dname##_delete_no_zero(_dtype *data,                            \
                                     size_t *dlen,                            \
                                     size_t index,                            \
                                     size_t count);                           \
                                                                              \
    _api void _dname##_delete_no_check(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       size_t index,                          \
                                       size_t count);                         \
                                                                              \
    _api int _dname##_delete(_dtype *data,                                    \
                             size_t *dlen,                                    \
                             size_t index,                                    \
                             size_t count);                                   \
                                                                              \
    _api void _dname##_delete_until_no_zero_no_check(_dtype *data,            \
                                                     size_t *dlen,            \
                                                     size_t index,            \
                                                     const _dtype *data2,     \
                                                     size_t dlen2);           \
                                                                              \
    _api int _dname##_delete_until_no_zero(_dtype *data,                      \
                                           size_t *dlen,                      \
                                           size_t index,                      \
                                           const _dtype *data2,               \
                                           size_t dlen2);                     \
                                                                              \
    _api void _dname##_delete_until_no_check(_dtype *data,                    \
                                             size_t *dlen,                    \
                                             size_t index,                    \
                                             const _dtype *data2,             \
                                             size_t dlen2);                   \
                                                                              \
    _api int _dname##_delete_until(_dtype *data,                              \
                                   size_t *dlen,                              \
                                   size_t index,                              \
                                   const _dtype *data2,                       \
                                   size_t dlen2);                             \
                                                                              \
    _api void _dname##_delete_unordered_no_zero_no_check(_dtype *data,        \
                                                         size_t *dlen,        \
                                                         size_t index,        \
                                                         size_t count);       \
                                                                              \
    _api int _dname##_delete_unordered_no_zero(_dtype *data,                  \
                                               size_t *dlen,                  \
                                               size_t index,                  \
                                               size_t count);                 \
                                                                              \
    _api void _dname##_delete_unordered_no_check(_dtype *data,                \
                                                 size_t *dlen,                \
                                                 size_t index,                \
                                                 size_t count);               \
                                                                              \
    _api int _dname##_delete_unordered(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       size_t index,                          \
                                       size_t count);                         \
                                                                              \
    _api void _dname##_pop_no_zero_no_check(_dtype *data,                     \
                                            size_t *dlen,                     \
                                            size_t index,                     \
                                            _dtype *element);                 \
                                                                              \
    _api int _dname##_pop_no_zero(_dtype *data,                               \
                                  size_t *dlen,                               \
                                  size_t index,                               \
                                  _dtype *element);                           \
                                                                              \
    _api void _dname##_pop_no_check(_dtype *data,                             \
                                    size_t *dlen,                             \
                                    size_t index,                             \
                                    _dtype *element);                         \
                                                                              \
    _api int _dname##_pop(_dtype *data,                                       \
                          size_t *dlen,                                       \
                          size_t index,                                       \
                          _dtype *element);                                   \
                                                                              \
    _api void _dname##_pop_unordered_no_zero_no_check(_dtype *data,           \
                                                      size_t *dlen,           \
                                                      size_t index,           \
                                                      _dtype *element);       \
                                                                              \
    _api int _dname##_pop_unordered_no_zero(_dtype *data,                     \
                                            size_t *dlen,                     \
                                            size_t index,                     \
                                            _dtype *element);                 \
                                                                              \
    _api void _dname##_pop_unordered_no_check(_dtype *data,                   \
                                              size_t *dlen,                   \
                                              size_t index,                   \
                                              _dtype *element);               \
                                                                              \
    _api int _dname##_pop_unordered(_dtype *data,                             \
                                    size_t *dlen,                             \
                                    size_t index,                             \
                                    _dtype *element);                         \
                                                                              \
    _api void _dname##_pop_left_no_zero_no_check(_dtype *data,                \
                                                 size_t *dlen,                \
                                                 _dtype *element);            \
                                                                              \
    _api int _dname##_pop_left_no_zero(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       _dtype *element);                      \
                                                                              \
    _api void _dname##_pop_left_no_check(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         _dtype *element);                    \
                                                                              \
    _api int _dname##_pop_left(_dtype *data, size_t *dlen, _dtype *element);  \
                                                                              \
    _api void _dname##_pop_left_unordered_no_check(_dtype *data,              \
                                                   size_t *dlen,              \
                                                   _dtype *element);          \
                                                                              \
    _api int _dname##_pop_left_unordered(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         _dtype *element);                    \
                                                                              \
    _api void _dname##_pop_right_no_check(_dtype *data,                       \
                                          size_t *dlen,                       \
                                          _dtype *element);                   \
                                                                              \
    _api int _dname##_pop_right(_dtype *data, size_t *dlen, _dtype *element); \
                                                                              \
    _api void _dname##_truncate_no_zero_no_check(size_t *dlen,                \
                                                 size_t new_length);          \
                                                                              \
    _api int _dname##_truncate_no_zero(size_t *dlen,                          \
                                       size_t new_length);                    \
                                                                              \
    _api void _dname##_truncate_no_check(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         size_t new_length);                  \
                                                                              \
    _api int _dname##_truncate(_dtype *data,                                  \
                               size_t *dlen,                                  \
                               size_t new_length);                            \
                                                                              \
    _api void _dname##_clear_no_zero_no_check(size_t *dlen);                  \
                                                                              \
    _api int _dname##_clear_no_zero(size_t *dlen);                            \
                                                                              \
    _api void _dname##_clear_no_check(_dtype *data, size_t *dlen);            \
                                                                              \
    _api int _dname##_clear(_dtype *data, size_t *dlen);

#define CBASE_DATA_MUTATIONS_IMPL(_api, _dname, _dtype)                       \
    _api _dtype *_dname##_mutable_index_no_check(_dtype *data,                \
                                                 size_t index) {              \
        return data + index;                                                  \
    }                                                                         \
                                                                              \
    _api int _dname##_mutable_index(_dtype *data,                             \
                                    size_t dlen,                              \
                                    size_t index,                             \
                                    _dtype **element) {                       \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_DOUBLE_POINTER_ARGUMENT(element);                         \
        CBASE_CHECK_INDEX_BOUNDS(dlen, index);                                \
                                                                              \
        *element = _dname##_mutable_index_no_check(data, index);              \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_zero_no_check(_dtype *data,                            \
                                     size_t index,                            \
                                     size_t count) {                          \
        cb_zero_buf_no_check(_dname##_mutable_index_no_check(data, index),    \
                             count * sizeof(_dtype));                         \
    }                                                                         \
                                                                              \
    _api int _dname##_zero(_dtype *data,                                      \
                           size_t dlen,                                       \
                           size_t index,                                      \
                           size_t count) {                                    \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_INDEX_BOUNDS(dlen, index);                                \
        CBASE_CHECK_OFFSET_INDEX_BOUNDS(dlen, index, count);                  \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            cb_zero_buf(_dname##_mutable_index_no_check(data, index),         \
                        count,                                                \
                        sizeof(_dtype)));                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_compact_no_check(size_t dlen, size_t *dcap) {          \
        (*dcap) = dlen;                                                       \
    }                                                                         \
                                                                              \
    _api int _dname##_compact(size_t dlen, size_t *dcap) {                    \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        if ((*dcap) > dlen) {                                                 \
            _dname##_compact_no_check(dlen, dcap);                            \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_set_no_check(_dtype *data,                             \
                                    size_t index,                             \
                                    const _dtype *data2,                      \
                                    size_t count) {                           \
        cb_memmove(_dname##_mutable_index_no_check(data, index),              \
                   data2,                                                     \
                   count,                                                     \
                   sizeof(_dtype));                                           \
    }                                                                         \
                                                                              \
    _api int _dname##_set(_dtype *data,                                       \
                          size_t dlen,                                        \
                          size_t index,                                       \
                          const _dtype *data2,                                \
                          size_t count) {                                     \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(data2);                                  \
        CBASE_CHECK_INDEX_BOUNDS(dlen, index);                                \
        CBASE_CHECK_OFFSET_INDEX_BOUNDS(dlen, index, count);                  \
                                                                              \
        _dname##_set_no_check(data, index, data2, count);                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_move_left_no_zero_no_check(_dtype *data,               \
                                                  size_t *dlen,               \
                                                  size_t index,               \
                                                  size_t count) {             \
        if ((index + count) < (*dlen)) {                                      \
            cb_memmove(_dname##_mutable_index_no_check(data, index - count),  \
                       _dname##_index_no_check(data, index),                  \
                       (*dlen) - index,                                       \
                       sizeof(_dtype));                                       \
        }                                                                     \
                                                                              \
        (*dlen) -= count;                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_move_left_no_zero(_dtype *data,                         \
                                        size_t *dlen,                         \
                                        size_t index,                         \
                                        size_t count) {                       \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        /* [FIXME] Custom bounds check */                                     \
        CBASE_ERROR_IF(count > index, CBASE_ERROR_OUT_OF_BOUNDS);             \
        CBASE_CHECK_OFFSET_INDEX_BOUNDS(*dlen, index, count);                 \
                                                                              \
        _dname##_move_left_no_zero_no_check(data, dlen, index, count);        \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_move_left_no_check(_dtype *data,                       \
                                          size_t *dlen,                       \
                                          size_t index,                       \
                                          size_t count) {                     \
        _dname##_move_left_no_zero_no_check(data, dlen, index, count);        \
        _dname##_zero_no_check(data, (*dlen), count);                         \
    }                                                                         \
                                                                              \
    _api int _dname##_move_left(_dtype *data,                                 \
                                size_t *dlen,                                 \
                                size_t index,                                 \
                                size_t count) {                               \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        /* [FIXME] Custom bounds check */                                     \
        CBASE_ERROR_IF(count > index, CBASE_ERROR_OUT_OF_BOUNDS);             \
        CBASE_CHECK_OFFSET_INDEX_BOUNDS(*dlen, index, count);                 \
                                                                              \
        _dname##_move_left_no_check(data, dlen, index, count);                \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_delete_no_zero_no_check(_dtype *data,                  \
                                               size_t *dlen,                  \
                                               size_t index,                  \
                                               size_t count) {                \
        if ((index + count) < (*dlen)) {                                      \
            cb_memmove(_dname##_mutable_index_no_check(data, index + count),  \
                       _dname##_index_no_check(data, index),                  \
                       (*dlen) - (index + count),                             \
                       sizeof(_dtype));                                       \
        }                                                                     \
                                                                              \
        (*dlen) -= count;                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_delete_no_zero(_dtype *data,                            \
                                     size_t *dlen,                            \
                                     size_t index,                            \
                                     size_t count) {                          \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_OFFSET_INDEX_BOUNDS(*dlen, index, count);                 \
                                                                              \
        _dname##_delete_no_zero_no_check(data, dlen, index, count);           \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_delete_no_check(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       size_t index,                          \
                                       size_t count) {                        \
        _dname##_delete_no_zero_no_check(data, dlen, index, count);           \
        _dname##_zero_no_check(data, (*dlen), count);                         \
    }                                                                         \
                                                                              \
    _api int _dname##_delete(_dtype *data,                                    \
                             size_t *dlen,                                    \
                             size_t index,                                    \
                             size_t count) {                                  \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_OFFSET_INDEX_BOUNDS(*dlen, index, count);                 \
                                                                              \
        _dname##_delete_no_check(data, dlen, index, count);                   \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_delete_until_no_zero_no_check(_dtype *data,            \
                                                     size_t *dlen,            \
                                                     size_t index,            \
                                                     const _dtype *data2,     \
                                                     size_t dlen2) {          \
        _dtype *cursor = NULL;                                                \
                                                                              \
        _dname##_find_no_check(data, *dlen, index, data2, dlen2, &cursor);    \
                                                                              \
        if (cursor) {                                                         \
            _dname##_delete_no_zero_no_check(data,                            \
                                             dlen,                            \
                                             cursor - data,                   \
                                             dlen2);                          \
        }                                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_delete_until_no_zero(_dtype *data,                      \
                                           size_t *dlen,                      \
                                           size_t index,                      \
                                           const _dtype *data2,               \
                                           size_t dlen2) {                    \
        size_t offset = 0;                                                    \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_find_index(data, *dlen, index, data2, dlen2, &offset));  \
                                                                              \
        _dname##_delete_no_zero_no_check(data, dlen, offset, dlen2);          \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_delete_until_no_check(_dtype *data,                    \
                                             size_t *dlen,                    \
                                             size_t index,                    \
                                             const _dtype *data2,             \
                                             size_t dlen2) {                  \
        _dtype *cursor = NULL;                                                \
                                                                              \
        _dname##_find_no_check(data, *dlen, index, data2, dlen2, &cursor);    \
                                                                              \
        if (cursor) {                                                         \
            _dname##_delete_no_check(data, dlen, cursor - data, dlen2);       \
        }                                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_delete_until(_dtype *data,                              \
                                   size_t *dlen,                              \
                                   size_t index,                              \
                                   const _dtype *data2,                       \
                                   size_t dlen2) {                            \
        size_t offset = 0;                                                    \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_find_index(data, *dlen, index, data2, dlen2, &offset));  \
                                                                              \
        _dname##_delete_no_check(data, dlen, offset, dlen2);                  \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_delete_unordered_no_zero_no_check(_dtype *data,        \
                                                         size_t *dlen,        \
                                                         size_t index,        \
                                                         size_t count) {      \
        if ((index + count) < ((*dlen) - count)) {                            \
            cb_memmove(_dname##_mutable_index_no_check(data, index),          \
                       _dname##_index_no_check(data, (*dlen) - (count + 1)),  \
                       count,                                                 \
                       sizeof(_dtype));                                       \
        }                                                                     \
                                                                              \
        (*dlen) -= count;                                                     \
    }                                                                         \
                                                                              \
    _api int _dname##_delete_unordered_no_zero(_dtype *data,                  \
                                               size_t *dlen,                  \
                                               size_t index,                  \
                                               size_t count) {                \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_OFFSET_INDEX_BOUNDS(*dlen, index, count);                 \
                                                                              \
        _dname##_delete_unordered_no_zero_no_check(data, dlen, index, count); \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_delete_unordered_no_check(_dtype *data,                \
                                                 size_t *dlen,                \
                                                 size_t index,                \
                                                 size_t count) {              \
        _dname##_delete_unordered_no_zero_no_check(data, dlen, index, count); \
        _dname##_zero_no_check(data, (*dlen), count);                         \
    }                                                                         \
                                                                              \
    _api int _dname##_delete_unordered(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       size_t index,                          \
                                       size_t count) {                        \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
        CBASE_CHECK_OFFSET_INDEX_BOUNDS(*dlen, index, count);                 \
                                                                              \
        _dname##_delete_unordered_no_check(data, dlen, index, count);         \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_no_zero_no_check(_dtype *data,                     \
                                            size_t *dlen,                     \
                                            size_t index,                     \
                                            _dtype *element) {                \
        _dname##_copy_no_check(data, index, 1, element);                      \
        _dname##_delete_no_check(data, dlen, index, 1);                       \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_no_zero(_dtype *data,                               \
                                  size_t *dlen,                               \
                                  size_t index,                               \
                                  _dtype *element) {                          \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(element);                                \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
                                                                              \
        _dname##_pop_no_zero_no_check(data, dlen, index, element);            \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_no_check(_dtype *data,                             \
                                    size_t *dlen,                             \
                                    size_t index,                             \
                                    _dtype *element) {                        \
        _dname##_copy_no_check(data, index, 1, element);                      \
        _dname##_zero_no_check(data, index, 1);                               \
        _dname##_delete_no_check(data, dlen, index, 1);                       \
    }                                                                         \
                                                                              \
    _api int _dname##_pop(_dtype *data,                                       \
                          size_t *dlen,                                       \
                          size_t index,                                       \
                          _dtype *element) {                                  \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(element);                                \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
                                                                              \
        _dname##_pop_no_check(data, dlen, index, element);                    \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_unordered_no_zero_no_check(_dtype *data,           \
                                                      size_t *dlen,           \
                                                      size_t index,           \
                                                      _dtype *element) {      \
        _dname##_copy_no_check(data, index, 1, element);                      \
        _dname##_delete_unordered_no_check(data, dlen, index, 1);             \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_unordered_no_zero(_dtype *data,                     \
                                            size_t *dlen,                     \
                                            size_t index,                     \
                                            _dtype *element) {                \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(element);                                \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
                                                                              \
        _dname##_pop_unordered_no_zero_no_check(data, dlen, index, element);  \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_unordered_no_check(_dtype *data,                   \
                                              size_t *dlen,                   \
                                              size_t index,                   \
                                              _dtype *element) {              \
        _dname##_copy_no_check(data, index, 1, element);                      \
        _dname##_zero_no_check(data, index, 1);                               \
        _dname##_delete_unordered_no_check(data, dlen, index, 1);             \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_unordered(_dtype *data,                             \
                                    size_t *dlen,                             \
                                    size_t index,                             \
                                    _dtype *element) {                        \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(element);                                \
        CBASE_CHECK_INDEX_BOUNDS(*dlen, index);                               \
                                                                              \
        _dname##_pop_unordered_no_check(data, dlen, index, element);          \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_left_no_zero_no_check(_dtype *data,                \
                                                 size_t *dlen,                \
                                                 _dtype *element) {           \
        _dname##_pop_no_zero_no_check(data, dlen, 0, element);                \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_left_no_zero(_dtype *data,                          \
                                       size_t *dlen,                          \
                                       _dtype *element) {                     \
        CBASE_DELEGATE(_dname##_pop_no_zero(data, dlen, 0, element));         \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_left_no_check(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         _dtype *element) {                   \
        _dname##_pop_no_check(data, dlen, 0, element);                        \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_left(_dtype *data, size_t *dlen, _dtype *element) { \
        CBASE_DELEGATE(_dname##_pop(data, dlen, 0, element));                 \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_left_unordered_no_check(_dtype *data,              \
                                                   size_t *dlen,              \
                                                   _dtype *element) {         \
        _dname##_pop_unordered_no_check(data, dlen, 0, element);              \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_left_unordered(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         _dtype *element) {                   \
        CBASE_DELEGATE(_dname##_pop_unordered(data, dlen, 0, element));       \
    }                                                                         \
                                                                              \
    _api void _dname##_pop_right_no_check(_dtype *data,                       \
                                          size_t *dlen,                       \
                                          _dtype *element) {                  \
        _dname##_pop_no_check(data, dlen, (*dlen) - 1, element);              \
    }                                                                         \
                                                                              \
    _api int _dname##_pop_right(_dtype *data,                                 \
                                size_t *dlen,                                 \
                                _dtype *element) {                            \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(element);                                \
        CBASE_ERROR_IF((*dlen) == 0, CBASE_ERROR_OUT_OF_BOUNDS);              \
                                                                              \
        _dname##_pop_right_no_check(data, dlen, element);                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_truncate_no_zero_no_check(size_t *dlen,                \
                                                 size_t new_length) {         \
        (*dlen) = new_length;                                                 \
    }                                                                         \
                                                                              \
    _api int _dname##_truncate_no_zero(size_t *dlen, size_t new_length) {     \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_LENGTH_BOUNDS(*dlen, new_length);                         \
                                                                              \
        _dname##_truncate_no_zero_no_check(dlen, new_length);                 \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_truncate_no_check(_dtype *data,                        \
                                         size_t *dlen,                        \
                                         size_t new_length) {                 \
        _dname##_zero_no_check(data, new_length, (*dlen) - new_length);       \
        _dname##_truncate_no_zero_no_check(dlen, new_length);                 \
    }                                                                         \
                                                                              \
    _api int _dname##_truncate(_dtype *data,                                  \
                               size_t *dlen,                                  \
                               size_t new_length) {                           \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        CBASE_CHECK_LENGTH_BOUNDS(*dlen, new_length);                         \
                                                                              \
        _dname##_truncate_no_check(data, dlen, new_length);                   \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_clear_no_zero_no_check(size_t *dlen) {                 \
        _dname##_truncate_no_zero_no_check(dlen, 0);                          \
    }                                                                         \
                                                                              \
    _api int _dname##_clear_no_zero(size_t *dlen) {                           \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
                                                                              \
        _dname##_clear_no_zero_no_check(dlen);                                \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_clear_no_check(_dtype *data, size_t *dlen) {           \
        _dname##_truncate_no_check(data, dlen, 0);                            \
    }                                                                         \
                                                                              \
    _api int _dname##_clear(_dtype *data, size_t *dlen) {                     \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
                                                                              \
        _dname##_clear_no_check(data, dlen);                                  \
                                                                              \
        return 0;                                                             \
    }

#endif

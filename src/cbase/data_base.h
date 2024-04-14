#pragma once

#ifndef _CBASE_DATA_BASE_H__
#define _CBASE_DATA_BASE_H__

/*
 * [TODO]
 * - find_*_reverse
 */

#define CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)                       \
    _api const _dtype *_dname##_index_no_check(const _dtype *data,            \
                                               size_t index);                 \
                                                                              \
    _api int _dname##_index(const _dtype *data,                               \
                            size_t dlen,                                      \
                            size_t index,                                     \
                            _dtype const **element);                          \
                                                                              \
    _api void _dname##_slice_no_check(const _dtype *data,                     \
                                      size_t index,                           \
                                      size_t len,                             \
                                      _dtype const **data2,                   \
                                      size_t *dlen2);                         \
                                                                              \
    _api int _dname##_slice(const _dtype *data,                               \
                            size_t dlen,                                      \
                            size_t index,                                     \
                            size_t len,                                       \
                            _dtype const **data2,                             \
                            size_t *dlen2);                                   \
                                                                              \
    _api void _dname##_copy_no_check(const _dtype *data,                      \
                                     size_t index,                            \
                                     size_t count,                            \
                                     _dtype *data2);                          \
                                                                              \
    _api int _dname##_copy(const _dtype *data,                                \
                           size_t dlen,                                       \
                           size_t index,                                      \
                           size_t count,                                      \
                           _dtype *data2,                                     \
                           size_t dlen2);                                     \
                                                                              \
    _api bool _dname##_equals_no_check(const _dtype *data,                    \
                                       size_t index,                          \
                                       const _dtype *data2,                   \
                                       size_t dlen2);                         \
                                                                              \
    _api int _dname##_equals(const _dtype *data,                              \
                             size_t dlen,                                     \
                             size_t index,                                    \
                             const _dtype *data2,                             \
                             size_t dlen2,                                    \
                             bool *equal);                                    \
                                                                              \
    _api bool _dname##_starts_with_no_check(const _dtype *data,               \
                                            const _dtype *data2,              \
                                            size_t dlen2);                    \
                                                                              \
    _api int _dname##_starts_with(const _dtype *data,                         \
                                  size_t dlen,                                \
                                  const _dtype *data2,                        \
                                  size_t dlen2,                               \
                                  bool *equal);                               \
                                                                              \
    _api bool _dname##_ends_with_no_check(const _dtype *data,                 \
                                          size_t dlen,                        \
                                          const _dtype *data2,                \
                                          size_t dlen2);                      \
                                                                              \
    _api int _dname##_ends_with(const _dtype *data,                           \
                                size_t dlen,                                  \
                                const _dtype *data2,                          \
                                size_t dlen2,                                 \
                                bool *equal);                                 \
                                                                              \
    _api void _dname##_find_no_check(const _dtype *data,                      \
                                     size_t dlen,                             \
                                     size_t index,                            \
                                     const _dtype *data2,                     \
                                     size_t dlen2,                            \
                                     _dtype **cursor);                        \
                                                                              \
    _api int _dname##_find(const _dtype *data,                                \
                           size_t dlen,                                       \
                           size_t index,                                      \
                           const _dtype *data2,                               \
                           size_t dlen2,                                      \
                           _dtype **cursor);                                  \
                                                                              \
    _api void _dname##_find_index_no_check(const _dtype *data,                \
                                           size_t dlen,                       \
                                           size_t index,                      \
                                           const _dtype *data2,               \
                                           size_t dlen2,                      \
                                           size_t *location);                 \
                                                                              \
    _api int _dname##_find_index(const _dtype *data,                          \
                                 size_t dlen,                                 \
                                 size_t index,                                \
                                 const _dtype *data2,                         \
                                 size_t dlen2,                                \
                                 size_t *location);

#define CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)                            \
    _api const _dtype *_dname##_index_no_check(const _dtype *data,            \
                                               size_t index) {                \
        return data + index;                                                  \
    }                                                                         \
                                                                              \
    _api int _dname##_index(const _dtype *data,                               \
                            size_t dlen,                                      \
                            size_t index,                                     \
                            _dtype const **element) {                         \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(element);                                \
        CBASE_CHECK_INDEX_BOUNDS(dlen, index);                                \
                                                                              \
        *element = _dname##_index_no_check(data, index);                      \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_slice_no_check(const _dtype *data,                     \
                                      size_t index,                           \
                                      size_t len,                             \
                                      _dtype const **data2,                   \
                                      size_t *dlen2) {                        \
        *data2 = _dname##_index_no_check(data, index);                        \
        *dlen2 = len;                                                         \
    }                                                                         \
                                                                              \
    _api int _dname##_slice(const _dtype *data,                               \
                            size_t dlen,                                      \
                            size_t index,                                     \
                            size_t len,                                       \
                            _dtype const **data2,                             \
                            size_t *dlen2) {                                  \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_OFFSET_INDEX_BOUNDS(dlen, index, len);                    \
        CBASE_CHECK_POINTER_ARGUMENT(data2);                                  \
        CBASE_CHECK_POINTER_ARGUMENT(dlen2);                                  \
                                                                              \
        _dname##_slice_no_check(data, index, len, data2, dlen2);              \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_copy_no_check(const _dtype *data,                      \
                                     size_t index,                            \
                                     size_t count,                            \
                                     _dtype *data2) {                         \
        cb_memmove(data2,                                                     \
                   _dname##_index_no_check(data, index),                      \
                   count,                                                     \
                   sizeof(_dtype));                                           \
    }                                                                         \
                                                                              \
    _api int _dname##_copy(const _dtype *data,                                \
                           size_t dlen,                                       \
                           size_t index,                                      \
                           size_t count,                                      \
                           _dtype *data2,                                     \
                           size_t dlen2) {                                    \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(data2);                                  \
        CBASE_CHECK_INDEX_BOUNDS(dlen, index);                                \
        CBASE_CHECK_OFFSET_INDEX_BOUNDS(dlen, index, count);                  \
        CBASE_CHECK_LENGTH_BOUNDS(dlen2, count);                              \
                                                                              \
        _dname##_copy_no_check(data, index, count, data2);                    \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api bool _dname##_equals_no_check(const _dtype *data,                    \
                                       size_t index,                          \
                                       const _dtype *data2,                   \
                                       size_t dlen2) {                        \
        return memcmp(data + index, data2, dlen2);                            \
    }                                                                         \
                                                                              \
    _api int _dname##_equals(const _dtype *data,                              \
                             size_t dlen,                                     \
                             size_t index,                                    \
                             const _dtype *data2,                             \
                             size_t dlen2,                                    \
                             bool *equal) {                                   \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(data2);                                  \
        CBASE_CHECK_POINTER_ARGUMENT(equal);                                  \
        CBASE_CHECK_INDEX_BOUNDS(dlen, index);                                \
        CBASE_CHECK_OFFSET_INDEX_BOUNDS(dlen, index, dlen2);                  \
                                                                              \
        *equal = _dname##_equals_no_check(data, index, data2, dlen2);         \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api bool _dname##_starts_with_no_check(const _dtype *data,               \
                                            const _dtype *data2,              \
                                            size_t dlen2) {                   \
        return _dname##_equals_no_check(data, 0, data2, dlen2);               \
    }                                                                         \
                                                                              \
    _api int _dname##_starts_with(const _dtype *data,                         \
                                  size_t dlen,                                \
                                  const _dtype *data2,                        \
                                  size_t dlen2,                               \
                                  bool *equal) {                              \
        CBASE_DELEGATE(_dname##_equals(data, dlen, 0, data2, dlen2, equal));  \
    }                                                                         \
                                                                              \
    _api bool _dname##_ends_with_no_check(const _dtype *data,                 \
                                          size_t dlen,                        \
                                          const _dtype *data2,                \
                                          size_t dlen2) {                     \
        return _dname##_equals_no_check(data, dlen - dlen2, data2, dlen2);    \
    }                                                                         \
                                                                              \
    _api int _dname##_ends_with(const _dtype *data,                           \
                                size_t dlen,                                  \
                                const _dtype *data2,                          \
                                size_t dlen2,                                 \
                                bool *equal) {                                \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(data2);                                  \
        CBASE_CHECK_POINTER_ARGUMENT(equal);                                  \
        CBASE_CHECK_LENGTH_BOUNDS(dlen, dlen2);                               \
                                                                              \
        *equal = _dname##_ends_with_no_check(data, dlen, data2, dlen2);       \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_find_no_check(const _dtype *data,                      \
                                     size_t dlen,                             \
                                     size_t index,                            \
                                     const _dtype *data2,                     \
                                     size_t dlen2,                            \
                                     _dtype **cursor) {                       \
        cb_memmem_no_check(data + index,                                      \
                           dlen - index,                                      \
                           data2,                                             \
                           dlen2,                                             \
                           (void **)&cursor);                                 \
    }                                                                         \
                                                                              \
    _api int _dname##_find(const _dtype *data,                                \
                           size_t dlen,                                       \
                           size_t index,                                      \
                           const _dtype *data2,                               \
                           size_t dlen2,                                      \
                           _dtype **cursor) {                                 \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(data2);                                  \
        CBASE_CHECK_POINTER_ARGUMENT(cursor);                                 \
        CBASE_CHECK_INDEX_BOUNDS(dlen, index);                                \
        /* [FIXME] Custom NULL pointer check, also probably not the right     \
         * code */                                                            \
        CBASE_ERROR_IF(dlen2 == 0, CBASE_ERROR_NULL_POINTER);                 \
                                                                              \
        CBASE_ERROR_IF(dlen2 > (dlen - index), CBASE_ERROR_NOT_FOUND);        \
                                                                              \
        _dtype *c2 = NULL;                                                    \
                                                                              \
        _dname##_find_no_check(data + index,                                  \
                               dlen - index,                                  \
                               index,                                         \
                               data2,                                         \
                               dlen2,                                         \
                               &c2);                                          \
                                                                              \
        if (!c2) {                                                            \
            CBASE_ERROR(CBASE_ERROR_NOT_FOUND);                               \
        }                                                                     \
                                                                              \
        (*cursor) = c2;                                                       \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api void _dname##_find_index_no_check(const _dtype *data,                \
                                           size_t dlen,                       \
                                           size_t index,                      \
                                           const _dtype *data2,               \
                                           size_t dlen2,                      \
                                           size_t *location) {                \
        _dtype *cursor = NULL;                                                \
                                                                              \
        cb_memmem_no_check(data + index,                                      \
                           dlen - index,                                      \
                           data2,                                             \
                           dlen2,                                             \
                           (void **)&cursor);                                 \
                                                                              \
        (*location) = cursor - data;                                          \
    }                                                                         \
                                                                              \
    _api int _dname##_find_index(const _dtype *data,                          \
                                 size_t dlen,                                 \
                                 size_t index,                                \
                                 const _dtype *data2,                         \
                                 size_t dlen2,                                \
                                 size_t *location) {                          \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(data2);                                  \
        CBASE_CHECK_POINTER_ARGUMENT(location);                               \
        CBASE_CHECK_INDEX_BOUNDS(dlen, index);                                \
        /* [FIXME] Custom NULL pointer check, also probably not the right     \
         * code */                                                            \
        CBASE_ERROR_IF(dlen2 == 0, CBASE_ERROR_NULL_POINTER);                 \
                                                                              \
        CBASE_ERROR_IF(dlen2 > (dlen - index), CBASE_ERROR_NOT_FOUND);        \
                                                                              \
        _dtype *cursor = NULL;                                                \
                                                                              \
        cb_memmem_no_check(data + index,                                      \
                           dlen - index,                                      \
                           data2,                                             \
                           dlen2,                                             \
                           (void **)&cursor);                                 \
                                                                              \
        if (!cursor) {                                                        \
            CBASE_ERROR(CBASE_ERROR_NOT_FOUND);                               \
        }                                                                     \
                                                                              \
        (*location) = cursor - data;                                          \
                                                                              \
        return 0;                                                             \
    }

#endif

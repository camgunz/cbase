#pragma once

#ifndef _CBASE_DATA_OWNERSHIP_MANAGEMENT_H__
#define _CBASE_DATA_OWNERSHIP_MANAGEMENT_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/checked_math.h"
#include "cbase/checks.h"
#include "cbase/errors.h"

#define _CBASE_TRY_EXPAND_DATA_IF_NEEDED_NO_ZERO(_dname,                      \
                                                 _data,                       \
                                                 _dcap,                       \
                                                 _excap)                      \
    do {                                                                      \
        size_t _slot_count = 0;                                               \
        CBASE_PROPAGATE_ERROR(                                                \
            cbase_safe_add_size((*(_dcap)), (_excap), &_slot_count));         \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_ensure_capacity_no_zero_no_check((_data),                \
                                                      (_dcap),                \
                                                      _slot_count));          \
    } while (0)

#define _CBASE_TRY_EXPAND_DATA_IF_NEEDED(_dname, _data, _dcap, _excap)        \
    do {                                                                      \
        size_t _slot_count = 0;                                               \
        CBASE_PROPAGATE_ERROR(                                                \
            cbase_safe_add_size((*(_dcap)), (_excap), &_slot_count));         \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_ensure_capacity_no_zero_no_check((_data),                \
                                                      (_dcap),                \
                                                      _slot_count));          \
    } while (0)

#endif

#define CBASE_DATA_OWNERSHIP_DECL(_api, _dname, _dtype)                       \
    _api int _dname##_ensure_capacity_no_zero(_dtype **data,                  \
                                              size_t *dcap,                   \
                                              size_t cap);                    \
                                                                              \
    _api int _dname##_ensure_capacity(_dtype **data, size_t *dcap, size_t cap);

#define CBASE_DATA_OWNERSHIP_IMPL(_api, _dname, _dtype)                       \
    _api int _dname##_ensure_capacity_no_zero(_dtype **data,                  \
                                              size_t *dcap,                   \
                                              size_t cap) {                   \
        CBASE_CHECK_INPUT_OBJECT(data);                                       \
        CBASE_CHECK_INPUT_ARGUMENT(dcap);                                     \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_ensure_capacity_no_zero_no_check(data, dcap, cap));      \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_ensure_capacity(_dtype **data,                          \
                                      size_t *dcap,                           \
                                      size_t cap) {                           \
        CBASE_CHECK_INPUT_OBJECT(data);                                       \
        CBASE_CHECK_INPUT_ARGUMENT(dcap);                                     \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_ensure_capacity_no_check(data, dcap, cap));              \
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
            _CBASE_TRY_EXPAND_DATA_IF_NEEDED_NO_ZERO(_dname,                  \
                                                     data,                    \
                                                     dcap,                    \
                                                     cap);                    \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_capacity_no_zero(_dtype **data,                     \
                                           size_t *dlen,                      \
                                           size_t *dcap,                      \
                                           size_t cap) {                      \
        CBASE_CHECK_INPUT_OBJECT(data);                                       \
        CBASE_CHECK_INPUT_ARGUMENT(dlen);                                     \
        CBASE_CHECK_INPUT_ARGUMENT(dcap);                                     \
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
            _CBASE_TRY_EXPAND_DATA_IF_NEEDED(_dname, data, dcap, cap);        \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    _api int _dname##_set_capacity(_dtype **data,                             \
                                   size_t *dlen,                              \
                                   size_t *dcap,                              \
                                   size_t cap) {                              \
        CBASE_CHECK_INPUT_OBJECT(data);                                       \
        CBASE_CHECK_INPUT_ARGUMENT(dlen);                                     \
        CBASE_CHECK_INPUT_ARGUMENT(dcap);                                     \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _dname##_set_capacity_no_check(data, dlen, dcap, cap));           \
                                                                              \
        return 0;                                                             \
    }

/* vi: set et ts=4 sw=4: */

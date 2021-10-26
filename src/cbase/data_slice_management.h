#pragma once

#ifndef _CBASE_DATA_SLICE_MANAGEMENT_H__
#define _CBASE_DATA_SLICE_MANAGEMENT_H__

#include "cbase/internal.h"

#include <stddef.h>

#include "cbase/alloc.h"
#include "cbase/checks.h"
#include "cbase/data_base.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#define CBASE_DATA_SLICE_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    _api void _dname##_assign_no_check(_dtype **data,                         \
                                       size_t *dlen,                          \
                                       _dtype *data2,                         \
                                       size_t dlen2);                         \
                                                                              \
    _api int _dname##_assign(_dtype **data,                                   \
                             size_t *dlen,                                    \
                             _dtype *data2,                                   \
                             size_t dlen2);

#define CBASE_DATA_SLICE_MANAGEMENT_IMPL(_api, _dname, _dtype)                \
    _api void _dname##_assign_no_check(_dtype **data,                         \
                                       size_t *dlen,                          \
                                       _dtype *data2,                         \
                                       size_t dlen2) {                        \
        (*data) = data2;                                                      \
        (*dlen) = dlen2;                                                      \
    }                                                                         \
                                                                              \
    _api int _dname##_assign(_dtype **data,                                   \
                             size_t *dlen,                                    \
                             _dtype *data2,                                   \
                             size_t dlen2) {                                  \
        _CBASE_DATA_BASE_CHECK_MUTABLE_INPUT_ARGS(data, dlen);                \
                                                                              \
        _dname##_assign_no_check(data, dlen, data2, dlen2);                   \
                                                                              \
        return 0;                                                             \
    }

#endif

#pragma once

#ifndef _CBASE_DATA_MANAGEMENT_H__
#define _CBASE_DATA_MANAGEMENT_H__

#define CBASE_DATA_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)                 \
    _api void _dname##_assign_no_check(_dtype **data,                         \
                                       size_t *dlen,                          \
                                       _dtype *data2,                         \
                                       size_t dlen2);                         \
                                                                              \
    _api int _dname##_assign(_dtype **data,                                   \
                             size_t *dlen,                                    \
                             _dtype *data2,                                   \
                             size_t dlen2);

#define CBASE_DATA_MANAGEMENT_IMPL(_api, _dname, _dtype)                      \
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
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dlen);                                   \
        /* [TODO] Only accept data2 == NULL and dlen2 == 0 together */        \
                                                                              \
        _dname##_assign_no_check(data, dlen, data2, dlen2);                   \
                                                                              \
        return 0;                                                             \
    }

#endif

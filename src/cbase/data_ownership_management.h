#pragma once

#ifndef _CBASE_DATA_OWNERSHIP_MANAGEMENT_H__
#define _CBASE_DATA_OWNERSHIP_MANAGEMENT_H__

#define CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)       \
    _api int _dname##_ensure_capacity_no_zero_no_check(_dtype **data,         \
                                                       size_t *dcap,          \
                                                       size_t cap);           \
                                                                              \
    _api int _dname##_ensure_capacity_no_zero(_dtype **data,                  \
                                              size_t *dcap,                   \
                                              size_t cap);                    \
                                                                              \
    _api int _dname##_ensure_capacity_no_check(_dtype **data,                 \
                                               size_t *dcap,                  \
                                               size_t cap);                   \
                                                                              \
    _api int _dname##_ensure_capacity(_dtype **data, size_t *dcap, size_t cap);

#define CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL(_api, _dname, _dtype)            \
    _api int _dname##_ensure_capacity_no_zero(_dtype **data,                  \
                                              size_t *dcap,                   \
                                              size_t cap) {                   \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        CBASE_DELEGATE(                                                       \
            _dname##_ensure_capacity_no_zero_no_check(data, dcap, cap));      \
    }                                                                         \
                                                                              \
    _api int _dname##_ensure_capacity(_dtype **data,                          \
                                      size_t *dcap,                           \
                                      size_t cap) {                           \
        CBASE_CHECK_POINTER_ARGUMENT(data);                                   \
        CBASE_CHECK_POINTER_ARGUMENT(dcap);                                   \
                                                                              \
        CBASE_DELEGATE(_dname##_ensure_capacity_no_check(data, dcap, cap));   \
    }

#endif

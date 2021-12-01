#pragma once

#ifndef _CBASE_DATA_H__
#define _CBASE_DATA_H__

#include "cbase/internal.h"

#include "cbase/data_base.h"
#include "cbase/data_slice_management.h"
#include "cbase/data_slice_mutations.h"
#include "cbase/data_static_management.h"
#include "cbase/data_mutations.h"
#include "cbase/data_static_mutations.h"
#include "cbase/data_dynamic_management.h"
#include "cbase/data_dynamic_mutations.h"

#define CBASE_DATA_IMPL_DECL(_api, _dname, _dtype)                            \
    CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)

#define CBASE_DATA_IMPL(_api, _dname, _dtype)                                 \
    CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)

#define CBASE_SLICE_IMPL_DECL(_api, _dname, _dtype)                           \
    CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)                           \
    CBASE_SLICE_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)

#define CBASE_SLICE_IMPL(_api, _dname, _dtype)                                \
    CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)                                \
    CBASE_SLICE_MANAGEMENT_IMPL(_api, _dname, _dtype)

#define CBASE_MUTABLE_SLICE_IMPL_DECL(_api, _dname, _dtype)                   \
    CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)                           \
    CBASE_SLICE_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)                    \
    CBASE_SLICE_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)

#define CBASE_MUTABLE_SLICE_IMPL(_api, _dname, _dtype)                        \
    CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)                                \
    CBASE_SLICE_MANAGEMENT_IMPL(_api, _dname, _dtype)                         \
    CBASE_SLICE_MUTATIONS_IMPL(_api, _dname, _dtype)

#define CBASE_STATIC_DATA_IMPL_DECL(_api, _dname, _dtype)                     \
    CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)                           \
    CBASE_DATA_SLICE_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)               \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    CBASE_DATA_STATIC_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)

#define CBASE_STATIC_DATA_IMPL(_api, _dname, _dtype)                          \
    CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)                                \
    CBASE_DATA_SLICE_MANAGEMENT_IMPL(_api, _dname, _dtype)                    \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    CBASE_DATA_STATIC_MANAGEMENT_IMPL(_api, _dname, _dtype)

#define CBASE_MUTABLE_STATIC_DATA_IMPL_DECL(_api, _dname, _dtype)             \
    CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)                           \
    CBASE_DATA_SLICE_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)               \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    CBASE_DATA_STATIC_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)              \
    CBASE_DATA_SLICE_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)                \
    CBASE_DATA_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)

#define CBASE_MUTABLE_STATIC_DATA_IMPL(_api, _dname, _dtype)                  \
    CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)                                \
    CBASE_DATA_SLICE_MANAGEMENT_IMPL(_api, _dname, _dtype)                    \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    CBASE_DATA_STATIC_MANAGEMENT_IMPL(_api, _dname, _dtype)                   \
    CBASE_DATA_SLICE_MUTATIONS_IMPL(_api, _dname, _dtype)                     \
    CBASE_DATA_MUTATIONS_IMPL(_api, _dname, _dtype)

#define CBASE_MUTABLE_DYNAMIC_DATA_IMPL_DECL(_api, _dname, _dtype)            \
    CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)                           \
    CBASE_DATA_SLICE_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)               \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    CBASE_DATA_DYNAMIC_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)             \
    CBASE_DATA_SLICE_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)                \
    CBASE_DATA_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)

#define CBASE_MUTABLE_DYNAMIC_DATA_IMPL(_api, _dname, _dtype)                 \
    CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)                                \
    CBASE_DATA_SLICE_MANAGEMENT_IMPL(_api, _dname, _dtype)                    \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    CBASE_DATA_DYNAMIC_MANAGEMENT_IMPL(_api, _dname, _dtype)                  \
    CBASE_DATA_SLICE_MUTATIONS_IMPL(_api, _dname, _dtype)                     \
    CBASE_DATA_MUTATIONS_IMPL(_api, _dname, _dtype)

#endif

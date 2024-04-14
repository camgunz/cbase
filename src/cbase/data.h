#pragma once

#ifndef _CBASE_DATA_H__
#define _CBASE_DATA_H__

#include "cbase/internal.h"

#include "cbase/alloc.h"
#include "cbase/checked_math.h"
#include "cbase/checks.h"
#include "cbase/errors.h"
#include "cbase/util.h"

#include "cbase/data_base.h"
#include "cbase/data_dynamic_management.h"
#include "cbase/data_dynamic_mutations.h"
#include "cbase/data_management.h"
#include "cbase/data_mutations.h"
#include "cbase/data_ownership_management.h"
#include "cbase/data_slice_mutations.h"
#include "cbase/data_static_management.h"
#include "cbase/data_static_mutations.h"

#define CBASE_STATIC_DATA_IMPL_DECL(_api, _dname, _dtype, _dmaxcap)           \
    CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)                           \
    CBASE_DATA_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)                     \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    CBASE_DATA_STATIC_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype, _dmaxcap)

#define CBASE_STATIC_DATA_IMPL(_api, _dname, _dtype, _dmaxcap)                \
    CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)                                \
    CBASE_DATA_MANAGEMENT_IMPL(_api, _dname, _dtype)                          \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    CBASE_DATA_STATIC_MANAGEMENT_IMPL(_api, _dname, _dtype, _dmaxcap)

#define CBASE_MUTABLE_STATIC_DATA_IMPL_DECL(_api, _dname, _dtype, _dmaxcap)   \
    CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)                           \
    CBASE_DATA_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)                     \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    CBASE_DATA_STATIC_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype, _dmaxcap)    \
    CBASE_DATA_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)                      \
    CBASE_DATA_STATIC_MUTATIONS_IMPL_DECL(_api, _dname, _dtype, _dmaxcap)

#define CBASE_MUTABLE_STATIC_DATA_IMPL(_api, _dname, _dtype, _dmaxcap)        \
    CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)                                \
    CBASE_DATA_MANAGEMENT_IMPL(_api, _dname, _dtype)                          \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL(_api, _dname, _dtype)                \
    CBASE_DATA_STATIC_MANAGEMENT_IMPL(_api, _dname, _dtype, _dmaxcap)         \
    CBASE_DATA_MUTATIONS_IMPL(_api, _dname, _dtype)                           \
    CBASE_DATA_STATIC_MUTATIONS_IMPL(_api, _dname, _dtype, _dmaxcap)

#define CBASE_DYNAMIC_DATA_IMPL_DECL(_api, _dname, _dtype)                    \
    CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)                           \
    CBASE_DATA_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)                     \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    CBASE_DATA_DYNAMIC_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)

#define CBASE_DYNAMIC_DATA_IMPL(_api, _dname, _dtype)                         \
    CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)                                \
    CBASE_DATA_MANAGEMENT_IMPL(_api, _dname, _dtype)                          \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    CBASE_DATA_DYNAMIC_MANAGEMENT_IMPL(_api, _dname, _dtype)

#define CBASE_MUTABLE_DYNAMIC_DATA_IMPL_DECL(_api, _dname, _dtype)            \
    CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)                           \
    CBASE_DATA_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)                     \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)           \
    CBASE_DATA_DYNAMIC_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)             \
    CBASE_DATA_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)                      \
    CBASE_DATA_DYNAMIC_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)

#define CBASE_MUTABLE_DYNAMIC_DATA_IMPL(_api, _dname, _dtype)                 \
    CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)                                \
    CBASE_DATA_MANAGEMENT_IMPL(_api, _dname, _dtype)                          \
    CBASE_DATA_OWNERSHIP_MANAGEMENT_IMPL(_api, _dname, _dtype)                \
    CBASE_DATA_DYNAMIC_MANAGEMENT_IMPL(_api, _dname, _dtype)                  \
    CBASE_DATA_MUTATIONS_IMPL(_api, _dname, _dtype)                           \
    CBASE_DATA_DYNAMIC_MUTATIONS_IMPL(_api, _dname, _dtype)

#define CBASE_DATA_SLICE_IMPL_DECL(_api, _dname, _dtype)                      \
    CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)                           \
    CBASE_DATA_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)

#define CBASE_DATA_SLICE_IMPL(_api, _dname, _dtype)                           \
    CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)                                \
    CBASE_DATA_MANAGEMENT_IMPL(_api, _dname, _dtype)

#define CBASE_MUTABLE_DATA_SLICE_IMPL_DECL(_api, _dname, _dtype)              \
    CBASE_DATA_BASE_IMPL_DECL(_api, _dname, _dtype)                           \
    CBASE_DATA_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)                     \
    CBASE_DATA_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)                      \
    CBASE_DATA_SLICE_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)

#define CBASE_MUTABLE_DATA_SLICE_IMPL(_api, _dname, _dtype)                   \
    CBASE_DATA_BASE_IMPL(_api, _dname, _dtype)                                \
    CBASE_DATA_MANAGEMENT_IMPL_DECL(_api, _dname, _dtype)                     \
    CBASE_DATA_MUTATIONS_IMPL(_api, _dname, _dtype)                           \
    CBASE_DATA_SLICE_MUTATIONS_IMPL_DECL(_api, _dname, _dtype)

#endif

#pragma once

#ifndef _CBASE_CHECKS_H__
#define _CBASE_CHECKS_H__

#include "cbase/internal.h"

#include "cbase/errors.h"

#ifndef CBASE_DISABLE_INDEX_BOUNDS_CHECKS
#define CBASE_CHECK_INDEX_BOUNDS(_len, _index)                                \
    CBASE_ERROR_IF((_index) >= (_len), CBASE_ERROR_OUT_OF_BOUNDS)
#else
#define CBASE_CHECK_INDEX_BOUNDS(_len, _index)
#endif

#ifndef CBASE_DISABLE_LENGTH_BOUNDS_CHECKS
#define CBASE_CHECK_LENGTH_BOUNDS(_len1, _len2)                               \
    CBASE_ERROR_IF((_len2) > (_len1), CBASE_ERROR_OUT_OF_BOUNDS)
#else
#define CBASE_CHECK_LENGTH_BOUNDS(_len1, _len2)
#endif

#ifndef CBASE_DISABLE_INDEXED_LENGTH_BOUNDS_CHECKS
#define CBASE_CHECK_INDEXED_LENGTH_BOUNDS(_len, _index, _count)               \
    do {                                                                      \
        size_t _slot_count = 0;                                               \
        CBASE_PROPAGATE_ERROR(cb_safe_add_size((_index), (_count), &_slot_count)); \
        CBASE_CHECK_LENGTH_BOUNDS((_len), _slot_count);                       \
    } while (0)
#else
#define CBASE_CHECK_INDEXED_LENGTH_BOUNDS(_len, _index, _count)
#endif

#ifndef CBASE_DISABLE_OVERLAPPING_MEMORY_CHECKS
#define CBASE_CHECK_MEMORY_OVERLAP(_p1, _len, _p2)                            \
    CBASE_ERROR_IF(((_p2) >= (_p1)) && ((const char *)(_p2) <=                \
                                        ((const char *)(_p1) + (_len))),      \
                   CBASE_ERROR_OVERLAPPING_MEMORY)
#else
#define CBASE_CHECK_MEMORY_OVERLAP(_p1, _len, _p2)
#endif

#ifndef CBASE_DISABLE_ALL_POINTER_CHECKS
#define CBASE_CHECK_POINTER(_arg)                                             \
    CBASE_ERROR_IF((!(_arg)), CBASE_ERROR_NULL_POINTER)
#define CBASE_CHECK_DOUBLE_POINTER(_arg) \
    CBASE_CHECK_POINTER(_arg) \
    CBASE_CHECK_POINTER((*_arg))
#else
#define CBASE_CHECK_POINTER(_arg)
#define CBASE_CHECK_DOUBLE_POINTER(_arg)
#endif

#ifndef CBASE_DISABLE_INPUT_OBJECT_POINTER_CHECKS
#define CBASE_CHECK_INPUT_OBJECT(_inobj) CBASE_CHECK_POINTER(_inobj)
#define CBASE_CHECK_REALLOCATABLE_INPUT_OBJECT(_inobj)                        \
    CBASE_CHECK_INPUT_OBJECT(_inobj);                                         \
    CBASE_CHECK_INPUT_OBJECT((*_inobj))
#else
#define CBASE_CHECK_INPUT_OBJECT(_inobj)
#define CBASE_CHECK_REALLOCATABLE_INPUT_OBJECT(_inobj)
#endif

#ifndef CBASE_DISABLE_INPUT_ARGUMENT_POINTER_CHECKS
#define CBASE_CHECK_INPUT_ARGUMENT(_inarg) CBASE_CHECK_POINTER(_inarg)
#else
#define CBASE_CHECK_INPUT_ARGUMENT(_inarg)
#endif

#ifndef CBASE_DISABLE_OUTPUT_POINTER_CHECKS
#define CBASE_CHECK_OUTPUT_ARGUMENT(_outptr) CBASE_CHECK_POINTER(_outptr)
#else
#define CBASE_CHECK_OUTPUT_ARGUMENT(_outptr)
#endif

#endif

/* vi: set et ts=4 sw=4: */

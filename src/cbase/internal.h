#pragma once

#ifndef _CBASE_INTERNAL_H__
#define _CBASE_INTERNAL_H__

#include <stdint.h>
#include <stdlib.h>

#define CBASE_LOG_DEFAULT             20003
#define CBASE_LOG_STDERR              20004
#define CBASE_LOG_CUSTOM              20005
#define CBASE_LOG_LEVEL_RUNTIME       20006
#define CBASE_ERROR_LEVEL_DEFAULTS    20007
#define CBASE_ERROR_LEVEL_RUNTIME     20008
#define CBASE_ERRORS_RUNTIME          20009
#define CBASE_FLATTEN_FUNCTIONS       20010
#define CBASE_INLINE_FUNCTIONS        20011
#define CBASE_NORMAL_INLINE_FUNCTIONS 20012
#define CBASE_NEVER_INLINE_FUNCTIONS  20013

#ifdef CBASE_HAVE_CONFIG_H
#include "cbase_config.h"
#endif

#ifdef HAVE_128BIT_INTEGERS
__extension__ typedef __int128 int128_t;
__extension__ typedef unsigned __int128 uint128_t;
#endif

#ifdef HAVE_FORMAT_FUNCTION_ATTRIBUTE
#define CBASE_PRINTF(format_arg, args_arg)                                    \
    __attribute__((format(printf, format_arg, args_arg)))

#define CBASE_VPRINTF(format_arg)                                             \
    __attribute__((format(printf, format_arg, 0)))
#else
#define CBASE_PRINTF(format_arg, args_arg)
#define CBASE_VPRINTF(format_arg)
#endif

#ifdef HAVE_FLATTEN_FUNCTION_ATTRIBUTE
#define CBASE_ATTR_FLATTEN __attribute__((flatten))
#else
#define CBASE_ATTR_FLATTEN
#endif

#if defined(HAVE_ALWAYS_INLINE_FUNCTION_ATTRIBUTE)
#define CBASE_ATTR_FORCE_INLINE __attribute__((always_inline))
#elif defined(_MSC_VER) /* Visual Studio */
#define CBASE_ATTR_FORCE_INLINE __forceinline
#endif

#ifdef _MSC_VER
#define CBASE_INLINE __inline
#else
#define CBASE_INLINE inline
#endif

#ifdef HAVE_UNUSED_FUNCTION_ATTRIBUTE
#define CBASE_ATTR_UNUSED __attribute__((unused))
#else
#define CBASE_ATTR_UNUSED
#endif

#ifdef HAVE_NOINLINE_FUNCTION_ATTRIBUTE
#ifdef _MSC_VER
#define CBASE_ATTR_NOINLINE __declspec(noinline)
#else
#define CBASE_ATTR_NOINLINE __attribute__((noinline))
#endif
#else
#define CBASE_ATTR_NOINLINE
#endif

#ifdef HAVE_MALLOC_FUNCTION_ATTRIBUTE
/*
 * GCC's malloc attribute will accept a deallocator and an allocated pointer
 * parameter index; but Clang's doesn't, and there's no way to check for it
 * without checking explicitly for GCC.  Therefore, just stick w/ no arguments
 * for now
 */
#define CBASE_ATTR_MALLOC(_dealloc, _pidx) __attribute__((malloc))
#else
#define CBASE_ATTR_MALLOC(_dealloc, _pidx)
#endif

#ifdef HAVE_NONNULL_FUNCTION_ATTRIBUTE
#define CBASE_ATTR_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#endif

#ifdef HAVE_RETURNS_NONNULL_FUNCTION_ATTRIBUTE
#define CBASE_ATTR_RETURNS_NONNULL __attribute__((returns_nonnull))
#endif

#ifdef HAVE_WARN_UNUSED_RESULT_FUNCTION_ATTRIBUTE
#define CBASE_ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#endif

/*
 * [TODO]
 * - Figure out how to use warn_unused_result. It only makes sense on functions
 *   that return a value, but we don't have a function preamble only for those
 *   just now.
 */

///

#define CBASE_API_MALLOC CBASE_ATTR_MALLOC
#define CBASE_API_DEALLOC

#if CBASE_INLINING == CBASE_FLATTEN_FUNCTIONS
#define CBASE_INLINING_DEFS CBASE_INLINE CBASE_ATTR_FORCE_INLINE CBASE_ATTR_FLATTEN
#define XXH_INLINE_ALL
#elif CBASE_INLINING == CBASE_INLINE_FUNCTIONS
#define CBASE_INLINING_DEFS CBASE_INLINE
#define XXH_INLINE_ALL
#elif CBASE_INLINING == CBASE_NEVER_INLINE_FUNCTIONS
#define CBASE_INLINING_DEFS CBASE_ATTR_NOINLINE
#define XXH_NO_INLINE_HINTS   1
#endif

#if defined(WIN32) || defined(_MSC_VER)
#ifdef CBASE_BUILDING_DLL /* Exporting DLL symbols */
#define CBASE_API_PUBLIC __declspec(dllexport)
#elif CBASE_USING_DLL /* Importing DLL symbols */
#define CBASE_API_PUBLIC __declspec(dllimport)
#else
#define CBASE_API_PUBLIC
#endif
#else
#define CBASE_API_PUBLIC
#endif

#define CBASE_STATIC_DEFS static CBASE_ATTR_UNUSED

#define CBASE_API_TMPL
#define CBASE_API_STATIC_TMPL CBASE_STATIC_DEFS CBASE_INLINING_DEFS

#define CBASE_API CBASE_API_PUBLIC
#define CBASE_API_STATIC CBASE_API_PUBLIC CBASE_STATIC_DEFS CBASE_INLINING_DEFS

/*
#ifdef _WIN32
#define UNICODE
#endif
*/

#endif

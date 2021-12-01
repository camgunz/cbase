#pragma once

#ifndef TABLE_H__
#define TABLE_H__

#include "cbase/internal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cbase/errors.h"
#include "cbase/array.h"
#include "cbase/hash.h"

#define CBASE_TABLE_START_BIT 4

#define CBASE_TABLE_LOAD_LEVEL_MAX 0.9f

#define cbase_bucket_empty(n) ((n)->distance == SIZE_MAX)

enum
{
    CBASE_TABLE_FULL = 22000,
};

#define TABLE_DECL(_ttype, _tname, _ktype, _otype)                            \
    typedef struct _ttype##BucketStruct {                                     \
        size_t distance;                                                      \
        size_t hash;                                                          \
        _otype obj;                                                           \
    } _ttype##Bucket;                                                         \
                                                                              \
    ARRAY_DEF(_ttype##BucketArray, _tname##_bucket_array, _ttype##Bucket)     \
                                                                              \
    typedef size_t(_ttype##GetHashFromKey)(const _ktype key, size_t seed);    \
                                                                              \
    typedef _ktype *(_ttype##GetKeyFromObj)(const _otype obj);                \
                                                                              \
    typedef bool(_ttype##KeyEqual)(const _ktype key1, const _ktype key2);     \
                                                                              \
    typedef struct _ttype##Struct {                                           \
        size_t seed;                                                          \
        size_t bucket_bit;                                                    \
        size_t bucket_max;                                                    \
        size_t bucket_mask;                                                   \
        size_t len;                                                           \
        _ttype##BucketArray buckets;                                          \
    } _ttype;

#endif

#define TABLE_IMPL(_ttype,                                                    \
                   _tname,                                                    \
                   _ktype,                                                    \
                   _otype,                                                    \
                   _key_to_hash,                                              \
                   _obj_to_key,                                               \
                   _keys_equal)                                               \
    static inline void _tname##_reset_buckets(_ttype *table) {                \
        _tname##_bucket_array_clear(&table->buckets);                         \
        table->buckets.len = table->bucket_max;                               \
                                                                              \
        for (size_t i = 0; i < table->buckets.alloc; i++) {                   \
            _ttype##Bucket *bucket =                                          \
                _tname##_bucket_array_index_fast(&table->buckets, i);         \
            bucket->distance = SIZE_MAX;                                      \
        }                                                                     \
    }                                                                         \
                                                                              \
    static inline int _tname##_resize(_ttype *table, size_t new_bucket_bit) { \
        if (new_bucket_bit < CBASE_TABLE_START_BIT) {                         \
            new_bucket_bit = CBASE_TABLE_START_BIT;                           \
        }                                                                     \
                                                                              \
        size_t new_bucket_max = (1 << new_bucket_bit);                        \
        size_t new_bucket_mask = new_bucket_max - 1;                          \
                                                                              \
        if (new_bucket_bit == table->bucket_bit) {                            \
            return 0;                                                         \
        }                                                                     \
                                                                              \
        if (new_bucket_bit > table->bucket_bit) {                             \
            CBASE_PROPAGATE_ERROR(                                            \
                _tname##_bucket_array_ensure_capacity(&table->buckets,        \
                                                      new_bucket_max));       \
                                                                              \
            table->buckets.len = new_bucket_max;                              \
                                                                              \
            for (size_t i = table->bucket_max; i < new_bucket_max; i++) {     \
                _ttype##Bucket *bucket =                                      \
                    _tname##_bucket_array_index_fast(&table->buckets, i);     \
                                                                              \
                bucket->distance = SIZE_MAX;                                  \
            }                                                                 \
        }                                                                     \
                                                                              \
        for (size_t i = 0; i < table->buckets.len; i++) {                     \
            _ttype##Bucket *bucket =                                          \
                _tname##_bucket_array_index_fast(&table->buckets, i);         \
                                                                              \
            if (cbase_bucket_empty(bucket)) {                                 \
                continue;                                                     \
            }                                                                 \
                                                                              \
            size_t hash = bucket->hash;                                       \
            _otype obj = bucket->obj;                                         \
            bool placed_bucket = false;                                       \
                                                                              \
            bucket->distance = SIZE_MAX;                                      \
                                                                              \
            for (size_t distance = 0; distance <= table->buckets.len;         \
                 distance++) {                                                \
                size_t j = (hash + distance) & new_bucket_mask;               \
                _ttype##Bucket *new_bucket =                                  \
                    _tname##_bucket_array_index_fast(&table->buckets, j);     \
                                                                              \
                if (cbase_bucket_empty(new_bucket)) {                         \
                    new_bucket->distance = distance;                          \
                    new_bucket->hash = hash;                                  \
                    new_bucket->obj = obj;                                    \
                                                                              \
                    placed_bucket = true;                                     \
                    break;                                                    \
                }                                                             \
                                                                              \
                if (new_bucket->distance < distance) {                        \
                    size_t new_distance = new_bucket->distance;               \
                    size_t new_hash = new_bucket->hash;                       \
                    _otype new_obj = new_bucket->obj;                         \
                                                                              \
                    new_bucket->distance = distance;                          \
                    new_bucket->hash = hash;                                  \
                    new_bucket->obj = obj;                                    \
                                                                              \
                    distance = new_distance;                                  \
                    hash = new_hash;                                          \
                    obj = new_obj;                                            \
                }                                                             \
            }                                                                 \
                                                                              \
            if (!placed_bucket) {                                             \
                return CBASE_TABLE_FULL;                                      \
            }                                                                 \
        }                                                                     \
                                                                              \
        if (new_bucket_bit < table->bucket_bit) {                             \
            CBASE_PROPAGATE_ERROR(                                            \
                _tname##_bucket_array_set_size(&table->buckets,               \
                                               new_bucket_max));              \
        }                                                                     \
                                                                              \
        table->bucket_bit = new_bucket_bit;                                   \
        table->bucket_max = new_bucket_max;                                   \
        table->bucket_mask = new_bucket_mask;                                 \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    static inline int _tname##_check_grow(_ttype *table) {                    \
        float load_level = ((float)table->len) / ((float)table->bucket_max);  \
                                                                              \
        if (load_level > CBASE_TABLE_LOAD_LEVEL_MAX) {                        \
            return _tname##_resize(table, table->bucket_bit + 1);             \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    static inline int _tname##_check_shrink(_ttype *table) {                  \
        float load_level = ((float)table->len) / ((float)table->bucket_max);  \
                                                                              \
        if (load_level >= (CBASE_TABLE_LOAD_LEVEL_MAX / 2.0f)) {              \
            return 0;                                                         \
        }                                                                     \
                                                                              \
        if (table->bucket_bit <= CBASE_TABLE_START_BIT) {                     \
            return 0;                                                         \
        }                                                                     \
                                                                              \
        return _tname##_resize(table, table->bucket_bit - 1);                 \
    }                                                                         \
                                                                              \
    static inline int _tname##_init(_ttype *table, size_t seed) {             \
        table->seed = seed;                                                   \
        table->bucket_bit = CBASE_TABLE_START_BIT;                            \
        table->bucket_max = 1 << table->bucket_bit;                           \
        table->bucket_mask = table->bucket_max - 1;                           \
        table->len = 0;                                                       \
                                                                              \
        CBASE_PROPAGATE_ERROR(                                                \
            _tname##_bucket_array_init_alloc(&table->buckets,                 \
                                             table->bucket_max));             \
                                                                              \
        table->buckets.len = table->bucket_max;                               \
                                                                              \
        for (size_t i = 0; i < table->bucket_max; i++) {                      \
            _tname##_bucket_array_index_fast(&table->buckets, i)->distance =  \
                SIZE_MAX;                                                     \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    static inline int _tname##_insert(_ttype *table, _otype obj) {            \
        _ttype##BucketArray *buckets = &table->buckets;                       \
        size_t hash = _key_to_hash(_obj_to_key(obj), table->seed);            \
        size_t distance = 0;                                                  \
                                                                              \
        for (size_t count = 0; count <= buckets->len; count++) {              \
            size_t i = (hash + distance) & table->bucket_mask;                \
            _ttype##Bucket *bucket =                                          \
                _tname##_bucket_array_index_fast(buckets, i);                 \
                                                                              \
            if (cbase_bucket_empty(bucket)) {                                 \
                bucket->distance = distance;                                  \
                bucket->hash = hash;                                          \
                bucket->obj = obj;                                            \
                table->len++;                                                 \
                                                                              \
                return _tname##_check_grow(table);                            \
            }                                                                 \
                                                                              \
            if (bucket->distance < distance) {                                \
                size_t new_distance = bucket->distance;                       \
                size_t new_hash = bucket->hash;                               \
                _otype new_obj = bucket->obj;                                 \
                                                                              \
                bucket->distance = distance;                                  \
                bucket->hash = hash;                                          \
                bucket->obj = obj;                                            \
                                                                              \
                distance = new_distance;                                      \
                hash = new_hash;                                              \
                obj = new_obj;                                                \
                                                                              \
                count = 0;                                                    \
            }                                                                 \
                                                                              \
            distance++;                                                       \
        }                                                                     \
                                                                              \
        return CBASE_TABLE_FULL;                                              \
    }                                                                         \
                                                                              \
    static inline int _tname##_remove(_ttype *table, const _ktype key) {      \
        _ttype##BucketArray *buckets = &table->buckets;                       \
        size_t hash = _key_to_hash(key, table->seed);                         \
        size_t start = hash;                                                  \
                                                                              \
        for (size_t distance = 0; distance < buckets->len; distance++) {      \
            size_t i = (start + distance) & table->bucket_mask;               \
            _ttype##Bucket *bucket =                                          \
                _tname##_bucket_array_index_fast(buckets, i);                 \
                                                                              \
            if (cbase_bucket_empty(bucket)) {                                 \
                continue;                                                     \
            }                                                                 \
                                                                              \
            if (bucket->hash != hash) {                                       \
                continue;                                                     \
            }                                                                 \
                                                                              \
            if (!_keys_equal(_obj_to_key(bucket->obj), key)) {                \
                continue;                                                     \
            }                                                                 \
                                                                              \
            bucket->distance = SIZE_MAX;                                      \
            table->len--;                                                     \
                                                                              \
            return _tname##_check_shrink(table);                              \
        }                                                                     \
                                                                              \
        return CBASE_ERROR_NOT_FOUND;                                         \
    }                                                                         \
                                                                              \
    static inline int _tname##_pop(_ttype *table,                             \
                                   const _ktype key,                          \
                                   _otype *obj) {                             \
        _ttype##BucketArray *buckets = &table->buckets;                       \
        size_t hash = _key_to_hash(key, table->seed);                         \
        size_t start = hash;                                                  \
                                                                              \
        for (size_t distance = 0; distance < buckets->len; distance++) {      \
            size_t i = (start + distance) & table->bucket_mask;               \
            _ttype##Bucket *bucket =                                          \
                _tname##_bucket_array_index_fast(buckets, i);                 \
                                                                              \
            if (cbase_bucket_empty(bucket)) {                                 \
                continue;                                                     \
            }                                                                 \
                                                                              \
            if (bucket->hash != hash) {                                       \
                continue;                                                     \
            }                                                                 \
                                                                              \
            if (!_keys_equal(_obj_to_key(bucket->obj), key)) {                \
                continue;                                                     \
            }                                                                 \
                                                                              \
            *obj = bucket->obj;                                               \
            bucket->distance = SIZE_MAX;                                      \
            table->len--;                                                     \
                                                                              \
            return _tname##_check_shrink(table);                              \
        }                                                                     \
                                                                              \
        return CBASE_ERROR_NOT_FOUND;                                         \
    }                                                                         \
                                                                              \
    static inline int _tname##_lookup(_ttype *table,                          \
                                      const _ktype key,                       \
                                      _otype *obj) {                          \
        _ttype##BucketArray *buckets = &table->buckets;                       \
        size_t hash = _key_to_hash(key, table->seed);                         \
        size_t start = hash;                                                  \
                                                                              \
        for (size_t distance = 0; distance < buckets->len; distance++) {      \
            size_t i = (start + distance) & table->bucket_mask;               \
            _ttype##Bucket *bucket =                                          \
                _tname##_bucket_array_index_fast(buckets, i);                 \
                                                                              \
            if (cbase_bucket_empty(bucket)) {                                 \
                continue;                                                     \
            }                                                                 \
                                                                              \
            if (bucket->hash != hash) {                                       \
                continue;                                                     \
            }                                                                 \
                                                                              \
            if (!_keys_equal(_obj_to_key(bucket->obj), key)) {                \
                continue;                                                     \
            }                                                                 \
                                                                              \
            if (obj) {                                                        \
                *obj = bucket->obj;                                           \
            }                                                                 \
                                                                              \
            return 0;                                                         \
        }                                                                     \
                                                                              \
        return CBASE_ERROR_NOT_FOUND;                                         \
    }                                                                         \
                                                                              \
    static inline bool _tname##_iterate(_ttype *table,                        \
                                        size_t *index,                        \
                                        _otype *obj) {                        \
        size_t i = 0;                                                         \
                                                                              \
        if (*obj) {                                                           \
            i = (*index) + 1;                                                 \
        }                                                                     \
                                                                              \
        while (i < table->buckets.len) {                                      \
            _ttype##Bucket *bucket =                                          \
                _tname##_bucket_array_index_fast(&table->buckets, i);         \
                                                                              \
            if (!cbase_bucket_empty(bucket)) {                                \
                *index = i;                                                   \
                *obj = bucket->obj;                                           \
                                                                              \
                return true;                                                  \
            }                                                                 \
                                                                              \
            i++;                                                              \
        }                                                                     \
                                                                              \
        *index = 0;                                                           \
                                                                              \
        return false;                                                         \
    }                                                                         \
                                                                              \
    static inline void _tname##_clear(_ttype *table) {                        \
        table->bucket_bit = CBASE_TABLE_START_BIT;                            \
        table->bucket_max = 1 << table->bucket_bit;                           \
        table->bucket_mask = table->bucket_max - 1;                           \
        table->len = 0;                                                       \
                                                                              \
        _tname##_reset_buckets(table);                                        \
    }                                                                         \
                                                                              \
    static inline void _tname##_free(_ttype *table) {                         \
        _tname##_bucket_array_free(&table->buckets);                          \
                                                                              \
        table->seed = 0;                                                      \
        table->bucket_bit = 0;                                                \
        table->bucket_max = 0;                                                \
        table->bucket_mask = 0;                                               \
        table->len = 0;                                                       \
    }                                                                         \
                                                                              \
    static inline int _tname##_copy(_ttype *dst, _ttype *src) {               \
        size_t index = 0;                                                     \
        _otype obj = NULL;                                                    \
                                                                              \
        _tname##_clear(dst);                                                  \
                                                                              \
        while (_tname##_iterate(src, &index, &obj)) {                         \
            CBASE_PROPAGATE_ERROR(_tname##_insert(dst, obj));                 \
        }                                                                     \
                                                                              \
        return 0;                                                             \
    }

#define TABLE_DEF(_ttype,                                                     \
                  _tname,                                                     \
                  _ktype,                                                     \
                  _otype,                                                     \
                  _key_to_hash,                                               \
                  _obj_to_key,                                                \
                  _keys_equal)                                                \
    TABLE_DECL(_ttype, _tname, _ktype, _otype)                                \
    TABLE_IMPL(_ttype,                                                        \
               _tname,                                                        \
               _ktype,                                                        \
               _otype,                                                        \
               _key_to_hash,                                                  \
               _obj_to_key,                                                   \
               _keys_equal)

#define STR_TABLE_DECL(_ttype, _tname, _otype)                                \
    TABLE_DECL(_ttype, _tname, char *, _otype)

#define STR_TABLE_IMPL(_ttype, _tname, _otype, _obj_to_key)                   \
    TABLE_IMPL(_ttype,                                                        \
               _tname,                                                        \
               char *,                                                        \
               _otype,                                                        \
               hash64_string,                                                 \
               _obj_to_key,                                                   \
               cstr_equal)

#define STR_TABLE_DEF(_ttype, _tname, _otype, _obj_to_key)                    \
    STR_TABLE_DECL(_ttype, _tname, _otype)                                    \
    STR_TABLE_IMPL(_ttype, _tname, _otype, _obj_to_key)

#define UINT_TABLE_DECL(_ttype, _tname, _otype)                               \
    TABLE_DECL(_ttype, _tname, uint64_t, _otype)

#define UINT_TABLE_IMPL(_ttype, _tname, _otype, _obj_to_key)                  \
    TABLE_IMPL(_ttype,                                                        \
               _tname,                                                        \
               uint64_t,                                                      \
               _otype,                                                        \
               hash64_string,                                                 \
               _obj_to_key,                                                   \
               cstr_equal)

#define UINT_TABLE_DEF(_ttype, _tname, _otype, _obj_to_key)                   \
    UINT_TABLE_DECL(_ttype, _tname, _otype)                                   \
    UINT_TABLE_IMPL(_ttype, _tname, _otype, _obj_to_key)

#define INT_TABLE_DECL(_ttype, _tname, _otype)                                \
    TABLE_DECL(_ttype, _tname, int64_t, _otype)

#define INT_TABLE_IMPL(_ttype, _tname, _otype, _obj_to_key)                   \
    TABLE_IMPL(_ttype,                                                        \
               _tname,                                                        \
               int64_t,                                                       \
               _otype,                                                        \
               hash64_string,                                                 \
               _obj_to_key,                                                   \
               cstr_equal)

#define INT_TABLE_DEF(_ttype, _tname, _otype, _obj_to_key)                    \
    INT_TABLE_DECL(_ttype, _tname, _otype)                                    \
    INT_TABLE_IMPL(_ttype, _tname, _otype, _obj_to_key)

#define STR32_TABLE_DEF(_ttype, _tname, _otype, _obj_to_key)                  \
    STR32_TABLE_DECL(_ttype, _tname, _otype)                                  \
    STR32_TABLE_IMPL(_ttype, _tname, _otype, _obj_to_key)

#define UINT32_TABLE_DECL(_ttype, _tname, _otype)                             \
    TABLE_DECL(_ttype, _tname, uint32_t, _otype)

#define UINT32_TABLE_IMPL(_ttype, _tname, _otype, _obj_to_key)                \
    TABLE_IMPL(_ttype,                                                        \
               _tname,                                                        \
               uint32_t,                                                      \
               _otype,                                                        \
               hash32_string,                                                 \
               _obj_to_key,                                                   \
               cstr_equal)

#define UINT32_TABLE_DEF(_ttype, _tname, _otype, _obj_to_key)                 \
    UINT32_TABLE_DECL(_ttype, _tname, _otype)                                 \
    UINT32_TABLE_IMPL(_ttype, _tname, _otype, _obj_to_key)

#define INT32_TABLE_DECL(_ttype, _tname, _otype)                              \
    TABLE_DECL(_ttype, _tname, int32_t, _otype)

#define INT32_TABLE_IMPL(_ttype, _tname, _otype, _obj_to_key)                 \
    TABLE_IMPL(_ttype,                                                        \
               _tname,                                                        \
               int32_t,                                                       \
               _otype,                                                        \
               hash32_string,                                                 \
               _obj_to_key,                                                   \
               cstr_equal)

#define INT32_TABLE_DEF(_ttype, _tname, _otype, _obj_to_key)                  \
    INT32_TABLE_DECL(_ttype, _tname, _otype)                                  \
    INT32_TABLE_IMPL(_ttype, _tname, _otype, _obj_to_key)

/* vi: set et ts=4 sw=4: */

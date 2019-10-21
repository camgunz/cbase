#pragma once

#ifndef TABLE_H__
#define TABLE_H__

#include <stdbool.h>
#include <stdlib.h>

#include "cbase/array.h"
#include "cbase/status.h"

#define table_node_empty(n) ((n)->distance == SIZE_MAX)

typedef struct TArrayNodeStruct {
    size_t distance;
    size_t hash;
    void *obj;
} TArrayNode;

enum {
    TABLE_FULL = 1
};

typedef size_t(TableGetHashFromKey)(const void *key, size_t seed);

typedef void*(TableGetKeyFromObj)(const void *obj);

typedef bool(TableKeyEqual)(const void *key1, const void *key2);

typedef struct TableStruct {
    TableGetHashFromKey *key_to_hash;
    TableGetKeyFromObj *obj_to_key;
    TableKeyEqual *key_equal;
    size_t seed;
    size_t bucket_bit;
    size_t bucket_max;
    size_t bucket_mask;
    size_t len;
    Array buckets;
} Table;

bool  table_init(Table *table, TableGetHashFromKey *key_to_hash,
                               TableGetKeyFromObj *obj_to_key,
                               TableKeyEqual *key_equal,
                               size_t seed,
                               Status *status);

bool  table_insert(Table *table, void *obj, Status *status);

bool  table_remove(Table *table, const void *key, Status *status);

bool  _table_pop(Table *table, const void *key, void **obj, Status *status);

#define table_pop(table, key, obj, status) \
    _table_pop(table, key, (void **)obj, status)

bool  _table_lookup(Table *table, const void *key, void **obj, Status *status);

#define table_lookup(table, key, obj, status) \
    _table_lookup(table, key, (void **)obj, status)

bool  table_copy(Table *dst, Table *src, Status *status);

bool  _table_iterate(Table *table, size_t *index, void **obj);

#define table_iterate(table, index, obj) \
    _table_iterate(table, index, (void **)obj)

void  table_clear(Table *table);

void  table_free(Table *table);

#endif

/* vi: set et ts=4 sw=4: */

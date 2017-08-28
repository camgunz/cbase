#ifndef TABLE_H__
#define TABLE_H__

#define table_node_empty(n) ((n)->distance == SIZE_MAX)

typedef struct {
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

typedef struct {
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
bool  table_remove(Table *table, void *key, void **obj, Status *status);
bool  table_lookup(Table *table, void *key, void **obj, Status *status);
bool  table_copy(Table *dst, Table *src, Status *status);
bool  table_iterate(Table *table, size_t *index, void **obj);
void  table_clear(Table *table);
void  table_free(Table *table);

#endif

/* vi: set et ts=4 sw=4: */

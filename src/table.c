#include "cbase.h"

#define START_BIT 4

#define LOAD_LEVEL_MAX 0.9f

#define table_full(status) status_failure( \
    status,                                \
    "table",                               \
    TABLE_FULL,                            \
    "Table is full"                        \
)

static bool table_resize(Table *table, size_t new_bucket_bit, Status *status) {
    if (new_bucket_bit < START_BIT) {
        new_bucket_bit = START_BIT;
    }

    size_t new_bucket_max = (1 << new_bucket_bit);
    size_t new_bucket_mask = new_bucket_max - 1;

    if (new_bucket_bit == table->bucket_bit) {
        return status_ok(status);
    }

    if (new_bucket_bit > table->bucket_bit) {
        if (!array_ensure_capacity(&table->buckets, new_bucket_max, status)) {
            return false;
        }

        table->buckets.len = new_bucket_max;

        for (size_t i = table->bucket_max; i < new_bucket_max; i++) {
            TArrayNode *node = array_index_fast(&table->buckets, i);

            node->distance = SIZE_MAX;
        }
    }

    for (size_t i = 0; i < table->buckets.len; i++) {
        TArrayNode *node = (TArrayNode *)array_index_fast(&table->buckets, i);

        if (table_node_empty(node)) {
            continue;
        }

        size_t hash = node->hash;
        void *obj = node->obj;
        bool placed_node = false;

        node->distance = SIZE_MAX;

        for (size_t distance = 0; distance <= table->buckets.len; distance++) {
            size_t j = (hash + distance) & new_bucket_mask;
            TArrayNode *new_node = (TArrayNode *)array_index_fast(
                &table->buckets, j
            );

            if (table_node_empty(new_node)) {
                new_node->distance = distance;
                new_node->hash = hash;
                new_node->obj = obj;

                placed_node = true;
                break;
            }

            if (new_node->distance < distance) {
                size_t new_distance = new_node->distance;
                size_t new_hash = new_node->hash;
                void * new_obj = new_node->obj;

                new_node->distance = distance;
                new_node->hash = hash;
                new_node->obj = obj;

                distance = new_distance; /* Reset distance here */
                hash = new_hash;
                obj = new_obj;
            }
        }

        if (!placed_node) {
            return table_full(status);
        }
    }

    if (new_bucket_bit < table->bucket_bit) {
        if (!array_set_size(&table->buckets, new_bucket_max, status)) {
            return false;
        }
    }

    table->bucket_bit = new_bucket_bit;
    table->bucket_max = new_bucket_max;
    table->bucket_mask = new_bucket_mask;

    return status_ok(status);
}

static bool table_check_grow(Table *table, Status *status) {
    float load_level = (float)table->len / (float)table->bucket_max;

    if (load_level > LOAD_LEVEL_MAX) {
        return table_resize(table, table->bucket_bit + 1, status);
    }

    return status_ok(status);
}

static bool table_check_shrink(Table *table, Status *status) {
    float load_level = (float)table->len / table->bucket_max;

    if (load_level >= (LOAD_LEVEL_MAX / 2.0f)) {
        return status_ok(status);
    }

    if (table->bucket_bit <= START_BIT) {
        return status_ok(status);
    }

    return table_resize(table, table->bucket_bit - 1, status);
}

bool table_init(Table *table, TableGetHashFromKey *key_to_hash,
                              TableGetKeyFromObj *obj_to_key,
                              TableKeyEqual *key_equal,
                              size_t seed,
                              Status *status) {
    table->key_to_hash = key_to_hash;
    table->obj_to_key = obj_to_key;
    table->key_equal = key_equal;
    table->seed = seed;
    table->bucket_bit = START_BIT;
    table->bucket_max = 1 << table->bucket_bit;
    table->bucket_mask = table->bucket_max - 1;
    table->len = 0;
    
    if (!array_init_alloc(&table->buckets,
                          sizeof(TArrayNode),
                          table->bucket_max,
                          status)) {
        return false;
    }

    table->buckets.len = table->bucket_max;

    for (size_t i = 0; i < table->bucket_max; i++) {
        TArrayNode *node = array_index_fast(&table->buckets, i);

        node->distance = SIZE_MAX;
    }

    return status_ok(status);
}

bool table_insert(Table *table, void *obj, Status *status) {
    Array *buckets = &table->buckets;
    size_t hash = table->key_to_hash(table->obj_to_key(obj), table->seed);
    size_t distance = 0;

    for (size_t count = 0; count <= buckets->len; count++) {
        size_t i = (hash + distance) & table->bucket_mask;
        TArrayNode *node = (TArrayNode *)array_index_fast(buckets, i);

        if (table_node_empty(node)) {
            node->distance = distance;
            node->hash = hash;
            node->obj = obj;
            table->len++;

            return table_check_grow(table, status);
        }

        if (node->distance < distance) {
            size_t new_distance = node->distance;
            size_t new_hash = node->hash;
            void * new_obj = node->obj;

            node->distance = distance;
            node->hash = hash;
            node->obj = obj;

            distance = new_distance;
            hash = new_hash;
            obj = new_obj;

            count = 0; /* Reset count here */
        }

        distance++;
    }

    return table_full(status);
}

bool table_remove(Table *table, void *key, void **obj, Status *status) {
    Array *buckets = &table->buckets;
    size_t hash = table->key_to_hash(key, table->seed);
    size_t start = hash;

    for (size_t distance = 0; distance < buckets->len; distance++) {
        size_t i = (start + distance) & table->bucket_mask;
        TArrayNode *node = (TArrayNode *)array_index_fast(buckets, i);

        if (table_node_empty(node)) {
            continue;
        }

        if (node->hash != hash) {
            continue;
        }

        if (!table->key_equal(table->obj_to_key(node->obj), key)) {
            continue;
        }

        if (obj) {
            *obj = node->obj;
        }

        node->distance = SIZE_MAX;
        table->len--;

        return table_check_shrink(table, status);
    }

    return not_found(status);
}

bool table_lookup(Table *table, void *key, void **obj, Status *status) {
    Array *buckets = &table->buckets;
    size_t hash = table->key_to_hash(key, table->seed);
    size_t start = hash;

    for (size_t distance = 0; distance < buckets->len; distance++) {
        size_t i = (start + distance) & table->bucket_mask;
        TArrayNode *node = (TArrayNode *)array_index_fast(buckets, i);

        if (table_node_empty(node)) {
            continue;
        }

        if (node->hash != hash) {
            continue;
        }

        if (!table->key_equal(table->obj_to_key(node->obj), key)) {
            continue;
        }

        if (obj) {
            *obj = node->obj;
        }

        return status_ok(status);
    }

    return not_found(status);
}

void* table_iterate(Table *table, size_t *index, void *obj) {
    size_t i = 0;

    if (obj) {
        i = (*index) + 1;
    }

    while (i < table->buckets.len) {
        TArrayNode *node = (TArrayNode *)array_index_fast(&table->buckets, i);

        if (!table_node_empty(node)) {
            *index = i;
            return node->obj;
        }

        i++;
    }

    *index = 0;

    return NULL;
}

void table_clear(Table *table) {
    array_clear(&table->buckets);
    table->bucket_bit = START_BIT;
    table->bucket_max = 1 << table->bucket_bit;
    table->bucket_mask = table->bucket_max - 1;
    table->len = 0;
}

void table_free(Table *table) {
    array_free(&table->buckets);

    table->key_to_hash = NULL;
    table->obj_to_key = NULL;
    table->key_equal = NULL;
    table->seed = 0;
    table->bucket_bit = 0;
    table->bucket_max = 0;
    table->bucket_mask = 0;
    table->len = 0;
}

/* vi: set et ts=4 sw=4: */

#pragma once

#ifndef _CBASE_HASH_H__
#define _CBASE_HASH_H__

#include "cbase/internal.h"

#include <stdint.h>
#include <string.h>

#include "cbase/errors.h"
#include "cbase/xxhash.h"

enum
{
    CBASE_HASHER_ERROR = 22000,
};

typedef XXH32_state_t Hasher32;
typedef XXH32_canonical_t Hasher32Canonical;
typedef XXH64_state_t Hasher64;
typedef XXH64_canonical_t Hasher64Canonical;

CBASE_API_STATIC
uint32_t hash32(const void *input, size_t length, uint32_t seed) {
    return XXH32(input, length, seed);
}

CBASE_API_STATIC
int hash32_new(Hasher32 **hasher) {
    Hasher32 *new_hasher = XXH32_createState();

    if (!new_hasher) {
        return CBASE_ERROR_MEMORY_ALLOC_FAILED;
    }

    *hasher = new_hasher;

    return 0;
}

CBASE_API_STATIC
int hash32_free(Hasher32 *hasher) {
    if (XXH32_freeState(hasher) != XXH_OK) {
        return CBASE_HASHER_ERROR;
    }

    return 0;
}

CBASE_API_STATIC
void hash32_copy(Hasher32 *dst, const Hasher32 *src) {
    XXH32_copyState(dst, src);
}

CBASE_API_STATIC
int hash32_reset(Hasher32 *hasher, uint32_t seed) {
    if (XXH32_reset(hasher, seed) != XXH_OK) {
        return CBASE_HASHER_ERROR;
    }

    return 0;
}

CBASE_API_STATIC
int hash32_update(Hasher32 *hasher, const void *input, size_t length) {
    if (XXH32_update(hasher, input, length) != XXH_OK) {
        return CBASE_HASHER_ERROR;
    }

    return 0;
}

CBASE_API_STATIC
uint32_t hash32_digest(Hasher32 *hasher) {
    return XXH32_digest(hasher);
}

CBASE_API_STATIC
void hash32_canonical(Hasher32Canonical *dst, uint32_t hash) {
    XXH32_canonicalFromHash(dst, hash);
}

CBASE_API_STATIC
uint32_t hash32_from_canonical(const Hasher32Canonical *src) {
    return XXH32_hashFromCanonical(src);
}

CBASE_API_STATIC
uint64_t hash64(const void *input, size_t length, uint64_t seed) {
    return XXH64(input, length, seed);
}

CBASE_API_STATIC
int hash64_new(Hasher64 **hasher) {
    Hasher64 *new_hasher = XXH64_createState();

    if (!new_hasher) {
        return CBASE_ERROR_MEMORY_ALLOC_FAILED;
    }

    *hasher = new_hasher;

    return 0;
}

CBASE_API_STATIC
int hash64_free(Hasher64 *hasher) {
    if (XXH64_freeState(hasher) != XXH_OK) {
        return CBASE_HASHER_ERROR;
    }

    return 0;
}

CBASE_API_STATIC
void hash64_copy(Hasher64 *dst, const Hasher64 *src) {
    XXH64_copyState(dst, src);
}

CBASE_API_STATIC
int hash64_reset(Hasher64 *hasher, uint64_t seed) {
    if (XXH64_reset(hasher, seed) != XXH_OK) {
        return CBASE_HASHER_ERROR;
    }

    return 0;
}

CBASE_API_STATIC
int hash64_update(Hasher64 *hasher, const void *input, size_t length) {
    if (XXH64_update(hasher, input, length) != XXH_OK) {
        return CBASE_HASHER_ERROR;
    }

    return 0;
}

CBASE_API_STATIC
uint64_t hash64_digest(Hasher64 *hasher) {
    return XXH64_digest(hasher);
}

CBASE_API_STATIC
void hash64_canonical(Hasher64Canonical *dst, uint64_t hash) {
    XXH64_canonicalFromHash(dst, hash);
}

CBASE_API_STATIC
uint64_t hash64_from_canonical(const Hasher64Canonical *src) {
    return XXH64_hashFromCanonical(src);
}

CBASE_API_STATIC
uint32_t hash32_int(int32_t i, uint32_t seed) {
    return hash32(((void *)&i), sizeof(int32_t), seed);
}

CBASE_API_STATIC
uint32_t hash32_uint(uint32_t u, uint32_t seed) {
    return hash32(((void *)&u), sizeof(uint32_t), seed);
}

CBASE_API_STATIC
uint32_t hash32_string(const char *s, uint32_t seed) {
    return hash32(s, strlen((char *)s), seed);
}

CBASE_API_STATIC
uint64_t hash64_int(int64_t i, uint64_t seed) {
    return hash64(((void *)&i), sizeof(int64_t), seed);
}

CBASE_API_STATIC
uint64_t hash64_uint(uint64_t u, uint64_t seed) {
    return hash64(((void *)&u), sizeof(uint64_t), seed);
}

CBASE_API_STATIC
uint64_t hash64_string(const char *s, uint64_t seed) {
    return hash64(s, strlen((char *)s), seed);
}

#endif

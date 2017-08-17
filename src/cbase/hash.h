#ifndef HASH_H__
#define HASH_H__

#include "xxhash.h"

enum {
    HASHER_ERROR = 1,
};

typedef XXH32_state_t Hasher32;

typedef XXH32_canonical_t Hasher32Canonical;

typedef XXH64_state_t Hasher64;

typedef XXH64_canonical_t Hasher64Canonical;

static inline uint32_t hash32(const void *input, size_t length, uint32_t seed) {
    return XXH32(input, length, seed);
}

static inline bool hash32_new(Hasher32 **hasher, Status *status) {
    Hasher32 *new_hasher = XXH32_createState();

    if (!new_hasher) {
        return alloc_failure(status);
    }

    *hasher = new_hasher;

    return status_ok(status);
}

static inline bool hash32_free(Hasher32 *hasher, Status *status) {
    if (XXH32_freeState(hasher) != XXH_OK) {
        return status_failure(
            status,
            "hash32",
            HASHER_ERROR,
            "Unknown hasher error"
        );
    }

    return status_ok(status);
}

static inline void hash32_copy(Hasher32 *dst, const Hasher32 *src) {
    XXH32_copyState(dst, src);
}

static inline bool hash32_reset(Hasher32 *hasher, uint32_t seed, Status *status) {
    if (XXH32_reset(hasher, seed) != XXH_OK) {
        return status_failure(
            status,
            "hash32",
            HASHER_ERROR,
            "Unknown hasher error"
        );
    }

    return status_ok(status);
}

static inline bool Hasher32_update(Hasher32 *hasher, const void *input,
                                                     size_t length,
                                                     Status *status) {
    if (XXH32_update(hasher, input, length) != XXH_OK) {
        return status_failure(
            status,
            "hash32",
            HASHER_ERROR,
            "Unknown hasher error"
        );
    }

    return status_ok(status);
}

static inline uint32_t Hasher32_digest(Hasher32 *hasher) {
    return XXH32_digest(hasher);
}

static inline void hash32_canonical(Hasher32Canonical *dst, uint32_t hash) {
    XXH32_canonicalFromHash(dst, hash);
}

static inline uint32_t hash32_from_canonical(const Hasher32Canonical *src) {
    return XXH32_hashFromCanonical(src);
}

static inline uint64_t hash64(const void *input, size_t length, uint64_t seed) {
    return XXH64(input, length, seed);
}

static inline bool hash64_new(Hasher64 **hasher, Status *status) {
    Hasher64 *new_hasher = XXH64_createState();

    if (!new_hasher) {
        return alloc_failure(status);
    }

    *hasher = new_hasher;

    return status_ok(status);
}

static inline bool hash64_free(Hasher64 *hasher, Status *status) {
    if (XXH64_freeState(hasher) != XXH_OK) {
        return status_failure(
            status,
            "hash64",
            HASHER_ERROR,
            "Unknown hasher error"
        );
    }

    return status_ok(status);
}

static inline void hash64_copy(Hasher64 *dst, const Hasher64 *src) {
    XXH64_copyState(dst, src);
}

static inline bool hash64_reset(Hasher64 *hasher, uint64_t seed, Status *status) {
    if (XXH64_reset(hasher, seed) != XXH_OK) {
        return status_failure(
            status,
            "hash64",
            HASHER_ERROR,
            "Unknown hasher error"
        );
    }

    return status_ok(status);
}

static inline bool Hasher64_update(Hasher64 *hasher, const void *input,
                                                     size_t length,
                                                     Status *status) {
    if (XXH64_update(hasher, input, length) != XXH_OK) {
        return status_failure(
            status,
            "hash64",
            HASHER_ERROR,
            "Unknown hasher error"
        );
    }

    return status_ok(status);
}

static inline uint64_t Hasher64_digest(Hasher64 *hasher) {
    return XXH64_digest(hasher);
}

static inline void hash64_canonical(Hasher64Canonical *dst, uint64_t hash) {
    XXH64_canonicalFromHash(dst, hash);
}

static inline uint64_t hash64_from_canonical(const Hasher64Canonical *src) {
    return XXH64_hashFromCanonical(src);
}

#endif

/* vi: set et ts=4 sw=4: */

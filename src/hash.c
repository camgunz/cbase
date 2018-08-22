#include "cbase.h"

inline
uint32_t hash32(const void *input, size_t length, uint32_t seed) {
    return XXH32(input, length, seed);
}

inline
bool hash32_new(Hasher32 **hasher, Status *status) {
    Hasher32 *new_hasher = XXH32_createState();

    if (!new_hasher) {
        return alloc_failure(status);
    }

    *hasher = new_hasher;

    return status_ok(status);
}

inline
bool hash32_free(Hasher32 *hasher, Status *status) {
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

inline
void hash32_copy(Hasher32 *dst, const Hasher32 *src) {
    XXH32_copyState(dst, src);
}

inline
bool hash32_reset(Hasher32 *hasher, uint32_t seed, Status *status) {
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

inline
bool hash32_update(Hasher32 *hasher, const void *input,
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

inline
uint32_t hash32_digest(Hasher32 *hasher) {
    return XXH32_digest(hasher);
}

inline
void hash32_canonical(Hasher32Canonical *dst, uint32_t hash) {
    XXH32_canonicalFromHash(dst, hash);
}

inline
uint32_t hash32_from_canonical(const Hasher32Canonical *src) {
    return XXH32_hashFromCanonical(src);
}

inline
uint64_t hash64(const void *input, size_t length, uint64_t seed) {
    return XXH64(input, length, seed);
}

inline
bool hash64_new(Hasher64 **hasher, Status *status) {
    Hasher64 *new_hasher = XXH64_createState();

    if (!new_hasher) {
        return alloc_failure(status);
    }

    *hasher = new_hasher;

    return status_ok(status);
}

inline
bool hash64_free(Hasher64 *hasher, Status *status) {
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

inline
void hash64_copy(Hasher64 *dst, const Hasher64 *src) {
    XXH64_copyState(dst, src);
}

inline
bool hash64_reset(Hasher64 *hasher, uint64_t seed, Status *status) {
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

inline
bool hash64_update(Hasher64 *hasher, const void *input,
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

inline
uint64_t hash64_digest(Hasher64 *hasher) {
    return XXH64_digest(hasher);
}

inline
void hash64_canonical(Hasher64Canonical *dst, uint64_t hash) {
    XXH64_canonicalFromHash(dst, hash);
}

inline
uint64_t hash64_from_canonical(const Hasher64Canonical *src) {
    return XXH64_hashFromCanonical(src);
}

/* vi: set et ts=4 sw=4: */

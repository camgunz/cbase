#pragma once

#ifndef HASH_H__
#define HASH_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "cbase/status.h"

#include "xxhash.h"

enum {
    HASHER_ERROR = 1,
};

typedef XXH32_state_t Hasher32;

typedef XXH32_canonical_t Hasher32Canonical;

typedef XXH64_state_t Hasher64;

typedef XXH64_canonical_t Hasher64Canonical;

uint32_t hash32(const void *input, size_t length, uint32_t seed);
bool     hash32_new(Hasher32 **hasher, Status *status);
bool     hash32_free(Hasher32 *hasher, Status *status);
void     hash32_copy(Hasher32 *dst, const Hasher32 *src);
bool     hash32_reset(Hasher32 *hasher, uint32_t seed, Status *status);
bool     hash32_update(Hasher32 *hasher, const void *input,
                                                     size_t length,
                                                     Status *status);
uint32_t hash32_digest(Hasher32 *hasher);
void     hash32_canonical(Hasher32Canonical *dst, uint32_t hash);
uint32_t hash32_from_canonical(const Hasher32Canonical *src);

uint64_t hash64(const void *input, size_t length, uint64_t seed);
bool     hash64_new(Hasher64 **hasher, Status *status);
bool     hash64_free(Hasher64 *hasher, Status *status);
void     hash64_copy(Hasher64 *dst, const Hasher64 *src);
bool     hash64_reset(Hasher64 *hasher, uint64_t seed, Status *status);
bool     hash64_update(Hasher64 *hasher, const void *input,
                                                     size_t length,
                                                     Status *status);
uint64_t hash64_digest(Hasher64 *hasher);
void     hash64_canonical(Hasher64Canonical *dst, uint64_t hash);
uint64_t hash64_from_canonical(const Hasher64Canonical *src);

#endif

/* vi: set et ts=4 sw=4: */

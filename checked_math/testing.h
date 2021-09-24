#pragma once

#ifndef __TESTING_H
#define __TESTING_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define compare_func_2(op, int_t, signed, bits)                               \
    static void compare_##op##_##signed##bits(int_t a, int_t b) {             \
        int_t r1, r2;                                                         \
        bool o1 = checked_##op##_##signed##bits##_1(a, b, &r1);               \
        bool o2 = checked_##op##_##signed##bits##_2(a, b, &r2);               \
        assert(r1 == r2);                                                     \
        assert(o1 == o2);                                                     \
    }

#define compare_func_3(op, int_t, signed, bits)                               \
    static void compare_##op##_##signed##bits(int_t a, int_t b) {             \
        int_t r1, r2, r3;                                                     \
        bool o1 = checked_##op##_##signed##bits##_1(a, b, &r1);               \
        bool o2 = checked_##op##_##signed##bits##_2(a, b, &r2);               \
        bool o3 = checked_##op##_##signed##bits##_3(a, b, &r3);               \
        assert(r1 == r2);                                                     \
        assert(r1 == r3);                                                     \
        assert(o1 == o2);                                                     \
        assert(o1 == o3);                                                     \
    }

#define compare_func_7(op, int_t, signed, bits)                               \
    static void compare_##op##_##signed##bits(int_t a, int_t b) {             \
        int_t r1, r2, r3, r4, r5, r6, r7;                                     \
        bool o1 = checked_##op##_##signed##bits##_1(a, b, &r1);               \
        bool o2 = checked_##op##_##signed##bits##_2(a, b, &r2);               \
        bool o3 = checked_##op##_##signed##bits##_3(a, b, &r3);               \
        bool o4 = checked_##op##_##signed##bits##_4(a, b, &r4);               \
        bool o5 = checked_##op##_##signed##bits##_5(a, b, &r5);               \
        bool o6 = checked_##op##_##signed##bits##_6(a, b, &r6);               \
        bool o7 = checked_##op##_##signed##bits##_7(a, b, &r7);               \
        assert(r1 == r2);                                                     \
        assert(r1 == r3);                                                     \
        assert(r1 == r4);                                                     \
        assert(r1 == r5);                                                     \
        assert(r1 == r6);                                                     \
        assert(r1 == r7);                                                     \
        assert(o1 == o2);                                                     \
        assert(o1 == o3);                                                     \
        assert(o1 == o4);                                                     \
        assert(o1 == o5);                                                     \
        assert(o1 == o6);                                                     \
        assert(o1 == o7);                                                     \
    }

#define all_test_func(op, int_t, signed, bits, min, max)                      \
    static void all_test_##op##_##signed##bits(void) {                        \
        int_t i = min;                                                        \
        int_t j = min;                                                        \
                                                                              \
        while (true) {                                                        \
            compare_##op##_##signed##bits(i, j);                              \
                                                                              \
            if (i != max) {                                                   \
                i++;                                                          \
            }                                                                 \
            else if (j == max) {                                              \
                break;                                                        \
            }                                                                 \
            else {                                                            \
                i = min;                                                      \
                j++;                                                          \
            }                                                                 \
        }                                                                     \
    }

#define rand_test_func(op, signed, bits)                                      \
    static void rand_test_##op##_##signed##bits(unsigned int test_count) {    \
        for (unsigned int i = 0; i < test_count; i++) {                       \
            compare_##op##_##signed##bits(rand##bits(), rand##bits());        \
        }                                                                     \
    }

#define edge_test_func(op, int_t, signed, bits, max)                          \
    static void edge_test_##op##_##signed##bits(void) {                       \
        unsigned __int128 x, y;                                               \
        __int128 z, w;                                                        \
        for (x = (__int128)max - 1000U; x < (__int128)max + 1000U; x++) {     \
            for (y = (__int128)max - 1000U; y < (__int128)max + 1000U; y++) { \
                compare_##op##_##signed##bits((int_t)x, (int_t)y);            \
            }                                                                 \
        }                                                                     \
        for (z = -1000; z < 1000; z++) {                                      \
            for (w = -1000; w < 1000; w++) {                                  \
                compare_##op##_##signed##bits((int_t)z, (int_t)w);            \
            }                                                                 \
        }                                                                     \
        for (x = (__int128)max - 1000U; x < (__int128)max + 1000U; x++) {     \
            for (w = -1000; w < 1000; w++) {                                  \
                compare_##op##_##signed##bits((int_t)x, (int_t)w);            \
                compare_##op##_##signed##bits((int_t)w, (int_t)x);            \
            }                                                                 \
        }                                                                     \
    }

#endif

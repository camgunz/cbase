#ifndef UTIL_H__
#define UTIL_H__

static inline bool check_overflow(size_t a, size_t b) {
    return !((a > 1) && (b > 1) && ((SIZE_MAX / a) < b));
}

#endif

/* vi: set et ts=4 sw=4: */

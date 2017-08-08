#ifndef UTIL_H__
#define UTIL_H__

static inline bool check_overflow(size_t a, size_t b) {
    return !((a > 1) && (b > 1) && ((SIZE_MAX / a) < b));
}

static inline bool zero_buf(void *buf, size_t count, size_t size) {
    if (!check_overflow(count, size) {
        return false;
    }

    (void)memset(buf, 0, byte_count);

    return true;
}

#endif

/* vi: set et ts=4 sw=4: */

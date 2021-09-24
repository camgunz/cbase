#include <stdbool.h>
#include <stdint.h>

bool _checked_add_s8_os(int8_t a, int8_t b, int8_t *rp) {
    uint8_t r = (uint8_t)a + (uint8_t)b;
    *rp = r;
    return (((uint8_t)a ^ r) & ((uint8_t)b ^ r)) >> (8 - 1);
}

bool _checked_add_s16_os(int16_t a, int16_t b, int16_t *rp) {
    uint16_t ur = (uint16_t)a + (uint16_t)b;
    uint16_t sr = ur >> (16 - 1);
    uint16_t sa = (uint16_t)a >> (16 - 1);
    uint16_t sb = (uint16_t)b >> (16 - 1);
    *rp = ur;
    return (sa && sb && !sr) || (!sa && !sb && sr);
}

bool _checked_add_s32_os(int32_t a, int32_t b, int32_t *rp) {
    int64_t lr = (int64_t)a + (int64_t)b;
    *rp = (int32_t)lr;
    return lr > INT32_MAX || lr < INT32_MIN;
}

bool _checked_add_s64_os(int64_t a, int64_t b, int64_t *rp) {
    static const uint64_t mask = (uint64_t)1 << (64 - 1);
    *rp = (uint64_t)a + (uint64_t)b;
    return ((uint64_t)a & mask) == ((uint64_t)b & mask) &&
           ((uint64_t)a & mask) != ((uint64_t)*rp & mask);
}

bool _checked_add_s8_o3(int8_t a, int8_t b, int8_t *rp) {
    static const uint8_t mask = (uint8_t)1 << (8 - 1);
    *rp = (uint8_t)a + (uint8_t)b;
    return ((uint8_t)a & mask) == ((uint8_t)b & mask) &&
           ((uint8_t)a & mask) != ((uint8_t)*rp & mask);
}

bool _checked_add_s16_o3(int16_t a, int16_t b, int16_t *rp) {
    uint16_t r = (uint16_t)a + (uint16_t)b;
    *rp = r;
    return (((uint16_t)a ^ r) & ((uint16_t)b ^ r)) >> (16 - 1);
}

bool _checked_add_s32_o3(int32_t a, int32_t b, int32_t *rp) {
    uint32_t r = (uint32_t)a + (uint32_t)b;
    *rp = r;
    return (((uint32_t)a ^ r) & ((uint32_t)b ^ r)) >> (32 - 1);
}

bool _checked_add_s64_o3(int64_t a, int64_t b, int64_t *rp) {
    static const uint64_t mask = (uint64_t)1 << (64 - 1);
    *rp = (uint64_t)a + (uint64_t)b;
    return ((uint64_t)a & mask) == ((uint64_t)b & mask) &&
           ((uint64_t)a & mask) != ((uint64_t)*rp & mask);
}

bool _checked_add_u8(uint8_t a, uint8_t b, uint8_t *rp) {
  *rp = a + b;

  return (((a > (UINT8_MAX >> 1)) && (b > (UINT8_MAX >> 1))) ||
          ((b < a) && ((b << 1) > (UINT8_MAX - (a - b)))) ||
          ((a < b) && ((a << 1) > (UINT8_MAX - (b - a)))));
}

bool _checked_add_u16(uint16_t a, uint16_t b, uint16_t *rp) {
  *rp = a + b;

  return (((a > (UINT16_MAX >> 1)) && (b > (UINT16_MAX >> 1))) ||
          ((b < a) && ((b << 1) > (UINT16_MAX - (a - b)))) ||
          ((a < b) && ((a << 1) > (UINT16_MAX - (b - a)))));
}

bool _checked_add_u32(uint32_t a, uint32_t b, uint32_t *rp) {
  *rp = a + b;

  return (((a > (UINT32_MAX >> 1)) && (b > (UINT32_MAX >> 1))) ||
          ((b < a) && ((b << 1) > (UINT32_MAX - (a - b)))) ||
          ((a < b) && ((a << 1) > (UINT32_MAX - (b - a)))));
}

bool _checked_add_u64(uint64_t a, uint64_t b, uint64_t *rp) {
  *rp = a + b;

  return (((a > (UINT64_MAX >> 1)) && (b > (UINT64_MAX >> 1))) ||
          ((b < a) && ((b << 1) > (UINT64_MAX - (a - b)))) ||
          ((a < b) && ((a << 1) > (UINT64_MAX - (b - a)))));
}

bool _checked_sub_s8(int8_t a, int8_t b, int8_t *rp) {
    int16_t lr = (int16_t)a - (int16_t) b;
    *rp = (int8_t)lr;
    return lr > INT8_MAX || lr < INT8_MIN;
}

bool _checked_sub_s16(int16_t a, int16_t b, int16_t *rp) {
    int32_t lr = (int32_t)a - (int32_t) b;
    *rp = (int16_t)lr;
    return lr > INT16_MAX || lr < INT16_MIN;
}

bool _checked_sub_s32(int32_t a, int32_t b, int32_t *rp) {
    int64_t lr = (int64_t)a - (int64_t) b;
    *rp = (int32_t)lr;
    return lr > INT32_MAX || lr < INT32_MIN;
}

bool _checked_sub_s64(int32_t a, int32_t b, int32_t *rp) {
    __int128 lr = (__int128)a - (__int128) b;
    *rp = (int32_t)lr;
    return lr > INT64_MAX || lr < INT64_MIN;
}

bool _checked_sub_u8(uint8_t a, uint8_t b, uint8_t *rp) {
  uint16_t lr = (uint16_t)a - (uint16_t)b;
  *rp = (uint8_t)lr;
  return lr > UINT8_MAX;
}

bool _checked_sub_u16(uint16_t a, uint16_t b, uint16_t *rp) {
  uint32_t lr = (uint32_t)a - (uint32_t)b;
  *rp = (uint16_t)lr;
  return lr > UINT16_MAX;
}

bool _checked_sub_u32(uint32_t a, uint32_t b, uint32_t *rp) {
  uint64_t lr = (uint64_t)a - (uint64_t)b;
  *rp = (uint32_t)lr;
  return lr > UINT32_MAX;
}

bool _checked_sub_u64(uint64_t a, uint64_t b, uint64_t *rp) {
  unsigned __int128 lr = (unsigned __int128)a - (unsigned __int128)b;
  *rp = (uint64_t)lr;
  return lr > UINT64_MAX;
}

bool _checked_mul_s8(int8_t a, int8_t b, int8_t *rp) {
    int16_t lr = (int16_t)a * (int16_t)b;
    *rp = (int8_t)lr;

    return lr > INT8_MAX || lr < INT8_MIN;
}

bool _checked_mul_s16(int16_t a, int16_t b, int16_t *rp) {
    int32_t lr = (int32_t)a * (int32_t)b;
    *rp = (int16_t)lr;

    return lr > INT16_MAX || lr < INT16_MIN;
}

bool _checked_mul_s32(int32_t a, int32_t b, int32_t *rp) {
    int64_t lr = (int64_t)a * (int64_t)b;
    *rp = (int32_t)lr;

    return lr > INT32_MAX || lr < INT32_MIN;
}

bool _checked_mul_s64(int64_t a, int64_t b, int64_t *rp) {
    __int128 lr = (__int128)a * (__int128)b;
    *rp = (int64_t)lr;

    return lr > INT64_MAX || lr < INT64_MIN;
}

bool _checked_mul_u8(uint8_t a, uint8_t b, uint8_t *rp) {
    *rp = a * b;
    return ((a > 1) && (b > 1) && ((UINT8_MAX / a) < b));
}

bool _checked_mul_u16(uint16_t a, uint16_t b, uint16_t *rp) {
    *rp = a * b;
    return ((a > 1) && (b > 1) && ((UINT16_MAX / a) < b));
}

bool _checked_mul_u32(uint32_t a, uint32_t b, uint32_t *rp) {
    *rp = a * b;
    return ((a > 1) && (b > 1) && ((UINT32_MAX / a) < b));
}

bool _checked_mul_u64(uint64_t a, uint64_t b, uint64_t *rp) {
    *rp = a * b;
    return ((a > 1) && (b > 1) && ((UINT64_MAX / a) < b));
}

bool _checked_div_s8(int8_t a, int8_t b, int8_t *rp) {
    if (b == 0) {
        return true;
    }

    if (a == 0) {
        *rp = 0;
        return false;
    }

    if (((a == -1) && (b == INT8_MIN)) || ((b == -1) && (a == INT8_MIN))) {
        *rp = 0;
        return true;
    }

    *rp = a / b;
    return false;
}

bool _checked_div_s16(int16_t a, int16_t b, int16_t *rp) {
    if (b == 0) {
        return true;
    }

    if (a == 0) {
        *rp = 0;
        return false;
    }

    if (((a == -1) && (b == INT16_MIN)) || ((b == -1) && (a == INT16_MIN))) {
        *rp = 0;
        return true;
    }

    *rp = a / b;
    return false;
}

bool _checked_div_s32(int32_t a, int32_t b, int32_t *rp) {
    if (b == 0) {
        return true;
    }

    if (a == 0) {
        *rp = 0;
        return false;
    }

    if (((a == -1) && (b == INT32_MIN)) || ((b == -1) && (a == INT32_MIN))) {
        *rp = 0;
        return true;
    }

    *rp = a / b;
    return false;
}

bool _checked_div_s64(int64_t a, int64_t b, int64_t *rp) {
    if (b == 0) {
        return true;
    }

    if (a == 0) {
        *rp = 0;
        return false;
    }

    if (((a == -1) && (b == INT64_MIN)) || ((b == -1) && (a == INT64_MIN))) {
        *rp = 0;
        return true;
    }

    *rp = a / b;
    return false;
}

bool _checked_div_u8(uint8_t a, uint8_t b, uint8_t *rp) {
    if (b == 0) {
        return true;
    }

    if (a == 0) {
        *rp = 0;
        return false;
    }

    *rp = a / b;
    return false;
}

bool _checked_div_u16(uint16_t a, uint16_t b, uint16_t *rp) {
    if (b == 0) {
        return true;
    }

    if (a == 0) {
        *rp = 0;
        return false;
    }

    *rp = a / b;
    return false;
}

bool _checked_div_u32(uint32_t a, uint32_t b, uint32_t *rp) {
    if (b == 0) {
        return true;
    }

    if (a == 0) {
        *rp = 0;
        return false;
    }

    *rp = a / b;
    return false;
}

bool _checked_div_u64(uint64_t a, uint64_t b, uint64_t *rp) {
    if (b == 0) {
        return true;
    }

    if (a == 0) {
        *rp = 0;
        return false;
    }

    *rp = a / b;
    return false;
}

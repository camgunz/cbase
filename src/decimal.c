#include "cbase.h"

#define invalid_context_config_value(status) status_failure( \
    status,                                                  \
    "decimal",                                               \
    DECIMAL_INVALID_CONTEXT_CONFIG_VALUE,                    \
    "Invalid context configuration value"                    \
)

#define invalid_conversion_syntax(status) status_failure( \
    status,                                               \
    "decimal",                                            \
    DECIMAL_INVALID_CONVERSION_SYNTAX,                    \
    "Invalid conversion syntax"                           \
)

#define division_impossible(status) status_failure( \
    status,                                         \
    "decimal",                                      \
    DECIMAL_DIVISION_IMPOSSIBLE,                    \
    "Division is impossible"                        \
)

#define division_undefined(status) status_failure( \
    status,                                        \
    "decimal",                                     \
    DECIMAL_DIVISION_UNDEFINED,                    \
    "Division is undefined"                        \
)

#define invalid_context(status) status_failure( \
    status,                                     \
    "decimal",                                  \
    DECIMAL_INVALID_CONTEXT,                    \
    "Invalid context"                           \
)

#define invalid_operation(status) status_failure( \
    status,                                       \
    "decimal",                                    \
    DECIMAL_INVALID_OPERATION,                    \
    "Invalid operation"                           \
)

#define clamped(status) status_failure( \
    status,                             \
    "decimal",                          \
    DECIMAL_CLAMPED,                    \
    "Clamped"                           \
)

#define division_by_zero(status) status_failure( \
    status,                                      \
    "decimal",                                   \
    DECIMAL_DIVISION_BY_ZERO,                    \
    "Division by zero"                           \
)

#define fpu_error(status) status_failure( \
    status,                               \
    "decimal",                            \
    DECIMAL_FPU_ERROR,                    \
    "FPU error"                           \
)

#define inexact(status) status_failure( \
    status,                             \
    "decimal",                          \
    DECIMAL_INEXACT,                    \
    "Inexact"                           \
)

#define not_implemented(status) status_failure( \
    status,                                     \
    "decimal",                                  \
    DECIMAL_NOT_IMPLEMENTED,                    \
    "Not implemented"                           \
)

#define overflow(status) status_failure( \
    status,                              \
    "decimal",                           \
    DECIMAL_OVERFLOW,                    \
    "Overflow"                           \
)

#define rounded(status) status_failure( \
    status,                             \
    "decimal",                          \
    DECIMAL_ROUNDED,                    \
    "Rounded"                           \
)

#define subnormal(status) status_failure( \
    status,                               \
    "decimal",                            \
    DECIMAL_SUBNORMAL,                    \
    "Subnormal"                           \
)

#define underflow(status) status_failure( \
    status,                               \
    "decimal",                            \
    DECIMAL_UNDERFLOW,                    \
    "Underflow"                           \
)

#define unknown(status) status_failure( \
    status,                             \
    "decimal",                          \
    DECIMAL_UNKNOWN_ERROR,              \
    "Unknown error"                     \
)

bool decimal_handle_error_code(uint32_t error_code, Status *status) {
    switch (error_code) {
        case 0:
            return status_ok(status);
        case MPD_Conversion_syntax:
            return invalid_conversion_syntax(status);
        case MPD_Division_impossible:
            return division_impossible(status);
        case MPD_Division_undefined:
            return division_undefined(status);
        case MPD_Invalid_context:
            return invalid_context(status);
        case MPD_Invalid_operation:
            return invalid_operation(status);
        case MPD_Malloc_error:
            return alloc_failure(status);
        case MPD_Clamped:
            return clamped(status);
        case MPD_Division_by_zero:
            return division_by_zero(status);
        case MPD_Fpu_error:
            return fpu_error(status);
        case MPD_Inexact:
            return inexact(status);
        case MPD_Not_implemented:
            return not_implemented(status);
        case MPD_Overflow:
            return overflow(status);
        case MPD_Rounded:
            return rounded(status);
        case MPD_Subnormal:
            return subnormal(status);
        case MPD_Underflow:
            return underflow(status);
        default:
            return status_ok(status);
    }
}

inline bool decimal_context_set_precision(DecimalContext *ctx,
                                          ssize_t emax,
                                          Status *status) {
    if (mpd_qsetemax(ctx, emax) == 0) {
        return invalid_context_config_value(status);
    }

    return status_ok(status);
}

inline bool decimal_context_set_eminision(DecimalContext *ctx,
                                          ssize_t emin,
                                          Status *status) {
    if (mpd_qsetemin(ctx, emin) == 0) {
        return invalid_context_config_value(status);
    }

    return status_ok(status);
}

inline bool decimal_context_set_rounding(DecimalContext *ctx, int rounding,
                                                              Status *status) {
    if (mpd_qsetround(ctx, rounding) == 0) {
        return invalid_context_config_value(status);
    }

    return status_ok(status);
}

inline bool decimal_context_set_traps(DecimalContext *ctx, uint32_t traps,
                                                           Status *status) {
    if (mpd_qsettraps(ctx, traps) == 0) {
        return invalid_context_config_value(status);
    }

    return status_ok(status);
}

inline bool decimal_context_set_status(DecimalContext *ctx,
                                       uint32_t ctx_status,
                                       Status *status) {
    if (mpd_qsetstatus(ctx, ctx_status) == 0) {
        return invalid_context_config_value(status);
    }

    return status_ok(status);
}

inline bool decimal_context_set_clamp(DecimalContext *ctx, int clamping,
                                                           Status *status) {
    if (mpd_qsetclamp(ctx, clamping) == 0) {
        return invalid_context_config_value(status);
    }

    return status_ok(status);
}

inline bool decimal_context_set_correct_rounding(DecimalContext *ctx,
                                                 int correct_rounding,
                                                 Status *status) {
    if (mpd_qsetcr(ctx, correct_rounding) == 0) {
        return invalid_context_config_value(status);
    }

    return status_ok(status);
}

inline bool decimal_from_cstr(Decimal *dec, const char *s,
                                            const DecimalContext *ctx,
                                            Status *status) {
    uint32_t res = 0;

    mpd_qset_string(dec, s, ctx, &res);

    return decimal_handle_error_code(res, status);
}

inline bool decimal_from_ssize(Decimal *dec, ssize_t ssize,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qset_ssize(dec, ssize, ctx, &res);

    return decimal_handle_error_code(res, status);
}

inline bool decimal_from_i32(Decimal *dec, int32_t i32,
                                           const DecimalContext *ctx,
                                           Status *status) {
    uint32_t res = 0;

    mpd_qset_i32(dec, i32, ctx, &res);

    return decimal_handle_error_code(res, status);
}

inline bool decimal_from_i64(Decimal *dec, int64_t i64,
                                           const DecimalContext *ctx,
                                           Status *status) {
    uint32_t res = 0;

    mpd_qset_i64(dec, i64, ctx, &res);

    return decimal_handle_error_code(res, status);
}

inline bool decimal_from_uint(Decimal *dec, unsigned int uint,
                                            const DecimalContext *ctx,
                                            Status *status) {
    uint32_t res = 0;

    mpd_qset_uint(dec, uint, ctx, &res);

    return decimal_handle_error_code(res, status);
}

inline bool decimal_from_u32(Decimal *dec, uint32_t u32,
                                           const DecimalContext *ctx,
                                           Status *status) {
    uint32_t res = 0;

    mpd_qset_u32(dec, u32, ctx, &res);

    return decimal_handle_error_code(res, status);
}

inline bool decimal_from_u64(Decimal *dec, uint64_t u64,
                                           const DecimalContext *ctx,
                                           Status *status) {
    uint32_t res = 0;

    mpd_qset_u64(dec, u64, ctx, &res);

    return decimal_handle_error_code(res, status);
}

inline bool decimal_from_max(Decimal *dec, DecimalContext *ctx,
                                           Status *status) {
    uint32_t res = 0;

    mpd_qmaxcoeff(dec, ctx, &res);

    return decimal_handle_error_code(res, status);
}

inline bool decimal_to_sci_cstr(Decimal *dec, bool uppercase, char **out,
                                                              Status *status) {
    int fmt = 0;

    if (uppercase) {
        fmt = 1;
    }

    char *local_out = mpd_to_sci(dec, fmt);

    if (!local_out) {
        return alloc_failure(status);
    }

    *out = local_out;

    return status_ok(status);
}

inline bool decimal_to_eng_cstr(Decimal *dec, bool uppercase, char **out,
                                                              Status *status) {
    int fmt = 0;

    if (uppercase) {
        fmt = 1;
    }

    char *local_out = mpd_to_eng(dec, fmt);

    if (!local_out) {
        return alloc_failure(status);
    }

    *out = local_out;

    return status_ok(status);
}

inline bool decimal_to_sci_cstr_size(Decimal *dec, bool uppercase,
                                                   char **out,
                                                   ssize_t *len,
                                                   Status *status) {
    int fmt = 0;
    char *local_out = NULL;
    ssize_t local_len = 0;

    if (uppercase) {
        fmt = 1;
    }

    local_len = mpd_to_sci_size(&local_out, dec, fmt);

    if (!local_out) {
        return alloc_failure(status);
    }

    *out = local_out;
    *len = local_len;

    return status_ok(status);
}

inline bool decimal_to_eng_cstr_size(Decimal *dec, bool uppercase,
                                                   char **out,
                                                   ssize_t *len,
                                                   Status *status) {
    int fmt = 0;
    char *local_out = NULL;
    ssize_t local_len = 0;

    if (uppercase) {
        fmt = 1;
    }

    local_len = mpd_to_eng_size(&local_out, dec, fmt);

    if (!local_out) {
        return alloc_failure(status);
    }

    *out = local_out;
    *len = local_len;

    return status_ok(status);
}

inline bool decimal_to_ssize(Decimal *dec, ssize_t *out, Status *status) {
    uint32_t res = 0;
    ssize_t local_out;
    
    local_out = mpd_qget_ssize(dec, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    *out = local_out;

    return status_ok(status);
}

inline bool decimal_to_i32(Decimal *dec, int32_t *out, Status *status) {
    uint32_t res = 0;
    int32_t local_out;

    local_out = mpd_qget_i32(dec, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    *out = local_out;

    return status_ok(status);
}

inline bool decimal_to_i64(Decimal *dec, int64_t *out, Status *status) {
    uint32_t res = 0;
    int64_t local_out;

    local_out = mpd_qget_i64(dec, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    *out = local_out;

    return status_ok(status);
}

inline bool decimal_to_uint(Decimal *dec, unsigned int *out, Status *status) {
    uint32_t res = 0;
    unsigned int local_out;
    
    local_out = mpd_qget_uint(dec, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    *out = local_out;

    return status_ok(status);
}

inline bool decimal_to_u32(Decimal *dec, uint32_t *out, Status *status) {
    uint32_t res = 0;
    uint32_t local_out;

    local_out = mpd_qget_u32(dec, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    *out = local_out;

    return status_ok(status);
}

inline bool decimal_to_u64(Decimal *dec, uint64_t *out, Status *status) {
    uint32_t res = 0;
    uint64_t local_out;

    local_out = mpd_qget_u64(dec, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    *out = local_out;

    return status_ok(status);
}

inline bool decimal_to_abs(Decimal *dec, unsigned int *out, Status *status) {
    uint32_t res = 0;
    unsigned int local_out;

    local_out = mpd_qabs_uint(dec, &res);
    
    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    *out = local_out;

    return status_ok(status);
}

inline bool decimal_copy(Decimal *dst, Decimal *src, Status *status) {
    uint32_t res = 0;

    (void)mpd_qcopy(dst, src, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_copy_abs(Decimal *dst, Decimal *src, Status *status) {
    uint32_t res = 0;

    (void)mpd_qcopy_abs(dst, src, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_copy_negate(Decimal *dst, Decimal *src, Status *status) {
    uint32_t res = 0;

    (void)mpd_qcopy_negate(dst, src, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_copy_sign(Decimal *dst, Decimal *src, Decimal *sign,
                                                          Status *status) {
    uint32_t res = 0;

    (void)mpd_qcopy_sign(dst, src, sign, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_cmp(const Decimal *a, const Decimal *b, int *result,
                                                            Status *status) {
    uint32_t mpd_status = 0;
    int local_result = 0;

    local_result = mpd_qcmp(a, b, &mpd_status);

    if (mpd_status != 0) {
        return decimal_handle_error_code(mpd_status, status);
    }

    *result = local_result;

    return status_ok(status);
}

inline bool decimal_add(Decimal *result, const Decimal *a,
                                         const Decimal *b,
                                         const DecimalContext *ctx,
                                         Status *status) {
    uint32_t res = 0;

    mpd_qadd(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_add_ssize(Decimal *result, const Decimal *a,
                                               ssize_t b,
                                               const DecimalContext *ctx,
                                               Status *status) {
    uint32_t res = 0;

    mpd_qadd_ssize(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_add_i32(Decimal *result, const Decimal *a,
                                             int32_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qadd_i32(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_add_i64(Decimal *result, const Decimal *a,
                                             int64_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qadd_i64(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_add_uint(Decimal *result, const Decimal *a,
                                              unsigned int b,
                                              const DecimalContext *ctx,
                                              Status *status) {
    uint32_t res = 0;

    mpd_qadd_uint(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_add_u32(Decimal *result, const Decimal *a,
                                             uint32_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qadd_u32(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_add_u64(Decimal *result, const Decimal *a,
                                             uint64_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qadd_u64(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_sub(Decimal *result, const Decimal *a,
                                         const Decimal *b,
                                         const DecimalContext *ctx,
                                         Status *status) {
    uint32_t res = 0;

    mpd_qsub(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_sub_ssize(Decimal *result, const Decimal *a,
                                               ssize_t b,
                                               const DecimalContext *ctx,
                                               Status *status) {
    uint32_t res = 0;

    mpd_qsub_ssize(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_sub_i32(Decimal *result, const Decimal *a,
                                             int32_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qsub_i32(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_sub_i64(Decimal *result, const Decimal *a,
                                             int64_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qsub_i64(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_sub_uint(Decimal *result, const Decimal *a,
                                              unsigned int b,
                                              const DecimalContext *ctx,
                                              Status *status) {
    uint32_t res = 0;

    mpd_qsub_uint(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_sub_u32(Decimal *result, const Decimal *a,
                                             uint32_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qsub_u32(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_sub_u64(Decimal *result, const Decimal *a,
                                             uint64_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qsub_u64(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_mul(Decimal *result, const Decimal *a,
                                         const Decimal *b,
                                         const DecimalContext *ctx,
                                         Status *status) {
    uint32_t res = 0;

    mpd_qmul(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_mul_ssize(Decimal *result, const Decimal *a,
                                               ssize_t b,
                                               const DecimalContext *ctx,
                                               Status *status) {
    uint32_t res = 0;

    mpd_qmul_ssize(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_mul_i32(Decimal *result, const Decimal *a,
                                             int32_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qmul_i32(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_mul_i64(Decimal *result, const Decimal *a,
                                             int64_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qmul_i64(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_mul_uint(Decimal *result, const Decimal *a,
                                              unsigned int b,
                                              const DecimalContext *ctx,
                                              Status *status) {
    uint32_t res = 0;

    mpd_qmul_uint(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_mul_u32(Decimal *result, const Decimal *a,
                                             uint32_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qmul_u32(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_mul_u64(Decimal *result, const Decimal *a,
                                             uint64_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qmul_u64(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_div(Decimal *result, const Decimal *a,
                                         const Decimal *b,
                                         const DecimalContext *ctx,
                                         Status *status) {
    uint32_t res = 0;

    mpd_qdiv(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_div_ssize(Decimal *result, const Decimal *a,
                                               ssize_t b,
                                               const DecimalContext *ctx,
                                               Status *status) {
    uint32_t res = 0;

    mpd_qdiv_ssize(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_div_i32(Decimal *result, const Decimal *a,
                                             int32_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qdiv_i32(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_div_i64(Decimal *result, const Decimal *a,
                                             int64_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qdiv_i64(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_div_uint(Decimal *result, const Decimal *a,
                                              unsigned int b,
                                              const DecimalContext *ctx,
                                              Status *status) {
    uint32_t res = 0;

    mpd_qdiv_uint(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_div_u32(Decimal *result, const Decimal *a,
                                             uint32_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qdiv_u32(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_div_u64(Decimal *result, const Decimal *a,
                                             uint64_t b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qdiv_u64(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_fma(Decimal *result, const Decimal *a,
                                         const Decimal *b,
                                         const Decimal *c,
                                         const DecimalContext *ctx,
                                         Status *status) {
    uint32_t res = 0;

    mpd_qfma(result, a, b, c, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_divint(Decimal *result, const Decimal *a,
                                            const Decimal *b,
                                            const DecimalContext *ctx,
                                            Status *status) {
    uint32_t res = 0;

    mpd_qdivint(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_rem(Decimal *result, const Decimal *a,
                                         const Decimal *b,
                                         const DecimalContext *ctx,
                                         Status *status) {
    uint32_t res = 0;

    mpd_qrem(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_rem_near(Decimal *result, const Decimal *a,
                                              const Decimal *b,
                                              const DecimalContext *ctx,
                                              Status *status) {
    uint32_t res = 0;

    mpd_qrem_near(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_divmod(Decimal *q, Decimal *r, const Decimal *a,
                                                   const Decimal *b,
                                                   const DecimalContext *ctx,
                                                   Status *status) {
    uint32_t res = 0;

    mpd_qdivmod(q, r, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_exp(Decimal *result, const Decimal *a,
                                         const DecimalContext *ctx,
                                         Status *status) {
    uint32_t res = 0;

    mpd_qexp(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_ln(Decimal *result, const Decimal *a,
                                        const DecimalContext *ctx,
                                        Status *status) {
    uint32_t res = 0;

    mpd_qln(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_log10(Decimal *result, const Decimal *a,
                                           const DecimalContext *ctx,
                                           Status *status) {
    uint32_t res = 0;

    mpd_qlog10(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_pow(Decimal *result, const Decimal *base,
                                         const Decimal *exp,
                                         const DecimalContext *ctx,
                                         Status *status) {
    uint32_t res = 0;

    mpd_qpow(result, base, exp, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_sqrt(Decimal *result, const Decimal *a,
                                          const DecimalContext *ctx,
                                          Status *status) {
    uint32_t res = 0;

    mpd_qsqrt(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_invroot(Decimal *result, const Decimal *a,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qinvroot(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_minus(Decimal *result, const Decimal *a,
                                           const DecimalContext *ctx,
                                           Status *status) {
    uint32_t res = 0;

    mpd_qminus(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_plus(Decimal *result, const Decimal *a,
                                          const DecimalContext *ctx,
                                          Status *status) {
    uint32_t res = 0;

    mpd_qplus(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_abs(Decimal *result, const Decimal *a,
                                         const DecimalContext *ctx,
                                         Status *status) {
    uint32_t res = 0;

    mpd_qabs(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_max(Decimal *result, const Decimal *a,
                                         const Decimal *b,
                                         const DecimalContext *ctx,
                                         Status *status) {
    uint32_t res = 0;

    mpd_qmax(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_max_mag(Decimal *result, const Decimal *a,
                                             const Decimal *b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qmax_mag(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_min(Decimal *result, const Decimal *a,
                                         const Decimal *b,
                                         const DecimalContext *ctx,
                                         Status *status) {
    uint32_t res = 0;

    mpd_qmin(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_min_mag(Decimal *result, const Decimal *a,
                                             const Decimal *b,
                                             const DecimalContext *ctx,
                                             Status *status) {
    uint32_t res = 0;

    mpd_qmin_mag(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_next_minus(Decimal *result, const Decimal *a,
                                                const DecimalContext *ctx,
                                                Status *status) {
    uint32_t res = 0;

    mpd_qnext_minus(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_next_plus(Decimal *result, const Decimal *a,
                                               const DecimalContext *ctx,
                                               Status *status) {
    uint32_t res = 0;

    mpd_qnext_plus(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_next_toward(Decimal *result, const Decimal *a,
                                                 const Decimal *b,
                                                 const DecimalContext *ctx,
                                                 Status *status) {
    uint32_t res = 0;

    mpd_qnext_toward(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_quantize(Decimal *result, const Decimal *a,
                                              const Decimal *b,
                                              const DecimalContext *ctx,
                                              Status *status) {
    uint32_t res = 0;

    mpd_qquantize(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_reduce(Decimal *result, const Decimal *a,
                                            const DecimalContext *ctx,
                                            Status *status) {
    uint32_t res = 0;

    mpd_qreduce(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_round_to_intx(Decimal *result, const Decimal *a,
                                                   const DecimalContext *ctx,
                                                   Status *status) {
    uint32_t res = 0;

    mpd_qround_to_intx(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_round_to_int(Decimal *result, const Decimal *a,
                                                  const DecimalContext *ctx,
                                                  Status *status) {
    uint32_t res = 0;

    mpd_qround_to_int(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_floor(Decimal *result, const Decimal *a,
                                           const DecimalContext *ctx,
                                           Status *status) {
    uint32_t res = 0;

    mpd_qfloor(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_ceil(Decimal *result, const Decimal *a,
                                          const DecimalContext *ctx,
                                          Status *status) {
    uint32_t res = 0;

    mpd_qceil(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_trunc(Decimal *result, const Decimal *a,
                                           const DecimalContext *ctx,
                                           Status *status) {
    uint32_t res = 0;

    mpd_qtrunc(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_logb(Decimal *result, const Decimal *a,
                                          const DecimalContext *ctx,
                                          Status *status) {
    uint32_t res = 0;

    mpd_qlogb(result, a, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_scaleb(Decimal *result, const Decimal *a,
                                            const Decimal *b,
                                            const DecimalContext *ctx,
                                            Status *status) {
    uint32_t res = 0;

    mpd_qscaleb(result, a, b, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

inline bool decimal_powmod(Decimal *result, const Decimal *base,
                                            const Decimal *exp,
                                            const Decimal *mod,
                                            const DecimalContext *ctx,
                                            Status *status) {
    uint32_t res = 0;

    mpd_qpowmod(result, base, exp, mod, ctx, &res);

    if (res != 0) {
        return decimal_handle_error_code(res, status);
    }

    return status_ok(status);
}

/* vi: set et ts=4 sw=4: */

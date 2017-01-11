#ifndef DECIMAL_H__
#define DECIMAL_H__

#include <mpdecimal.h>

#define DECIMAL_MAX_PRECISION MPD_MAX_PREC
#define DECIMAL_MAX_POSITIVE_EXPONENT MPD_MAX_EMAX
#define DECIMAL_MIN_NEGATIVE_EXPONENT MPD_MIN_EMIN
#define DECIMAL_ROUND_UP MPD_ROUND_UP
#define DECIMAL_ROUND_DOWN MPD_ROUND_DOWN
#define DECIMAL_ROUND_CEILING MPD_ROUND_CEILING
#define DECIMAL_ROUND_FLOOR MPD_ROUND_FLOOR
#define DECIMAL_ROUND_HALF_UP MPD_ROUND_HALF_UP
#define DECIMAL_ROUND_HALF_DOWN MPD_ROUND_HALF_DOWN
#define DECIMAL_ROUND_HALF_EVEN MPD_ROUND_HALF_EVEN
#define DECIMAL_ROUND_05_UP MPD_ROUND_05UP
#define DECIMAL_ROUND_TRUNCATE MPD_ROUND_TRUNC
#define DECIMAL_IEEE_CONTEXT_MAX_BITS MPD_IEEE_CONTEXT_MAX_BITS
#define DECIMAL_DECIMAL32 MPD_DECIMAL32
#define DECIMAL_DECIMAL64 MPD_DECIMAL64
#define DECIMAL_DECIMAL128 MPD_DECIMAL128

#define DECIMAL_POSITIVE MPD_POS
#define DECIMAL_NEGATIVE MPD_NEG
#define DECIMAL_INFINITY MPD_INF
#define DECIMAL_NAN MPD_NAN
#define DECIMAL_SIGNALLING_NAN MPD_SNAN

typedef mpd_t Decimal;
typedef mpd_context_t DecimalContext;

enum {
    DECIMAL_INVALID_CONTEXT_CONFIG_VALUE = 1,
    DECIMAL_INVALID_CONVERSION_SYNTAX,
    DECIMAL_DIVISION_IMPOSSIBLE,
    DECIMAL_DIVISION_UNDEFINED,
    DECIMAL_INVALID_CONTEXT,
    DECIMAL_INVALID_OPERATION,
    DECIMAL_CLAMPED,
    DECIMAL_DIVISION_BY_ZERO,
    DECIMAL_FPU_ERROR,
    DECIMAL_INEXACT,
    DECIMAL_NOT_IMPLEMENTED,
    DECIMAL_OVERFLOW,
    DECIMAL_ROUNDED,
    DECIMAL_SUBNORMAL,
    DECIMAL_UNDERFLOW
};

extern void (* mpd_traphandler)(mpd_context_t *);

#define decimal_trap_handler mpd_traphandler

#define decimal_context_init mpd_init
#define decimal_context_set_max mpd_maxcontext
#define decimal_context_set_default mpd_defaultcontext
#define decimal_context_set_basic mpd_basiccontext
#define decimal_context_set_ieee_bits mpd_ieee_context

#define decimal_context_get_precision mpd_getprec
#define decimal_context_get_max_positive_exponent mpd_getemax
#define decimal_context_get_min_negative_exponent mpd_getemin
#define decimal_context_get_rounding
#define decimal_context_get_traps mpd_gettraps
#define decimal_context_get_status mpd_getstatus
#define decimal_context_get_clamp mpd_getclamp
#define decimal_context_get_correct_rounding mpd_getcr
#define decimal_context_get_smallest_exponent mpd_etiny
#define decimal_context_get_largest_exponent mpd_etop

#define decimal_clear mpd_del
#define decimal_from_special mpd_setspecial
#define decimal_from_zero mpd_zerocoeff
#define decimal_get_adjusted_exponent mpd_adjexp
#define decimal_get_class mpd_class
#define decimal_is_finite mpd_isfinite
#define decimal_is_infinite mpd_isinfinite
#define decimal_is_nan mpd_isnan
#define decimal_is_negative mpd_isnegative
#define decimal_is_positive mpd_ispositive
#define decimal_is_quiet_nan mpd_isqnan
#define decimal_is_signed mpd_issigned
#define decimal_is_signalling_nan mpd_issnan
#define decimal_is_special mpd_isspecial
#define decimal_is_zero mpd_iszero
#define decimal_is_normal mpd_isnormal
#define decimal_is_subnormal mpd_issubnormal
#define decimal_is_integer mpd_isinteger
#define decimal_is_odd mpd_isodd
#define decimal_is_even mpd_iseven
#define decimal_get_sign mpd_sign
#define decimal_get_arithmetic_sign mpd_arith_sign
#define decimal_get_trailing_zeroes mpd_trail_zeros
#define decimal_is_zero_coefficient mpd_iszerocoeff
#define decimal_is_odd_coefficient mpd_isoddcoeff
#define decimal_get_most_significant_word mpd_msword
#define decimal_clear_flags  mpd_clear_flags
#define decimal_set_flags mpd_set_flags
#define decimal_copy_flags mpd_copy_flags
#define decimal_set_digits mpd_setdigits
#define decimal_set_sign mpd_set_sign
#define decimal_set_negative mpd_set_negative
#define decimal_set_positive mpd_set_positive
#define decimal_cmp_total mpd_cmp_total
#define decimal_cmp_total_mag mpd_cmp_total_mag
#define decimal_same_quantum mpd_same_quantum

#define decword_get_digits mpd_word_digits
#define decword_get_most_significant_digit mpd_msd
#define decword_get_least_significant_digit mpd_lsd
#define decword_is_odd mpd_isoddword

#define decexp_get_digits mpd_exp_digits

#define decutil_digits_to_size mpd_digits_to_size

#endif

/* vi: set et ts=4 sw=4: */

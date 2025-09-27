
// RhinoDevel, Marcel Timm, 2025sep25

#ifndef MT_NORM
#define MT_NORM

#ifdef __cplusplus
extern "C" {
#endif

/** Return the factor that will scale the given value into the given range, fill
 *  output value with exponent used in factor (2^n is the factor, n is the
 *  exponent), fill other output value with normalized value.
 * 
 * - TODO: Can be simplified & made faster & more robust/compatible by assuming
 *         IEEE-754 floating-point format and using bit-level access
 *         [like frexp()]!
 * 
 * - Input value must be a non-zero, positive number.
 * - Range must be 0 < range-from < range-through.
 * - Returns negative value, if such a factor could not be found.
 */
double norm_get_in_range_factor_and_fill(
    double const pos_val,
    double const range_from_incl,
    double const range_through_excl,
    int * const out_exp,
    double * const out_norm_val);

#ifdef __cplusplus
}
#endif

#endif //MT_NORM

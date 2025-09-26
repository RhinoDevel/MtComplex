
// RhinoDevel, Marcel Timm, 2025sep12

#ifndef MT_LN
#define MT_LN

#ifdef __cplusplus
extern "C" {
#endif

/**
 * - Tries to apply range-reduction of input value to [0.5, 2.1), if not already
 *   inside that range and returns with not-a-number, if that fails.
 * - Returns not-a-number, if no reasonably precise result was found by
 *   approximation.
 */
double ln_ln(double const val);

/**
 * - Returns not-a-number, if x is negative.
 * - Returns not-a-number, if no reasonably precise intermediate result for
 *   ln(x) or result exp(0.5 x ln(x)) was found by approximation.
 */
double ln_sqrt(double const x);

#ifdef __cplusplus
}
#endif

#endif // MT_LN

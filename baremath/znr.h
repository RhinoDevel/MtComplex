
// RhinoDevel, Marcel Timm, 2017dec10

// This is a complex number calculation library more or less for educational
// purposes, but it works and it has some tricks included like calculating the
// complex exponential by power series and the sine via the sine identity that
// includes the complex exponential function (and thus makes use of it).

#ifndef MT_ZNR
#define MT_ZNR

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct znr
{
    double r; // The real part of the complex number.
    double i; // The imaginary part of the complex number.
};

double znr_squared_magnitude(struct znr const nr);

struct znr znr_add(struct znr const a, struct znr const b);
struct znr znr_sub(struct znr const a, struct znr const b);
struct znr znr_mul(struct znr const a, struct znr const b);

/** Return a / b.
 * 
 *  - Check return value with znr_is_nan(), which will return true, if division
 *    by zero was avoided (because squared magnitude of b was 0) and no defined
 *    return value could be calculated.
 */
struct znr znr_div(struct znr const a, struct znr const b);

/** Divide real and imaginary part by given real number.
 * 
 *  - Check return value with znr_is_nan(), which will return true, if division
 *    by zero was avoided (because 0.0 was given as r) and no defined return
 *    value could be calculated.
 */
struct znr znr_div_r(struct znr const nr, double const r);

/** Calculates the complex sine of given real value by using the exponential
 *  function [see znr_exp()].
 * 
 *  - The term count is for the power series used for exponential calculation
 *    [see znr_exp()].
 *  - Warning: This function does no range reduction!
 */
struct znr znr_sin(struct znr const nr, int const n_terms);

/** Calculates the complex cosine of given real value by using the exponential
 *  function [see znr_exp()].
 * 
 *  - The term count is for the power series used for exponential calculation
 *    [see znr_exp()].
 *  - Warning: This function does no range reduction!
 *  - No need to know the constant Pi for this one. :-)
 */
struct znr znr_cos(struct znr const nr, int const n_terms);

/** Calculates the complex tangent of given complex value using the exponential
 *  functions.
 *
 *  - Returns complex not-a-number, if denominator in used mathematical function
 *    is 0. Check after call via znr_is_nan().
 *  - The term count is for the power series used for exponential calculation
 *    [see znr_exp()].
 *  - Warning: This function does no range reduction!
 */
struct znr znr_tan(struct znr const nr, int const n_terms);

struct znr znr_conjugate(struct znr const nr);

/** Create complex exponential of given nr., using power series with given count
 *  of terms.
 * 
 *  - Warning: This function does no range reduction!
 */
struct znr znr_exp(struct znr const nr, int const n_terms);

/** Returns true, if the given complex nr. is invalid.
 */
bool znr_is_nan(struct znr const nr);

#ifdef __cplusplus
}
#endif

#endif //MT_ZNR


// RhinoDevel, Marcel Timm, 2017dec10

#ifndef MT_ZNR
#define MT_ZNR

#ifdef __cplusplus
extern "C" {
#endif

struct znr
{
    double const r; // The real part of the complex number.
    double const i; // The imaginary part of the complex number.
};

/**
 * - Caller takes ownership of return value, which is to be freed via
 *   znr_delete().
 */
struct znr * znr_add(struct znr const * const a, struct znr const * const b);

/**
 * - Caller takes ownership of return value, which is to be freed via
 *   znr_delete().
 */
struct znr * znr_sub(struct znr const * const a, struct znr const * const b);

/**
 * - Caller takes ownership of return value, which is to be freed via
 *   znr_delete().
 */
struct znr * znr_mul(struct znr const * const a, struct znr const * const b);

/** Return a / b.
 * 
 *  - Returns NULL, if result is undefined, because squared magnitude of b is 0
 *    (which would cause a division by zero).
 *  - Caller takes ownership of return value, which is to be freed via
 *    znr_delete().
 */
struct znr * znr_div(struct znr const * const a, struct znr const * const b);

/** Divide real and imaginary part by given real number.
 * 
 *  - Returns NULL, if result is undefined, if given r is 0.0 (which would cause
 *    a division by zero).
 *  - Caller takes ownership of return value, which is to be freed via
 *    znr_delete().
 */
struct znr * znr_div_r(struct znr const * const nr, double const r);

/** Return the absolute value (modulus).
 */
double znr_magnitude(struct znr const * const nr);

/** Return the argument ("phase"), which is the angle phi.
 */
double znr_phi(struct znr const * const nr);

/**
 *  - The term count is for the power series used for exponential calculation
 *    [see znr_exp()].
 *  - Warning: This function does no range reduction!
 */
double znr_real_sin(double const r, int const n_terms);

/**
 * - Caller takes ownership of return value, which is to be freed via
 *   znr_delete().
 */
struct znr * znr_create_from_polar(double const phi, double const magnitude);

/**
 * - Caller takes ownership of return value, which is to be freed via
 *   znr_delete().
 */
struct znr * znr_create(double const r, double const i);

/**
 * - Caller takes ownership of return value, which is to be freed via
 *   znr_delete().
 */
struct znr * znr_create_copy(struct znr const * const nr);

/**
 * - Caller takes ownership of return value, which is to be freed via
 *   znr_delete().
 */
struct znr * znr_create_conjugate(struct znr const * const nr);

/** Create complex exponential of given nr., using power series with given count
 *  of terms.
 * 
 *  - Caller takes ownership of return value, which is to be freed via
 *    znr_delete().
 */
struct znr * znr_exp(struct znr const * const nr, int const n_terms);

/** Frees memory of given object which also invalidates given pointer.
 * 
 *  - Works with NULL pointer given.
 */
void znr_delete(struct znr * const nr);

#ifdef __cplusplus
}
#endif

#endif // MT_ZNR

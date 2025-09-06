
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

struct znr * znr_add(struct znr const * const a, struct znr const * const b);
struct znr * znr_sub(struct znr const * const a, struct znr const * const b);
struct znr * znr_mul(struct znr const * const a, struct znr const * const b);

/** Return a / b.
 * 
 *  - Returns NULL, if result is undefined, because squared magnitude of b is 0
 *    (which would cause a division by zero).
 */
struct znr * znr_div(struct znr const * const a, struct znr const * const b);

/** Return the absolute value (modulus).
 */
double znr_magnitude(struct znr const * const nr);

/** Return the argument ("phase"), which is the angle phi.
 */
double znr_phi(struct znr const * const nr);

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

/** Frees memory of given object which also invalidates given pointer.
 * 
 *  - Works with NULL pointer given.
 */
void znr_delete(struct znr * const nr);

#ifdef __cplusplus
}
#endif

#endif // MT_ZNR

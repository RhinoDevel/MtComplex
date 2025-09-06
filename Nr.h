
// RhinoDevel, Marcel Timm, 2017dec10

#ifndef MT_NR
#define MT_NR

#ifdef __cplusplus
extern "C" {
#endif

struct Nr
{
    double const r; // The real part of the complex number.
    double const i; // The imaginary part of the complex number.
};

struct Nr * Nr_add(struct Nr const * const a, struct Nr const * const b);
struct Nr * Nr_sub(struct Nr const * const a, struct Nr const * const b);
struct Nr * Nr_mul(struct Nr const * const a, struct Nr const * const b);
struct Nr * Nr_div(struct Nr const * const a, struct Nr const * const b);

/** Return the absolute value (modulus).
 */
double Nr_magnitude(struct Nr const * const nr);

/** Return the argument ("phase"), which is the angle phi.
 */
double Nr_phi(struct Nr const * const nr);

/**
 * - Caller takes ownership of return value, which is to be freed via
 *   Nr_delete().
 */
struct Nr * Nr_create_from_polar(double const phi, double const magnitude);

/**
 * - Caller takes ownership of return value, which is to be freed via
 *   Nr_delete().
 */
struct Nr * Nr_create(double const r, double const i);

void Nr_delete(struct Nr * const nr);

#ifdef __cplusplus
}
#endif

#endif // MT_NR

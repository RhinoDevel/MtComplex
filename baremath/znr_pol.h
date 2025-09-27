
// RhinoDevel, Marcel Timm, 2025sep16

// Polar-coordintes "add-on" to znr to avoid circular dependencies.

#ifndef MT_ZNR_POL
#define MT_ZNR_POL

#include "znr.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Return the absolute value (modulus).
 * 
 * - Returns not-a-number, if internal approximation used failed to produce a
 *   reasonably precise intermediate result.
 */
double znr_pol_magnitude(struct znr const nr);

/** Return the argument ("phase"), which is the angle phi.
 */
double znr_pol_phi(struct znr const nr);

struct znr znr_pol_from(double const phi, double const magnitude);

#ifdef __cplusplus
}
#endif

#endif //MT_ZNR_POL

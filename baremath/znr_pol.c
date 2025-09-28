
// RhinoDevel, Marcel Timm, 2025sep16

#include "znr_pol.h"
#include "atan.h"
#include "znr.h"
#include "ln.h"

double znr_pol_magnitude(struct znr const nr)
{
    return ln_sqrt(znr_squared_magnitude(nr));
}

double znr_pol_phi(struct znr const nr)
{
    return atan_atan2(nr.i, nr.r);
}

struct znr znr_pol_from(double const phi, double const magnitude)
{
    // The terms to calculate cosine & sine.
    static int const n_terms = 50; // TODO: More or less?

    struct znr const phi_complex = (struct znr){ .r = phi, .i = 0.0 };
    double const cos_phi = znr_cos(phi_complex, n_terms).r;
    double const sin_phi = znr_sin(phi_complex, n_terms).r;

    return (struct znr){ .r = magnitude * cos_phi, .i = magnitude * sin_phi };
}
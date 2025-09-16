
// RhinoDevel, Marcel Timm, 2025sep16

#include "znr_pol.h"
#include "znr.h"

double znr_pol_magnitude(struct znr const nr)
{
    return sqrt(znr_squared_magnitude(nr));
}

double znr_pol_phi(struct znr const nr)
{
    return atan2(nr.i, nr.r);
}

struct znr znr_pol_from(double const phi, double const magnitude)
{
    return (struct znr){ .r = magnitude * cos(phi), .i = magnitude * sin(phi) };
}
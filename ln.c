
// RhinoDevel, Marcel Timm, 2025sep12

#include "ln.h"
#include "znr.h"

#include <math.h>

double ln_ln(double const val)
{
    // Approximate ln(val) by using exponential function and Newton-Raphson.

    // Break after this maximum iteration count:
    static int const max_steps = 30; // TODO: More or less?

    // Break, if last and current results difference is less than this value:
    static double const done_diff = 1.0 / 100000.0; // TODO: More or less?

    // The initial guess:
    static double const x_0 = 1.0; // TODO: Improve generation?

    // The terms to calculate by exponential function.
    static int const exp_terms = 50; // TODO: More or less?

    // TODO: Add check, if given value is supported, return NAN otherwise!

    // x_n+1 = val / e^x_n + x_n - 1

    double x_last = 0.0;
    double x = x_0;

    for(int n = 1; n <= max_steps; ++n)
    {
        // TODO: Not using range reduction for exponential function!

        x_last = x;
        x = val / znr_exp((struct znr){ .r = x, .i = 0.0 }, exp_terms).r
                + x_last
                - 1.0;

        if(fabs(x - x_last) < done_diff)
        {
            return x;
        }
    }
    return NAN;
}

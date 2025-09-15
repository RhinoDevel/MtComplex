
// RhinoDevel, Marcel Timm, 2025sep12

#include "ln.h"
#include "znr.h"
#include "newton_raphson.h"

#include <math.h> // For isnan().

static double newton_raphson_step_ln(double const x, double const val)
{
    // The terms to calculate by exponential function.
    static int const exp_terms = 50; // TODO: More or less?

    // x_n+1 = val / e^x_n + x_n - 1
    return val / znr_exp((struct znr){ .r = x, .i = 0.0 }, exp_terms).r
        + x
        - 1.0;
}

double ln_ln(double const val)
{
    // Approximate ln(val) by using exponential function and Newton-Raphson.

    // Break after this maximum iteration count:
    static int const max_steps = 30; // TODO: More or less?

    // Break, if last and current results difference is less than this value:
    static double const done_diff = 1.0 / 100000.0; // TODO: More or less?

    // The initial guess:
    static double const x_0 = 1.0; // TODO: Improve generation?

    // TODO: Add check, if given value is supported, return NAN otherwise!

    return newton_raphson(
        max_steps, done_diff, x_0, val, newton_raphson_step_ln);
}

double ln_sqrt(double const x)
{
    static int const exp_terms = 20; // TODO: More or less?

    // sqrt(x) = exp(0.5 * ln(x))

    double const ln_x = ln_ln(x);
    
    if(isnan(ln_x))
    {
        return NAN;
    }

    struct znr exp = znr_exp(
        (struct znr){.r = 0.5 * ln_x, .i = 0.0}, exp_terms);

    if(znr_is_nan(exp))
    {
        return NAN;
    }

    return exp.r;
}

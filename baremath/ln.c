
// RhinoDevel, Marcel Timm, 2025sep12

#include "ln.h"
#include "znr.h"
#include "newton_raphson.h"
#include "nan.h"
#include "norm.h"
#include "deb.h"

static double s_ln_2 = 0.0; // Filled and used by ln_ln().

static double newton_raphson_step_ln(double const x, double const val)
{
    // The terms to calculate by exponential function.
    static int const exp_terms = 50; // TODO: More or less?

    // x_n+1 = val / e^x_n + x_n - 1

    double const denom = znr_exp((struct znr){ .r = x, .i = 0.0 }, exp_terms).r;

    //deb_line("exp(%f) = %f", x, denom)

    return val / denom + x - 1.0;
}

double ln_ln(double const val)
{
    // ln(x) = ?
    //
    // 0 < x
    //
    // x = f * 2^n
    //
    // 0.5 <= f < 2.1 // TODO: Use larger range (why start at 0.5?)?
    //
    // ln(f * 2^n) = ln(f) - n * ln(2)
    //
    // => Proceed this way:
    // 0) Pre-calculate ln(2) once.
    // 1) Scale value to range. => f, n, 2^n
    // 2) Calculate ln(f) with own method.
    // 3) Calculate n * ln(2).
    // 4) Calculate ln(x) by subtracting result of step 3 from step 2 result.

    if(val <= 0.0)
    {
        return nan_get();
    }

    int norm_exp = 0;
    double norm_val = 0.0;
    double const norm_factor = norm_get_in_range_factor_and_fill(
        val,
        0.5,
        2.1,
        &norm_exp,
        &norm_val);

    if(norm_factor < 0.0)
    {
        return nan_get();
    }

    // Approximate ln(val) by using exponential function and Newton-Raphson.

    // Break after this maximum iteration count:
    static int const max_steps = 30; // TODO: More or less?

    // Break, if last and current results difference is less than this value:
    static double const done_diff = 1e-15; // TODO: More?

    // The initial guess:
    static double const x_0 = 1.0; // TODO: Improve generation?

    double const norm_ln = newton_raphson(
        max_steps, done_diff, x_0, norm_val, newton_raphson_step_ln);

    if(nan_is(norm_ln))
    {
        return norm_ln/*nan_get()*/;
    }

    if(norm_factor == 1.0)
    {
        return norm_ln;
    }

    if(s_ln_2 == 0.0)
    {
        s_ln_2 = ln_ln(2.0); // *** RECURSION ***
    }
    //deb_line("ln(%f) = %f + %d * %f", val, norm_ln, norm_exp, s_ln_2)
    return norm_ln - (double)norm_exp * s_ln_2;
}

double ln_sqrt(double const x)
{
    //deb_line("Entered with x = %.16f.", x)

    static int const exp_terms = 20; // TODO: More or less?

    // sqrt(x) = exp(0.5 * ln(x))

    if(x < 0.0)
    {
        return nan_get();
    }

    double const ln_x = ln_ln(x);
    
    //deb_line("ln_ln(x) = %.16f.", ln_x)

    if(nan_is(ln_x))
    {
        return nan_get();
    }

    struct znr exp = znr_exp(
        (struct znr){.r = 0.5 * ln_x, .i = 0.0}, exp_terms);

    if(znr_is_nan(exp))
    {
        return nan_get();
    }

    return exp.r;
}

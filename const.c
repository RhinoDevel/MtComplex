
// RhinoDevel, Marcel Timm, 2025sep15

#include "const.h"
#include "znr.h"
#include "newton_raphson.h"

static double newton_raphson_step_pi_div_two(double const x, double const val)
{
    // The terms to calculate by exponential function.
    static int const exp_terms = 21;

    double const cos_x = znr_real_cos(x, exp_terms);
    double const sin_x = znr_real_sin(x, exp_terms);

    // x_n+1 = x_n + cos_x / sin_x
    double const ret_val = x + cos_x / sin_x;

    return ret_val;
}

double const_e(void)
{
    static int const exp_terms = 18;

    return znr_exp((struct znr){.r = 1.0, .i = 0.0}, exp_terms).r;
}

double const_pi(void)
{
    // Approximate Pi by using Newton-Raphson.

    // Break after this maximum iteration count:
    static int const max_steps = 4;

    // Break, if last and current results difference is less than this value:
    static double const done_diff = 1e-15; // A larger number would be OK, too..

    // The initial guess:
    static double const x_0 = 1.5;

    double const pi_div_two = newton_raphson(
        max_steps, done_diff, x_0, 0.0, newton_raphson_step_pi_div_two);

    return 2.0 * pi_div_two;
}

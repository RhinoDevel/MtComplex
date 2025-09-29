
// RhinoDevel, Marcel Timm, 2025sep15

#include "const.h"
#include "znr.h"
#include "newton_raphson.h"

#include <assert.h>

#define MT_CONST_UNSET 0.0

// The(-se) constants will be calculated once via const_init():
//
static double s_e = MT_CONST_UNSET;
static double s_pi = MT_CONST_UNSET;

static double newton_raphson_step_pi_div_two(double const x, double const val)
{
    (void)val; // For the compiler.

    // The terms to calculate by exponential function.
    static int const exp_terms = 21;

    struct znr const complex_x = (struct znr){ .r = x, .i = 0.0 };
    double const cos_x = znr_cos(complex_x, exp_terms).r;
    double const sin_x = znr_sin(complex_x, exp_terms).r;

    // x_n+1 = x_n + cos_x / sin_x
    double const ret_val = x + cos_x / sin_x;

    return ret_val;
}

static double create_e(void)
{
    static int const exp_terms = 18;

    return znr_exp((struct znr){.r = 1.0, .i = 0.0}, exp_terms).r;
}

static double create_pi(void)
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

double const_e(void)
{
    assert(s_e != MT_CONST_UNSET);
    return s_e;
}

double const_pi(void)
{
    assert(s_pi != MT_CONST_UNSET);
    return s_pi;
}

void const_init(void)
{
    // Although nothing bad will happen, just unnecessary re-calculation:
    assert(s_e == MT_CONST_UNSET);
    assert(s_pi == MT_CONST_UNSET);

    s_e = create_e();
    s_pi = create_pi();
}
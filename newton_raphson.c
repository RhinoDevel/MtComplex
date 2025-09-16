
// RhinoDevel, Marcel Timm, 2025sep15

#include "newton_raphson.h"
#include "nan.h"

#include <assert.h>

double newton_raphson(
    int const max_steps,
    double const done_diff,
    double const initial_guess,
    double const val,
    double (*step_func)(double, double))
{
    assert(0 < max_steps);
    assert(0.0 < done_diff);
    // initial_guess
    // val
    assert(step_func != NULL);

    double x_last = 0.0;
    double x = initial_guess;

    for(int n = 1; n <= max_steps; ++n)
    {
        x_last = x;
        x = step_func(x, val);

        if(fabs(x - x_last) < done_diff)
        {
            return x;
        }
    }
    return nan_get();
}
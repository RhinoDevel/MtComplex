
// RhinoDevel, Marcel Timm, 2025sep15

#include "newton_raphson.h"
#include "nan.h"

#include <assert.h>

// #ifndef NDEBUG
//     #include <stdlib.h>
// #endif //NDEBUG

static double abs_diff(double const a, double const b)
{
    if(b < a)
    {
        return a - b;
    }
    return b - a;
}

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
       
// #ifndef NDEBUG
//         printf("n = %d, x_last = %.16f, x = %.16f\n", n, x_last, x);
// #endif //NDEBUG

        if(nan_is(x))
        {
// #ifndef NDEBUG
//             printf(
//                 "Exiting early, because step function returned not-a-number..");
// #endif //NDEBUG 
            return x/*nan_get()*/;
        }

        if(abs_diff(x, x_last) < done_diff)
        {
// #ifndef NDEBUG
//             printf("Found x = %.16f\n", x);
// #endif //NDEBUG
            return x;
        }
    }
    return nan_get();
}
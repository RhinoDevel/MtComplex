
// RhinoDevel, Marcel Timm, 2025sep25

#include "norm.h"
#include "deb.h"

#include <assert.h>

double norm_get_in_range_factor_and_fill(
    double const pos_val,
    double const range_from_incl,
    double const range_through_excl,
    int * const out_exp,
    double * const out_norm_val)
{
    assert(0.0 < pos_val);
    assert(0.0 < range_from_incl);
    assert(range_from_incl < range_through_excl);
    assert(out_exp != NULL);
    assert(out_norm_val != NULL);

    // 1021 for DBL_MIN & [0.5, 2.0).
    // 1023 for DBL_MAX & [0.5, 2.0).
    static int const max_iter = 2000; // Just to prevent an infinite loop.

    int i = 0;
    double factor = 1.0;

    *out_norm_val = pos_val;
    *out_exp = 0;

    i = -1;
    while(++i < max_iter)
    {
        if(range_from_incl <= *out_norm_val)
        {
            //deb_line(
            //    "Reached %.16e (>= %.16e) after %d iterations, exponent is %d.",
            //     *out_norm_val,
            //     range_from_incl,
            //     i,
            //     *out_exp)
            break; // Done
        }

        *out_norm_val *= 2.0;
        factor *= 2.0;
        ++(*out_exp);
    }
    if(i == max_iter)
    {
        return -1.0; // Not found (too small).
    }

    i = -1;
    while(++i < max_iter)
    {
        if(*out_norm_val < range_through_excl)
        {
            //deb_line(
            //    "Reached %.16e (< %.16e) after %d iterations, exponent is %d.",
            //     *out_norm_val,
            //     range_through_excl,
            //     i,
            //     *out_exp)
            break; // Done
        }

        *out_norm_val *= 0.5;
        factor *= 0.5;
        --(*out_exp);
    }
    if(i == max_iter)
    {
        return -2.0; // Not found (too large).
    }
    if(*out_norm_val < range_from_incl)
    {
        // Entering given range for given value via scaling by powers of two
        // does not seem to be possible.
        return -3.0;
    }

    assert(range_from_incl <= *out_norm_val);
    assert(*out_norm_val < range_through_excl);
    assert(pos_val * factor == *out_norm_val); // TODO: Allow small rounding errors?
    return factor;
}
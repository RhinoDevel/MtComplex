
// RhinoDevel, Marcel Timm, 2017dec10

#include <stdlib.h>
#include <math.h> // For NAN.
#include <assert.h>
#include <stdbool.h>

#include "znr.h"

static struct znr const s_nan = { .r = NAN, .i = NAN };

static bool znr_is_nan(struct znr const nr)
{
    return nr.r == s_nan.r && nr.i == s_nan.i;
}

static double squared_magnitude(struct znr const nr)
{
    return nr.r * nr.r + nr.i * nr.i;
}

struct znr znr_add(struct znr const a, struct znr const b)
{
    return (struct znr){ .r = a.r + b.r, .i = a.i + b.i };
}

struct znr znr_sub(struct znr const a, struct znr const b)
{
    return (struct znr){ .r = a.r - b.r, .i = a.i - b.i };
}

struct znr znr_mul(struct znr const a, struct znr const b)
{
    return (struct znr)
    {
        .r = a.r * b.r - a.i * b.i,
        .i = a.r * b.i + a.i * b.r
    };
}

struct znr znr_div(struct znr const a, struct znr const b)
{
    double const buf = squared_magnitude(b);

    if(buf == 0.0)
    {
        return s_nan; // Result is undefined.
    }
    return (struct znr)
    {
        .r = (a.r * b.r + a.i * b.i) / buf,
        .i = (a.i * b.r - a.r * b.i) / buf
    };
}

struct znr znr_div_r(struct znr const nr, double const r)
{
    if(r == 0.0)
    {
        return s_nan; // As results of divisions are undefined.
    }
    return (struct znr){ .r = nr.r / r, .i = nr.i / r };
}

double znr_magnitude(struct znr const nr)
{
    return sqrt(squared_magnitude(nr));
}

double znr_phi(struct znr const nr)
{
    return atan2(nr.i, nr.r);
}

double znr_real_sin(double const r, int const n_terms)
{
    struct znr const ix = (struct znr){ .r = 0.0, .i = r }; // 0 + ix = ix
    struct znr const neg_ix = znr_conjugate(ix); // 0 - ix = -ix
    struct znr const e_ix = znr_exp(ix, n_terms); // e^ix
    struct znr const e_neg_ix = znr_exp(neg_ix, n_terms); // e^-ix
    struct znr const num = znr_sub(e_ix, e_neg_ix); // e^ix - e^-ix
    struct znr const denom = (struct znr){ .r = 0.0, .i = 2.0 }; // 0 + 2i = 2i
    struct znr const result = znr_div(num, denom); // (e^ix - e^-ix) / 2i 

    return result.r;
}

double znr_real_cos(double const r, int const n_terms)
{
    struct znr const ix = (struct znr){ .r = 0.0, .i = r }; // 0 + ix = ix
    struct znr const neg_ix = znr_conjugate(ix); // 0 - ix = -ix
    struct znr const e_ix = znr_exp(ix, n_terms); // e^ix
    struct znr const e_neg_ix = znr_exp(neg_ix, n_terms); // e^-ix
    struct znr const num = znr_add(e_ix, e_neg_ix); // e^ix + e^-ix
    struct znr const denom = (struct znr){ .r = 2.0, .i = 0.0 }; // 2 + 0i = 2
    struct znr const result = znr_div(num, denom); // (e^ix + e^-ix) / 2 

    return result.r;
}

double znr_real_tan(double const r, int const n_terms)
{
    double const cos_r = znr_real_cos(r, n_terms);

    if(cos_r == 0.0)
    {
        return NAN;
    }
    
    double const sin_r = znr_real_sin(r, n_terms);

    return sin_r / cos_r;
}

struct znr znr_from_polar(double const phi, double const magnitude)
{
    return (struct znr){ .r = magnitude * cos(phi), .i = magnitude * sin(phi) };
}

struct znr znr_conjugate(struct znr const nr)
{
    return (struct znr){ .r = nr.r, .i = -1.0 * nr.i };
}

struct znr znr_exp(struct znr const nr, int const n_terms)
{
    // TODO: Add range reduction (for large values).

    // TODO: Improve performance by optimizing calculation in loop (e.g.
    //       eventually use Horner's method to reduce calculations and avoid
    //       overflow).
    //
    //       Additionally break, if current sum of terms and latest sum of terms
    //       before current iteration are no longer different enough (a "delta"
    //       needs to be defined for this to know when to break the loop).
    //       Maybe also return "not a number", if wanted precision could not be
    //       reached (see Newton-Raphson used in ln.c)?

    struct znr ret_val = (struct znr){ .r = 1.0, .i = 0.0 };
    struct znr term = ret_val;

    for(int n = 1; n < n_terms; ++n) // (starts with the second term)
    {
        // term = term * nr / n

        term = znr_div_r(znr_mul(term, nr), n);
        ret_val = znr_add(ret_val, term);
    }
    return ret_val;
}

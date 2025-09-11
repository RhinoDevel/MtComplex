
// RhinoDevel, Marcel Timm, 2017dec10

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "znr.h"

static double squared_magnitude(struct znr const * const nr)
{
    assert(nr != NULL);

    return nr->r * nr->r + nr->i * nr->i;
}

struct znr * znr_create(double const r, double const i)
{
    struct znr * const ret_val = malloc(sizeof *ret_val);

    assert(ret_val != NULL);

    struct znr const buf = { r, i };

    memcpy(ret_val, &buf, sizeof *ret_val);

    return ret_val;
}

struct znr * znr_add(struct znr const * const a, struct znr const * const b)
{
    assert(a != NULL);
    assert(b != NULL);

    return znr_create(a->r + b->r, a->i + b->i);
}

struct znr * znr_sub(struct znr const * const a, struct znr const * const b)
{
    assert(a != NULL);
    assert(b != NULL);

    return znr_create(a->r - b->r, a->i - b->i);
}

struct znr * znr_mul(struct znr const * const a, struct znr const * const b)
{
    assert(a != NULL);
    assert(b != NULL);

    return znr_create(a->r * b->r - a->i * b->i, a->r * b->i + a->i * b->r);
}

struct znr * znr_div(struct znr const * const a, struct znr const * const b)
{
    assert(a != NULL);
    assert(b != NULL);

    double const buf = squared_magnitude(b);

    if(buf == 0.0)
    {
        return NULL; // Result is undefined.
    }

    return znr_create(
        (a->r * b->r + a->i * b->i) / buf,
        (a->i * b->r - a->r * b->i) / buf);
}

struct znr * znr_div_r(struct znr const * const nr, double const r)
{
    assert(nr != NULL);

    if(r == 0.0)
    {
        return NULL; // As results of divisions are undefined.
    }

    return znr_create(nr->r / r, nr->i / r);
}

double znr_magnitude(struct znr const * const nr)
{
    assert(nr != NULL);

    return sqrt(squared_magnitude(nr));
}

double znr_phi(struct znr const * const nr)
{
    assert(nr != NULL);

    return atan2(nr->i, nr->r);
}

double znr_real_sin(double const r, int const n_terms)
{
    struct znr * z = NULL;
    struct znr * z_conj = NULL;
    struct znr * eix = NULL;
    struct znr * emix = NULL;
    struct znr * num = NULL; // Numerator
    struct znr * denom = NULL; // Denominator
    struct znr * result = NULL;

    z = znr_create(0.0, r); // 0 + ix = ix
    z_conj = znr_create_conjugate(z); // 0 - ix = -ix
    eix = znr_exp(z, n_terms); // e^ix

    znr_delete(z);
    z = NULL;

    emix = znr_exp(z_conj, n_terms); // e^-ix

    znr_delete(z_conj);
    z_conj = NULL;

    num = znr_sub(eix, emix); // e^ix - e^-ix

    znr_delete(eix);
    eix = NULL;

    znr_delete(emix);
    emix = NULL;

    denom = znr_create(0.0, 2.0); // 0 + 2i = 2i

    result = znr_div(num, denom); // (e^ix - e^-ix) / 2i 

    znr_delete(num);
    num = NULL;

    znr_delete(denom);
    denom = NULL;

    double const ret_val = result->r;  // sin(x) is the real part.

    znr_delete(result);
    result = NULL;

    return ret_val;
}

struct znr * znr_create_from_polar(double const phi, double const magnitude)
{
    return znr_create(magnitude * cos(phi), magnitude * sin(phi));
}

struct znr * znr_create_copy(struct znr const * const nr)
{
    assert(nr != NULL);

    return znr_create(nr->r, nr->i);
}

struct znr * znr_create_conjugate(struct znr const * const nr)
{
    assert(nr != NULL);

    return znr_create(nr->r, -1.0 * nr->i);
}

struct znr * znr_exp(struct znr const * const nr, int const n_terms)
{
    // TODO: Add range reduction (for large values).

    // TODO: Improve performance by optimizing calculation in loop (e.g.
    //       eventually use Horner's method to reduce calculations and avoid
    //       overflow).

    struct znr * ret_val = znr_create(1.0, 0.0);
    struct znr * term = znr_create_copy(ret_val);

    for(int n = 1; n < n_terms; ++n)
    {
        // term = term * nr / n

        struct znr * z_div = znr_div_r(nr, (double)n);

        struct znr * new_term = znr_mul(term, z_div);
        
        znr_delete(z_div);
        z_div = NULL;

        znr_delete(term);
        term = new_term;
        new_term = NULL;
        
        struct znr * new_sum = znr_add(ret_val, term);

        znr_delete(ret_val);
        ret_val = new_sum;
        new_sum = NULL;
    }

    znr_delete(term);
    term = NULL;
    return ret_val;
}

void znr_delete(struct znr * const nr)
{
    free(nr);
}

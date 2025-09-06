
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

struct znr * znr_create_from_polar(double const phi, double const magnitude)
{
    return znr_create(magnitude * cos(phi), magnitude * sin(phi));
}

void znr_delete(struct znr * const nr)
{
    free(nr);
}


// RhinoDevel, Marcel Timm, 2017dec10

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "Nr.h"

struct Nr * Nr_create(double const r, double const i)
{
    struct Nr * const ret_val = malloc(sizeof *ret_val);

    assert(ret_val != NULL);

    struct Nr const buf = { r, i };

    memcpy(ret_val, &buf, sizeof *ret_val);

    return ret_val;
}

struct Nr * Nr_add(struct Nr const * const a, struct Nr const * const b)
{
    assert(a != NULL);
    assert(b != NULL);

    return Nr_create(a->r + b->r, a->i + b->i);
}

struct Nr * Nr_sub(struct Nr const * const a, struct Nr const * const b)
{
    assert(a != NULL);
    assert(b != NULL);

    return Nr_create(a->r - b->r, a->i - b->i);
}

struct Nr * Nr_mul(struct Nr const * const a, struct Nr const * const b)
{
    assert(a != NULL);
    assert(b != NULL);

    return Nr_create(a->r * b->r - a->i * b->i, a->r * b->i + a->i * b->r);
}

struct Nr * Nr_div(struct Nr const * const a, struct Nr const * const b)
{
    assert(a != NULL);
    assert(b != NULL);

    double const buf = b->r * b->r + b->i * b->i;

    return Nr_create(
        (a->r * b->r + a->i * b->i) / buf,
        (a->i * b->r - a->r * b->i) / buf);
}

double Nr_magnitude(struct Nr const * const nr)
{
    assert(nr != NULL);

    return sqrt(nr->r * nr->r + nr->i * nr->i);
}

double Nr_phi(struct Nr const * const nr)
{
    assert(nr != NULL);

    return atan2(nr->i, nr->r);
}

struct Nr * Nr_create_from_polar(double const phi, double const magnitude)
{
    return Nr_create(magnitude * cos(phi), magnitude * sin(phi));
}

void Nr_delete(struct Nr * const nr)
{
    free(nr);
}

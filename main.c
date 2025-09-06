
// RhinoDevel, Marcel Timm, 2017dec10

#include <stdio.h>
#include <stdlib.h>

#include "znr.h"

int main()
{
    struct znr * a = znr_create(123.45, 33.3),
        * b = znr_create_from_polar(znr_phi(a), znr_magnitude(a)),
        * c = znr_sub(a, b);

    printf("%f + j%f\n", a->r, a->i);
    printf("%f + j%f\n", b->r, b->i);
    printf("%f + j%f\n", c->r, c->i);

    znr_delete(a);
    a = NULL;
    znr_delete(b);
    b = NULL;
    znr_delete(c);
    c = NULL;

    return EXIT_SUCCESS;
}

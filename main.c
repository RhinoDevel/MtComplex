
// RhinoDevel, Marcel Timm, 2017dec10

#include <stdio.h>
#include <stdlib.h>

#include "Nr.h"

int main()
{
    struct Nr * a = Nr_create(123.45, 33.3),
        * b = Nr_create_from_polar(Nr_phi(a), Nr_magnitude(a)),
        * c = Nr_sub(a, b);

    printf("%f + j%f\n", a->r, a->i);
    printf("%f + j%f\n", b->r, b->i);
    printf("%f + j%f\n", c->r, c->i);

    return EXIT_SUCCESS;
}


// RhinoDevel, Marcel Timm, 2017dec10

#include <stdio.h>
#include <stdlib.h>

#include "znr.h"

static void test_simple(void)
{
    struct znr * a = znr_create(123.45, 33.3),
        * b = znr_create_from_polar(znr_phi(a), znr_magnitude(a)),
        * c = znr_sub(a, b);

    printf("Simple test results:\n");
    printf("%f + j%f\n", a->r, a->i);
    printf("%f + j%f\n", b->r, b->i);
    printf("%f + j%f\n", c->r, c->i);

    znr_delete(a);
    a = NULL;
    znr_delete(b);
    b = NULL;
    znr_delete(c);
    c = NULL;
}

static void test_exp()
{
    static int const n_terms = 20;

    struct znr * a = znr_create(1.0, 0.0);
    struct znr * b = znr_exp(a, n_terms);

    printf("Exponential test results:\n");
    printf("%f + j%f\n", a->r, a->i);
    printf("%f + j%f\n", b->r, b->i);

    znr_delete(a);
    a = NULL;
    znr_delete(b);
    b = NULL;
}

int main(void)
{
    test_simple();
    
    printf("\n");

    test_exp();

    return EXIT_SUCCESS;
}

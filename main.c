
// RhinoDevel, Marcel Timm, 2017dec10

#include <stdio.h>
#include <stdlib.h>

#include "znr.h"
#include "ln.h"

static void test_simple(void)
{
    struct znr const a = (struct znr){ .r = 123.45, .i = 33.3 };
    struct znr const b = znr_from_polar(znr_phi(a), znr_magnitude(a));
    struct znr const c = znr_sub(a, b);

    printf("Simple test results:\n");
    printf("%f + j%f\n", a.r, a.i);
    printf("%f + j%f\n", b.r, b.i);
    printf("%f + j%f\n", c.r, c.i);
}

static void test_exp()
{
    static int const n_terms = 20;

    struct znr const a = (struct znr){ .r = 1.0, .i = 0.0};
    struct znr const b = znr_exp(a, n_terms);

    printf("Exponential test results:\n");
    printf("%f + j%f\n", a.r, a.i);
    printf("%f + j%f\n", b.r, b.i);
}

static void test_real_sin()
{
    static int const n_terms = 20;

    double const real_sin = znr_real_sin(3.0 * 3.14159265 / 2.0, n_terms);

    printf("Real sine via exponential test results:\n");
    printf("%f\n", real_sin);
}

static void test_real_ln()
{
    printf("Natural logarithm via exponential test results:\n");
    printf("%f\n", ln_ln(5.0));
}

int main(void)
{
    test_simple();
    
    printf("\n");

    test_exp();

    printf("\n");

    test_real_sin();
    
    printf("\n");

    test_real_ln();

    return EXIT_SUCCESS;
}

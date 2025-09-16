
// RhinoDevel, Marcel Timm, 2017dec10

#define _USE_MATH_DEFINES

#include "znr.h"
#include "znr_pol.h"
#include "ln.h"
#include "const.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void test_simple(void)
{
    struct znr const a = (struct znr){ .r = 123.45, .i = 33.3 };
    struct znr const b = znr_pol_from(znr_pol_phi(a), znr_pol_magnitude(a));
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

    double const e = const_e();

    printf("Exponential test results:\n");
    printf("%f + j%f\n", a.r, a.i);
    printf("%f + j%f\n", b.r, b.i);
    printf("e             = %.16f\n", e);
    printf("C's constant e: %.16f\n", M_E);
}

static void test_real_trig()
{
    static int const n_terms = 50;

    double const r = 1.0;

    double const real_sin = znr_real_sin(r, n_terms);
    double const real_cos = znr_real_cos(r, n_terms);
    double const real_tan = znr_real_tan(r, n_terms);

    double const pi = const_pi();

    printf("Real trigonometric functions via exponential test results:\n");
    printf("sin(%f): %.16f\n", r, real_sin);
    printf("cos(%f): %.16f\n", r, real_cos);
    printf("tan(%f): %.16f\n", r, real_tan);
    printf("Pi             = %.16f\n", pi);
    printf("C's constant Pi: %.16f\n", M_PI);
}

static void test_real_ln()
{
    printf("Natural logarithm via exponential test results:\n");
    printf("ln(5) = %.16f\n", ln_ln(5.0));
    printf("sqrt(17.53) = %.16f\n", ln_sqrt(17.53));
}

int main(void)
{
    // Note: With "%.16f", the last digit includes some "garbage", because of
    //       the limited precision of a 64 bit floating-point value.
    //       <=> E.g. Pi and e can be precise up to the 15th digit behind the
    //           decimal point, only.

    test_simple();
    
    printf("\n");

    test_exp();

    printf("\n");

    test_real_trig();
    
    printf("\n");

    test_real_ln();

    return EXIT_SUCCESS;
}

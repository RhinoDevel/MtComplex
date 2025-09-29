
// Marcel Timm, RhinoDevel, 2025sep27

#include "znr_pol.h"
#include "atan.h"
#include "ln.h"
#include "const.h"
#include "znr.h"
#include "nan.h"
#include "norm.h"

#include <stdio.h>
#include <assert.h>

static void test_nan(void)
{
	double const nan = nan_get();

	assert(nan_is(nan)); // Own

	//assert(isnan(nan)); // Standard math lib.

	printf("*** TEST NAN ***\n");
	printf("Own not a number = %f\n", nan);
	printf("\n");
}

static void test_norm(void)
{
	static double const range_from_incl = 0.5;
	static double const range_through_excl = 2.0;

	static double const pos_val = 123.456;
	int norm_exp = 0;
	double norm_val = 0.0;

	double const norm_factor = norm_get_in_range_factor_and_fill(
		pos_val,
		range_from_incl,
		range_through_excl,
		&norm_exp,
		&norm_val);

	printf("*** TEST NORM ***\n");
	printf("Range          = [%f, %f)\n", range_from_incl, range_through_excl);
	printf("Norm. input    = %.16f\n", pos_val);
	printf("Norm. factor   = %.16f\n", norm_factor);
	printf("Norm. exponent = %d\n", norm_exp);
	printf("Norm. value    = %.16f\n", norm_val);
	printf("\n");
}

static void test_znr(void)
{
	static int const exp_terms = 30;
	struct znr const a = (struct znr){ .r = 123.456, .i = -78.9 };
	struct znr const b = (struct znr){ .r = -67.89,.i = 234.56789 };
	static double const r = 5.4321;
	struct znr a_plus_b = znr_add(a, b);
	struct znr a_min_b = znr_sub(a, b);
	struct znr a_mul_b = znr_mul(a, b);
	struct znr a_div_b = znr_div(a, b);
	struct znr a_div_r = znr_div_r(a, r);
	struct znr a_conj = znr_conjugate(a);

	printf("*** TEST ZNR ***\n");
	printf("a      = %f + j%f\n", a.r, a.i);
	printf("b      = %f + j%f\n", b.r, b.i);
	printf("|a|^2  = %f\n", znr_squared_magnitude(a));
	printf("a + b  = %f + j%f\n", a_plus_b.r, a_plus_b.i);
	printf("a - b  = %f + j%f\n", a_min_b.r, a_min_b.i);
	printf("a * b  = %f + j%f\n", a_mul_b.r, a_mul_b.i);
	printf("a / b  = %f + j%f\n", a_div_b.r, a_div_b.i);
	printf("a*     = %f + j%f\n", a_conj.r, a_conj.i);
	printf("a / %f = %f + j%f\n", r, a_div_r.r, a_div_r.i);
	printf(
		"sin(%f) = %.16f\n",
		r,
		znr_sin((struct znr){ .r = r, .i = 0.0 }, exp_terms).r);
	printf(
		"cos(%f) = %.16f\n",
		r,
		znr_cos((struct znr){ .r = r, .i = 0.0 }, exp_terms).r);
	printf(
		"tan(%f) = %.16f\n",
		r,
		znr_tan((struct znr){ .r = r, .i = 0.0 }, exp_terms).r);
	printf(
		"e^%f = %f\n",
		r,
		znr_exp((struct znr){ .r = r, .i = 0.0 }, exp_terms).r);
	printf("\n");
}

static void test_const(void)
{
	printf("*** TEST CONST ***\n");
	printf("Pi = %.16f\n", const_pi()); // (uses newton_raphson)
	printf("e  = %.16f\n", const_e());
	printf("\n");
}

static void test_ln(void)
{
	double const e = const_e();
	static double const val = 17.11;

	printf("*** TEST LN ***\n");
	printf("ln(%f) = %f\n", e, ln_ln(e));
	printf("sqrt(%f) = %f\n", val, ln_sqrt(val));
	printf("\n");
}

static void test_znr_pol(void)
{
	struct znr const a = (struct znr){ .r = 123.456, .i = -78.9 };
	double const magnitude = znr_pol_magnitude(a);
	double const phi = znr_pol_phi(a);
	struct znr const b = znr_pol_from(phi, magnitude);

	printf("*** TEST ZNR_POL ***\n");
	printf("a   = %f + j%f\n", a.r, a.i);
	printf("|a| = %f\n", magnitude);
	printf("Phi = %f\n", phi);
	printf("b   = %f + j%f\n", b.r, b.i);
	printf("\n");
}

static void test_atan(void)
{
	double const val = 0.3215;//-512.0;//1.234;
	double const atan_val = atan_atan(val);

	double const x = -512.0;
	double const y = 1.234;
	double const atan2_val = atan_atan2(y, x);

	printf("*** TEST ATAN ***\n");
	printf("atan(%f) = %f\n", val, atan_val);
	printf("atan2(%f, %f) = %f\n", y, x, atan2_val);
	printf("\n");
}

int main(void)
{
	printf("Bare Math!\n");
	printf("\n");

	const_init();

	test_nan();

	test_norm();

	test_znr();

	test_const();

	test_ln();

	test_znr_pol();

	test_atan();

	return 0;
}

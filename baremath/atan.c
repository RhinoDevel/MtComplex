
// RhinoDevel, Marcel Timm, 2025sep28

#include "atan.h"
#include "znr.h"
#include "const.h"
#include "newton_raphson.h"
#include "nan.h"

static double newton_raphson_step_atan(double const phi, double const x)
{
	// The terms to calculate by exponential function.
	static int const exp_terms = 50; // TODO: More or less?

	// phi_n+1 = phi_n - cos(phi_n) * (sin(phi_n) - x * cos(phi_n))

	struct znr const phi_complex = (struct znr){ .r = phi, .i = 0.0 };
	double const cos_phi = znr_cos(phi_complex, exp_terms).r;
	double const sin_phi = znr_sin(phi_complex, exp_terms).r;
	double const ret_val = phi - cos_phi * (sin_phi - x * cos_phi);

	return ret_val;
}

double atan_atan(double const val)
{
	// phi = atan(val) = ?
	// phi             = atan(val)
	// =>
	// tan(phi)        = val
	// tan(phi) - val  = 0
	// =>
	// f(phi)          = tan(phi) - val
	// f'(phi)         = sec(phi)^2
	// f'(phi)         = 1 / cos(phi)^2
	// with: sin(x)^2 + cos(x)^2 = 1 and tan(x)^2 = sin(x)^2 / cos(x)^2
	// =>
	// f'(phi)         = 1 + (tan(phi)^2)
	// =>
	// phi_n+1 = phi_n - (tan(phi_n) - val) / (1 + tan(phi_n)^2)
	// =>
	// phi_n+1 = phi_n - cos(phi_n) * (sin(phi_n) - x * cos(phi_n))

	bool const val_is_neg = val < 0.0;
	double const abs_val = val_is_neg ? -val : val;
	bool const use_range_reduction = 1.0 < abs_val;
	double val_to_use = val;
	double newton_raphson_result = 0.0;
	double result = 0.0;

	// Range reduction (1/2):
	if(use_range_reduction)
	{
		// arctan(x) = +/- Pi/2 - arctan(1/x)
		//
		// +, if given value is positive or zero.
		// -, if given value is negative.

		val_to_use = 1 / val;
	}

	// Break after this maximum iteration count:
	static int const max_steps = 30; // TODO: More or less?

	// Break, if last and current results difference is less than this value:
	static double const done_diff = 1e-15; // TODO: More?

	// The initial guess:
	static double const phi_0 = 0.5; // TODO: Improve generation?

	newton_raphson_result = newton_raphson(
		max_steps, done_diff, phi_0, val_to_use, newton_raphson_step_atan);
	if(nan_is(newton_raphson_result))
	{
		return newton_raphson_result/*nan_get()*/;
	}

	result = newton_raphson_result;
	// Range reduction (2/2):
	if(use_range_reduction)
	{
		double buf = const_pi() / 2.0;

		if(val_is_neg)
		{
			buf = -buf;
		}
		result = buf - result;
	}
	return result;
}


// RhinoDevel, Marcel Timm, 2025sep28

#include "atan.h"
#include "nan.h"

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

	return nan_get(); // TODO: Implement!
}

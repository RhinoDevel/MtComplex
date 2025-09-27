
// RhinoDevel, Marcel Timm, 2025sep16

#include "nan.h"

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <string.h> // For memcpy().

bool nan_is(double const val)
{
    return val != val;
}

double nan_get(void)
{
    // Modern compilers should reduce this:

    static uint64_t const nan_int = 0x7ff8000000000000ULL;
    
    double ret_val = 0.0;

    memcpy(&ret_val, &nan_int, sizeof ret_val);

    assert(nan_is(ret_val));

    return ret_val;
}

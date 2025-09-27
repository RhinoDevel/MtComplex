
// RhinoDevel, Marcel Timm, 2025sep16

#ifndef MT_NAN
#define MT_NAN

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool nan_is(double const);

double nan_get(void);

#ifdef __cplusplus
}
#endif

#endif //MT_NAN

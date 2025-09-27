
// RhinoDevel, Marcel Timm, 2025sep15

#ifndef MT_NEWTON_RAPHSON
#define MT_NEWTON_RAPHSON

#ifdef __cplusplus
extern "C" {
#endif

/**
 * - Returns not-a-number, if no reasonably precise result was found by
 *   approximation.
 */
double newton_raphson(
    int const max_steps,
    double const done_diff,
    double const initial_guess,
    double const val,
    double (*step_func)(double, double));

#ifdef __cplusplus
}
#endif

#endif //MT_NEWTON_RAPHSON

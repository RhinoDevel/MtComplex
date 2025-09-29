
// RhinoDevel, Marcel Timm, 2025sep15

#ifndef MT_CONST
#define MT_CONST

#ifdef __cplusplus
extern "C" {
#endif

/**
 * - Call const_init() first!
 */
double const_e(void);

/**
 * - Call const_init() first!
 */
double const_pi(void);

/** Call this once before use to calculate all constants.
 */
void const_init(void);

#ifdef __cplusplus
}
#endif

#endif //MT_CONST


// RhinoDevel, Marcel Timm, 2025sep28

#ifndef MT_ATAN
#define MT_ATAN

#ifdef __cplusplus
extern "C" {
#endif

/** Get arcus tangent of given value via Newton-Raphson.
 * 
 * - Returns not-a-number, if no reasonably precise result was found by
 *   approximation.
 */
double atan_atan(double const val);

#ifdef __cplusplus
}
#endif

#endif //MT_ATAN

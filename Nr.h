
// RhinoDevel, Marcel Timm, 2017dec10

#ifndef MT_NR
#define MT_NR

#ifdef __cplusplus
extern "C" {
#endif

struct Nr
{
    double const r;
    double const i;
};

struct Nr * Nr_add(struct Nr const * const a, struct Nr const * const b);
struct Nr * Nr_sub(struct Nr const * const a, struct Nr const * const b);
struct Nr * Nr_mul(struct Nr const * const a, struct Nr const * const b);
struct Nr * Nr_div(struct Nr const * const a, struct Nr const * const b);

double Nr_magnitude(struct Nr const * const nr);
double Nr_phi(struct Nr const * const nr);

struct Nr * Nr_create_from_polar(double const phi, double const magnitude);

struct Nr * Nr_create(double const r, double const i);
void Nr_delete(struct Nr * nr);

#ifdef __cplusplus
}
#endif

#endif // MT_NR

#include <stdint.h>

#define NUMWORDS 40

typedef uint32_t ff_t[NUMWORDS];

#define ff_zero(a) memset(a, 0, NUMWORDS * sizeof(uint32_t))
#define ff_copy(a,b) memcpy(a, b, NUMWORDS * sizeof(uint32_t))

void ff_rnd(ff_t);
void ff_print(ff_t);
void ff_print_poly(ff_t);
void ff_add(ff_t, const ff_t, const ff_t);
void ff_mul(ff_t, const ff_t, const ff_t);
void ff_exp(ff_t, const ff_t, const ff_t);

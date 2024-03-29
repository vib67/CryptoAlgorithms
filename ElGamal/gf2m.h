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
void ff_inv(ff_t, const ff_t);

// TODO: new stuff
void ff_keygen(ff_t, ff_t);
void ff_encrypt(unsigned char *, unsigned char *, int, const ff_t);
int ff_decrypt(unsigned char *, unsigned char *, const ff_t);
void shiftleft(ff_t res, ff_t v, int shift);
int degree(ff_t p);



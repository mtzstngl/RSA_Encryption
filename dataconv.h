#include <gmp.h>
#include <gmpxx.h>

uint8_t* I2OSP(mpz_class uIntX, size_t octetXLen);
mpz_class OS2IP(uint8_t *octetX, size_t octetXLen);

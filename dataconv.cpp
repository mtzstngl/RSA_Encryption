#include "dataconv.h"

uint8_t* I2OSP(mpz_class uIntX, size_t octetXLen)
{
  uint8_t *octetX = new uint8_t[octetXLen];
  mpz_class tmp;
  int index = 0;

  while(uIntX > 0){
    tmp = uIntX % 256;
    octetX[octetXLen - 1 - index] = tmp.get_ui();
    uIntX /= 256;

    index++;
  }

  //fill the rest with 0x00
  std::fill_n(octetX, octetXLen - index, 0x00);

  return octetX;
}

mpz_class OS2IP(uint8_t *octetX, size_t octetXLen)
{
  mpz_class ret, rop;
  
  for(int i = octetXLen - 1; i >= 0; i--){
    mpz_ui_pow_ui(rop.get_mpz_t(), 256, octetXLen - 1 - i);
    ret += rop * octetX[i];
  }

  return ret;
}

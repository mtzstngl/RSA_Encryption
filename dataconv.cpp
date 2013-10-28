/*
 *Copyright (C) 2013 by Matthias Stangl
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
 */

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

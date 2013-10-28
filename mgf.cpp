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

#include "mgf.h"

void mgf(CryptoPP::SHA256 hash, uint8_t *mask, size_t maskLen, uint8_t *seed, uint8_t seedLen)
{
  size_t hLen = CryptoPP::SHA256::DIGESTSIZE;
  uint8_t mgfSeed[seedLen + 4];
  uint8_t digest[hLen];
  size_t maxCount = (maskLen / hLen) - 1;
  if(maskLen % hLen){
    maxCount++;
  }

  for(size_t i = 0; i <= maxCount; i++){
    uint8_t *C = I2OSP(i, 4);
    std::copy(seed, seed + seedLen, mgfSeed);
    std::copy(C, C + 4, mgfSeed + seedLen);
    hash.CalculateDigest(digest, mgfSeed, seedLen + 4);
    std::copy(digest, digest + hLen, mask + hLen * i);
  }
}

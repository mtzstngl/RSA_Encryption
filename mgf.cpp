#include "mgf.h"

void mgf(CryptoPP::SHA256 hash, uint8_t *mask, size_t maskLen, uint8_t *seed, uint8_t seedLen)
{
  size_t hLen = CryptoPP::SHA256::DIGESTSIZE;
  size_t maxCount = (maskLen / hLen) - 1;
  uint8_t mgfSeed[seedLen + 4];
  uint8_t digest[hLen];

  for(size_t i = 0; i <= maxCount; i++){
    uint8_t *C = I2OSP(i, 4);
    std::copy(seed, seed + seedLen, mgfSeed);
    std::copy(C, C + 4, mgfSeed + seedLen);
    hash.CalculateDigest(digest, mgfSeed, seedLen + 4);
    std::copy(digest, digest + hLen, mask + hLen * i);
  }
}

#ifndef MGF_H
#define MGF_H

#include <cryptlib.h>
#include <sha.h>
#include "dataconv.h"

void mgf(CryptoPP::SHA256 hash, uint8_t *mask, size_t maskLen, uint8_t *seed, uint8_t seedLen);

#endif //MGF_H

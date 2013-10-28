#ifndef RSAES_OAEP_H
#define RSAES_OAEP_H

#include <string>
#include <algorithm>
#include <chrono>
#include <gmp.h>
#include <gmpxx.h>
#include <sha.h>
#include <pubkey.h>
#include <cryptlib.h>
#include "dataconv.h"
#include "mgf.h"

using namespace std;

string rsaes_oaep_enc(string eStr, string NStr, string M, string L);
string rsaes_oaep_dec(string dStr, string NStr, string CStr, string L);

#endif //RSAES_OAEP_H

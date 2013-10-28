#ifndef RSA_H
#define RSA_H

#include <string>
#include <chrono>
#include <algorithm>
#include <gmpxx.h>
#include <gmp.h>
#include "dataconv.h"

using namespace std;

mpz_class gcd(mpz_class a, mpz_class b);
void extended_ea(mpz_class a, mpz_class &b, mpz_class &s, mpz_class &t);
bool miller_rabin_test(mpz_class prime, mpz_class rounds);
bool fermat_test(mpz_class prime, mpz_class rounds);
void genrsa(mpz_class block_size, mpz_class &q, mpz_class &p, mpz_class &N, mpz_class &e, mpz_class &d);
string rsa_enc(string plainText, string eStr, string NStr);
string rsa_dec(string encrypted, string dStr, string NStr);
string rsa_enc_completely(string plainText, string eStr, string NStr);
string rsa_dec_completely(string encrypted, string dStr, string NStr);

#endif //RSA_H

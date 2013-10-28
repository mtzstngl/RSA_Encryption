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

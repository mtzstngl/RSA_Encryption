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

#include "rsa.h"

string rsa_enc_completely(string plainText, string eStr, string NStr)
{
  string encrypted, tmp;
  mpz_class e, N, enc;
  mpz_class plain;
  
  if( (!std::all_of(eStr.begin(), eStr.end(), ::isdigit)) || (eStr == "") ){
    return "e is not a number";
  }
  if( (!std::all_of(NStr.begin(), NStr.end(), ::isdigit)) || (NStr == "") ){
    return "N is not a number";
  }

  e.set_str(eStr, 10);
  N.set_str(NStr, 10);
  
  plain = OS2IP(reinterpret_cast<uint8_t*>(const_cast<char*>(plainText.data())), plainText.size());
  
  if(plain < N){
    mpz_powm(enc.get_mpz_t(), plain.get_mpz_t(), e.get_mpz_t(), N.get_mpz_t());
    encrypted = enc.get_str();
  }else{
    encrypted = "plainText too big";
  }

  return encrypted;
}

string rsa_dec_completely(string encrypted, string dStr, string NStr)
{
  mpz_class d, N, dec, enc;

  if( (!std::all_of(dStr.begin(), dStr.end(), ::isdigit)) || (dStr == "") ){
    return "d is not a number";
  }
  if( (!std::all_of(NStr.begin(), NStr.end(), ::isdigit)) || (NStr == "") ){
    return "N is not a number";
  }

  d.set_str(dStr, 10);
  N.set_str(NStr, 10);


  enc.set_str(encrypted, 10);
  mpz_powm(dec.get_mpz_t(), enc.get_mpz_t(), d.get_mpz_t(), N.get_mpz_t());
  
  size_t k = mpz_sizeinbase(dec.get_mpz_t(), 256);

  uint8_t *octetText = I2OSP(dec, k);
  
  return string(octetText, octetText + k);
}

string rsa_enc(string plainText, string eStr, string NStr)
{
  string encrypted;
  mpz_class asciiNum;
  mpz_class e, N, enc;
  
  if( (!std::all_of(eStr.begin(), eStr.end(), ::isdigit)) || (eStr == "") ){
    return "e is not a number";
  }
  if( (!std::all_of(NStr.begin(), NStr.end(), ::isdigit)) || (NStr == "") ){
    return "N is not a number";
  }

  e.set_str(eStr, 10);
  N.set_str(NStr, 10);

  if(N < 256){
    return "N is too small";
  }
  
  for(char asciiChar : plainText){
    uint8_t asciiUint = asciiChar;
    asciiNum = OS2IP(&asciiUint, 1);
    mpz_powm(enc.get_mpz_t(), asciiNum.get_mpz_t(), e.get_mpz_t(), N.get_mpz_t());
    encrypted += enc.get_str() + " ";
  }

  return encrypted;
}

string rsa_dec(string encrypted, string dStr, string NStr)
{
  string plainText;
  mpz_class d, N, dec, enc;

  if( (!std::all_of(dStr.begin(), dStr.end(), ::isdigit)) || (dStr == "") ){
    return "d is not a number";
  }
  if( (!std::all_of(NStr.begin(), NStr.end(), ::isdigit)) || (NStr == "") ){
    return "N is not a number";
  }

  d.set_str(dStr, 10);
  N.set_str(NStr, 10);

  while(encrypted.find_first_not_of(" ") != string::npos){
    size_t pos, pos2;

    pos = encrypted.find_first_not_of(" ");
    pos2 = encrypted.find_first_of(" ", pos);
    
    enc.set_str(encrypted.substr(pos, pos2), 10);
    encrypted.erase(pos, pos2);
    
    mpz_powm(dec.get_mpz_t(), enc.get_mpz_t(), d.get_mpz_t(), N.get_mpz_t());
    plainText += static_cast<char>(dec.get_ui());
  }
  
  return plainText;
}

void genrsa(mpz_class block_size, mpz_class &q, mpz_class &p, mpz_class &N, mpz_class &e, mpz_class &d)
{
  //generate numbers with desired length

  mpz_class m,s;
  gmp_randclass randClass(gmp_randinit_default);

  block_size /= 2; //size of a prime

  //generate p
  randClass.seed(mpz_class(chrono::high_resolution_clock::now().time_since_epoch().count()));
  p = randClass.get_z_bits(block_size);

  if( (!fermat_test(p, 200)) || (!miller_rabin_test(p, 200)) ){
    while( (!fermat_test(p, 200)) || (!miller_rabin_test(p, 200)) ){
      p++;
    }
  }

  //generate q
  q = randClass.get_z_bits(block_size);
  if( ((!fermat_test(q, 200)) || (!miller_rabin_test(q, 200))) /*|| (q == p) */){
    while( ((!fermat_test(q, 200)) || (!miller_rabin_test(q, 200))) /*|| (q == p)*/ ){
      q++;
    }
  }

  N = p * q;

  m = (p - 1) * (q - 1);

  randClass.seed(chrono::high_resolution_clock::now().time_since_epoch().count());
  do{
    e = randClass.get_z_range(m);
  }while( (e <= 1) || (gcd(e, m) != 1) );

  mpz_class tmp = m;
  extended_ea(e, tmp, s, d);
  if(d <= 0){
    d = d + m;
  }
}

//gcd using gmplib for big numbers
mpz_class gcd(mpz_class a, mpz_class b)
{
  mpz_class tmp;

  //test if a and b are natural numbers
  if( (a <= 0) || (b <= 0) ){
    return -1;
  }

  while( b != 0){
    tmp = b;
    b = a % b;
    a = tmp;
  }
  
  return a;
}

//inductive eea method
// b = gcd;
// s = x;
// t = y;
void extended_ea(mpz_class a, mpz_class &b, mpz_class &s, mpz_class &t)
{
  mpz_class  q, u, v, r, tmp;

  //initialize all the variables
  u = 1;
  s = 0;
  v = 0;
  t = 1;

  //test if a and b are natural numbers
  if((a <= 0) || (b <= 0)){
    b = -1;
    s = -1;
    t = -1;
    return;
  }

  //if b is bigger than a switch it
  if( b > a){
    tmp = b;
    b = a;
    a = tmp;
  }

  while(true){
    q = a / b;
    r = a % b;
    
    //check if we already reached the end of the eea
    if(r == 0){
      break;
    }

    tmp = s;
    s = u - q * s;
    u = tmp;

    tmp = t;
    t = v - q * t;
    v = tmp;

    a = b;
    b = r;
  }
}

mpz_class log2(mpz_class op)
{
  mpfr_t tmpMpfr;
  mpf_class tMpf;

  mpfr_init2(tmpMpfr, 10);
  mpfr_set_z(tmpMpfr, op.get_mpz_t(), MPFR_RNDZ);
  mpfr_log2(tmpMpfr, tmpMpfr, MPFR_RNDZ);

  mpfr_get_f(tMpf.get_mpf_t(), tmpMpfr, MPFR_RNDZ);
  mpz_set_f(op.get_mpz_t(), tMpf.get_mpf_t());

  return op;
}

bool miller_rabin_test(mpz_class prime, mpz_class rounds)
{
  mpz_class a, d, s = 1;
  mpz_class i = 0;
  mpz_class result = 0;
  mpz_class j = 0;
  mpz_class prefix = 0;
  gmp_randclass rand(gmp_randinit_default);

  //test if even or too small
  if( ((prime % 2) == 0) || (prime <= 2) || (rounds <= 0) ){
    return false;
  }
  
  //calculate s
  i = log2(prime);
  do{
    mpz_pow_ui(s.get_mpz_t(), mpz_class(2).get_mpz_t(), i.get_ui());
    i--;
  }while( ((prime - 1) % s) != 0);
  s = i + 1;
  
  //calculate d
  mpz_pow_ui(d.get_mpz_t(), mpz_class(2).get_mpz_t(), s.get_ui());
  d = (prime - 1) / d;

  //use the miller rabin test for x rounds
  for(mpz_class i = 0; i < rounds; i++){
    //generate random number
    //use chrono time since epoch to generate the seed
    mpz_class seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    rand.seed(seed);
    // a is only allowed from 2 to n-1 but rand.get_z_range outputs numbers from 0 to n-1
    do{
      a = rand.get_z_range(prime);
      //check if this a was already used
    }while(a < 2);
    //test if a^d % prime == 1
    mpz_powm(result.get_mpz_t(), a.get_mpz_t(), d.get_mpz_t(), prime.get_mpz_t());
    if( (result == 1) || ((result - prime) == -1) ){
      continue;
    }
    //test r from 0 to s - 1 if a^((2^r) * d) % prime == -1
    while( j <= s ){
      mpz_pow_ui(prefix.get_mpz_t(), mpz_class(2).get_mpz_t(), j.get_ui());
      prefix *= d;
      mpz_powm(result.get_mpz_t(), a.get_mpz_t(), prefix.get_mpz_t(), prime.get_mpz_t());
      if( (result == -1) || ((result - prime) == -1) ) {
        break;
      }else if( j >= (s - 1)){
        return false;
      }
      j++;
    } 
  }
  
  return true;
}

//a^(n-1) mod n == 1
bool fermat_test(mpz_class prime, mpz_class rounds)
{
  //needed otherwise we would lose the value of prime
  mpz_class exp = prime - 1;
  mpz_class result, a;
  gmp_randclass rand(gmp_randinit_default);
  
  //test if too small
  if(prime <= 0){
    return false;
  }

  for(mpz_class i = 1; i < rounds; i++){
    //generate random number
    //use chrono time since epoch to generate the seed
    mpz_class seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    rand.seed(seed);
    // a is only allowed from 1 to n but rand.get_z_range outputs numbers from 0 to n-1
    do{
      a = rand.get_z_range(prime);
      //check if this a was already used
    }while(a < 1);

    mpz_powm(result.get_mpz_t(), a.get_mpz_t(), exp.get_mpz_t(), prime.get_mpz_t());
    if(result != 1){
      return false;
    }
  }
  return true;
}

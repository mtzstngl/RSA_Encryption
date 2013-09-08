#include "rsa.h"

string rsa_enc_completely(string plainText, string eStr, string NStr)
{
  string encrypted, tmp;
  int asciiNum;
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
  
  for(char asciiChar : plainText){
    asciiNum = asciiChar;
    if(asciiNum < 10){
      tmp += "00" + std::to_string(asciiNum);
    }else if(asciiNum < 100){
      tmp += "0" + std::to_string(asciiNum);
    }else{
      tmp += std::to_string(asciiNum);
    }
  }
  
  plain.set_str(tmp, 10);
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
  string plainText, sub;
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

  encrypted = dec.get_str();

  while(encrypted.length() > 0){
    if(encrypted.length() >= 3){
      sub = encrypted.substr(encrypted.length() - 3, encrypted.length());
      encrypted.erase(encrypted.length() - 3, encrypted.length());
    }else{
      sub = encrypted.substr(encrypted.length() - encrypted.length(), encrypted.length());
      encrypted.erase(encrypted.length() - encrypted.length(), encrypted.length());
    }
    plainText += static_cast<char>(std::stoi(sub));
  }
  
  std::reverse(plainText.begin(), plainText.end());

  return plainText;
}

string rsa_enc(string plainText, string eStr, string NStr)
{
  string encrypted;
  int asciiNum;
  mpz_class e, N, enc;
  
  if( (!std::all_of(eStr.begin(), eStr.end(), ::isdigit)) || (eStr == "") ){
    return "e is not a number";
  }
  if( (!std::all_of(NStr.begin(), NStr.end(), ::isdigit)) || (NStr == "") ){
    return "N is not a number";
  }

  e.set_str(eStr, 10);
  N.set_str(NStr, 10);
  
  for(char asciiChar : plainText){
    asciiNum = asciiChar;
    mpz_powm(enc.get_mpz_t(), mpz_class(asciiNum).get_mpz_t(), e.get_mpz_t(), N.get_mpz_t());
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
/*
 *  gmp_randclass randClass(gmp_randinit_default);
 *
 *  for(mpz_class i = 0; i < 1000000000; i+= 10000){
 *    randClass.seed(mpz_class(chrono::high_resolution_clock::now().time_since_epoch().count()));
 *    mpf_class f(0, 4096);
 *    f = randClass.get_f();
 *    f *= 10000000000 * i;
 *    f += 200000000000 * i;
 *    cout << f << endl;
 *    mpz_class integer;
 *    mpz_set_f(integer.get_mpz_t(), f.get_mpf_t());
 *    cout << integer << endl;
 *  }
 */

  mpz_class m,s;
  gmp_randclass randClass(gmp_randinit_default);

  block_size/2; //size of a prime

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
  while( ((prime - 1) % s) == 0){
    i++;
    mpz_pow_ui(s.get_mpz_t(), mpz_class(2).get_mpz_t(), i.get_ui());
  }
  s = i - 1;
  
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

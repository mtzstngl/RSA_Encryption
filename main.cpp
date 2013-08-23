#include <iostream>
#include <gmpxx.h>
#include <gmp.h>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

mpz_class gcd(mpz_class a, mpz_class b);
void extended_ea(mpz_class a, mpz_class &b, mpz_class &s, mpz_class &t);
bool miller_rabin_test(mpz_class prime, mpz_class rounds);
bool fermat_test(mpz_class prime, mpz_class rounds);

int main()
{
  mpz_class inA, inB, x, y;
  
  cout << "gcd: enter two numbers" << endl;
  cin >> inA;
  cin >> inB;
  cout << "gcd returned: " << gcd(inA, inB) << endl;

  cout << "extended_ea: enter two numbers" << endl;
  cin >> inA;
  cin >> inB;
  extended_ea(inA, inB, x, y);
  cout << "extended_ea returned: inB = " << inB << " x = " << x << " y = " << y << endl;

  cout << "fermat_test: enter a number" << endl;
  cin >> inA;
  cin >> inB;
  if(fermat_test(inA, inB.get_ui())){
    cout << "fermat_test returned true" << endl;
  }else{
    cout << "fermat_test returned false" << endl;
  }

  cout << "miller_rabin_test: enter two numbers" << endl;
  cin >> inA;
  cin >> inB;
  if(miller_rabin_test(inA, inB.get_ui())){
    cout << "miller_rabin_test returned true" << endl;
  }else{
    cout << "miller_rabin_test returned false" << endl;
  }

  return 0;
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
    cout << "result: " << result << " result - prime: " << result - prime << endl;
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

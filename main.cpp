#include <iostream>
#include <gmpxx.h>
#include <gmp.h>
#include <chrono>

using namespace std;

mpz_class gcd(mpz_class a, mpz_class b);
void extended_ea(mpz_class a, mpz_class &b, mpz_class &s, mpz_class &t);
bool miller_rabin_test(mpz_class prime, unsigned int rounds);
bool fermat_test(mpz_class prime);

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
  if(fermat_test(inA)){
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
    
    //check if already reached the end of the eea
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

//FIXME: sometimes a is still the same number over and over again -> vary seed and generation
bool miller_rabin_test(mpz_class prime, unsigned int rounds)
{
  mpz_class a, d, s = 1; //will be needed later
  mpz_class i = 0;
  mpz_class randMax = prime - 1;
  mpz_class result = 0;
  mpz_class j = 1;
  mpz_class prefix = 0;
  gmp_randclass rr(gmp_randinit_default);

  //test if uneven or too small
  if( ((prime % 2) == 0) || (prime <= 2) || (rounds <= 0) ){
    return false;
  }
  
  cout << "miller_rabin_test: prime = " << prime << endl;
  //calculate s
  while( ((prime - 1) % s) == 0){
    i++;
    mpz_pow_ui(s.get_mpz_t(), mpz_class(2).get_mpz_t(), i.get_ui());
  }
  s = i - 1;
  cout << "miller_rabin_test: s = " << s << endl;
  
  //calculate d
  mpz_pow_ui(d.get_mpz_t(), mpz_class(2).get_mpz_t(), s.get_ui());
  d = (prime - 1) / d;
  cout << "miller_rabin_test: d = " << d << endl;

  //use the miller rabin test for x rounds
  for(unsigned int i = 0; i < rounds; i++){
    cout << "miller_rabin_test: round = " << i << endl;
    //generate random number
    rr.seed(time(NULL));
    a = rr.get_z_range(randMax);
    cout << "miller_rabin_test: a = " << a << endl;
    //test if a^d % prime == 1
    mpz_powm(result.get_mpz_t(), a.get_mpz_t(), d.get_mpz_t(), prime.get_mpz_t());
    cout << "miller_rabin_test: a^d mod prime: " << result << endl;
    if( (result == 1) || ((result - prime) == -1) ){
      continue;
    }
    //test r from 0 to s - 1 if a^((2^r) * d) % prime == -1
    while( j < s ){
      mpz_pow_ui(prefix.get_mpz_t(), mpz_class(2).get_mpz_t(), j.get_ui());
      prefix *= d;
      mpz_powm(result.get_mpz_t(), a.get_mpz_t(), prefix.get_mpz_t(), prime.get_mpz_t());
      cout << "miller_rabin_test: " << a << "^" << prefix << " % " << prime << " == " << result << endl;
      if( (result == -1) || ((result - prime) == -1) ) {
        cout << "miller_rabin_test: you passed" << endl;
        break;
      }else if( j == (s - 1)){
        cout << "miller_rabin_test: you failed" << endl;
        return false;
      }
      j++;
    } 
  }
  
  cout << "miller_rabin_test: you passed" << endl;
  return true;
}

//TODO:add max number for testing
//TODO:dont count upwards use random numbers
//a^(n-1) -1 mod n == 0
bool fermat_test(mpz_class prime)
{
  //needed otherwise we would lose the value of prime
  mpz_class exp = prime - 1;
  mpz_class result;
  
  //test if too small
  if(prime <= 0){
    return false;
  }

  for( mpz_class i = 1; i < prime; i++){
    cout << "i: " << i << endl;
    mpz_powm(result.get_mpz_t(), i.get_mpz_t(), exp.get_mpz_t(), prime.get_mpz_t());
    cout << "result: " << result << endl;
    if(result != 1){
      return false;
    }
  }
  return true;
}

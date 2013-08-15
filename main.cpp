#include <iostream>
#include <gmpxx.h>
#include <chrono>

using namespace std;

mpz_class gcd(mpz_class a, mpz_class b);
void extended_ea(mpz_class a, mpz_class &b, mpz_class &s, mpz_class &t);

//TODO: write fermats test
//TODO: write miller rabin test
int main()
{
  mpz_class inputA, inputB, x, y;

  cout << "enter two natural numbers:" << endl;
  cin >> inputA;
  cin >> inputB;
  
  chrono::time_point<chrono::high_resolution_clock> start2 = chrono::high_resolution_clock::now();
  extended_ea(inputA, inputB, x, y);
  chrono::time_point<chrono::high_resolution_clock> end2 = chrono::high_resolution_clock::now();
  cout << "extended_ea: x: " << x << " y: " << y  << " gcd: " << inputB << " time: " <<
    chrono::duration_cast<chrono::microseconds>(end2 - start2).count() << endl;
 
  return 0;
}

mpz_class gcd(mpz_class a, mpz_class b)
{
  mpz_class tmp;
  while( b != 0){
    if( (a <= 0) || (b <= 0) ){ //only allow natural numbers
      a = 0;
      break;
    }
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
  q = 1;
  u = 1;
  s = 0;
  v = 0;
  t = 1;
  r = 1;

  while( r != 0){
    q = a / b;
    r = a % b;

    a = b;
    b = r;
    
    tmp = s;
    s = u - q * s;
    u = tmp;

    tmp = t;
    t = v - q * t;
    v = tmp;
    
    r = a % b; //otherwise it would leave the loop too late
  }
}

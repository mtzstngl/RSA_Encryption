#include <iostream>
#include <gmpxx.h>

using namespace std;

void eea (int a, int b,
        int& gcd, int& x, int& y) {
        x=0, y=1; 
        int u=1, v=0, m, n, q, r;
        gcd = b;
        while (a!=0) {
                q=gcd/a; r=gcd%a;
                m=x-u*q; n=y-v*q;
                gcd=a; a=r; x=u; y=v; u=m; v=n;
        }
}

mpz_class gcd(mpz_class a, mpz_class b);
void extended_ea(mpz_class a, mpz_class b, mpz_class &gcd, mpz_class &x, mpz_class &y);

//TODO: write extended_gcd
//TODO: write fermats test
//TODO: write miller rabin test
int main(int argc, char *argv[])
{
  int inputA, inputB, x, y, tmp;

  cout << "enter two natural numbers:" << endl;
  cin >> inputA;
  cin >> inputB;
  
  eea(inputA, inputB, tmp, x, y);
  //extended_ea(inputA, inputB, tmp, x, y);
  cout << "x:" << x << " y: " << y  << " gcd: " << tmp << endl;
  
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

void extended_ea(mpz_class a, mpz_class b, mpz_class &gcd, mpz_class &x, mpz_class &y)
{
  mpz_class u, v, m, n, q, r;
  u = 1;
  v = 0;
  x = 0;
  y = 1;

  gcd = b;
  while(a != 0){
    //q = gcd / a; r = gcd % a;
    //m = x - u * q; n = y - v * q;
    //gcd = a; a = r; x = u; y = v; v = n;
    r = gcd % a;
    q = gcd / a;
    n = y - v * q;
    m = x - u * q;
    v = n;
    y = v;
    x = u;
    a = r;
    gcd = a;
  }
}

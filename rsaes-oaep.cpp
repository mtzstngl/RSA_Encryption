#include "rsaes-oaep.h"

string rsaes_oaep_enc(string eStr, string NStr, string M, string L)
{
  mpz_class e, N;

  if( (!std::all_of(eStr.begin(), eStr.end(), ::isdigit)) || (eStr == "") ){
    return "e is not a number";
  }
  if( (!std::all_of(NStr.begin(), NStr.end(), ::isdigit)) || (NStr == "") ){
    return "N is not a number";
  }

  e.set_str(eStr, 10);
  N.set_str(NStr, 10);

  size_t mLen = M.size(); //length of M
  size_t k = mpz_sizeinbase(N.get_mpz_t(), 2); //length of RSA modulus N in octets
  if(k % 8){ //convert bit to octets
    cout << "k before: " << k << endl;
    k = (k / 8) + 1;
  }else{
    k /= 8;
  }
  cout << "k: " << k << endl;

  size_t hLen = CryptoPP::SHA256::DIGESTSIZE;
  uint8_t lHash[hLen];//hash output
  size_t PSsize = k - mLen - (2 * hLen) - 2;
  uint8_t PS[PSsize];//octet stream consisting of zero octets
  uint8_t *seed;
  uint8_t DB[k - hLen - 1];
  CryptoPP::SHA256 hash; //hash of type SHA256
  
  //k needs to be k >= 2*hLen + 2
  if(k  < (2 * hLen + 2) ){
    return "encryption error.\nN is too small";
  }

  //Step 1 Length checking
  //1.a check label
  if(L.size() > hLen){
    return "label too long";
  }

  //1.b check the message length
  if(mLen > (k - (2 * hLen) - 2) ){
    return "message too long";
  }

  //Step 2 EME-OAEP
  //2.a
  hash.CalculateDigest(lHash, reinterpret_cast<uint8_t*>(const_cast<char*>(L.data())), L.size());
  
  //2.b
  std::fill_n(PS, PSsize, 0x00);

  //2.c
  std::copy(lHash, lHash + hLen, DB);
  std::copy(PS, PS + PSsize, DB + hLen);
  DB[PSsize + hLen] = 0x01;
  std::copy(M.begin(), M.end(), DB + hLen + PSsize + 1);
  
  //2.d
  gmp_randclass gmp_rand(gmp_randinit_default);
  gmp_rand.seed(chrono::high_resolution_clock::now().time_since_epoch().count());
  mpz_class gmp_seed = gmp_rand.get_z_bits(hLen * 8);
  seed = I2OSP(gmp_seed, hLen);

  //2.e
  size_t tmpSize = k - hLen - 1;
  uint8_t dbMask[tmpSize];
  mgf(hash, dbMask, tmpSize, seed, hLen);

  //2.f
  uint8_t maskedDB[tmpSize];
  for(size_t i = 0; i < tmpSize; i++){
    maskedDB[i] = DB[i] ^ dbMask[i];
  }

  //2.g
  uint8_t seedMask[hLen];
  mgf(hash, seedMask, hLen, maskedDB, tmpSize);

  //2.h
  uint8_t maskedSeed[hLen];
  for(size_t i = 0; i < hLen; i++){
    maskedSeed[i] = seed[i] ^ seedMask[i];
  }

  //2.i
  uint8_t EM[k];
  EM[0] = 0x00;
  std::copy(maskedSeed, maskedSeed + hLen, EM + 1);
  std::copy(maskedDB, maskedDB + tmpSize, EM + 1 + hLen);

  //3 RSA encryption
  //3.a
  mpz_class m = OS2IP(EM, k);

  //3.b
  mpz_class c;
  mpz_powm(c.get_mpz_t(), m.get_mpz_t(), e.get_mpz_t(), N.get_mpz_t());

  //3.c convert c via I2OSP to an octet string
  //not needed because the output wouldn't be readable unless it is converted to HEX

  return c.get_str(10);
}

string rsaes_oaep_dec(string dStr, string NStr,string CStr, string L)
{
  mpz_class d, N, C;

  if( (!std::all_of(dStr.begin(), dStr.end(), ::isdigit)) || (dStr == "") ){
    return "e is not a number";
  }
  if( (!std::all_of(NStr.begin(), NStr.end(), ::isdigit)) || (NStr == "") ){
    return "N is not a number";
  }
  if( (!std::all_of(CStr.begin(), CStr.end(), ::isdigit)) || (CStr == "") ){
    return "C is not a number";
  }

  d.set_str(dStr, 10);
  N.set_str(NStr, 10);
  C.set_str(CStr, 10);
  
  CryptoPP::SHA256 hash;
  size_t hLen = CryptoPP::SHA256::DIGESTSIZE;
  size_t k = mpz_sizeinbase(N.get_mpz_t(), 2); //length of RSA modulus N in octets
  cout << "k before: " << k << endl;
  if(k % 8){ //convert bit to octets
    k = (k / 8) + 1;
  }else{
    k /= 8;
  }

  size_t Clen = mpz_sizeinbase(C.get_mpz_t(), 2); //length of C in octets
  cout << "Clen before: " << Clen << endl;
  if(Clen % 8){ //convert bit to octets
    Clen = (Clen / 8) + 1;
  }else{
    Clen /= 8;
  }
  //1.b
  if(Clen != k){
    cout << "k: " << k << " " << "Clen: " << Clen << endl;
    return "C has insufficient size";
  }

  //1.c k needs to be k >= 2*hLen + 2
  if(k  < (2 * hLen + 2) ){
    return "decryption error.\nN is too small";
  }
  
  //2 RSA decryption
  //2.a
  //already done
  
  //2.b
  mpz_class m;
  mpz_powm(m.get_mpz_t(), C.get_mpz_t(), d.get_mpz_t(), N.get_mpz_t());

  //2.c
  uint8_t *EM = I2OSP(m, k);

  //3 EME-OAEP decoding
  //3.a
  uint8_t lHash[hLen];
  hash.CalculateDigest(lHash, reinterpret_cast<uint8_t*>(const_cast<char*>(L.data())), L.size());

  //3.b
  uint8_t Y;
  uint8_t maskedSeed[hLen];
  size_t tmpSize = k - hLen - 1;
  uint8_t maskedDB [tmpSize];
  Y = EM[0];
  std::copy(EM + 1, EM + hLen + 1, maskedSeed);
  std::copy(EM + 1 + hLen, EM + 1 + hLen + tmpSize, maskedDB);
  
  if(Y != 0x00){
    return "decryption error.\nY wasn't as expected";
  }

  //3.c
  uint8_t seedMask[hLen];
  mgf(hash, seedMask, hLen, maskedDB, tmpSize);

  //3.d
  uint8_t seed[hLen];
  for(size_t i = 0; i < hLen; i++){
    seed[i] = maskedSeed[i] ^ seedMask[i];
  }

  //3.e
  uint8_t dbMask[tmpSize];
  mgf(hash, dbMask, tmpSize, seed, hLen);

  //3.f
  uint8_t DB[tmpSize];
  for(size_t i = 0; i < tmpSize; i++){
    DB[i] = maskedDB[i] ^ dbMask[i];
  }

  //3.g
  for(size_t i = 0; i < hLen; i++){
    if(lHash[i] != DB[i]){
      return "decryption error.\nlHash != lHash_i";
    }
  }

  size_t index = 0;
  while(DB[hLen + index] == 0x00){
    if( (hLen + index) == tmpSize - 1){
      return "decryption error.\n0x01 not found";
    }else if(DB[hLen + index + 1] == 0x01){
      index++;
      break;
    }
    index++;
  }

  uint8_t M[tmpSize - hLen - index - 1];
  std::copy(DB + hLen + index + 2, DB + tmpSize, M);

  string output;
  for(size_t i = 0; i < (tmpSize - hLen - index - 1); i++){
    output.push_back(M[i]);
  }

  return output;
}

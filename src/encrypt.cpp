#include "encrypt.h"

void Crypt::Encrypt(std::string &input) {
  /*
  int j = 0;
  for (char &i : input) {
	if (++j > key.size()) {
	  j = 0;
	}
	i = i ^ (key[j] & 0x012);
  }
   */
}
void Crypt::Decrypt(std::string &input) {
  int j = 0;
  for (char &i : input) {
	if (++j > key.size()) {
	  j = 0;
	}
	i = i ^ (key[j] & 0x012);
  }
}

int Crypt::GenerateInt(int min, int max) {
  static thread_local std::mt19937_64 mt(std::random_device{}());
  std::uniform_int_distribution<int> dist(min, max);

  return dist(mt);
}

void Crypt::GenerateKeys() {
  key = GenerateKey(32);
}

std::string Crypt::GenerateKey(UINT keyLen) {
  std::string genKey;

  for (int i = 0; i < keyLen; i++) {
	genKey += GenerateInt(33, 126);
  }
  return genKey;
}


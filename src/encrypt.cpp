#include "encrypt.h"

#include <iostream>

void Crypt::Encrypt(std::string &input) {
  for (UINT i = 0; i < input.size(); i++) {
	input[i] = (UINT)input[i] ^ (key[i] & hexKey[i] + (hexKey[4] & hexKey[2])) * 0x0BU;
  }
}
void Crypt::Decrypt(std::string &input) {
  for (UINT i = 0; i < input.size(); i++) {
	input[i] = (UINT)input[i] ^ (key[i] & hexKey[i] + (hexKey[4] & hexKey[2])) * 0x0BU;
  }
}

int Crypt::GenerateInt(int min, int max) {
  static thread_local std::mt19937_64 mt(std::random_device{}());
  std::uniform_int_distribution<int> dist(min, max);

  return dist(mt);
}

void Crypt::GenerateKeys() {
  key = GenerateKey(32);
  hexKey = GenerateHexKey(16);
}

std::string Crypt::GenerateKey(UINT keyLen) {
  std::string genKey;

  for (int i = 0; i < keyLen; i++) {
	genKey += GenerateInt(33, 126);
  }
  return genKey;
}

std::vector<ULONG> Crypt::GenerateHexKey(ULONG keyLen) {
  std::vector<ULONG> genKey;

  for (int i = 0; i < keyLen; i++) {
	ULONG val = GenerateInt(0x0FFC, 0xFFFF);
	genKey.push_back(val);
  }
  return genKey;
}

#include "encrypt.h"

#include <iostream>

void crypto::Encrypt(std::string &input) {
  for (UINT i = 0; i < input.size(); i++) {
	input[i] = (UINT)input[i] ^ (key[i] & hex_key[i] + (hex_key[4] & hex_key[2])) * 0x0BU;
  }
}
void crypto::Decrypt(std::string &input) {
  for (UINT i = 0; i < input.size(); i++) {
	input[i] = (UINT)input[i] ^ (key[i] & hex_key[i] + (hex_key[4] & hex_key[2])) * 0x0BU;
  }
}

int crypto::GenerateInt(int min, int max) {
  static thread_local std::mt19937_64 mt(std::random_device{}());
  std::uniform_int_distribution<int> dist(min, max);

  return dist(mt);
}

void crypto::GenerateKeys() {
  key = GenerateKey(32);
  hex_key = GenerateHexKey(16);
}

std::string crypto::GenerateKey(UINT key_len) {
  std::string gen_key;

  for (int i = 0; i < key_len; i++) {
	gen_key += GenerateInt(33, 126);
  }
  return gen_key;
}

std::vector<ULONG> crypto::GenerateHexKey(ULONG key_len) {
  std::vector<ULONG> gen_key;

  for (int i = 0; i < key_len; i++) {
	ULONG val = GenerateInt(0x0FFC, 0xFFFF);
	gen_key.push_back(val);
  }
  return gen_key;
}

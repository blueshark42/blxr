#include "encrypt.h"

void Crypt::Encrypt(std::string &input) {
  std::ostringstream ostream;
  ostream << key;
  Stream::WriteLog(ostream.str(), 0x0, false);

  // TODO Encryption algorithm like whaaaaaaa
  // ASCII -> Binary (Reverse) -> ASCII (Divide & Remainder) -> 1st (Divide result) -> 2nd BINARY(shift left by remainder)

  for (auto c : input) {

  }

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

std::string Crypt::StrToBinary(const std::string &input) {
  std::string binary;

  for (auto c : input) {
	for (int i = 0; i < sizeof(char) * 8; i++) {
	  binary += (c & (1 << i)) ? '1' : '0';
	}
	std::reverse(binary.begin(), binary.end());
  }
  return binary;
}

char *Crypt::BinaryToStr(const std::string &input) {
  std::string str[32];

  // TODO finish, returns wrong ascii, maybe remove str[32] and use normal string
  for (auto &i : str) {
	i = std::to_string(std::stoi(input, nullptr, 2));
  }
  return (char *)str;
}

#ifndef BLXR_SRC_ENCRYPT_H_
#define BLXR_SRC_ENCRYPT_H_

#include <string>
#include <random>
#include <vector>

typedef unsigned int UINT;
typedef unsigned long ULONG;

namespace crypto {
static std::string key;
static std::vector<ULONG> hex_key;

int GenerateInt(int min, int max);
void GenerateKeys();
std::string GenerateKey(UINT key_len);
std::vector<ULONG> GenerateHexKey(ULONG key_len);
void Encrypt(std::string &input);
void Decrypt(std::string &input);
}

#endif //BLXR_SRC_ENCRYPT_H_

#ifndef BLXR_SRC_ENCRYPT_H_
#define BLXR_SRC_ENCRYPT_H_

#include <string>
#include <random>
#include <vector>

#include "stream.h"

typedef unsigned int UINT;
typedef unsigned long ULONG;

namespace Crypt {
static std::string key;

int GenerateInt(int min, int max);
void GenerateKeys();
std::string GenerateKey(UINT keyLen);
void Encrypt(std::string &input);
void Decrypt(std::string &input);
}

#endif //BLXR_SRC_ENCRYPT_H_

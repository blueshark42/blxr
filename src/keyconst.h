#ifndef BLXR__KEYCONST_H_
#define BLXR__KEYCONST_H_

#include <string>
#include <map>
#include <Windows.h>

class KeyData {
 public:
  KeyData(std::string keyCode = "", std::string name = "") :
	  VirKey(std::move(keyCode)), Name(std::move(name)) {}
  std::string Name;
  std::string VirKey;
};

namespace KeyConst {
std::string AddKey(DWORD idx, bool caps, bool shift);
}

#endif //BLXR__KEYCONST_H_

//
// Created by Rolo on 2. 6. 2020.
//

#ifndef BLXR__KEYCONST_H_
#define BLXR__KEYCONST_H_

#include <string>
#include <map>
#include <Windows.h>


class KeyData {
 public:
  KeyData(std::string key_code = "", std::string name = "") :
  	vir_key(std::move(key_code)), name(std::move(name)){}
  std::string vir_key;
  std::string name;
};

namespace key_const {
  std::string AddKey(DWORD idx, bool caps, bool shift);
}


#endif //BLXR__KEYCONST_H_

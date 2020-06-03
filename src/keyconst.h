//
// Created by Rolo on 2. 6. 2020.
//

#ifndef BLXR__KEYCONST_H_
#define BLXR__KEYCONST_H_

#include <string>
#include <map>


class KeyData {
 public:
  KeyData(std::string key_code = "", std::string name = "") : vir_key(std::move(key_code)), name(std::move(name)){}
  std::string vir_key;
  std::string name;
};

class KeyList {
 public:
  static std::map<int, KeyData> key_list;
};


#endif //BLXR__KEYCONST_H_

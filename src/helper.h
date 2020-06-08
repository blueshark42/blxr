#ifndef BLXR_SRC_HELPER_H_
#define BLXR_SRC_HELPER_H_

#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>

#include <windows.h>

namespace system_time {

struct SystemTime {
  SystemTime() {
	struct tm time{};
	time_t now = std::time(nullptr);
	localtime_s(&time, &now);

	year_ = time.tm_year + 1900;
	month_ = time.tm_mon + 1;
	day_ = time.tm_mday;
	hour_ = time.tm_hour;
	minute_ = time.tm_min;
	second_ = time.tm_sec;
  }
  int year_, month_, day_, hour_, minute_, second_;

  SystemTime(int year, int month, int day, int hour, int minute, int second) :
	  year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {}
  SystemTime(int year, int month, int day) : year_(year), month_(month), day_(day),
											 hour_(0), minute_(0), second_(0) {}

  static SystemTime Now();
  static std::string GetTime(const std::string &sep = ":");
  static std::string GetDate(const std::string &sep = "/");
  std::string GetFullDate(const std::string &sep = "-");
};

};

namespace convert {
template<typename T>
std::string ToString(T &t);
std::string HwndToString(HWND hwnd);
}

namespace system_data {
uint32_t GetProcessId();
bool ProcessChanged(uint32_t &original, uint32_t current, bool update_process = false);
}

#endif //BLXR_SRC_HELPER_H_

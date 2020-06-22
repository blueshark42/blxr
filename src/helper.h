#ifndef BLXR_SRC_HELPER_H_
#define BLXR_SRC_HELPER_H_

#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>

#include <windows.h>

namespace SysTime {

struct SystemTime {
  SystemTime() {
	struct tm time{};
	time_t now = std::time(nullptr);
	localtime_s(&time, &now);

	Year = time.tm_year + 1900;
	Month = time.tm_mon + 1;
	Day = time.tm_mday;
	Hour = time.tm_hour;
	Minute = time.tm_min;
	Second = time.tm_sec;
  }
  int Year, Month, Day, Hour, Minute, Second;

  SystemTime(int year, int month, int day, int hour, int minute, int second) :
	  Year(year), Month(month), Day(day), Hour(hour), Minute(minute), Second(second) {}
  SystemTime(int year, int month, int day) : Year(year), Month(month), Day(day),
											 Hour(0), Minute(0), Second(0) {}

  static SystemTime Now();
  static std::string GetTime(const std::string &sep = ":");
  static std::string GetDate(const std::string &sep = "/");
  static std::string GetFullDate(const std::string &sep = "-");
};

};

namespace Convert {
template<typename T>
std::string ToString(T &t);
std::string HwndToString(HWND hwnd);
std::string GetFinalFile(const std::string &input, char character);
}

namespace SystemData {
uint32_t GetProcessId();
bool ProcessChanged(uint32_t &original, uint32_t current, bool updateProcess = false);
}

#endif //BLXR_SRC_HELPER_H_

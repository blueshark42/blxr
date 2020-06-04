//
// Created by Rolo on 4. 6. 2020.
//

#include "helper.h"
// 04/06/2020-13:22:21h
template<typename T>
std::string convert::ToString(T &t) {
  std::ostringstream s;
  s << t;
  return s.str();
}

systime::SystemTime systime::SystemTime::Now() {
  return {};
}

std::string systime::SystemTime::GetTime(const std::string &sep) {
  SystemTime sys = SystemTime().Now();
  return std::string(sys.hour_ < 10 ? "0" : "") + convert::ToString(sys.hour_) + sep +
	  std::string(sys.minute_ < 10 ? "0" : "") + convert::ToString(sys.minute_) + sep +
	  std::string(sys.second_ < 10 ? "0" : "") + convert::ToString(sys.second_);
}

std::string systime::SystemTime::GetDate(const std::string &sep) {
  SystemTime sys = SystemTime().Now();
  return std::string(sys.day_ < 10 ? "0" : "") + convert::ToString(sys.day_) + sep +
	  std::string(sys.month_ < 10 ? "0" : "") + convert::ToString(sys.month_) + sep +
	  convert::ToString(sys.year_);
}

std::string systime::SystemTime::GetFullDate(const std::string &sep) {
  return systime::SystemTime::GetDate() + sep + systime::SystemTime::GetTime();
}


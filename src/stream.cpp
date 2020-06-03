//
// Created by Rolo on 2. 6. 2020.
//
#include "stream.h"
#include <iostream>

#define APPDATA "APPDATA"

stream::LogFile* log_file = new stream::LogFile();

std::string stream::GetPath() {
  char* buf = nullptr;
  size_t size = 0;
  std::string app_data_dir;

  if (_dupenv_s(&buf, &size, APPDATA) == 0 && buf != nullptr) {
    app_data_dir = buf;
  }
  app_data_dir += "\\Microsoft\\blxr";

  free(buf);
  return app_data_dir;
}

bool stream::MakeDir(const std::string &path) {
  return CreateDirectory(path.c_str(), nullptr) || GetLastError() == ERROR_ALREADY_EXISTS;
}
template<class T>
bool stream::WriteLog(T &t) {

}

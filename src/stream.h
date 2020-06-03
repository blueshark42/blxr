//
// Created by Rolo on 2. 6. 2020.
//

#ifndef BLXR__STREAM_H_
#define BLXR__STREAM_H_

#include <fstream>
#include <sstream>
#include <rpc.h>


namespace stream {
	std::string GetPath();
	bool MakeDir(const std::string& path);

	template <class T>
	bool WriteLog(T& t);

	class LogFile {
 	 public:
  		std::fstream fstream_;
  		std::string name_;
  		std::string path_;

  		void SetupFile(const std::string& name) {
			path_ = GetPath();
			name_ = name;
			fstream_.open(path_ + name_);
  		}

  		bool FileExists() {
  		  struct stat buffer {};
  		  return (stat(name_.c_str(), &buffer) == 0);
  		}


	 };
}

#endif //BLXR__STREAM_H_

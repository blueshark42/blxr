#ifndef BLXR__STREAM_H_
#define BLXR__STREAM_H_

#include <fstream>
#include <sstream>
#include <rpc.h>


namespace stream {
	std::string GetPath(bool append = false);
	bool MakeDir(const std::string& path);
	bool WriteLog(const std::string& input);

	class LogFile {
	 public:
	  std::ofstream ofstream_;
	  std::string name_;
	  std::string path_;

	  LogFile(const std::string& path, const std::string& name)
	  		: ofstream_(path + name)
	  		, name_(name)
	  		, path_(path) {}
	};

}

#endif //BLXR__STREAM_H_

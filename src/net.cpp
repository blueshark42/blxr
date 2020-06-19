#include "net.h"

bool Network::UploadFileFtp(const std::string &path, const std::string &name) {
  HINTERNET internet;
  HINTERNET session;
  internet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
  if (internet == NULL) {
	return false;
  }
  session = InternetConnect(internet, "server", INTERNET_DEFAULT_FTP_PORT, "user", "pass", INTERNET_SERVICE_FTP, 0, 0);
  if (session == nullptr) {
	return false;
  }

  if (name.empty() || name.length() < 1) {
	return FtpPutFile(session, path.c_str(), name.c_str(), FTP_TRANSFER_TYPE_BINARY, 0);
  }

}

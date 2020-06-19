#ifndef BLXR_SRC_NET_H_
#define BLXR_SRC_NET_H_

#include <iostream>
#include <cstring>

#include <Windows.h>
#include <WinInet.h>

#pragma comment(lib, "Wininet")

namespace Network {
bool UploadFileFtp(const std::string &path, const std::string &name = "");    // empty name = all files
}

#endif //BLXR_SRC_NET_H_

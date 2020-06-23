#ifndef BLXR_SRC_SCREEN_H_
#define BLXR_SRC_SCREEN_H_

#include <string>
#include <sstream>

#include <Windows.h>
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

namespace Screen {
static int picId = 0;
int GetEncoderClsId(const WCHAR *format, CLSID *clsId);
void CaptureScreen(const std::string &path,
				   const std::string &name,
				   bool loopForever = false,
				   float delay = 0.0f,
				   int loopAmount = 0);
}

#endif //BLXR_SRC_SCREEN_H_

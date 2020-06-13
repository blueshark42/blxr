#ifndef BLXR_SRC_SCREEN_H_
#define BLXR_SRC_SCREEN_H_

#include <string>

#include <Windows.h>
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

namespace Screen {
static int picId = 0;
int GetEncoderClsId(const WCHAR *format, CLSID *clsId);
void CaptureScreen(const std::string &path, const std::string &name);
}

#endif //BLXR_SRC_SCREEN_H_

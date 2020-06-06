#ifndef BLXR_SRC_SCREEN_H_
#define BLXR_SRC_SCREEN_H_

#include <string>

#include <Windows.h>
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

namespace screen {
int GetEncoderClsId(const WCHAR *format, CLSID *cls_id);
void CaptureScreen(const std::string &path, const std::string &name);
}

#endif //BLXR_SRC_SCREEN_H_

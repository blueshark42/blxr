#ifndef BLXR_SRC_SCREEN_H_
#define BLXR_SRC_SCREEN_H_

#include <string>

#include <Windows.h>
#include <gdiplus.h>

namespace screen {
int GetEncoderClsId(const WCHAR *format, CLSID *cls_id);
bool CaptureScreen();
}

#endif //BLXR_SRC_SCREEN_H_

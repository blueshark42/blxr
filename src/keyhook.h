#ifndef BLXR__KEYHOOK_H_
#define BLXR__KEYHOOK_H_

#include <iostream>

#include <Windows.h>

#include "keyconst.h"
#include "stream.h"

namespace KeyHook {
LRESULT RunHook(int nCode, WPARAM wParam, LPARAM lParam);
bool InstallHook();
bool UninstallHook();
void HandleMessage(bool logMsg);
bool KillProcess();

static uint32_t activeProcess = 0x0;
}

#endif //BLXR__KEYHOOK_H_

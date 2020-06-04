#ifndef BLXR__KEYHOOK_H_
#define BLXR__KEYHOOK_H_

#include <iostream>

#include <Windows.h>

#include "keyconst.h"

namespace key_hook {
LRESULT RunHook(int n_code, WPARAM wparam, LPARAM lparam);
bool InstallHook();
bool UninstallHook();
void HandleMessage(bool log_msg);
bool KillProcess();

static uint32_t active_process = 0x0;
}

#endif //BLXR__KEYHOOK_H_

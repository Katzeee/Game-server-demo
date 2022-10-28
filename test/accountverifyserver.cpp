#include "../src/app_PCH.h"
#include "../src/ecslibserver.h"
using namespace xac;

int main() {
  auto *tm = ThreadManager::GetInstance();
  tm->CreateComponent<NetworkListener>("127.0.0.1", 2233);
  //tm->CreateComponent<Console>();
  tm->CreateComponent<Account>();
  tm->StartAllThread();
  while (tm->IsLoop()) {
    sleep(1);
  }
  return 0;
}
#include "../src/ecslibserver.h"
using namespace xac;

int main() {
  auto *tm = ThreadManager::GetInstance();
  tm->CreateComponent<NetworkListener>("127.0.0.1", 2233);
  tm->CreateComponent<Console>();

  return 0;
}
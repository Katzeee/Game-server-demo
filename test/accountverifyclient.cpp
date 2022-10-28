#include <sstream>
#include "../src/app_PCH.h"
#include "../src/ecslibserver.h"
#include "../src/robot/Robot.h"

using namespace xac;

int main() {
  auto *tm = ThreadManager::GetInstance();
  tm->CreateComponent<xac::Robot>(); 
  tm->StartAllThread();
  while (tm->IsLoop())
    ;
}
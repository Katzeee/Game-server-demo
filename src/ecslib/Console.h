#pragma once
#include "ConsoleBase.h"
#include "ThreadManager.h"

namespace xac {
class Console : public ConsoleBase, public IPoolObject<Console> {
 public:
  void Reset() override{}
  Console() {
    handle_funcs_["quit"] = [&](const SplitCommandType &command) {
      std::cout << "quit" << std::endl;
      ThreadManager::GetInstance()->StopAllThread();
    };
  }
};
}  // end namespace xac
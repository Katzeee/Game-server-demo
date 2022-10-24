#pragma once
#include "ConsoleBase.h"
#include "ThreadManager.h"

namespace xac {
class Console : public ConsoleBase {
 public:
  Console() {
    handle_funcs_["quit"] = [&](const SplitCommandType &command) {

    };
  }
};
}  // end namespace xac
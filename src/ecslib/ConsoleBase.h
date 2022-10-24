#pragma once
#include <unistd.h>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include "../common.h"
#include "IComponent.h"
#include "Singleton.h"

namespace xac {
class ConsoleBase : public Singleton<ConsoleBase>, public IUpdateComponent {
 public:
  using SplitCommandType = std::vector<std::string_view>;
  using HandleFuncType = std::function<void(SplitCommandType)>;
  ConsoleBase();
  void Update() override;

 protected:
  void HandleInput(const SplitCommandType &command);
  static void HandleErrorCommands();
  std::map<std::string_view, HandleFuncType> handle_funcs_;
  std::string command_buffer_;
  std::string ps = "server > ";
};
}  // end namespace xac

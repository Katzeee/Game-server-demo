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
#include "ThreadManager.h"

namespace xac {
class Console : public Singleton<Console>, public IUpdateComponent {
 public:
  using SplitCommandType = std::vector<std::string_view>;
  using HandleFuncType = std::function<void(SplitCommandType)>;
  Console();
  void Update() override;

 private:
  void HandleInput(const SplitCommandType &command);
  void HandleErrorCommands();
  void HandleQuitCommand(const SplitCommandType &command);
  void HandlePrintCommand(const SplitCommandType &command);
  std::map<std::string_view, HandleFuncType> handle_funcs_;
  bool is_running = true;
  std::string command_buffer_;
};
}  // end namespace xac

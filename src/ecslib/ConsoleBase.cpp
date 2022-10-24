#include "ConsoleBase.h"

namespace xac {

ConsoleBase::ConsoleBase() { std::cout << ps; }

void ConsoleBase::Update() {
  if (std::getline(std::cin, command_buffer_)) {
    auto split_command = split(command_buffer_);
    HandleInput(split_command);
    std::cout << ps;
  }
}

void ConsoleBase::HandleErrorCommands() { std::cout << "Wrong Command!" << std::endl; }

void ConsoleBase::HandleInput(const SplitCommandType &command) {
  if (command.empty()) {
    return;
  }
  auto it = handle_funcs_.find(command[0]);
  if (it == handle_funcs_.end()) {
    ConsoleBase::HandleErrorCommands();
  } else {
    it->second(command);
  }
}
}  // end namespace xac
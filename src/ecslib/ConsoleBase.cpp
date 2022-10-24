#include "ConsoleBase.h"

namespace xac {

Console::Console() {
  handle_funcs_["quit"] = [&](const SplitCommandType &command) { HandleQuitCommand(command); };
}

void Console::Update() {
  std::vector<std::string_view> split_command;
  std::cout << "(input)";
  while (is_running) {
    if (std::getline(std::cin, command_buffer_)) {
      split_command = split(command_buffer_);
      HandleInput(split_command);
      std::cout << "(input)";
    } else {
      continue;
    }
  }
}

void Console::HandleErrorCommands() { std::cout << "Wrong Command!" << std::endl; }

void Console::HandleQuitCommand(const SplitCommandType &command) { is_running = false; }

void Console::HandleInput(const SplitCommandType &command) {
  if (command.empty()) {
    return;
  }
  auto it = handle_funcs_.find(command[0]);
  if (it == handle_funcs_.end()) {
    HandleErrorCommands();
  } else {
    it->second(command);
  }
}
}  // end namespace xac
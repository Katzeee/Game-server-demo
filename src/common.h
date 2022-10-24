#pragma once
#include <string>
#include <vector>

namespace xac {

static auto split(std::string_view strv, std::string_view delims = " ") -> std::vector<std::string_view> {
  std::vector<std::string_view> output;
  size_t start = 0;
  while (start < strv.size()) {
    const auto next = strv.find_first_of(delims, start);
    if (start != next) {
      output.emplace_back(strv.substr(start, next - start));
    }
    if (next == std::string_view::npos) {
      break;
    }
    start = next + 1;
  }
  return output;
}

}  // end namespace xac

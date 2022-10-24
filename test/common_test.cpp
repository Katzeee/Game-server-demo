#include "../src/common.h"
#include "iostream"

using namespace xac;

int main() {
  std::string test;
  while (true) {
    std::getline(std::cin, test);
    auto res = split(test);
    for (auto it : res) {
      std::cout << it << "//";
    }
    std::cout << std::endl;
  }

  return 0;
}
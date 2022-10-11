#include "../src/ecslibserver.h"

using namespace xac;

class A : public IPoolObject<A, int> {
public:
  void Reset(int i) override { std::cout << i << std::endl; }
  void BackToPool() override {}
};

int main() {
    auto es = std::make_shared<EntitySystem>();
    es->AddComponent<A, int>(1);
}
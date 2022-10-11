#include "../src/ecslibserver.h"

using namespace xac;

class A : public IPoolObject<A, int> {
public:
  void Reset(int i) override { std::cout << i << std::endl; }
  void BackToPool() override {}
};

int main() {
  //ObjectPool<A>::Instance();
  for (auto i = 0; i < 1000; i++) {
    auto obj = ObjectPool<A>::GetInstance()->InstantiateOne(i);
    ObjectPool<A>::GetInstance()->FreeOne(obj);
  }
  ObjectPool<A>::DestroyInstance();
  return 0;
}
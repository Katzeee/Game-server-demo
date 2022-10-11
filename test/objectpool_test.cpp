#include <thread>
#include "../src/ecslibserver.h"

using namespace xac;

class A : public IPoolObject<A, int> {
 public:
  void Reset(int i) override { std::cout << i << std::endl; }
  void BackToPool() override {}
};

int main() {
  // ObjectPool<A>::Instance();
  auto t1 = std::thread([]() {
    for (auto i = 0; i < 10000; i++) {
      auto obj = ObjectPool<A>::GetInstance()->InstantiateOne(i);
      ObjectPool<A>::GetInstance()->FreeOne(obj);
    }
  });
  auto t2 = std::thread([]() {
    for (auto i = 10000; i < 20000; i++) {
      auto obj = ObjectPool<A>::GetInstance()->InstantiateOne(i);
      ObjectPool<A>::GetInstance()->FreeOne(obj);
    }
  });
  t2.join();
  t1.join();
  ObjectPool<A>::DestroyInstance();
  return 0;
}
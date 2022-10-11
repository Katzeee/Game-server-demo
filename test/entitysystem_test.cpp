#include "../src/ecslibserver.h"

using namespace xac;

class A : public IPoolObject<A, int>, public ComponentBase, public IUpdateComponent {
 public:
  void Reset(int i) override { std::cout << i << std::endl; }
  void BackToPool() override {}
  void Update() override {
    if (!isupdate) {
        std::cout << "update" << std::endl;
        isupdate = true;
    }
  }
  private:
    bool isupdate = false;
};

int main() {
  auto es = std::make_shared<EntitySystem>();
  es->AddComponent<A, int>(1);
  es->Update();
}
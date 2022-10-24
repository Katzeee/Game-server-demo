#include <memory>
#include "../src/ecslibserver.h"

using namespace xac;

class A : public IPoolObject<A>,
          public ComponentBase,
          public IUpdateComponent,
          public IMessageComponent,
          public IResetable<int> {
 public:
  void Reset(int i) override { std::cout << i << std::endl; }
  void BackToPool() override { ObjectPool<A>::GetInstance()->FreeOne(this); }
  void Update() override {
    if (!isupdate) {
      std::cout << "update" << std::endl;
      isupdate = true;
    }
  }
  void RegistCBFuncs() override {
    auto message_list = std::make_unique<MessageList>();
    message_list->RegistCBFunc(Proto::MsgId::MI_TestMsg,
                               [](std::shared_ptr<Packet> packet) { std::cout << "test message" << std::endl; });
    message_list_ = std::unique_ptr<MessageListBase>(message_list.release());
  }

 private:
  bool isupdate = false;
};

int main() {
  auto es = std::make_shared<Thread>();
  es->AddComponent<A>(1);
  es->Start();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  es->Stop();
  return 0;
}
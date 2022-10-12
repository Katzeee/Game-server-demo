#include "../src/ecslibserver.h"

using namespace xac;

class A : public IPoolObject<A, int>, public ComponentBase, public IUpdateComponent, public IMessageComponent {
 public:
  void Reset(int i) override { std::cout << i << std::endl; }
  void Dispose() override {}
  void Update() override {
    if (!isupdate) {
      std::cout << "update" << std::endl;
      isupdate = true;
    }
  }
  void RegistCBFuncs() override {
    auto message_list = std::make_unique<MessageList>();
    message_list->RegistCBFunc(Proto::MsgId::MI_TestMsg, [](std::shared_ptr<Packet> packet) {
        std::cout << "test message" << std::endl;
    });
    message_list_ = std::unique_ptr<MessageListBase>(message_list.release());
  }

 private:
  bool isupdate = false;
};

int main() {
  ThreadManager::GetInstance()->CreateComponent<NetworkListener>("127.0.0.1", 2233);
  ThreadManager::GetInstance()->CreateComponent<A>(1);
  ThreadManager::GetInstance()->StartAllThread();
  while(ThreadManager::GetInstance()->IsLoop());
  return 0;
}
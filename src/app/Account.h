#pragma once
#include "../ecslibserver.h"

namespace xac {

class Account : public ComponentBase, public IMessageComponent, public IPoolObject<Account> {
 public:
  void Reset() override {}
  void RegistCBFuncs() {
    auto message_list = new MessageList();
    message_list->RegistCBFunc(Proto::C2L_AccountCheck, [&](std::shared_ptr<Packet> packet) {
      auto proto = packet->ParseToProto<Proto::AccountCheck>();
      if (this->accounts_.find(proto.account()) == this->accounts_.end()) {
        std::cout << "new account request, username: " << proto.account() << ", password: " << proto.password()
                  << std::endl;
        this->accounts_.emplace(proto.account());
      }
    });
    message_list_.reset(message_list);
  }

 private:
  std::set<std::string> accounts_;
};

}  // end namespace xac

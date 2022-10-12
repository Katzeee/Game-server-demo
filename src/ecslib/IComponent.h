#pragma once
#include "MessageList.h"

namespace xac {

class IUpdateComponent {
 public:
  virtual ~IUpdateComponent() = default;
  virtual void Update() = 0;
};
class IMessageComponent {
 public:
  virtual void RegistCBFuncs() = 0;
  void InformMessageList(std::shared_ptr<Packet> packet) {
    if (!message_list_) {
      std::cout << "No message list" << std::endl;
      return;
    }
    if (message_list_->IsConcernAbout(packet)) {
      message_list_->HandleMessage(packet);
    }
  }

 protected:
  std::unique_ptr<MessageListBase> message_list_;
};
}  // end namespace xac

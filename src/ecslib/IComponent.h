#pragma once
#include "MessageHandler.h"

namespace xac {

class IUpdateComponent {
 public:
  virtual ~IUpdateComponent() = default;
  virtual void Update() = 0;
};
class IMessageComponent {
 public:
  virtual void Init() = 0;
  virtual void RegistCBFuncs() = 0;

 protected:
  std::unique_ptr<MessageHandler> message_handler_;
};
}  // end namespace xac

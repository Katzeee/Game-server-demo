#pragma once

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include "Packet.h"
#include "protobuf/proto.h"
namespace xac {

class MessageListBase {
 public:
  using CallBackFunc = std::function<void(std::shared_ptr<Packet>)>;
  MessageListBase() = default;
  ~MessageListBase() = default;
  // virtual void RegistCBFunc(Proto::MsgId msg_id, CallBackFunc callback_func) = 0;
  virtual auto IsConcernAbout(std::shared_ptr<Packet> packet) -> bool = 0;
  virtual void HandleMessage(std::shared_ptr<Packet> packet) = 0;
};

}  // end namespace xac

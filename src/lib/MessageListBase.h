#pragma once

#include <functional>
#include <map>
#include <memory>
#include <list>
#include <mutex>
#include "IDisposable.h"
#include "Packet.h"
#include "protobuf/proto.h"
namespace xac {

class MessageListBase {
public:
    using CallBackFunc = std::function<void(std::shared_ptr<Packet>)>;
    MessageListBase() = default;
    ~MessageListBase() = default;
    // virtual void RegistCBFunc(Proto::MsgId msg_id, CallBackFunc callback_func) = 0;
    virtual bool IsConcernAbout(std::shared_ptr<Packet> packet) = 0;
    virtual void HandleMessages() = 0;
    void AddToMsgList(std::shared_ptr<Packet> packet); 
    bool HaveMessage(); 
protected:
    std::mutex lock_;
    std::list<std::shared_ptr<Packet>> message_list_{};
};

} // end namespace xac

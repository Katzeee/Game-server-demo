#pragma once

#include <functional>
#include <map>
#include <memory>
#include <list>
#include "IDisposable.h"
#include "Packet.h"
namespace xac {

class MessageListBase : public IDisposable {
public:
    using CallBackFunc = std::function<void(std::shared_ptr<Packet>)>;
    // virtual void Init() = 0;
    virtual void RegistCBFunc(int msg_id, CallBackFunc callback_func) = 0;
    virtual bool IsConcernAbout(int msg_id) = 0;
    void AddToMsgList(std::shared_ptr<Packet> packet) { message_list_.push_back(packet); }
protected:
    std::list<std::shared_ptr<Packet>> message_list_;
    std::map<int, CallBackFunc> callback_func_list_;
};

} // end namespace xac

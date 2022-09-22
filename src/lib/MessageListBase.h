#pragma once

#include <functional>
#include <map>
#include <memory>
#include <list>
#include <mutex>
#include "IDisposable.h"
#include "Packet.h"
namespace xac {

class MessageListBase : public IDisposable {
public:
    using CallBackFunc = std::function<void(std::shared_ptr<Packet>)>;
    // virtual void Init() = 0;
    MessageListBase() {
        message_list_.clear();
        callback_func_list_.clear();
    }
    virtual void RegistCBFunc(int msg_id, CallBackFunc callback_func) = 0;
    virtual bool IsConcernAbout(int msg_id) = 0;
    void AddToMsgList(std::shared_ptr<Packet> packet) { message_list_.push_back(packet); }
    bool HaveMessage() { return !message_list_.empty(); }
    void HandleMessages() {
        std::list<std::shared_ptr<Packet>> tmp_message_list;
        lock_.lock();
        std::swap(message_list_, tmp_message_list);
        lock_.unlock();
        for (auto it : tmp_message_list) {
            callback_func_list_.find(it->GetMsgId())->second(it);
        }
    }
protected:
    std::mutex lock_;
    std::list<std::shared_ptr<Packet>> message_list_{};
    std::map<int, CallBackFunc> callback_func_list_{};
};

} // end namespace xac

#pragma once

#include <functional>
#include "MessageListBase.h"

namespace xac {
class MessageList : public MessageListBase {
public:
    // void Init() override;
    void RegistCBFunc(Proto::MsgId msg_id, CallBackFunc callback_func);
    void HandleMessages() override;
    bool IsConcernAbout(std::shared_ptr<Packet> packet) override;
protected:
    std::map<int, CallBackFunc> callback_func_list_{};
};    

class MessageListWithFilter : public MessageListBase {
public:
    using FilterFunc = std::function<bool(std::shared_ptr<Packet>)>;
    void HandleMessages() override;
    bool IsConcernAbout(std::shared_ptr<Packet> packet) override;
    void RegistCBFunc(Proto::MsgId msg_id, CallBackFunc callback_func, FilterFunc filter_func);
protected:
    std::map<int, std::pair<FilterFunc ,CallBackFunc>> callback_func_list_{};
};
} // end namespace xac

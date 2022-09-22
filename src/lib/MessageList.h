#pragma once

#include <functional>
#include "MessageListBase.h"

namespace xac {
class MessageListHandleAll : public MessageListBase {
public:
    void Dispose() override;
    // void Init() override;
    void RegistCBFunc(Proto::MsgId msg_id, CallBackFunc callback_func) override;
    bool IsConcernAbout(std::shared_ptr<Packet> packet) override;
};    

class MessageListHandleFiltered : public MessageListHandleAll {
public:
    void Dispose() override;
    void RegistCBFunc(Proto::MsgId msg_id, CallBackFunc callback_func) override;
    bool IsConcernAbout(std::shared_ptr<Packet> packet) override;
    void SetFilterFunc(std::function<bool(std::shared_ptr<Packet>)> filter_function);
protected:
    std::function<bool(std::shared_ptr<Packet>)> filter_function_{ nullptr };
};
} // end namespace xac

#pragma once
#include <memory>
#include "MessageListBase.h"

namespace xac {

class MessageHandler {
public:
    MessageHandler() = default;
     virtual ~MessageHandler() = default;
    void InformMessageList(std::shared_ptr<Packet> packet);
protected:
    std::shared_ptr<MessageListBase> message_list_ { nullptr };

};

} // end namespace xac
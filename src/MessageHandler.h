#pragma once
#include <memory>
#include "IDisposable.h"
#include "MessageListBase.h"

namespace xac {

class MessageHandler : public IDisposable {
public:
    void Dispose() override {}
    void InformMessageList(std::shared_ptr<Packet> packet);
private:
    std::shared_ptr<MessageListBase> message_list_ { nullptr };

};

} // end namespace xac
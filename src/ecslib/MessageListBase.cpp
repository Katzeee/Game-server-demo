#include "MessageListBase.h"

namespace xac {


void MessageListBase::AddToMsgList(std::shared_ptr<Packet> packet) { 
    auto guard = std::lock_guard(lock_);
    message_list_.emplace_back(packet); 
}


bool MessageListBase::HaveMessage() {
    return !message_list_.empty(); 
}


} // end namespace xac

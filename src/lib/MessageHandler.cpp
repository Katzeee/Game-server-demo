#include "MessageHandler.h"
#include <iostream>

namespace xac {
    

void MessageHandler::InformMessageList(std::shared_ptr<Packet> packet) {
    if (!message_list_) {
        // std::cout << "No message list" << std::endl;
        return;
    }
    if (message_list_->IsConcernAbout(packet)) {
        message_list_->AddToMsgList(packet);
    }
}

} // end namespace xac

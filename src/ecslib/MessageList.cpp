#include <iostream>
#include "MessageList.h"

namespace xac {


void MessageList::RegistCBFunc(Proto::MsgId msg_id, CallBackFunc callback_func) {
    if (callback_func_list_.find(msg_id) != callback_func_list_.end()) {
        std::cout << "Func exist! Modify it use another function!" << std::endl;
        return;
    }
    callback_func_list_.insert(std::pair(msg_id, callback_func));
}


bool MessageList::IsConcernAbout(std::shared_ptr<Packet> packet) {
    if (callback_func_list_.find(packet->GetMsgId()) != callback_func_list_.end()) {
        return true;
    }
    return false;
}


void MessageList::HandleMessage(std::shared_ptr<Packet> packet) {
    auto it = callback_func_list_.find(packet->GetMsgId());
    if (it == callback_func_list_.end()) {
        return;
    }
    it->second(packet);
}


void MessageListWithFilter::RegistCBFunc(Proto::MsgId msg_id, CallBackFunc callback_func, FilterFunc filter_func = nullptr) {
    if (callback_func_list_.find(msg_id) != callback_func_list_.end()) {
        std::cout << "Func exist! Modify it use another function!" << std::endl;
        return;
    }
    callback_func_list_.insert(std::pair(msg_id, std::pair(filter_func, callback_func)));
}

bool MessageListWithFilter::IsConcernAbout(std::shared_ptr<Packet> packet) {
    auto call_back_pair = callback_func_list_.find(packet->GetMsgId());
    if (call_back_pair == callback_func_list_.end()) {
        return false;
    }
    if (call_back_pair->second.first == nullptr) {
        return true;
    }
    return call_back_pair->second.first(packet);
}

void MessageListWithFilter::HandleMessage(std::shared_ptr<Packet> packet) {
    auto it = callback_func_list_.find(packet->GetMsgId());
    if (it == callback_func_list_.end()) {
        return;
    }
    (it->second).second(packet);
}

} // end namespace xac

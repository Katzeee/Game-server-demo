#include <iostream>
#include "MessageList.h"

namespace xac {

void MessageListHandleAll::Dispose() {

}

void MessageListHandleAll::RegistCBFunc(Proto::MsgId msg_id, CallBackFunc callback_func) {
    if (callback_func_list_.find(msg_id) != callback_func_list_.end()) {
        std::cout << "Func exist! Modify it use another function!" << std::endl;
        return;
    }
    callback_func_list_.insert(std::pair(msg_id, callback_func));
}


bool MessageListHandleAll::IsConcernAbout(std::shared_ptr<Packet> packet) {
    if (callback_func_list_.find(packet->GetMsgId()) != callback_func_list_.end()) {
        return true;
    }
    return false;
}


void MessageListHandleFiltered::Dispose() {

}

void MessageListHandleFiltered::RegistCBFunc(Proto::MsgId msg_id, CallBackFunc callback_func) {
    if (callback_func_list_.find(msg_id) != callback_func_list_.end()) {
        std::cout << "Func exist! Modify it use another function!" << std::endl;
        return;
    }
    callback_func_list_.insert(std::pair(msg_id, callback_func));
}

bool MessageListHandleFiltered::IsConcernAbout(std::shared_ptr<Packet> packet) {
    if (!filter_function_) {
        return false;
    }
    if (filter_function_(packet)) {
        return MessageListHandleAll::IsConcernAbout(packet);
    }
    return false;
}

void MessageListHandleFiltered::SetFilterFunc(std::function<bool(std::shared_ptr<Packet>)> filter_function) {
    filter_function_ = filter_function;
}

} // end namespace xac

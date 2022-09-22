#include <iostream>
#include "MessageList.h"

namespace xac {

void MessageListHandleAll::Dispose() {

}

void MessageListHandleAll::RegistCBFunc(int msg_id, CallBackFunc callback_func) {
    if (callback_func_list_.find(msg_id) != callback_func_list_.end()) {
        std::cout << "Func exist! Modify it use another function!" << std::endl;
        return;
    }
    callback_func_list_.insert(std::pair(msg_id, callback_func));
}


bool MessageListHandleAll::IsConcernAbout(int msg_id) {
    if (callback_func_list_.find(msg_id) != callback_func_list_.end()) {
        return true;
    }
    return false;
}


} // end namespace xac

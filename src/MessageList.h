#pragma once

#include "MessageListBase.h"

namespace xac {
class MessageListHandleAll : public MessageListBase {
public:
    void Dispose() override;
    // void Init() override;
    void RegistCBFunc(int msg_id, CallBackFunc callback_func) override;
    bool IsConcernAbout(int msg_id) override;
};    

class MessageListHandleFiltered : public MessageListHandleAll {

};
} // end namespace xac

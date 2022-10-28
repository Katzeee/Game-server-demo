#pragma once
#include "../ecslibserver.h"

namespace xac {
    
class Account : public IMessageComponent {
public:
    void RegistCBFuncs() {
        auto message_list = new MessageList();
        message_list->RegistCBFunc(
    }

private:

};

} // end namespace xac

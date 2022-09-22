#include "Account.h"

namespace xac {

void Account::Init() {
    message_list_ = std::make_shared<MessageListHandleAll>();
    message_list_->RegistCBFunc(Proto::C2L_AccountCheck, [](std::shared_ptr<Packet> packet){
        auto proto = packet->ParseToProto<Proto::AccountCheckRs>();
        std::cout << proto.return_code() << std::endl;
    });
}

}
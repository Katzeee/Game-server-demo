#include <string>
#include <cstring>
#include "NetworkConnecter.h"

namespace xac {

bool NetworkConnecter::Connect(std::string ip_addr, uint16_t port) {
    master_socket_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (master_socket_fd_ <= 0) {
        std::cout << "socket error" << std::endl;
        return false;
    }
    sockaddr_in sockaddr_struct;
    memset(&sockaddr_struct, 0, sizeof(sockaddr_in));
    sockaddr_struct.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    sockaddr_struct.sin_family = AF_INET;
    sockaddr_struct.sin_port = htons(port);
    if (connect(master_socket_fd_, (sockaddr*)&sockaddr_struct, sizeof(sockaddr_struct)) < 0) {
        std::cout << "connect error" << std::endl;
        return false;
    }
    SetNonBlock(master_socket_fd_);
    ConnectObj* connect_obj = new ConnectObj(master_socket_fd_);
    connects_.insert(std::pair(master_socket_fd_, connect_obj));

    return true;
}

void NetworkConnecter::Update() {
    auto i = 5;
    auto packet = std::make_shared<Packet>(Proto::MsgId::SendData);
    Proto::TestMsg test_msg;
    while (i--) {
        test_msg.set_index(i);
        test_msg.set_msg("sssss");
        packet->SerializeToBuffer(test_msg);
        for (auto it : connects_) {
            it.second->SendPacket(packet);
            std::cout << "send msgid: " << packet->GetMsgId() << " msg_index: " << i << std::endl;
        }
        Select();
    }
}

} // end namespace xac

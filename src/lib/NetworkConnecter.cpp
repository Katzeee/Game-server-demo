#include <string>
#include <cstring>
#include "NetworkConnecter.h"

namespace xac {

bool NetworkConnecter::Connect() {
    return NetworkConnecter::Connect(ip_addr_, port_);
}

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
    ip_addr_ = ip_addr;
    port_ = port;
    return true;
}

void NetworkConnecter::Update() {

    if (master_socket_fd_ == -1) {
        if (!Connect()) {
            return;
        }

        std::cout << "Re connect" << std::endl;
    }

    Select();

    if (i > 1) {
        i--;
        auto packet = std::make_shared<Packet>(Proto::MsgId::MI_TestMsg, master_socket_fd_);
        Proto::TestMsg test_msg;
        test_msg.set_index(i);
        test_msg.set_msg("sssss");
        packet->SerializeToBuffer(test_msg);
        SendPacket(packet);
        std::cout << "send msgid: " << packet->GetMsgId() << " msg_index: " << i  << ", socket: " << master_socket_fd_ << std::endl;
    }
    NetworkBase::Update();
    
}

} // end namespace xac

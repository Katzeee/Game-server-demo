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

    auto packet = new Packet(3);
    std::string buffer("sssssssssssssssssssssssssssssss");
    packet->SetMessageData(const_cast<char*>(buffer.c_str()), buffer.length());
    
    std::cout << "send msgid: " << packet->GetMsgId() << " data: " << buffer << std::endl;
    connect_obj->SendPacket(packet);
    return true;
}

void NetworkConnecter::Update() {
    auto i = 2;
    while (i--) {
        Select();
        
    }
}

} // end namespace xac

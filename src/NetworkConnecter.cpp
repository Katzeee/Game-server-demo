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
    ConnectObj* connect_obj = new ConnectObj(master_socket_fd_);
    connects_.insert(std::pair(master_socket_fd_, connect_obj));

    Packet* packet = new Packet(2);
    std::string data("connect");
    packet->SetMessageData(const_cast<char*>(data.c_str()), data.length());
    connect_obj->SendPacket(packet);
    return true;
}

void NetworkConnecter::Update() {
    Select();
}

}
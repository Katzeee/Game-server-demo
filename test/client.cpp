#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <memory.h>
#include <string>
#include "../src/libserver.h"
using namespace xac;


int main() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in socket_addr;
    if (socket_fd < 0) {
        std::cout << "error" << std::endl;
        return -1;
    }

    bool is_reuse_addr = true;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&is_reuse_addr, sizeof(is_reuse_addr));

    memset(&socket_addr, 0, sizeof(sockaddr_in));
    socket_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_port = htons(2233);
    if (::connect(socket_fd, (sockaddr*)&socket_addr, sizeof(sockaddr)) < 0) {
        std::cout << "error: " << errno <<  std::endl;
        return -1;
    }

    // NetworkBase::SetSocketOpt(socket_fd);

    Proto::TestMsg proto;
    proto.set_index(1);
    proto.set_msg("hello");
    auto packet = new Packet(Proto::MI_TestMsg, socket_fd);

    packet->SerializeToBuffer(proto);

    PacketHead head;
    head.msg_id_ = packet->GetMsgId();
    head.data_size_ = packet->GetSize();

    ::send(socket_fd, reinterpret_cast<char*>(&head), sizeof(head), 0);
    ::send(socket_fd, reinterpret_cast<char*>(packet->GetBufferStartAddr()), packet->GetSize(), 0);
    
    

    ::shutdown(socket_fd, SHUT_RDWR);

    return 0;
}
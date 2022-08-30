#include <memory.h>
#include "NetworkListener.h"

namespace xac {
bool NetworkListener::Listen(std::string ip_addr, uint16_t port) {
    master_socket_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (master_socket_fd_ < 0) {
        // TODO:LOG
        return false;
    }
    sockaddr_in sock_addr;
    memset(&sock_addr, 0, sizeof(sockaddr_in));
    sock_addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    if (::bind(master_socket_fd_, (sockaddr*)&sock_addr, sizeof(sockaddr)) < 0) {
        // TODO:LOG
        return false;
    }
    int back_log = 10;
    if (::listen(master_socket_fd_, back_log) < 0) {
        // TODO:LOG
        return false;
    }
    return true;
}
}
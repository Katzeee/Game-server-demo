#include <iostream>
#include <arpa/inet.h>
#include <memory.h>
#include <string>

int main() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in socket_addr;
    if (socket_fd < 0) {
        std::cout << "error" << std::endl;
        return -1;
    }
    memset(&socket_addr, 0, sizeof(sockaddr_in));
    socket_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_port = htons(2233);
    if (::connect(socket_fd, (sockaddr*)&socket_addr, sizeof(sockaddr)) < 0) {
        std::cout << "error" << std::endl;
        return -1;
    }
    std::string buf = "hello";
    ::send(socket_fd, buf.c_str(), buf.length(), 0);
    ::shutdown(socket_fd, SHUT_RDWR);
    return 0;
}
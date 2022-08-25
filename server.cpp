#include<iostream>
#include <arpa/inet.h>
#include <memory.h>

int main() {
    sockaddr_in sock_addr;
    int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&sock_addr, 0, sizeof(sockaddr_in));
    ::inet_pton(AF_INET, "127.0.0.1", &sock_addr.sin_addr.s_addr);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(2233);

    if (::bind(socket_fd, (sockaddr*)&sock_addr, sizeof(sock_addr)) < 0) {
        std::cout << "error" << std::endl;
        return -1;
    }

    if (::listen(socket_fd, 10) < 0) {
        std::cout << "error" << std::endl;
        return -1;
    }
    sockaddr client_sockaddr;
    socklen_t socket_length = sizeof(client_sockaddr);
    int client_socket = ::accept(socket_fd, &client_sockaddr, &socket_length);
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    auto size = ::recv(client_socket, buf, sizeof(buf), 0);
    if (size > 0) {
        std::cout << buf << std::endl;
    }
    return 0;
}
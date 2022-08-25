#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <map>

#include "../Disposal/IDisposable.h"

namespace xac {

class NetworkBase {
public:
    NetworkBase();
    ~NetworkBase();
    bool Select();
private:
    int master_socket_fd_{-1}; // listen fd or connect fd
    class ConnectObj : public IDisposable {
    public:
        bool HasSendData();
        bool Receive();
        bool Send();
    };
    std::map<int, ConnectObj*> connects_;
    fd_set read_fds_, write_fds_, except_fds_;
};

}
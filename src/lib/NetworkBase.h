#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <map>

#include "IDisposable.h"
#include "ConnectObj.h"

namespace xac {

class NetworkBase : public IDisposable {
public:
    NetworkBase() {}
    virtual ~NetworkBase();
    bool Select();
    void Dispose() override {}
    // virtual void Update() = 0;
protected:
    int master_socket_fd_{-1}; // listen fd or connect fd
    std::map<int, ConnectObj*> connects_;
    fd_set read_fds_, write_fds_, except_fds_;
    static void SetSocketOpt(int socket);
    static void SetNonBlock(int socket);
};

}
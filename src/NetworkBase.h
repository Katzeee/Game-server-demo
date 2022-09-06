#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <map>

#include "IDisposable.h"
#include "ConnectObj.h"

namespace xac {

class NetworkBase {
public:
    NetworkBase() {}
    ~NetworkBase();
    bool Select();
protected:
    int master_socket_fd_{-1}; // listen fd or connect fd
    
    std::map<int, ConnectObj*> connects_;
    fd_set read_fds_, write_fds_, except_fds_;
};

}
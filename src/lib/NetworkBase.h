#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <map>
#include <list>
#include <mutex>

#include "IDisposable.h"
#include "ConnectObj.h"
#include "ThreadObj.h"
#include "Packet.h"

namespace xac {

class NetworkBase : public ThreadObj {
public:
    NetworkBase() {}
    virtual ~NetworkBase();
    bool Select();
    void Update() override;
    virtual void Init() = 0;
    void SendPacket(std::shared_ptr<Packet> packet);
    // virtual void Update() = 0;
protected:
    int master_socket_fd_{-1}; // listen fd or connect fd
    std::map<int, ConnectObj*> connects_;
    std::list<std::shared_ptr<Packet>> send_msg_list_;
    fd_set read_fds_, write_fds_, except_fds_;
    std::mutex lock_;
    static void SetSocketOpt(int socket);
    static void SetNonBlock(int socket);
};

}
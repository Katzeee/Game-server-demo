#pragma once
#include "NetworkListener.h"
#include "NetworkBase.h"

namespace xac {

class Server : public NetworkListener {
public:
    Server();
    ~Server() {}
    void Update() override;
    void DataHandler();
    int GetSocket() { return master_socket_fd_; }
private:
    bool is_running_;
};


} // end namespace xac
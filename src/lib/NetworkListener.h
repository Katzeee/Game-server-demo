#pragma once

#include "NetworkBase.h"
#include "ThreadObj.h"
#include <arpa/inet.h>

namespace xac {
class NetworkListener : public NetworkBase , public ThreadObj {
public:
    void Init() override {}
    void Update() override;
    bool Listen(std::string ip_addr, uint16_t port);
protected:
    int Accept();
};
}
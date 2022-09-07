#pragma once

#include "NetworkBase.h"
#include <arpa/inet.h>

namespace xac {
class NetworkListener : public NetworkBase {
public:
    void Update() override;
    bool Listen(std::string ip_addr, uint16_t port);
protected:
    int Accept();
};
}
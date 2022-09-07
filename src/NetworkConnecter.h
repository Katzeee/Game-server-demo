#pragma once
#include "NetworkBase.h"

namespace xac {

class NetworkConnecter : public NetworkBase {
public:
    bool Connect(std::string ip_addr, uint16_t port);
    void Update() override;
};
} // end namespace xac
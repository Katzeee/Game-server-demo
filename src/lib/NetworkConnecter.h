#pragma once
#include "NetworkBase.h"
#include "protobuf/msg.pb.h"
#include "protobuf/proto_msg_id.pb.h"

namespace xac {

class NetworkConnecter : public NetworkBase {
public:
    NetworkConnecter() = default;
    NetworkConnecter(std::string ip_addr, uint16_t port) : ip_addr_(ip_addr), port_(port) {}
    void Init() override {}
    void Reconnect();
    bool Connect(std::string ip_addr, uint16_t port);
    bool Connect();
    void Update();
private:
    std::string ip_addr_;
    uint16_t port_;
    int i = 2;
};
} // end namespace xac
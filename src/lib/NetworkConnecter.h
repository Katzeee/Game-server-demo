#pragma once
#include "NetworkBase.h"
#include "protobuf/msg.pb.h"
#include "protobuf/proto_msg_id.pb.h"

namespace xac {

class NetworkConnecter : public NetworkBase {
public:
    NetworkConnecter() : is_running_(true) {}
    bool Connect(std::string ip_addr, uint16_t port);
    void Update();
private:
    bool is_running_;
};
} // end namespace xac
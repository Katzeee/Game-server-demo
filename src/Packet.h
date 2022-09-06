#pragma once
#pragma pack(push)
#pragma pack(4)
#include <iostream>
#include "Buffer.h"

namespace xac {
struct PacketHead {
    // exclude head size
    uint16_t data_size_;
    uint16_t msg_id_;
};

#pragma pack(pop)

class Packet : public NormalBuffer {
public:
    Packet() = delete;
    Packet(uint16_t msg_id) : msg_id_(msg_id) {}
    uint16_t GetMsgId() { return msg_id_; }
    ~Packet() {}
protected:
    uint16_t msg_id_;
};

}
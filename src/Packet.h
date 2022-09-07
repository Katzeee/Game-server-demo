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
    Packet() : msg_id_(0) {}
    Packet(uint16_t msg_id) : msg_id_(msg_id) { std:: cout << "new packet" << std::endl; }
    uint16_t GetMsgId() { return msg_id_; }
    void SetMessageData(char* src, size_t size);
    ~Packet() { std::cout << "free packet" << std::endl; }
protected:
    uint16_t msg_id_;
};

}
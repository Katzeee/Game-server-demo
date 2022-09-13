#pragma once
#include <iostream>
#include "Buffer.h"

namespace xac {

#pragma pack(push)
#pragma pack(4)
struct PacketHead {
    // exclude head size
    uint16_t data_size_;
    uint16_t msg_id_;
};

#pragma pack(pop)

class Packet : public NormalBuffer {
public:
    Packet() = delete;
    Packet(uint16_t msg_id) : msg_id_(msg_id) { 
        //std:: cout << "new packet" << std::endl; 
    }
    uint16_t GetMsgId() { return msg_id_; }
    void SetMessageData(char* src, size_t size);
    void SetMessageData(std::string src);
    ~Packet() { 
        std::cout << "free packet " << buffer_ << std::endl; 
    }

    template<typename ProtoClass>
    ProtoClass ParseToProto() {
        ProtoClass proto;
        proto.ParsePartialFromArray(GetBufferAddr(), GetSize());
        return proto;
    }
    template<typename ProtoClass>
    void SerializeToBuffer(ProtoClass& proto_class) {
        auto total_size = proto_class.ByteSizeLong();
        ReAlloc(total_size);
        proto_class.SerializePartialToArray(GetBufferAddr(), total_size);
        FillData(total_size);
    }
protected:
    uint16_t msg_id_;
};

}
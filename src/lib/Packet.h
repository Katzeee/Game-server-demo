#pragma once
#include <iostream>
#include "BufferBase.h"
#include "../protobuf/proto.h"

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
    Packet(Proto::MsgId msg_id, int socket_fd) : msg_id_(msg_id), socket_fd_(socket_fd) { 
        //std:: cout << "new packet" << std::endl; 
    }
    uint16_t GetMsgId() { return msg_id_; }
    int GetSocket() { return socket_fd_; }
    void SetMessageData(char* src, size_t size);
    void SetMessageData(std::string src);
    ~Packet() { 
        // std::cout << "free packet " << buffer_ << std::endl; 
    }

    template<typename ProtoClass>
    ProtoClass ParseToProto() {
        ProtoClass proto;
        proto.ParsePartialFromArray(GetBufferStartAddr(), GetSize());
        return proto;
    }
    template<typename ProtoClass>
    void SerializeToBuffer(ProtoClass& proto_class) {
        auto total_size = proto_class.ByteSizeLong();
        ReAlloc(total_size);
        proto_class.SerializePartialToArray(GetBufferEndAddr(), total_size);
        FillData(total_size);
    }
protected:
    Proto::MsgId msg_id_;
    int socket_fd_;
};

}
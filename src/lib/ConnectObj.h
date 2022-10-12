#pragma once
#include <iostream>
#include <memory>
#include "BufferBase.h"
#include "Packet.h"

namespace xac {

class RecvBuffer;
class SendBuffer : public RingBuffer {
public:
    void AddPacket(std::shared_ptr<Packet> packet);
};

class RecvBuffer : public RingBuffer {
public:
    std::shared_ptr<Packet> GetPacket(int socket_fd);
};


class ConnectObj {

public:
	ConnectObj(int socket_fd);
    virtual ~ConnectObj();
	bool Send();
    bool HasSendData();
    bool HasRecvData();
    bool Receive();
    void SendPacket(std::shared_ptr<Packet> packet);
    int GetSocket() const;
    std::shared_ptr<Packet> GetPacket();

protected:
    const int socket_fd_;
    RecvBuffer* read_buffer_{ nullptr };
    SendBuffer* write_buffer_{ nullptr };
};

}

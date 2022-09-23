#pragma once
#include <iostream>
#include <memory>
#include "IDisposable.h"
#include "BufferBase.h"
#include "Packet.h"

namespace xac {

class ReadBuffer;
class WriteBuffer : public RingBuffer {
public:
    void AddPacket(std::shared_ptr<Packet> packet);
};

class ReadBuffer : public RingBuffer {
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
    ReadBuffer* read_buffer_{ nullptr };
    WriteBuffer* write_buffer_{ nullptr };
};

}

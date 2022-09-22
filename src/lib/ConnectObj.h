#pragma once
#include <iostream>
#include <memory>
#include "IDisposable.h"
#include "Buffer.h"
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


class ConnectObj : public IDisposable {

public:
	ConnectObj(int socket_fd);
    ~ConnectObj() override;
	bool Send();
    bool HasSendData();
    bool HasRecvData();
    bool Receive();
    void Dispose() override;
    void SendPacket(std::shared_ptr<Packet> packet);
    int GetSocket() const;
    std::shared_ptr<Packet> GetPacket();

protected:
    const int socket_fd_;
    ReadBuffer* read_buffer_{ nullptr };
    WriteBuffer* write_buffer_{ nullptr };
};

}

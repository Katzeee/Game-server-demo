#pragma once
#include <iostream>
#include "IDisposable.h"
#include "Buffer.h"
#include "Packet.h"

namespace xac {

class ReadBuffer;
class WriteBuffer : public RingBuffer {
public:
    void AddPacket(Packet* packet);
};

class ReadBuffer : public RingBuffer {
public:
    Packet* GetPacket();
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
    void SendPacket(Packet* packet);
    Packet* GetPacket();

protected:
    const int socket_fd_;
    ReadBuffer* read_buffer_{ nullptr };
    WriteBuffer* write_buffer_{ nullptr };
};

}

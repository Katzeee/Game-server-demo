#pragma once
#include <iostream>
#include "IDisposable.h"
#include "Buffer.h"

namespace xac {

class WriteBuffer : public RingBuffer {
public:
    void AddPacket(char* src) {

    }
};

class ReadBuffer : public NormalBuffer {

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

protected:
    const int socket_fd_;
    ReadBuffer* read_buffer_{ nullptr };
    WriteBuffer* write_buffer_{ nullptr };
};

}

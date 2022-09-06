#pragma once
#include <iostream>
#include "IDisposable.h"
#include "Buffer.h"

namespace xac {

class WriteBuffer : public RingBuffer {

};

class ReadBuffer : public NormalBuffer {

};

class ConnectObj : public IDisposable {

public:
	ConnectObj();
	bool Send();
    bool HasSendData();
    bool HasRecvData();
    bool Receive();

protected:
    ReadBuffer* read_buffer_;
    WriteBuffer* write_Buffer_;
};

}

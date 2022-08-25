#pragma once
#include "../Disposal/IDisposable.h"

namespace xac {

class ConnectObj : public IDisposable {
public:
    ConnectObj();
    bool HasSendData();
    bool Receive();
    bool Send();
    void Dispose() override;
};
}
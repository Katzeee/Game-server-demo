#pragma once
#include "NetworkListener.h"
#include "NetworkBase.h"

namespace xac {

class Server : public NetworkListener {
public:
    Server();
    ~Server() {}
    void Update() override;
    void DataHandler();
private:
    bool is_running_;
};


} // end namespace xac
#pragma once

#include <iostream>
#include <arpa/inet.h>

namespace xac {

class NetworkBase {
public:
    NetworkBase();
    ~NetworkBase();
private:
    int socket_fd_{-1};
};

}
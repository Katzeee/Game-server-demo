#include <iostream>
#include "../src/NetworkListener.h"
#include "../src/Buffer.h"
#include "../src/ConnectObj.h"
using namespace xac;

int main() {
    auto network_listener = new NetworkListener();
    network_listener->Listen("127.0.0.1", 2233);
    network_listener->Update();
    return 0;
}
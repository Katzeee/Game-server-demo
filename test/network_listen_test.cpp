#include <iostream>
#include "../src/Server.h"
#include "../src/NetworkListener.h"
#include "../src/Buffer.h"
#include "../src/ConnectObj.h"
using namespace xac;

int main() {
    auto server = new Server();
    server->Listen("127.0.0.1", 2233);
    server->Update();
    // auto i = 100;
    // while(i--) {
    //     new Packet(100);
    // }
    return 0;
}
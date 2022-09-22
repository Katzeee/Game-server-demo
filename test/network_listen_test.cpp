#include <iostream>
#include "../src/libserver.h"
using namespace xac;

int main() {
    auto server = new Server();
    server->Listen("127.0.0.1", 2233);
    server->Update();
    auto i = 100;
    while(i--) {
        new Packet((Proto::MsgId)100, server->GetSocket());
    }
    return 0;
}
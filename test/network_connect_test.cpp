#include <thread>
#include "../src/NetworkConnecter.h"

using namespace xac;

int main() {
    // network_connecter->Update();
    NetworkConnecter* network_conn[5];
    std::thread t[5];
    for (auto i = 0; i < 5; i++) {
        network_conn[i] = new NetworkConnecter();
        network_conn[i]->Connect("127.0.0.1", 2233);
        t[i] = std::thread([network_conn, i](){
            std::cout << "t" << i << std::endl;
            network_conn[i]->Update();
        });
    }
    
    for (auto i = 0; i < 5; i++) {
        t[i].join();
    }
}
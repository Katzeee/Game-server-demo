#include <thread>
#include "../src/NetworkConnecter.h"

using namespace xac;

int main() {
    NetworkConnecter* network_connecter = new NetworkConnecter();
    network_connecter->Connect("127.0.0.1", 2233);
    // network_connecter->Update();
    auto t1 = std::thread([network_connecter](){
        std::cout << "t1" << std::endl;
        network_connecter->Update();
    });
    // auto t2 = std::thread([network_connecter](){
    //     std::cout << "t2" << std::endl;
    //     network_connecter->Update();
    // });
    t1.join();
    //t2.join();
}
#include "../src/NetworkConnecter.h"

using namespace xac;

int main() {
     NetworkConnecter* network_connecter = new NetworkConnecter();
     network_connecter->Connect("127.0.0.1", 2233);
     network_connecter->Select();
}
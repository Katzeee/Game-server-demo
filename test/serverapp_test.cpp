#include "../src/ServerApp.h"

using namespace xac;

int main() {
    ServerApp* server_app = new ServerApp(1);
    server_app->InitApp();
    server_app->StartAllThread();
    server_app->Run();
}
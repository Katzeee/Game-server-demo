#include "ServerApp.h"
#include "NetworkListener.h"

namespace xac {

ServerApp::ServerApp(APP_TYPE app_type) : app_type_(app_type) {
    ThreadManager::Instance();
    thread_manager_ = ThreadManager::GetInstance();
    auto network_listener = new NetworkListener();
    network_listener->Listen("127.0.0.1", 2233);
    thread_manager_->AddObjToThread(network_listener);
}

ServerApp::~ServerApp() {
    Dispose();
}

void ServerApp::Dispose() {

}

void ServerApp::StartAllThread() {
    thread_manager_->StartAllThread();
}

void ServerApp::Run() {
    while(true) {

    }
}

}
#include <iostream>
#include "Thread.h"

namespace xac {


Thread::~Thread() {
    Stop();
}

void Thread::Start() {
    is_running_ = true;
//    std::cout << "thread start" << std::endl;
    thread_ = new std::thread([this](){
        while (is_running_) {
            EntitySystem::Update();
        }
    });
}

void Thread::Stop() {
    is_running_ = false;
//    std::cout << "thread stop" << std::endl;
}


} // end namespace xac
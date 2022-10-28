#include <iostream>
#include "Thread.h"

namespace xac {



void Thread::Start() {
    is_running_ = true;
//    std::cout << "thread start" << std::endl;
    thread_ = std::make_unique<std::thread>([&](){
        while (is_running_) {
            EntitySystem::Update();
        }
    });
}

void Thread::Stop() {
    is_running_ = false;
    //thread_->join();
//    std::cout << "thread stop" << std::endl;
}


} // end namespace xac
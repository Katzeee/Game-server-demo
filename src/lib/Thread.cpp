#include <iostream>
#include "Thread.h"

namespace xac {

Thread::Thread() {
    
}

Thread::~Thread() {
    Stop();
    delete thread_;
    thread_ = nullptr;
    for (auto it : thread_objs_) {
        delete it;
    }
    thread_objs_.clear();
}

void Thread::Start() {
    is_running_ = true;
    std::cout << "thread start" << std::endl;
    thread_ = new std::thread([this](){
        while (is_running_) {
            Thread::Update();
        }
    });
}
void Thread::Update() {
    std::list<ThreadObj*> thread_objs_copy;
    lock_.lock();
    std::copy(thread_objs_.begin(), thread_objs_.end(), std::back_inserter(thread_objs_copy));
    lock_.unlock();
    for (auto it : thread_objs_copy) {
        it->Update();
    }
}
void Thread::Stop() {
    is_running_ = false;
    std::cout << "thread stop" << std::endl;
}

void Thread::AddThreadObj(ThreadObj* thread_obj) {
    lock_.lock();
    thread_objs_.emplace_back(thread_obj);
    lock_.unlock();
}


void Thread::DispatchPacket(std::shared_ptr<Packet> packet) {
    auto guard = std::lock_guard(lock_);
    for (auto it : thread_objs_) {
        it->InformMessageList(packet);
    }
}

} // end namespace xac
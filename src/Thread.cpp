#include <iostream>
#include "Thread.h"

namespace xac {

Thread::Thread() {
    
}

void Thread::Dispose() {
    Stop();
    delete thread_;
    thread_ = nullptr;
    for (auto it : thread_objs_) {
        delete it;
    }
    thread_objs_.clear();
}

Thread::~Thread() {
    Dispose();
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
    thread_lock_.lock();
    std::copy(thread_objs_.begin(), thread_objs_.end(), std::back_inserter(thread_objs_copy));
    thread_lock_.unlock();
    for (auto it : thread_objs_copy) {
        it->Update();
    }
}
void Thread::Stop() {
    is_running_ = false;
    std::cout << "thread stop" << std::endl;
}

void Thread::AddThreadObj(ThreadObj* thread_obj) {
    thread_lock_.lock();
    thread_objs_.emplace_back(thread_obj);
    thread_lock_.unlock();
}

}
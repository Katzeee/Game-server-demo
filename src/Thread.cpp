#include <iostream>
#include "Thread.h"

namespace xac {

Thread::Thread() {
    
}

void Thread::Dispose() {
    delete thread_;
    for (auto it : thread_objs_) {
        delete it;
    }
}

Thread::~Thread() {
    Dispose();
}

void Thread::Start() {
    is_running_ = true;
    thread_ = new std::thread([this](){
        while (is_running_) {
            Thread::Update(this);
        }
    });
}
void Thread::Update(Thread* this_class) {
    std::list<ThreadObj*> thread_objs_copy;
    this_class->thread_lock_.lock();
    std::copy(this_class->thread_objs_.begin(), this_class->thread_objs_.end(), std::back_inserter(thread_objs_copy));
    this_class->thread_lock_.unlock();
    std::cout << "update" << std::endl;
    for (auto it : thread_objs_copy) {
        it->Update();
    }
}
void Thread::Stop() {
    is_running_ = false;
}

void Thread::AddThreadObj(ThreadObj* thread_obj) {
    thread_lock_.lock();
    thread_objs_.emplace_back(thread_obj);
    thread_lock_.unlock();
}

}
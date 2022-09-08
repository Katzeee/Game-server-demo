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
    thread_ = new std::thread(Thread::Update, this);
    return;
}
void Thread::Update(Thread* this_class) {
    std::list<ThreadObj*> thread_objs_copy;
    this_class->thread_lock_.lock();
    std::copy(this_class->thread_objs_.begin(), this_class->thread_objs_.end(), std::back_inserter(thread_objs_copy));
    this_class->thread_lock_.unlock();
    for (auto it : thread_objs_copy) {
        it->Update();
    }
}
void Thread::Stop() {
    thread_->join();
}

}
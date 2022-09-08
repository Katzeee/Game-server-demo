#include "ThreadManager.h"
#include "Thread.h"

namespace xac {

ThreadManager::ThreadManager() {
    NewThread();
}

void ThreadManager::StartAllThread() {
    auto threads_copy = std::list<Thread*>();
    thread_lock_.lock();
    std::copy(threads_.begin(), threads_.end(), std::back_inserter(threads_copy));
    thread_lock_.unlock();
    for (auto it : threads_copy) {
        it->Start();
    }
}

void ThreadManager::NewThread() {
    auto thread = new Thread();
    thread_lock_.lock();
    threads_.emplace_back(thread);
    thread_lock_.unlock();
}

void ThreadManager::AddObjToThread(ThreadObj* thread_obj) {
    thread_lock_.lock();
    threads_[0]->AddThreadObj(thread_obj);
    std::cout << "add thread obj" << std::endl;
    thread_lock_.unlock();
}

}
#include "ThreadManager.h"
#include "Thread.h"

namespace xac {

ThreadManager::ThreadManager() {
    NewThread();
}

void ThreadManager::StartAllThread() {
    auto threads_copy = std::list<Thread*>();
    lock_.lock();
    std::copy(threads_.begin(), threads_.end(), std::back_inserter(threads_copy));
    lock_.unlock();
    for (auto it : threads_copy) {
        it->Start();
    }
}

void ThreadManager::NewThread() {
    auto thread = new Thread();
    lock_.lock();
    threads_.emplace_back(thread);
    lock_.unlock();
}

void ThreadManager::AddObjToThread(ThreadObj* thread_obj) {
    lock_.lock();
    auto thread = GetLeastObjThread();
    if (thread == nullptr) {
        throw std::logic_error("no thread!");
        return;
    }
    thread->AddThreadObj(thread_obj);
    std::cout << "add thread obj" << std::endl;
    lock_.unlock();
}

bool ThreadManager::IsLoop() {
    lock_.lock();
    for (auto it : threads_)  {
        if (it->IsRunning()) {
            return true;
        }
    }
    lock_.unlock();
    return false;
}

void ThreadManager::DispatchMessage(std::shared_ptr<Packet> packet) {
    auto guard = std::lock_guard(lock_);
    for (auto it : threads_) {
        it->DispatchMessage(packet);
    }
}

Thread* ThreadManager::GetLeastObjThread() {
    size_t count = -1; // LONG_MAX
    Thread* res = nullptr;
    for (auto& it : threads_) {
        if (it->ThreadObjCount() < count) {
            count = it->ThreadObjCount();
            res = it;
        }
    }
    return res;
}
}
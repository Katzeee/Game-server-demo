#include "ThreadManager.h"
#include "Thread.h"

namespace xac {

ThreadManager::ThreadManager() {
    CreateThread();
}

void ThreadManager::StartAllThread() {
    auto threads_copy = std::list<Thread*>();
    mutex_.lock();
    std::copy(threads_.begin(), threads_.end(), std::back_inserter(threads_copy));
    mutex_.unlock();
    for (auto it : threads_copy) {
        it->Start();
    }
}

void ThreadManager::CreateThread() {
    auto thread = new Thread();
    mutex_.lock();
    threads_.emplace_back(thread);
    mutex_.unlock();
}

void ThreadManager::AddObjToThread(ThreadObj* thread_obj) {
    mutex_.lock();
    auto thread = GetLeastObjThread();
    if (thread == nullptr) {
        throw std::logic_error("no thread!");
        return;
    }
    thread->AddThreadObj(thread_obj);
    std::cout << "add thread obj" << std::endl;
    mutex_.unlock();
}

void ThreadManager::AddNetworkToThread(NetworkBase* network) {
    AddObjToThread(network);
    network_ = network;
}

bool ThreadManager::IsLoop() {
    mutex_.lock();
    for (auto it : threads_)  {
        if (it->IsRunning()) {
            return true;
        }
    }
    mutex_.unlock();
    return false;
}

void ThreadManager::DispatchPacket(std::shared_ptr<Packet> packet) {
    auto guard = std::lock_guard(mutex_);
    for (auto it : threads_) {
        it->DispatchPacket(packet);
    }
}

void ThreadManager::SendPacket(std::shared_ptr<Packet> packet) {
    if (!network_) {
        assert(0);
    }
    network_->AddPacketToList(packet);
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
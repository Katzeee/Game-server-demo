#include "ThreadManager.h"
#include "Thread.h"

namespace xac {

ThreadManager::ThreadManager() { CreateThread(); }

void ThreadManager::StartAllThread() {
  auto threads_copy = std::list<Thread *>();
  {
    auto guard = std::lock_guard(mutex_);
    std::copy(threads_.begin(), threads_.end(), std::back_inserter(threads_copy));
  }
  for (auto *it : threads_copy) {
    it->Start();
  }
}

void ThreadManager::StopAllThread() {
  auto guard = std::lock_guard(mutex_);
  for (auto* it : threads_) {
    it->Stop();
  }
}

void ThreadManager::CreateThread() {
  auto *thread = new Thread();
  mutex_.lock();
  threads_.emplace_back(thread);
  mutex_.unlock();
}

auto ThreadManager::IsLoop() -> bool {
  auto guard = std::lock_guard(mutex_);
  for (auto *it : threads_) {
    if (it->IsRunning()) {
      return true;
    }
  }
  return false;
}

void ThreadManager::DispatchPacket(std::shared_ptr<Packet> packet) {
  auto threads_copy = std::list<Thread *>();
  {
    auto guard = std::lock_guard(mutex_);
    std::copy(threads_.begin(), threads_.end(), std::back_inserter(threads_copy));
  }
  for (auto it : threads_copy) {
    it->AddPacket(packet);
  }
}

}  // namespace xac
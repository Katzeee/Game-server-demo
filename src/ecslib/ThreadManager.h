#pragma once

#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <vector>
#include "Singleton.h"
#include "Thread.h"

namespace xac {

class ThreadManager : public Singleton<ThreadManager>, public EntitySystem {
 public:
  ThreadManager();
  ~ThreadManager() = default;
  void StartAllThread();
  void StopAllThread();
  void CreateThread();
  void DispatchPacket(std::shared_ptr<Packet> packet);
  auto IsLoop() -> bool;
  template <typename T, typename... Args>
  void CreateComponent(Args &&...args);

 private:
  std::mutex mutex_;
  std::list<Thread *> threads_;  // TODO(xac): Refresh list
};

template <typename T, typename... Args>
void ThreadManager::CreateComponent(Args &&...args) {
  // TODO(xac) : dispatch to different threads
  threads_.front()->AddComponent<T>(args...);
}

}  // end namespace xac
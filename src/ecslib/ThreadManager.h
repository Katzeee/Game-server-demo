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
  std::vector<Thread *> threads_;      // TODO(xac): Refresh list
  size_t component_thread_num_ = 0;  // determine put this component to which thread
};

template <typename T, typename... Args>
void ThreadManager::CreateComponent(Args &&...args) {
  // TODO(xac) : dispatch to different threads
  component_thread_num_ = component_thread_num_ < threads_.size() ? component_thread_num_ : 0;
  threads_[component_thread_num_]->AddComponent<T>(args...);
}

}  // end namespace xac
#pragma once
#include "Singleton.h"

#include <memory>
#include <mutex>
#include <queue>

namespace xac {

template <typename T>
class ObjectPool : public Singleton<ObjectPool<T>> {
 public:
  ~ObjectPool() { std::cout << free_objs_.size() << std::endl; }
  template <typename... Args>
  auto InstantiateOne(Args &&...args) -> std::shared_ptr<T>;
  void FreeOne(std::shared_ptr<T> free_obj) {
    auto guard = std::lock_guard(mutex_);
    free_objs_.push(free_obj);
  }

 private:
  std::mutex mutex_;
  std::queue<std::shared_ptr<T>> free_objs_;
  auto CreateOne() -> std::shared_ptr<T> {
    auto obj = std::make_shared<T>();
    obj->SetPool(this);
    return obj;
  }
};

template <typename T>
template <typename... Args>
auto ObjectPool<T>::InstantiateOne(Args &&...args) -> std::shared_ptr<T> {
  std::shared_ptr<T> obj = nullptr;
  {
    auto guard = std::lock_guard(mutex_);
    if (!free_objs_.empty()) {
      obj = free_objs_.front();
      free_objs_.pop();
    }
  }
  if (obj == nullptr) {
    obj = CreateOne();
  }
  obj->Reset(std::forward<Args>(args)...);
  return obj;
}

}  // namespace xac

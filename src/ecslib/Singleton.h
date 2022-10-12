#pragma once
#include <error.h>
#include <exception>
#include <iostream>
#include <mutex>

namespace xac {

template <typename T>
class Singleton {
 public:
  template <typename... Args>
  static auto Instance(Args &&...args) -> T * {
    if (instance_ == nullptr) {
      instance_ = new T(std::forward(args)...);
    }
    return instance_;
  }
  static auto GetInstance() -> T * {
    auto guard = std::lock_guard(Singleton<T>::mutex_);
    if (instance_ == nullptr) {
      Instance();
      //throw std::logic_error("No instance!");
    }
    return instance_;
  }
  static void DestroyInstance() {
    delete instance_;
    instance_ = nullptr;
  }

 private:
  static T *instance_;
  static std::mutex mutex_;
};

template <typename T>
T *Singleton<T>::instance_ = nullptr;

template <typename T>
std::mutex Singleton<T>::mutex_;

}  // end namespace xac
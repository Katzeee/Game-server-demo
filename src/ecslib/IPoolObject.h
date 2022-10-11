#pragma once

#include <memory>
#include "ObjectPool.h"

// class xac::ObjectPool;

namespace xac {

template <typename T, typename... Args>
class IPoolObject {
 public:
  virtual ~IPoolObject() = default;
  virtual void Reset(Args... args) = 0;
  virtual void BackToPool() = 0;
  void SetPool(ObjectPool<T> *obj_pool) { obj_pool_ = obj_pool; }

 private:
  ObjectPool<T> *obj_pool_;
};

};  // namespace xac
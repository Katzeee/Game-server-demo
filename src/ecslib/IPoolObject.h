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
  virtual void Dispose() = 0;
  void BackToPool() {
    assert(obj_pool_);
    obj_pool_->FreeOne(this);
  }
  void SetPool(ObjectPool<T> *obj_pool) { obj_pool_ = obj_pool; }

 protected:
  ObjectPool<T> *obj_pool_;
};

};  // namespace xac
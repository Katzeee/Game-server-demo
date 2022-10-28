#pragma once

#include <memory>
#include "ObjectPool.h"

// class xac::ObjectPool;

namespace xac {

template <typename T, typename... Args>
class IPoolObject {
 public:
  virtual ~IPoolObject() = default;
  virtual void Dispose() {}
  void SetPool(ObjectPool<T> *obj_pool) {
    assert(!obj_pool_);
    obj_pool_ = obj_pool;
  }
  void BackToPool() {
    Dispose();
    obj_pool_->FreeOne(dynamic_cast<T *>(this));
  }
  virtual void Reset(Args... args) = 0;

 protected:
  ObjectPool<T> *obj_pool_ = nullptr;
};

};  // namespace xac
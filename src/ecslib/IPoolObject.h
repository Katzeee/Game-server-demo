#pragma once

#include <memory>
#include "ObjectPool.h"

// class xac::ObjectPool;

namespace xac {

template <typename T>
class IPoolObject {
 public:
  virtual ~IPoolObject() = default;
  // virtual void Dispose() = 0;
  virtual void BackToPool() = 0;
  void SetPool(ObjectPool<T> *obj_pool) {
    assert(!obj_pool_);
    obj_pool_ = obj_pool;
  }

 protected:
  ObjectPool<T> *obj_pool_;
};

};  // namespace xac
#pragma once

#include <cstdint>
#include <list>
#include <map>
#include <memory>
#include <string>
#include "ComponentBase.h"
#include "IComponent.h"
#include "ObjectPool.h"

namespace xac {
class EntitySystem {
 public:
  template <typename T, typename... Args>
  void AddComponent(Args... args) {
    auto pcomp = ObjectPool<T>::GetInstance()->InstantiateOne(std::forward<Args>(args)...);
    components_[0] = std::make_shared(*pcomp);
  }

 private:
  std::map<uint64_t, std::shared_ptr<ComponentBase>> components_;
  std::list<std::shared_ptr<IUpdateComponent>> update_components_;
  std::list<std::shared_ptr<IMessageComponent>> message_components_;
};
}  // end namespace xac

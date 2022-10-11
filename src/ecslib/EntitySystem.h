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
  void AddComponent(Args... args);
  void Update();

 private:
  std::map<uint64_t, std::shared_ptr<ComponentBase>> components_;
  std::list<std::shared_ptr<IUpdateComponent>> update_components_;
  std::list<std::shared_ptr<IMessageComponent>> message_components_;
};

template <typename T, typename... Args>
void EntitySystem::AddComponent(Args... args) {
  auto comp = ObjectPool<T>::GetInstance()->InstantiateOne(std::forward<Args>(args)...);
  auto update_comp = std::dynamic_pointer_cast<IUpdateComponent>(comp);
  if (update_comp) {
    update_components_.emplace_back(update_comp);
  }
  auto message_comp = std::dynamic_pointer_cast<IMessageComponent>(comp);
  if (message_comp) {
    message_components_.emplace_back(message_comp);
  }
}

}  // end namespace xac

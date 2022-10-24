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
  EntitySystem() = default;
  virtual ~EntitySystem() = default;
  template <typename T, typename... Args>
  auto AddComponent(Args &&...args) -> std::shared_ptr<T>;
  void AddPacket(const std::shared_ptr<Packet>& packet);
  void Update();

 protected:
  template <typename T>
  void AddComponentToSystem(std::shared_ptr<T> component);
  void HandleMessage();
  void HandleUpdate();
  std::map<uint64_t, std::shared_ptr<ComponentBase>> components_;
  std::list<std::shared_ptr<IUpdateComponent>> update_components_;
  std::list<std::shared_ptr<IMessageComponent>> message_components_;
  std::mutex packet_mutex_;
  std::list<std::shared_ptr<Packet>> packet_list_; // TODO: block queue
};

template <typename T, typename... Args>
auto EntitySystem::AddComponent(Args &&...args) -> std::shared_ptr<T> {
  auto comp = std::shared_ptr<T>(ObjectPool<T>::GetInstance()->InstantiateOne(std::forward<Args>(args)...));
  AddComponentToSystem(comp);
  return comp;
}

template <typename T>
void EntitySystem::AddComponentToSystem(std::shared_ptr<T> component) {
  auto update_comp = std::dynamic_pointer_cast<IUpdateComponent>(component);
  if (update_comp) {
    update_components_.emplace_back(update_comp);
  }
  auto message_comp = std::dynamic_pointer_cast<IMessageComponent>(component);
  if (message_comp) {
    message_comp->RegistCBFuncs();
    message_components_.emplace_back(message_comp);
  }
}

}  // end namespace xac

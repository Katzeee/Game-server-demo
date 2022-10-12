#include "EntitySystem.h"

namespace xac {

void EntitySystem::AddPacket(const std::shared_ptr<Packet>& packet) {
    auto guard = std::lock_guard(packet_mutex_);
    packet_list_.emplace_back(packet);
}

void EntitySystem::Update() {
  HandleUpdate();
  HandleMessage();
}

void EntitySystem::HandleUpdate() {
  for (const auto &it : update_components_) {
    it->Update();
  }
}

void EntitySystem::HandleMessage() {
  std::list<std::shared_ptr<Packet>> tmp_packet_list;
  {
    auto guard = std::lock_guard(packet_mutex_);
    if (packet_list_.empty()) {
      return;
    }
    tmp_packet_list.swap(packet_list_);
  }
  for (const auto& it_msg_comp : message_components_) {
    for (const auto& it_packet : tmp_packet_list) {
        it_msg_comp->InformMessageList(it_packet);
    }
  } 
}

}  // end namespace xac

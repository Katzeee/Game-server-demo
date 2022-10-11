#include "EntitySystem.h"

namespace xac {
void EntitySystem::Update() {
  for (const auto &it : update_components_) {
    it->Update();
  }
}

}  // end namespace xac

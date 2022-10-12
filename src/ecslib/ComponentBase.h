#pragma once

#include <cstdint>
#include <memory>

namespace xac {
class ComponentBase {
 public:
  void SetParent(const std::shared_ptr<ComponentBase>& parent);
  auto GetUID() -> uint64_t;
  auto GetParent() -> std::shared_ptr<ComponentBase>;

 private:
  uint64_t u_id_;
  std::shared_ptr<ComponentBase> parent_;
};
}  // end namespace xac

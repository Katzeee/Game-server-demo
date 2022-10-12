#include "ComponentBase.h"

namespace xac {
void ComponentBase::SetParent(const std::shared_ptr<ComponentBase>& parent) { parent_ = parent; }

auto ComponentBase::GetUID() -> uint64_t { return u_id_; }
auto ComponentBase::GetParent() -> std::shared_ptr<ComponentBase> { return parent_; }
}  // end namespace xac

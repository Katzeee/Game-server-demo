#include "ComponentBase.h"

namespace xac
{
void ComponentBase::SetParent(std::shared_ptr<ComponentBase> parent) {
    parent_ = parent;
} 
} // end namespace xac

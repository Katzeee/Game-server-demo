#pragma once

#include <memory>
#include <cstdint>

namespace xac {
class ComponentBase : public std::enable_shared_from_this<ComponentBase> {
public:
    void SetParent(std::shared_ptr<ComponentBase> parent);

private:
    uint64_t u_id_;
    std::shared_ptr<ComponentBase> parent_;
};
}  // end namespace xac

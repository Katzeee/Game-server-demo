#pragma once

namespace xac {

template <typename... Args>
class IResetable {
 public:
  virtual void Reset(Args... args) = 0;
  IResetable() = default;
  virtual ~IResetable() = default;
};
}  // end namespace xac
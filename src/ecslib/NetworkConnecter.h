#pragma once
#include "../protobuf/proto.h"
#include "IComponent.h"
#include "IPoolObject.h"
#include "NetworkBase.h"

namespace xac {

class NetworkConnecter : public NetworkBase,
                         public IPoolObject<NetworkConnecter, std::string, uint16_t>,
                         public IUpdateComponent {
 public:
  NetworkConnecter() = default;
  virtual ~NetworkConnecter() = default;
  NetworkConnecter(std::string ip_addr, uint16_t port) : ip_addr_(ip_addr), port_(port) {}
  void Reset(std::string ip_addr, uint16_t port) override;
  void Dispose() override;
  bool Connect(std::string ip_addr, uint16_t port);
  void Update() override;
  auto IsConnected() -> bool {
    auto guard = std::lock_guard(mutex_);
    return IsConnectedInternal();
  }
  bool Connect();

 protected:
  auto IsConnectedInternal() -> bool { return !connects_.empty(); }
  void Reconnect();
  std::string ip_addr_;
  uint16_t port_;
};
}  // end namespace xac
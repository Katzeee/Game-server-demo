#pragma once
#include "IComponent.h"
#include "IPoolObject.h"
#include "NetworkBase.h"
#include "protobuf/proto.h"

namespace xac {

class NetworkConnecter : public NetworkBase,
                         public IPoolObject<NetworkConnecter, std::string, uint16_t>,
                         public IUpdateComponent {
 public:
  NetworkConnecter() = default;
  NetworkConnecter(std::string ip_addr, uint16_t port) : ip_addr_(ip_addr), port_(port) {}
  void Reset(std::string ip_addr, uint16_t port) override;
  void Dispose() override;
  bool Connect(std::string ip_addr, uint16_t port);
  void Update() override;

 private:
  void Reconnect();
  bool Connect();
  std::string ip_addr_;
  uint16_t port_;
  int i = 2;
};
}  // end namespace xac
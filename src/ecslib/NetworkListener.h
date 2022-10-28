#pragma once

#include <arpa/inet.h>
#include "IComponent.h"
#include "IPoolObject.h"
#include "IResetable.h"
#include "NetworkBase.h"

namespace xac {
class NetworkListener : public NetworkBase,
                        public IPoolObject<NetworkListener, std::string, uint16_t>,
                        public IUpdateComponent {
 public:
  void Update() override;
  void Reset(std::string ip_addr, uint16_t port) override { Listen(ip_addr, port); }

  void Dispose() override {
    master_socket_fd_ = -1;
    // TODO():send message to inform
  }

 protected:
  auto Accept() -> int;
  auto Listen(std::string ip_addr, uint16_t port) -> bool;
};
}  // namespace xac
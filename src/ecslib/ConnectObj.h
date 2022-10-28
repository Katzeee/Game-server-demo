#pragma once
#include <iostream>
#include <memory>
#include "BufferBase.h"
#include "IPoolObject.h"
#include "IResetable.h"
#include "Packet.h"

namespace xac {

class RecvBuffer;
class SendBuffer : public RingBuffer {
 public:
  void AddPacket(std::shared_ptr<Packet> packet);
};

class RecvBuffer : public RingBuffer {
 public:
  std::shared_ptr<Packet> GetPacket(int socket_fd);
};

class ConnectObj : public IPoolObject<ConnectObj, int> {
 public:
  ConnectObj() = default;
  ConnectObj(int socket_fd);
  virtual ~ConnectObj();
  void Reset(int socket_fd) override;
  void Dispose() override;
  auto Send() -> bool;
  auto HasSendData() -> bool;
  auto HasRecvData() -> bool;
  auto Receive() -> bool;
  void SendPacket(std::shared_ptr<Packet> packet);
  auto GetSocket() const -> int;
  auto GetPacket() -> std::shared_ptr<Packet>;

 protected:
  int socket_fd_ = -1;
  std::unique_ptr<RecvBuffer> read_buffer_;
  std::unique_ptr<SendBuffer> write_buffer_;
};

}  // namespace xac

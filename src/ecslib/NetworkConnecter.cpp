#include "NetworkConnecter.h"
#include <sys/select.h>
#include <cstring>
#include <string>

namespace xac {

void NetworkConnecter::Reset(std::string ip_addr, uint16_t port) { Connect(ip_addr, port); }

void NetworkConnecter::Dispose() {
  ::shutdown(master_socket_fd_, SHUT_RDWR);
  master_socket_fd_ = -1;
  // TODO(): maybe cause reconnect
  for (const auto &it : connects_) {
    it.second->BackToPool();
  }
  connects_.clear();
}

bool NetworkConnecter::Connect() { return NetworkConnecter::Connect(ip_addr_, port_); }

bool NetworkConnecter::Connect(std::string ip_addr, uint16_t port) {
  if (master_socket_fd_ == -1) {
    if (!CreateSocket()) {
      return false;
    }
  }
  sockaddr_in sockaddr_struct;
  memset(&sockaddr_struct, 0, sizeof(sockaddr_in));
  sockaddr_struct.sin_addr.s_addr = inet_addr(ip_addr.c_str());
  sockaddr_struct.sin_family = AF_INET;
  sockaddr_struct.sin_port = htons(port);
  // TODO: connect before listen?
  if (connect(master_socket_fd_, reinterpret_cast<sockaddr *>(&sockaddr_struct), sizeof(sockaddr_struct)) < 0) {
    std::cout << "connect error: " << errno << std::endl;
    return false;
  }
  SetSocketOpt(master_socket_fd_);
  auto* connect_obj = ObjectPool<ConnectObj>::GetInstance()->InstantiateOne(master_socket_fd_);
  connects_.insert(std::pair(master_socket_fd_, connect_obj));
  ip_addr_ = ip_addr;
  port_ = port;
  return true;
}

void NetworkConnecter::Update() {
  if (connects_.empty()) {
    Reconnect();
  }

  Select();
  NetworkBase::SendPacketUpdate();
}

void NetworkConnecter::Reconnect() {
  master_socket_fd_ = -1;
  while (!Connect())
    ;
  auto packet = std::make_shared<Packet>(Proto::MsgId::MI_TestMsg, master_socket_fd_);
  Proto::TestMsg test_msg;
  test_msg.set_index(1);
  test_msg.set_msg("reconnect");
  packet->SerializeToBuffer(test_msg);
  AddPacketToList(packet);
}

}  // end namespace xac

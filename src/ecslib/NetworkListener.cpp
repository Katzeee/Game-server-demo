#include "NetworkListener.h"
#include <arpa/inet.h>
#include <memory.h>
#include "ConnectObj.h"
#include "Packet.h"
#include "protobuf/msg.pb.h"
#include "protobuf/proto_msg_id.pb.h"

namespace xac {

auto NetworkListener::Listen(std::string ip_addr, uint16_t port) -> bool {
  master_socket_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (master_socket_fd_ < 0) {
    // TODO:LOG
    std::cout << "socket error" << std::endl;
    return false;
  }
  sockaddr_in sock_addr;
  memset(&sock_addr, 0, sizeof(sockaddr_in));
  sock_addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons(port);
  if (::bind(master_socket_fd_, reinterpret_cast<sockaddr *>(&sock_addr), sizeof(sockaddr)) < 0) {
    // TODO(1):LOG
    std::cout << "bind error" << std::endl;
    assert(0);
    return false;
  }
  int back_log = 10;
  if (::listen(master_socket_fd_, back_log) < 0) {
    // TODO():LOG
    std::cout << "listen error" << std::endl;
    return false;
  }
  NetworkBase::SetNonBlock(master_socket_fd_);
  return true;
}

auto NetworkListener::Accept() -> int {
  sockaddr sock_addr;
  memset(&sock_addr, 0, sizeof(sockaddr));
  socklen_t sock_addr_len = sizeof(sockaddr);
  int res = 0;
  while (true) {
    auto socket_fd = ::accept(master_socket_fd_, &sock_addr, &sock_addr_len);
    if (socket_fd <= 0) {
      return res;
    }
    NetworkBase::SetSocketOpt(socket_fd);
    auto connectobj_ptr = std::make_shared<ConnectObj>(socket_fd);
    std::cout << "accept " << socket_fd << std::endl;

    connects_.insert(std::pair(socket_fd, connectobj_ptr));
    res++;
  }
  return res;
}

void NetworkListener::Update() {
  if (FD_ISSET(master_socket_fd_, &read_fds_)) {
    Accept();
  }
  Select();
  NetworkBase::SendPacketUpdate();
  // for (auto it : connects_) {
  //     if (it.second->HasRecvData()) {
  //         auto packet = it.second->GetPacket();
  //         if (!packet) {
  //             continue;
  //         }
  //         auto proto = packet->ParseToProto<Proto::TestMsg>();
  //         std::cout << "recv id: " << proto.index() << " msg: " << proto.msg() << std::endl;
  //     }
  // }
}
}  // end namespace xac
#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/epoll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <iostream>
#include <list>
#include <map>
#include <mutex>

#include "ComponentBase.h"
#include "ConnectObj.h"
#include "Packet.h"

namespace xac {

class NetworkBase : public ComponentBase {
 public:
  NetworkBase() = default;
  virtual ~NetworkBase();
  auto Select() -> bool;
  void AddPacketToList(std::shared_ptr<Packet> packet);
  void SendPacketUpdate();

 protected:
  int master_socket_fd_{-1};  // listen fd or connect fd
  std::map<int, ConnectObj *> connects_;
  std::list<std::shared_ptr<Packet>> send_msg_list_;
  fd_set read_fds_, write_fds_, except_fds_;
  std::mutex mutex_;
  static void SetSocketOpt(int socket);
  static void SetNonBlock(int socket);
  auto CreateSocket() -> bool;
};

}  // end namespace xac
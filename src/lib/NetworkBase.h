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


#include "ConnectObj.h"
#include "IDisposable.h"
#include "Packet.h"
#include "ThreadObj.h"


namespace xac {

class NetworkBase : public ThreadObj {
 public:
  NetworkBase() {}
  virtual ~NetworkBase();
  bool Select();
  void Update() override;
  virtual void Init() = 0;
  void SendPacket(std::shared_ptr<Packet> packet);
  // virtual void Update() = 0;
 protected:
  int master_socket_fd_{-1};  // listen fd or connect fd
  std::map<int, std::shared_ptr<ConnectObj>> connects_;
  std::list<std::shared_ptr<Packet>> send_msg_list_;
  fd_set read_fds_, write_fds_, except_fds_;
  std::mutex lock_;
  static void SetSocketOpt(int socket);
  static void SetNonBlock(int socket);
  bool CreateSocket();
};

}  // namespace xac
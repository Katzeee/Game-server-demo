#include "NetworkBase.h"
#include <fcntl.h>
#include <memory.h>

namespace xac {

bool NetworkBase::Select() {
  // initialize fd_sets
  FD_ZERO(&read_fds_);
  FD_ZERO(&write_fds_);
  FD_ZERO(&except_fds_);
  // put master_socket_fd_ into all fd_set
  FD_SET(master_socket_fd_, &read_fds_);
  FD_SET(master_socket_fd_, &write_fds_);
  FD_SET(master_socket_fd_, &except_fds_);
  int fd_max = master_socket_fd_;
  for (auto it = connects_.begin(); it != connects_.end(); it++) {
    fd_max = fd_max > it->first ? fd_max : it->first;
    FD_SET(it->first, &read_fds_);
    FD_SET(it->first, &except_fds_);
    if (it->second->HasSendData()) {
      FD_SET(it->first, &write_fds_);
    } /*else {
        if (it->first == master_socket_fd_) {
            FD_CLR(master_socket_fd_, &write_fds_);
        }
    }*/
  }
  timeval timeout;
  memset(&timeout, 0, sizeof(timeval));
  timeout.tv_sec = 0;
  timeout.tv_usec = 50 * 1000;
  if (::select(fd_max + 1, &read_fds_, &write_fds_, &except_fds_, &timeout) <= 0) {
    return false;
  }
  for (auto it = connects_.begin(); it != connects_.end();) {
    if (FD_ISSET(it->first, &except_fds_)) {  // if fd has exception, close the connection
      std::cout << "except " << it->first << std::endl;
      it = connects_.erase(it);
      continue;
    }
    if (FD_ISSET(it->first, &read_fds_)) {
      if (!it->second->Receive()) {
        it = connects_.erase(it);
        continue;
      }
    }
    if (FD_ISSET(it->first, &write_fds_)) {
      if (!it->second->Send()) {
        it = connects_.erase(it);
        continue;
      }
    }
    ++it;
  }
  return true;
}

void NetworkBase::AddPacketToList(std::shared_ptr<Packet> packet) {
  auto guard = std::lock_guard(lock_);
  // lock_.try_lock();
  send_msg_list_.emplace_back(packet);
}

void NetworkBase::Update() {
  std::list<std::shared_ptr<Packet>> tmp_list;
  if (send_msg_list_.empty()) {
    return;
  }
  lock_.lock();
  tmp_list.swap(send_msg_list_);
  lock_.unlock();
  for (auto it : tmp_list) {
    auto connect = connects_.find(it->GetSocket());
    if (connect != connects_.end()) {
      connect->second->SendPacket(it);
    }
  }
}

bool NetworkBase::CreateSocket() {
  master_socket_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (master_socket_fd_ <= 0) {
    std::cout << "socket fail: " << errno << std::endl;
    return false;
  }
  return true;
}

void NetworkBase::SetSocketOpt(int socket) {
  // once the port closed, reuse it
  bool is_reuse_addr = true;
  setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (void *)&is_reuse_addr, sizeof(is_reuse_addr));

  // set the timeout
  int net_timeout = 3000;
  setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, (void *)&net_timeout, sizeof(net_timeout));
  setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (void *)&net_timeout, sizeof(net_timeout));

  // keep alive
  int keep_alive = 1;
  socklen_t opt_len = sizeof(keep_alive);
  int keep_idle = 60 * 2;
  int keep_interval = 10;
  int keep_count = 5;

  setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (void *)&keep_alive, opt_len);
  if (getsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, &keep_alive, &opt_len) < 0) {
    std::cout << "getsocketopt Keep alive failed" << std::endl;
  }

  setsockopt(socket, SOL_TCP, TCP_KEEPIDLE, (void *)&keep_idle, opt_len);
  if (getsockopt(socket, SOL_TCP, TCP_KEEPIDLE, &keep_idle, &opt_len) < 0) {
    std::cout << "getsocketopt Keep idle failed" << std::endl;
  }

  setsockopt(socket, SOL_TCP, TCP_KEEPINTVL, (void *)&keep_interval, opt_len);
  setsockopt(socket, SOL_TCP, TCP_KEEPCNT, (void *)&keep_count, opt_len);

  // set non block
  NetworkBase::SetNonBlock(socket);
}

void NetworkBase::SetNonBlock(int socket) {
  int flags = fcntl(socket, F_GETFL, 0);
  fcntl(socket, F_SETFL, flags | O_NONBLOCK);
}

NetworkBase::~NetworkBase() { connects_.clear(); }

}  // end namespace xac
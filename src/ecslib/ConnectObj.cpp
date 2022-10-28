#include "ConnectObj.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <memory>
#include "ThreadManager.h"

namespace xac {

ConnectObj::ConnectObj(int socket_fd) : socket_fd_(socket_fd) {
  read_buffer_ = std::make_unique<RecvBuffer>();
  write_buffer_ = std::make_unique<SendBuffer>();
}
auto ConnectObj::Send() -> bool {
  while (true) {
    auto need_send_size = write_buffer_->GetSize();
    if (need_send_size == 0) {
      return true;
    }
    char *buffer = new char[need_send_size]{0};
    if (need_send_size <= 0) {
      return true;
    }
    write_buffer_->MemcopyFromBuffer(buffer, need_send_size);
    auto send_size = ::send(socket_fd_, buffer, need_send_size, 0);
    delete[] buffer;
    if (send_size > 0) {
      write_buffer_->RemoveData(send_size);
      return true;
    } else {
      return false;
    }
  }
  return true;
}
auto ConnectObj::HasSendData() -> bool { return write_buffer_->GetSize() > 0; }
auto ConnectObj::HasRecvData() -> bool { return read_buffer_->GetSize() > 0; }
auto ConnectObj::Receive() -> bool {
  auto hasData = false;
  char *buffer = new char[read_buffer_->GetEmptySize()];
  ssize_t data_size = 0;
  while (true) {
    if (read_buffer_->GetEmptySize() <= sizeof(PacketHead)) {
      read_buffer_->ReAlloc(sizeof(PacketHead));
    }
    data_size = ::recv(socket_fd_, buffer, read_buffer_->GetEmptySize(), 0);
    if (data_size > 0) {
      if (static_cast<ssize_t>(read_buffer_->GetEmptySize()) <= data_size) {
        read_buffer_->ReAlloc(data_size);
      }
      // std::cout << "recv " << data_size <<  std::endl;
      read_buffer_->MemcopyToBuffer(buffer, data_size);
      read_buffer_->FillData(data_size);
    } else if (data_size == 0) {
      break;
    } else {
      const auto socket_error = errno;
      if (socket_error == EINTR || socket_error == EWOULDBLOCK || socket_error == EAGAIN) {
        hasData = true;
      }
      break;
    }
  }
  if (hasData) {
    while (true) {
      const auto packet = read_buffer_->GetPacket(socket_fd_);
      if (packet == nullptr) {
        break;
      }
      std::cout << "dispatch one from socket " << packet->GetSocket() << std::endl;
      ThreadManager::GetInstance()->DispatchPacket(packet);
    }
  }
  delete[] buffer;
  return hasData;
}

auto ConnectObj::GetSocket() const -> int { return socket_fd_; }

void ConnectObj::Reset(int socket_fd) {
  socket_fd_ = socket_fd;
  read_buffer_ = std::make_unique<RecvBuffer>();
  write_buffer_ = std::make_unique<SendBuffer>();
}

void ConnectObj::Dispose() {
  socket_fd_ = -1;
  read_buffer_ = nullptr;
  write_buffer_ = nullptr;
}

ConnectObj::~ConnectObj() {
  std::cout << "shutdown: " << socket_fd_ << std::endl;
  ::shutdown(socket_fd_, SHUT_RDWR);
  read_buffer_ = nullptr;
  write_buffer_ = nullptr;
}

auto ConnectObj::GetPacket() -> std::shared_ptr<Packet> { return read_buffer_->GetPacket(socket_fd_); }

void ConnectObj::SendPacket(std::shared_ptr<Packet> packet) { write_buffer_->AddPacket(packet); }

std::shared_ptr<Packet> RecvBuffer::GetPacket(int socket_fd) {
  if (size_ < sizeof(uint16_t)) {  // check whether enough length for data size
    return nullptr;
  }
  uint16_t total_packet_size;
  MemcopyFromBuffer(reinterpret_cast<char *>(&total_packet_size), sizeof(uint16_t));
  if (size_ < total_packet_size + sizeof(PacketHead)) {  // check whether enough length for whole data packet
    return nullptr;
  }
  // get packet head
  PacketHead head;
  MemcopyFromBuffer(reinterpret_cast<char *>(&head), sizeof(PacketHead));
  RemoveData(sizeof(PacketHead));
  // get packet
  auto packet = std::make_shared<Packet>((Proto::MsgId)head.msg_id_, socket_fd);
  packet->ReAlloc(total_packet_size);
  char *buffer = (char *)malloc(total_packet_size);
  MemcopyFromBuffer(buffer, total_packet_size);
  RemoveData(total_packet_size);
  packet->SetMessageData(buffer, total_packet_size);
  free(buffer);
  return packet;
}

void SendBuffer::AddPacket(std::shared_ptr<Packet> packet) {
  PacketHead head;
  head.msg_id_ = packet->GetMsgId();
  head.data_size_ = packet->GetSize();
  if (GetEmptySize() <= sizeof(PacketHead)) {
    ReAlloc(sizeof(PacketHead));
  }
  MemcopyToBuffer(reinterpret_cast<char *>(&head), sizeof(PacketHead));
  FillData(sizeof(PacketHead));
  if (GetEmptySize() <= head.data_size_) {
    ReAlloc(head.data_size_);
  }
  char *buffer =  new char[head.data_size_];
  packet->MemcopyFromBuffer(buffer, head.data_size_);
  MemcopyToBuffer(buffer, head.data_size_);
  FillData(head.data_size_);
  delete[] buffer;
}
}  // namespace xac

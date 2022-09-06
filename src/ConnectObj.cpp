#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <memory>
#include "ConnectObj.h"

namespace xac {

ConnectObj::ConnectObj(int socket_fd) : socket_fd_(socket_fd) {
    read_buffer_ = new ReadBuffer();
    write_buffer_ = new WriteBuffer();
}
bool ConnectObj::Send() {
    while (true) {
        char* buffer = nullptr;
        if (write_buffer_->GetSize() <= 0) {
            return true;
        }
        buffer = (char*)malloc(write_buffer_->GetSize());
        write_buffer_->MemcopyFromBuffer(buffer, write_buffer_->GetSize());
        auto send_size = ::send(socket_fd_, buffer, sizeof(buffer), 0);
        if (send_size > 0) {
            write_buffer_->RemoveData(send_size);
            return true;
        } else {
            return false;
        }
    }
    return true;
}
bool ConnectObj::HasSendData() {
    if (write_buffer_->GetSize() > 0) {
        return true;
    }
    return false;
}
bool ConnectObj::HasRecvData() {
    if (read_buffer_->GetSize() > 0) {
        return true;
    }
    return false;
}
bool ConnectObj::Receive() {
    char* buffer = (char*)malloc(sizeof(PacketHead));
    ssize_t data_size = 0;
    while(true) {
        if (read_buffer_->GetEmptySize() <= sizeof(PacketHead)) {
            read_buffer_->ReAlloc(sizeof(PacketHead));
        }
        data_size = ::recv(socket_fd_, buffer, read_buffer_->GetEmptySize(), 0);
        if (data_size > 0) {
            if ((ssize_t)read_buffer_->GetEmptySize() <= data_size) {
                read_buffer_->ReAlloc(data_size);
            }
            std::cout << "recv " << data_size <<  std::endl;
            read_buffer_->MemcopyToBuffer(buffer, data_size);
            read_buffer_->FillData(data_size);
        } else {
            break;
        }
    }
    free(buffer);
    return true;
}

void ConnectObj::Dispose() {
    free(read_buffer_);
    free(write_buffer_);
}

ConnectObj::~ConnectObj() {
    Dispose();
}

Packet* ConnectObj::GetPacket() {
    return read_buffer_->GetPacket();
}

void ConnectObj::SendPacket(Packet* packet) {
    write_buffer_->AddPacket(packet);
}

Packet* ReadBuffer::GetPacket() {
    if (size_ < sizeof(uint16_t)) { // check whether enough length for data size
        return nullptr;
    }
    uint16_t total_packet_size;
    MemcopyFromBuffer(reinterpret_cast<char*>(&total_packet_size), sizeof(uint16_t));
    if (size_ < total_packet_size + sizeof(PacketHead)) { // check whether enough length for whole data packet
        return nullptr;
    }
    PacketHead head;
    MemcopyFromBuffer(reinterpret_cast<char*>(&head), sizeof(PacketHead));
    RemoveData(sizeof(PacketHead));
    Packet* packet = new Packet(head.msg_id_);
    packet->ReAlloc(total_packet_size);
    char* buffer = (char*)malloc(total_packet_size);
    MemcopyFromBuffer(buffer, total_packet_size);
    RemoveData(total_packet_size);
    packet->MemcopyToBuffer(buffer, total_packet_size);
    packet->FillData(total_packet_size);
    free(buffer);
    return packet;
}

void WriteBuffer::AddPacket(Packet* packet) {
    PacketHead head;
    head.msg_id_ = packet->GetMsgId();
    head.data_size_ = packet->GetSize();
    if (GetEmptySize() <= sizeof(PacketHead)) {
        ReAlloc(sizeof(PacketHead));
    }
    MemcopyToBuffer(reinterpret_cast<char*>(&head), sizeof(PacketHead));
    FillData(sizeof(PacketHead));
    if (GetEmptySize() <= head.data_size_) {
        ReAlloc(head.data_size_);
    }
    char* buffer = (char*)malloc(head.data_size_);
    packet->MemcopyFromBuffer(buffer, head.data_size_);
    MemcopyToBuffer(buffer, head.data_size_);
    FillData(head.data_size_);
    delete packet;
    free(buffer);
}
}


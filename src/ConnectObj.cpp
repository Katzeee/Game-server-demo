#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include "ConnectObj.h"

namespace xac {
ConnectObj::ConnectObj(int socket_fd) : socket_fd_(socket_fd) {
    read_buffer_ = new ReadBuffer();
    write_buffer_ = new WriteBuffer();
}
bool ConnectObj::Send() {
    write_buffer_->RemoveData(1);
    std::string buf = "data";
    ::send(socket_fd_, buf.c_str(), buf.length(), 0);
    return true;
}
bool ConnectObj::HasSendData() {
    if (write_buffer_->GetSize() > 0) {
        return true;
    }
    return false;
}
bool ConnectObj::HasRecvData() {
    return true;
}
bool ConnectObj::Receive() {
    char* buffer = new char[100];
    ssize_t data_size = 0;
    while(true) {
        memset(buffer, 0, 100);
        data_size = ::recv(socket_fd_, buffer, 100, 0);
        if (data_size > 0) {
            if ((ssize_t)read_buffer_->GetEmptySize() <= data_size) {
                read_buffer_->ReAlloc(data_size);
            }
            std::cout << "recv " << data_size <<  std::endl;
            read_buffer_->MemcopyToBuffer(buffer, data_size);
            read_buffer_->FillData(data_size);
            write_buffer_->MemcopyToBuffer(buffer, data_size);
            write_buffer_->FillData(data_size);
        } else {
            break;
        }
    }
    return true;
}

void ConnectObj::Dispose() {
    free(read_buffer_);
    free(write_buffer_);
}

ConnectObj::~ConnectObj() {
    Dispose();
}
}


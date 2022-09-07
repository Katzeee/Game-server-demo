#include <memory.h>
#include <fcntl.h>
#include "NetworkBase.h"

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
        } else {
            if (it->first == master_socket_fd_) {
                FD_CLR(master_socket_fd_, &write_fds_);
            }
        }
    }
    timeval timeout;
    memset(&timeout, 0, sizeof(timeval));
    timeout.tv_sec = 0;
    timeout.tv_usec = 50 * 1000;
    if (::select(fd_max + 1, &read_fds_, &write_fds_, & except_fds_, &timeout) <= 0) {
        return false;
    }
    for (auto it = connects_.begin(); it != connects_.end(); it++) {
        if (FD_ISSET(it->first, &except_fds_)) { // if fd has exception, close the connection
            std::cout << "except " << it->first << std::endl;
            it->second->Dispose();
            delete it->second;
            connects_.erase(it->first);
            continue;
        }
        if (FD_ISSET(it->first, &read_fds_)) {
            if (!it->second->Receive()) {
                it->second->Dispose();
                delete it->second;
                connects_.erase(it->first);
                continue;
            }
        }
        if (FD_ISSET(it->first, &write_fds_)) {
            if (!it->second->Send()) {
                it->second->Dispose();
                delete it->second;
                connects_.erase(it->first);
                continue;
            }
        }
    }
    return true;
}


void NetworkBase::SetSocketOpt(int socket) {
    bool is_reuse_addr = true;
    setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (void*)&is_reuse_addr, sizeof(is_reuse_addr));
    int net_timeout = 3000;
    setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, (void*)&net_timeout, sizeof(net_timeout));
    setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (void*)&net_timeout, sizeof(net_timeout));
    NetworkBase::SetNonBlock(socket);
}

void NetworkBase::SetNonBlock(int socket) {
    int flags = fcntl(socket, F_GETFL, 0);
    fcntl(socket, F_SETFL, flags | O_NONBLOCK);
}

NetworkBase::~NetworkBase() {
    for (auto it : connects_) {
        it.second->Dispose();
        delete it.second;
    }
}
} // end namespace xac
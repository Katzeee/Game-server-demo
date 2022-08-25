#include <memory.h>
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
        return true;
    }
    for (auto it = connects_.begin(); it != connects_.end(); it++) {
        if (FD_ISSET(it->first, &except_fds_)) { // if fd has exception, close the connection
            it->second->Dispose();
            delete it->second;
            connects_.erase(it->first);
            continue;
        }
        if (FD_ISSET(it->first, &read_fds_)) {
            if (!it->second->Receive()) {
                // TODO: Do something when fail
                continue;
            }
        }
        if (FD_ISSET(it->first, &write_fds_)) {
            if (!it->second->Send()) {
                // TODO: Do something when fail
                continue;
            }
        }
    }
    return true;
}
}
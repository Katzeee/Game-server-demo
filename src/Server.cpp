#include "Server.h"

namespace xac {


Server::Server() : is_running_(true) {
    
}

void Server::DataHandler() {
    for (auto it : connects_) {
        if (it.second->HasRecvData()) {
            auto packet = it.second->GetPacket();
            if (!packet) {
                continue;
            }
            char* buffer = (char*)malloc(packet->GetSize());
            packet->MemcopyFromBuffer(buffer, packet->GetSize());
            std::cout << "recv msgid: " << packet->GetMsgId() << " data: " << buffer << std::endl;
            free(buffer);
        }
    }

}

void Server::Update() {
    while (is_running_) {
        Select();
        if (FD_ISSET(master_socket_fd_, &read_fds_)) {
            Accept();
        }
        DataHandler();
    }
}

} // end namespace xac
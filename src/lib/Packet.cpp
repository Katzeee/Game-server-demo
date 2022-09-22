#include "Packet.h"

namespace xac {

void Packet::SetMessageData(char* src, size_t size) {
    ReAlloc(size);
    MemcopyToBuffer(src, size);
    FillData(size);
}

void Packet::SetMessageData(std::string src) {
    SetMessageData(const_cast<char*>(src.c_str()), src.length());
}

} // end namespace xac
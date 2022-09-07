#include "Packet.h"

namespace xac {

void Packet::SetMessageData(char* src, size_t size) {
    ReAlloc(size);
    MemcopyToBuffer(src, size);
    FillData(size);
}

} // end namespace xac
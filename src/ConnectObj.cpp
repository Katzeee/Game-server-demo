#include <iostream>
#include "ConnectObj.h"

namespace xac {
ConnectObj::ConnectObj() {

}
bool ConnectObj::Send() {
    return true;
}
bool ConnectObj::HasSendData() {
    return true;
}
bool ConnectObj::HasRecvData() {
    return true;
}
bool ConnectObj::Receive() {
    return true;
}
}


#include <sstream>
#include "../src/app_PCH.h"
#include "../src/ecslibserver.h"

using namespace xac;

class Robot : public NetworkConnecter {
 public:
  Robot(std::string account, const std::string password) : NetworkConnecter("127.0.0.1", 2233) {
    Connect();
    auto proto = Proto::AccountCheck();
    proto.set_account(account);
    proto.set_password(password);
    auto packet = std::make_shared<Packet>(Proto::C2L_AccountCheck, master_socket_fd_);
    packet->SerializeToBuffer(proto);
    AddPacketToList(packet);
    for (int i = 0; i < 500; i++) {
      NetworkConnecter::Update();
    }
    sleep(1);
    AddPacketToList(packet);
    for (int i = 0; i < 500; i++) {
      NetworkConnecter::Update();
    }
    //printf("send pack %s\n", account.c_str());
  }
};

int main() {
  std::vector<std::thread> tv;
  for (int i = 0; i < 500; i++) {
    auto t = std::thread([=]() {
      std::stringstream ss;
      ss << "acc" << i;
      Robot(ss.str(), "123");
    });
    tv.push_back(std::move(t));
  }
  for (auto &i : tv) {
    i.join();
  }
  return 0;
}
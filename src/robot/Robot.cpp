#include "Robot.h"

namespace xac {

void Robot::Update() {
  UpdateState();
  NetworkConnecter::Update();
}

void Robot::RegistCBFuncs() {
  auto filter_func = [&](std::shared_ptr<Packet> packet) { return this->master_socket_fd_ == packet->GetSocket(); };
  auto *message_list = new MessageListWithFilter();
  message_list->RegistCBFunc(
      Proto::C2L_AccountCheckRs,
      [&](std::shared_ptr<Packet> packet) {
        printf("get rs\n");
        this->is_logged_ = true;
      },
      filter_func);
  message_list_.reset(message_list);
}

void Robot::SendAccountRequest() {
  auto proto = Proto::AccountCheck();
  proto.set_account(account_);
  proto.set_password(password_);
  auto packet = std::make_shared<Packet>(Proto::C2L_AccountCheck, master_socket_fd_);
  packet->SerializeToBuffer(proto);
  AddPacketToList(packet);
}

auto Robot::IsLogged() -> bool { return is_logged_; }

void Robot::RegisterStates() {
  RegisterStateCreator(RobotStatesEnum::IDLE, []() { return new RobotIdle(); });
  RegisterStateCreator(RobotStatesEnum::CONNECTING, []() { return new RobotConnecting(); });
  // RegisterStateCreator(RobotStatesEnum::CONNECTED, []() { return new RobotConnected(); });
  RegisterStateCreator(RobotStatesEnum::LOGGING, []() { return new RobotLogging(); });
  RegisterStateCreator(RobotStatesEnum::TERMINATE, []() { return new RobotTerminate(); });
}

}  // end namespace xac
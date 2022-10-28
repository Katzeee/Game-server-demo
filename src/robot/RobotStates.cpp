#include "RobotStates.h"
#include <unistd.h>
#include <iostream>
#include "../protobuf/proto.h"

namespace xac {
void RobotIdle::OnEnter() { printf("new robo\n"); }

auto RobotIdle::Update() -> RobotStatesEnum { return RobotStatesEnum::CONNECTING; }

void RobotConnecting::OnEnter() { origin_object_->Connect(); }

auto RobotConnecting::Update() -> RobotStatesEnum {
  if (origin_object_->IsConnected()) {
    return RobotStatesEnum::LOGGING;
  }
  return RobotStatesEnum::TERMINATE;
}

auto RobotLogging::Update() -> RobotStatesEnum {
  if(origin_object_->IsLogged()) {
    return RobotStatesEnum::LOGGED;
  }
  origin_object_->SendAccountRequest();
  return RobotStatesEnum::LOGGING;
}

auto RobotTerminate::Update() -> RobotStatesEnum {
  sleep(5);
  return RobotStatesEnum::LOGGED;
}

}  // end namespace xac
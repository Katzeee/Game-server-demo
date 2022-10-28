#pragma once
#include <cstdint>
#include "../ecslib/StateMachineBase.h"
#include "Robot.h"

enum class RobotStatesEnum;


namespace xac {

class Robot;

using RobotStateBase = StateBase<RobotStatesEnum, Robot>;

class RobotIdle : public RobotStateBase {
 public:
  void OnEnter() override;
  auto Update() -> RobotStatesEnum override;
};

class RobotConnecting : public RobotStateBase {
 public:
  void OnEnter() override;
  auto Update() -> RobotStatesEnum override;
};

class RobotConnected : public RobotStateBase {
 public:
  auto Update() -> RobotStatesEnum override;
};

class RobotLogging : public RobotStateBase {
 public:
  auto Update() -> RobotStatesEnum override;
};

class RobotLogged : public RobotStateBase {
 public:
  void OnEnter() override;
  void OnExit() override;
  auto Update() -> RobotStatesEnum override;
};

class RobotTerminate : public RobotStateBase {
 public:
  auto Update() -> RobotStatesEnum override;
};

}  // end namespace xac
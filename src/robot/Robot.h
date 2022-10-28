#pragma once
#include "../ecslibserver.h"
#include "RobotStates.h"

//TODO(xac):put enum class into namespace

enum class RobotStatesEnum {
  IDLE = 0,
  CONNECTING,
  CONNECTED,
  LOGGING,
  LOGGED,
  TERMINATE,
};

namespace xac {

class Robot : public IPoolObject<Robot>,
              public NetworkConnecter,
              public IMessageComponent,
              public StateMachineBase<RobotStatesEnum, Robot> {
 public:
  using IPoolObject<Robot>::SetPool;
  Robot() : NetworkConnecter("127.0.0.1", 2233), StateMachineBase(RobotStatesEnum::IDLE) {
      RegisterStates();
  }
  virtual ~Robot() = default;
  void Reset() override {}
  void Update() override;
  void RegistCBFuncs() override;
  void SendAccountRequest();
  auto IsLogged() -> bool;
  void RegisterStates();

 private:
  std::string account_ = "test";
  bool is_logged_ = false;
  std::string password_ = "123456";
};

}  // end namespace xac
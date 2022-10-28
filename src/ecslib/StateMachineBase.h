#pragma once
#include <functional>
#include <map>
#include <memory>

namespace xac {

// states change because of class T changed, so we must add T as a template varible to get the real states of class T
template <typename StatesEnum, typename T>
class StateBase {
 public:
  virtual void OnEnter(){};
  virtual void OnExit(){};
  virtual auto Update() -> StatesEnum = 0;
  virtual ~StateBase() = default;
  void SetOriginObject(T *origin_object) { origin_object_ = origin_object; }

 protected:
  T *origin_object_;  // to get the states of T
};

template <typename StatesEnum, typename T>
class StateMachineBase {
 public:
  using StateCreateFunc = std::function<StateBase<StatesEnum, T> *(void)>;
  explicit StateMachineBase(StatesEnum default_state) : default_state_(default_state) {}
  void ChangeState(StatesEnum state) {
    auto creator = state_creator_[state];
    if (state_obj_) {
      state_obj_->OnExit();
    }
    auto origin_obj = static_cast<T *>(this);
    assert(origin_obj);
    state_obj_ = std::unique_ptr<StateBase<StatesEnum, T>>();
    state_obj_.reset(creator());
    state_obj_->SetOriginObject(origin_obj);
    state_obj_->OnEnter();
    cur_state_ = state;
  }
  void UpdateState() {
    if (!state_obj_) {
      ChangeState(default_state_);
      // state_obj_ = std::unique_ptr<StateBase<StatesEnum>>(state_creator_[default_state_]());
      // cur_state_ = default_state_;
    }
    auto state = state_obj_->Update();
    if (state != cur_state_) {
      ChangeState(state);
    }
  }
  void RegisterStateCreator(StatesEnum state, StateCreateFunc create_func) { state_creator_[state] = create_func; }

 protected:
  StatesEnum cur_state_;
  StatesEnum default_state_;
  std::map<StatesEnum, StateCreateFunc> state_creator_;
  std::unique_ptr<StateBase<StatesEnum, T>> state_obj_;
};

}  // end namespace xac

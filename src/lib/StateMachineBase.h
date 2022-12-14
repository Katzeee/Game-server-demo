#pragma once
#include <memory>
#include <map>
#include <functional>

namespace xac {

template<typename StatesEnum>
class StateBase {
public:
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual StatesEnum Update() = 0;
};

template<typename StatesEnum>
class StateMachineBase {
public:
    using StateCreateFunc = std::function<StateBase<StatesEnum>*(void)>;
    StateMachineBase(StatesEnum default_state) : default_state_(default_state) {}
    void ChangeState(StatesEnum state) {
        auto creator = state_creator_[state];
        if (state_obj_) {
            state_obj_->OnExit();
        }
        state_obj_ = std::unique_ptr<StateBase<StatesEnum>>(creator());
        state_obj_->OnEnter();
        cur_state_ = state;

    }
    void Update() {
        if (!state_obj_) {
            ChangeState(default_state_);
            //state_obj_ = std::unique_ptr<StateBase<StatesEnum>>(state_creator_[default_state_]());
            //cur_state_ = default_state_;
        }
        auto state = state_obj_->Update();
        if (state != cur_state_) {
            ChangeState(state);
        }
    }
    void RegisterStateCreator(StatesEnum state, StateCreateFunc create_func) {
        state_creator_[state] = create_func;
    }
private:
    StatesEnum cur_state_;
    StatesEnum default_state_;
    std::map<StatesEnum, StateCreateFunc> state_creator_;
    std::unique_ptr<StateBase<StatesEnum>> state_obj_;
};

} // end namespace xac

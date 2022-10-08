#include <iostream>
#include "../src/lib/StateMachineBase.h"

using namespace xac;

enum class TestStateEnum : uint8_t {
    First,
    Second,
    Third
};

class TestStates : public StateBase<TestStateEnum> {
public:
    void OnEnter() override {}
    void OnExit() override {}
};

class FirstState : public TestStates {
public:
    void OnEnter() override {
        std::cout << "enter first" << std::endl;
    }
    void OnExit() override {
        std::cout << "exit first" << std::endl;
    }

    TestStateEnum Update() override {
        return TestStateEnum::Second;
    }

    static FirstState* Create() { return new FirstState(); }
};

class SecondState : public TestStates {
public:
    void OnEnter() override {
        std::cout << "enter second" << std::endl;
    }
    void OnExit() override {
        std::cout << "exit second" << std::endl;
    }

    TestStateEnum Update() override {
        return TestStateEnum::Second;
    }

    static SecondState* Create() { return new SecondState(); }
};

class Mgr : public StateMachineBase<TestStateEnum> {
public:
    Mgr(TestStateEnum d_s) : StateMachineBase(d_s) {}
};


int main() {
    auto mgr = new Mgr(TestStateEnum::First);
    mgr->RegisterStateCreator(TestStateEnum::First, FirstState::Create);
    mgr->RegisterStateCreator(TestStateEnum::Second, SecondState::Create);
    while(true) {
        mgr->Update();
    }
    delete mgr;
    return 0;
}


#include "../../src/libserver.h"
using namespace xac;


class Robot : public NetworkConnecter {
public:
    Robot() {
        ThreadManager::Instance();
        auto message_list = std::make_shared<MessageListWithFilter>();
        auto filter_func = [this](std::shared_ptr<Packet> packet){
            return this->master_socket_fd_ == packet->GetSocket();
        };
        message_list->RegistCBFunc(Proto::C2L_AccountCheckRs, [](std::shared_ptr<Packet> pakcet){
            auto proto = pakcet->ParseToProto<Proto::AccountCheckRs>();
            std::cout << "rs code: " << proto.return_code() << std::endl;
        }, filter_func);
        message_list_ = message_list;
    }

    void Update() override {
        NetworkConnecter::Update();

        if (message_list_->HaveMessage()) {
            message_list_->HandleMessages();
        }
    }

};

class RobotManager : public ServerApp {
public:
    RobotManager(APP_TYPE app_type) : ServerApp(app_type) {}
    void InitApp() override {
        auto robot1 = new Robot();
        auto robot2 = new Robot();
        robot1->Connect("127.0.0.1", 2233);
        robot2->Connect("127.0.0.1", 2233);
        ThreadManager::Instance();
        thread_manager_ = ThreadManager::GetInstance();
        thread_manager_->AddObjToThread(robot1);
        thread_manager_->AddObjToThread(robot2);
    }
    void StartAllThread() override {
        thread_manager_->StartAllThread();
    }
    void Run() {
        while(1);
    }

};

int main() {
    auto robot_mgr = new RobotManager(1);
    robot_mgr->InitApp();
    robot_mgr->StartAllThread();
    robot_mgr->Run();
    return 0;
}
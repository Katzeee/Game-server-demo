#include "../../src/libserver.h"

using namespace xac;


class TestMsgHandler : public ThreadObj {
public:
    void HandleTestMsg(std::shared_ptr<Packet> packet) {

    }

    void Init() override {
        message_list_ = std::make_shared<MessageListHandleAll>();
        message_list_->RegistCBFunc(Proto::MI_TestMsg, [](std::shared_ptr<Packet> packet) {
            auto proto = packet->ParseToProto<Proto::TestMsg>();
            std::cout << "id: " << proto.index() << ", msg: " <<  proto.msg() << std::endl;
        });
    }
    void Update() override {
        if (message_list_->HaveMessage()) {
            message_list_->HandleMessages();
        }
    }
};

class MsgTestApp : public ServerApp { 
public:
    MsgTestApp(APP_TYPE app_type) : ServerApp(app_type) {
        ThreadManager::Instance();
        thread_manager_ = ThreadManager::GetInstance();
        auto network_listener = new NetworkListener();
        network_listener->Listen("127.0.0.1", 2233);
        thread_manager_->AddObjToThread(network_listener);
    }
    ~MsgTestApp() override { Dispose(); }
    void InitApp() override {
        auto test_msg_handler = new TestMsgHandler();
        test_msg_handler->Init();
        thread_manager_->AddObjToThread(test_msg_handler);
    }
    void Dispose() override {}
    void StartAllThread() override {
        thread_manager_->StartAllThread();
    }
    void Run() override { while(1); }
};

int main() {
    auto msg_test_app = new MsgTestApp(1);
    msg_test_app->InitApp();
    msg_test_app->StartAllThread();
    msg_test_app->Run();
    return 0;
}

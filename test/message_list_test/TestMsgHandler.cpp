#include "../../src/libserver.h"

using namespace xac;


class TestMsgHandler : public ThreadObj {
public:

    void Init() override {
        auto message_list = std::make_shared<MessageList>();
        message_list->RegistCBFunc(Proto::MI_TestMsg, [](std::shared_ptr<Packet> packet) {
            auto proto = packet->ParseToProto<Proto::TestMsg>();
            std::cout << "index: " << proto.index() << ", msg: " <<  proto.msg()  << ", socket: " << packet->GetSocket() << std::endl;
            Proto::AccountCheckRs proto_rs;
            proto_rs.set_return_code(Proto::AccountCheckRs_ReturnCode_ARC_UNKNOWN);
            auto packet_rs = std::make_shared<Packet>(Proto::C2L_AccountCheckRs, packet->GetSocket());
            packet_rs->SerializeToBuffer(proto_rs);
            ThreadManager::GetInstance()->SendPacket(packet_rs);
        });
        message_list_ = message_list;
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
        thread_manager_->AddNetworkToThread(network_listener);
    }
    ~MsgTestApp() override {}
    void InitApp() override {
        auto test_msg_handler = new TestMsgHandler();
        test_msg_handler->Init();
        thread_manager_->AddObjToThread(test_msg_handler);
        //thread_manager_->AddObjToThread(test_msg_handler);
    }
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

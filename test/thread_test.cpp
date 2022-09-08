#include "../src/ThreadManager.h"
#include "../src/ThreadObj.h"

using namespace xac;


class OneObj : public ThreadObj {
public:
    void Init() {}
    void Update() {
        std::cout << "update" << std::endl;
    }
};

class TwoObj : public ThreadObj {
public:
    void Init() {}
    void Update() {
        std::cout << "update2" << std::endl;
    }
};

int main() {
    ThreadManager::Instance();
    auto thread_manager = ThreadManager::GetInstance();
    //thread_manager->NewThread();
    auto one_obj = new OneObj();
    thread_manager->AddObjToThread(one_obj);
    auto two_obj = new TwoObj();
    thread_manager->AddObjToThread(two_obj);
    thread_manager->StartAllThread();
    while(1);
}
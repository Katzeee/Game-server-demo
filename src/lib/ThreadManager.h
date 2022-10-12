#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <vector>
#include "Thread.h"
#include "NetworkBase.h"
#include "ThreadObj.h"
#include "Singleton.h"
#include "IDisposable.h"

namespace xac {

class ThreadManager : public Singleton<ThreadManager> {
public:
    ThreadManager();
    ~ThreadManager() {}
    void StartAllThread();
    void CreateThread();
    void AddObjToThread(ThreadObj* thread_obj);
    void AddNetworkToThread(NetworkBase* network);
    void DispatchPacket(std::shared_ptr<Packet> packet);
    void SendPacket(std::shared_ptr<Packet> packet);
    bool IsLoop();
private:
    Thread* GetLeastObjThread();
    std::mutex mutex_;
    std::vector<Thread*> threads_;
    NetworkBase* network_;
};

} // end namespace xac
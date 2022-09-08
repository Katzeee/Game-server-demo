#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <vector>
#include "Thread.h"
#include "ThreadObj.h"
#include "Singleton.h"
#include "IDisposable.h"

namespace xac {

class ThreadManager : public Singleton<ThreadManager> {
public:
    ThreadManager();
    ~ThreadManager() {}
    void StartAllThread();
    void NewThread();
    void AddObjToThread(ThreadObj* thread_obj);
    bool IsLoop();
private:
    Thread* GetLeastObjThread();
    std::mutex lock_;
    std::vector<Thread*> threads_;
};

} // end namespace xac
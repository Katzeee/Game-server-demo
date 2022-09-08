#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include "Thread.h"
#include "ThreadObj.h"
#include "Singleton.h"
#include "IDisposable.h"

namespace xac {

class ThreadManager : public Singleton<ThreadManager> {
public:
    ThreadManager() = default;
    ~ThreadManager() {}
    void StartAllThread();
    void NewThread();
    void AddObjToThread(ThreadObj* thread_obj);
private:
    std::mutex thread_lock_;
    std::list<Thread*> threads_;
};

} // end namespace xac
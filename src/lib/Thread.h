#pragma once
#include <thread>
#include <list>
#include <mutex>
#include "IDisposable.h"
#include "ThreadObj.h"

namespace xac {

class Thread : public IDisposable {
public:
    Thread();
    ~Thread();
    void Dispose();
    void Start(); // start thread
    void Update(); // update function
    void Stop(); // stop thread
    void AddThreadObj(ThreadObj* thread_obj); // add a thread object to this thread
    void DispatchMessage(std::shared_ptr<Packet> packet);
    bool IsRunning() { return is_running_; } // check if this thread is running
    size_t ThreadObjCount() { return thread_objs_.size(); } // return the count of thread objects on this thread
private:
    bool is_running_ = false;
    std::thread* thread_ = nullptr;
    std::mutex lock_;
    std::list<ThreadObj*> thread_objs_;
};

} // end namespace xac
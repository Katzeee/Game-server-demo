#pragma once
#include <thread>
#include <list>
#include <mutex>

#include "EntitySystem.h"

namespace xac {

class Thread : public EntitySystem {
public:
    Thread() = default;
    ~Thread() override;
    void Start(); // start thread
    void Stop(); // stop thread
    auto IsRunning() -> bool { return is_running_; } // check if this thread is running
    // size_t ThreadObjCount() { return thread_objs_.size(); } // return the count of thread objects on this thread
private:
    bool is_running_ = false;
    std::thread* thread_ = nullptr;
    std::mutex lock_;
};

} // end namespace xac
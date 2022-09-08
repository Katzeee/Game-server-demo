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
    void Start();
    static void Update(Thread* this_class);
    void Stop();
    void AddThreadObj(ThreadObj* thread_obj);

private:
    bool is_running_ = false;
    std::thread* thread_ = nullptr;
    std::mutex thread_lock_;
    std::list<ThreadObj*> thread_objs_;
};

} // end namespace xac
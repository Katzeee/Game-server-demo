#pragma once
#include "ThreadManager.h"
#include "IDisposable.h"

namespace xac {

class ServerApp : public IDisposable {
public:
    using APP_TYPE = uint16_t;
    // ServerApp() = delete;
    ServerApp(APP_TYPE app_type) : app_type_(app_type) {}
    ~ServerApp() override {}
    void Dispose() override {}
    virtual void InitApp() = 0;
    virtual void StartAllThread() = 0;
    virtual void Run() = 0;

protected:
    ThreadManager* thread_manager_;
    APP_TYPE app_type_;
};

} // end namespace xac
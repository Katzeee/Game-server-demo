#pragma once
#include "ThreadManager.h"
#include "IDisposable.h"

namespace xac {

class ServerApp : public IDisposable {
public:
    using APP_TYPE = uint16_t;
    ServerApp(APP_TYPE app_type);
    ~ServerApp();
    void Dispose() override;
    virtual void InitApp() = 0;
    void StartAllThread();
    void Run();

protected:
    ThreadManager* thread_manager_;
    APP_TYPE app_type_;
};

} // end namespace xac
#pragma once
#include "IDisposable.h"

namespace xac {

class ThreadObj : public IDisposable {
public:
    ~ThreadObj() {}
    void Dispose() override {}
    virtual void Init() = 0;
    virtual void Update() = 0;
private:
    
};

} // end namespace xac
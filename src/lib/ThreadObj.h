#pragma once
#include "IDisposable.h"
#include "MessageHandler.h"

namespace xac {

class ThreadObj : public MessageHandler {
public:
    virtual ~ThreadObj() = default;
    virtual void Init() = 0;
    virtual void Update() = 0;

};

} // end namespace xac
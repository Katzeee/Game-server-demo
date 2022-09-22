#pragma once
#include "../libserver.h"

namespace xac {
    
class Account : public ThreadObj {
public:
    void Init() override;
    void Update() override;
};

} // end namespace xac

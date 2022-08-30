#pragma once
namespace xac {
class IDisposable {
public:
    virtual ~IDisposable() = default;
    virtual void Dispose() = 0;
};
}
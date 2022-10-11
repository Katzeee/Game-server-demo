#pragma once
#include <exception>
#include <iostream>
#include <error.h>

namespace xac {

template<typename T>
class Singleton {
public:
    template<typename... Args>
    static T* Instance(Args&&... args) {
        if (instance_ == nullptr) {
            instance_ = new T(std::forward(args)...);
        }
        return instance_;
    }
    static T* GetInstance() {
        if (instance_ == nullptr) {
            throw std::logic_error("No instance!");
            //Instance();
        }
        return instance_;
    }
    static void DestroyInstance() {
        delete instance_;
        instance_ = nullptr;
    }
private:
    static T* instance_;

};

template<typename T>
T* Singleton<T>::instance_ = Singleton<T>::Instance();

} // end namespace xac
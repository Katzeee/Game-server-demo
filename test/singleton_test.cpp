#include "../src/ThreadManager.h"
using namespace xac;

int main() {
    ThreadManager::Instance();
    ThreadManager* thread_manager = ThreadManager::GetInstance();
    thread_manager->StartAllThread();
    ThreadManager::DestroyInstance();
}
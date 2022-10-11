#pragma once
#include <iostream>

namespace xac {

// static void* malloc(size_t size) {
//     std::cout << "malloc " << size << std::endl;
//     return ::malloc(size);
// }

// static void free(void* ptr) {
//     std::cout << "free " << std::endl;
//     ::free(ptr);
// }
class BufferBase {
 protected:
  char *buffer_ = nullptr;
  size_t start_ = 0;  // buffer start position
  size_t end_ = 0;    // buffer end position
  size_t size_ = 0;   // buffer size
  // when end_ == start_, buffer is empty
  size_t capacity_ = 0;  // buffer capacity
 public:
  BufferBase();
  explicit BufferBase(size_t size);
  virtual ~BufferBase();
  auto GetSize() -> size_t;
  auto GetCapacity() -> size_t;
  virtual void ReAlloc(size_t size);
  virtual auto GetEmptySize() -> size_t;
  virtual auto MemcopyFromBuffer(char *des, size_t size) -> bool;
  virtual auto MemcopyToBuffer(char *src, size_t size) -> bool;
  virtual auto FillData(size_t size) -> bool;
  virtual auto RemoveData(size_t size) -> bool;
  virtual auto GetBufferEndAddr() -> char *;
  virtual auto GetBufferStartAddr() -> char *;
};

class RingBuffer : public BufferBase {
 public:
  RingBuffer() = default;
  explicit RingBuffer(size_t size) : BufferBase(size) {}
  ~RingBuffer() override = default;
  auto MemcopyFromBuffer(char *des, size_t size) -> bool override;
  auto MemcopyToBuffer(char *src, size_t size) -> bool override;
  auto RemoveData(size_t size) -> bool override;
  auto FillData(size_t size) -> bool override;
  auto GetEmptySize() -> size_t override;
};

class NormalBuffer : public BufferBase {
 public:
  NormalBuffer() = default;
  explicit NormalBuffer(size_t size) : BufferBase(size) {}
  ~NormalBuffer() override;
};

}  // namespace xac

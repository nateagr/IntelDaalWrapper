#include <algorithm>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

template<typename T>
class ThreadsafeQueue {
  std::queue<T> queue_;
  mutable std::mutex mutex_;

  // Moved out of public interface to prevent races between this
  // and pop().
  bool empty() const {
    return queue_.empty();
  }

 public:
  ThreadsafeQueue() = default;

  virtual ~ThreadsafeQueue() noexcept(false) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!empty()) {
      throw;
    }
  }

  unsigned long size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
  }

  T pop() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) {
      throw;
    }
    T tmp = queue_.front();
    queue_.pop();
    return tmp;
  }

  void push(const T &item) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(item);
  }
};

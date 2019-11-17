#ifndef BLOCKINGQUEUE_H_
#define BLOCKINGQUEUE_H_

#include <stdint.h>   // uint32_t
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

template<class T>
class BlockingQueue {
  std::mutex mtx;
  std::condition_variable empty_cv, full_cv;
  std::queue<T> q;
  size_t max_size;
  bool closed;

  public:
  explicit BlockingQueue(int size)
    : mtx(), empty_cv(), full_cv(), q(), max_size(size), closed(false)
  {}

  // Non-copyable
  BlockingQueue(const BlockingQueue&) = delete;
  BlockingQueue& operator=(const BlockingQueue&) = delete;

  void push(T&& x) {
    std::unique_lock<std::mutex> lock(mtx);
    while (q.size() == max_size && !closed)
      full_cv.wait(lock);

    if (closed) throw std::runtime_error("trying to push to a closed queue");

    q.push(std::move(x));
    empty_cv.notify_all();
  }

  bool trypop(T* out) {
    std::unique_lock<std::mutex> lock(mtx);
    while ((q.size() == 0) && !closed)
      empty_cv.wait(lock);

    if (q.size() == 0)
      return false;

    *out = std::move(q.front());
    q.pop();
    full_cv.notify_all();
    return true;
  }

  // Delete all items in the queue
  void clear() {
    std::unique_lock<std::mutex> lock(mtx);
    // std::queue does not have a clear method, and we are not supposed to know
    // what the container underlying this template actually is. Some research
    // suggests that it is a standard idiom to create a temporary empty queue
    // and swap its contents with the queue we want to clear. When the
    // (no longer empty) queue goes out of scope it will handle item deletion
    // for us.
    std::queue<T>().swap(q);
  }

  void swap(std::queue<T>& other) {
    std::unique_lock<std::mutex> lock(mtx);
    q.swap(other);
  }

  void close() {
    std::unique_lock<std::mutex> lock(mtx);
    closed = true;
    empty_cv.notify_all();
    full_cv.notify_all();
  }
};

#endif // BLOCKINGQUEUE_H_

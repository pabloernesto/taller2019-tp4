#ifndef FRAMEDROPPER_H_
#define FRAMEDROPPER_H_

#include <mutex>
#include <condition_variable>

// Example workflow for the producer:
// while (true) {
//   auto b = fd.GetBuffer();
//   memcpy(b, other_b, n);
//   fd.Produce();
// }
//
// Example workflow for the consumer:
// while (true) {
//   auto b = fd.Consume();
//   do something with b...
// }
template<class T>
class FrameDropper {
  T buffers[3];

  T* consuming;    // buffer currently used by the producer
  T* producing;    // buffer currently used by the consumer
  T* next;         // buffer currently in wait to be consumed

  std::mutex m;
  std::condition_variable cv;

  bool closed = false;

public:
  bool Consume(T** output) {
    std::unique_lock<std::mutex> lock(m);
    while (!next && !closed) cv.wait(lock);

    if (closed) return false;

    consuming = next;
    next = nullptr;

    *output = consuming;
    return true;
  }

  // This function is not meant to be called repeatedly in sequence,
  // call Produce after using the returned buffer
  T& GetBuffer() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& p : buffers)
      if (&p != consuming && &p != next) {
        producing = &p;
        break;
      }
    return *producing;
  }

  void Produce() {
    std::lock_guard<std::mutex> lock(m);
    // If next has not been consumed yet, ignore it
    next = producing;
    producing = nullptr;
    cv.notify_one();
  }

  void close() {
    std::lock_guard<std::mutex> lock(m);
    closed = true;
    cv.notify_one();
  }
};

#endif  // FRAMEDROPPER_H_

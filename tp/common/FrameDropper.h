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
class FrameDropper {
  void* buffers[3];

  void* consuming;    // buffer currently used by the producer
  void* producing;    // buffer currently used by the consumer
  void* next;         // buffer currently in wait to be consumed

  std::mutex m;
  std::condition_variable cv;

public:
  void* Consume() {
    std::unique_lock<std::mutex> lock(m);
    while (!next) cv.wait(lock);

    consuming = next;
    next = nullptr;

    return consuming;
  }

  // This function is not meant to be called repeatedly in sequence,
  // call Produce after using the returned buffer
  void* GetBuffer() {
    std::lock_guard<std::mutex> lock(m);
    for (auto p : buffers)
      if (p != consuming && p != next) {
        producing = p;
        break;
      }
    return producing;
  }

  void Produce() {
    std::lock_guard<std::mutex> lock(m);
    // If next has not been consumed yet, ignore it
    next = producing;
    producing = nullptr;
    cv.notify_one();
  }

  FrameDropper(int size) {
    for (int i = 0; i < 3; i++)
      buffers[i] = new char[size];
  }

  ~FrameDropper() {
    for (int i = 0; i < 3; i++)
      delete[] buffers[i];
  }
};

#endif  // FRAMEDROPPER_H_

#ifndef SYNCHRONIZEDSTORAGE_H_
#define SYNCHRONIZEDSTORAGE_H_

#include <mutex>
#include <condition_variable>

template<class T>
class SynchronizedStorage {
  bool set;
  T data;
  std::mutex m;
  std::condition_variable cv;

public:
  T get() {
    std::unique_lock<std::mutex> lock(m);
    while (!set) cv.wait(lock);

    set = false;
    return std::move(data);
  }

  bool tryset_drop(T&& data) {
    std::lock_guard<std::mutex> lock(m);
    if (set) return;

    this->data = data;
    set = true;
    cv.notify_one();
  }

  bool tryset_overwrite(T&& data) {
    std::lock_guard<std::mutex> lock(m);
    this->data = data;
    set = true;
    cv.notify_one();
  }
};

#endif  // SYNCHRONIZEDSTORAGE_H_

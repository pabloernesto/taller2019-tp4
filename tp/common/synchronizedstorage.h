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

  // Try to set the value of data. If data was already set, do nothing.
  // Returns true if data was already set.
  bool tryset_dropnew(T&& data) {
    std::lock_guard<std::mutex> lock(m);
    if (set) return true;

    this->data = data;
    set = true;
    cv.notify_one();
    return false;
  }

  // Try to set the value of data. If data was already set, overwrite it.
  // Returns true if data was already set.
  bool tryset_dropold(T&& data) {
    std::lock_guard<std::mutex> lock(m);
    auto old_set = set;
    set = true;

    this->data = data;
    cv.notify_one();
    return old_set;
  }
};

#endif  // SYNCHRONIZEDSTORAGE_H_

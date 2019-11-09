#ifndef RESPONSIBILITY_H_
#define RESPONSIBILITY_H_

#include <memory>

// This file describes the public interface of a Chain of Responsibility
// pattern implementation.

class TaskHandler {
  // Each handler may choose to ignore a given task, which will be passed on
  // to the next handler in line.
  // When a handler is destroyed, unique_ptr ensures that subordinate handlers
  // will be destroyed too.
  std::unique_ptr<TaskHandler> next;

public:
  // Template method that defines handler chaining logic
  void Handle(void* t);

  // Subclasses should call this method on their initializer lists
  // WARNING: the constructed TaskHandler will take ownership of next.
  //   Do not explicitly destroy next.
  TaskHandler(TaskHandler* next);

  virtual ~TaskHandler();


  // Subclasses of TaskHandler must implement the following virtual methods

  // Return true if the handler should handle the given task
  virtual bool ShouldHandle(void* t) = 0;

  // Handle the task, return true if the task should additionally be passed
  // onwards through the chain
  virtual bool OnHandle(void* t) = 0;
};

#endif  // RESPONSIBILITY_H_

#include "Responsibility.h"

void TaskHandler::Handle(void* t) {
  bool pass_on = true;

  if (ShouldHandle(t))
    pass_on = OnHandle(t);

  if (next && pass_on)
    next->Handle(t);
}

TaskHandler::TaskHandler(TaskHandler* next) : next(next) {}

TaskHandler::~TaskHandler() {}

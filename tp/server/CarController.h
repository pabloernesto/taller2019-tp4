#ifndef _CARCONTROLLER_H_
#define _CARCONTROLLER_H_
#include "../common/Responsibility.h"
#include "Car.h"

class CarController : public TaskHandler{

  private:
    Car& car;

  public:
    CarController(TaskHandler* next, Car& car);
    virtual bool ShouldHandle(void* t) override;
    virtual bool OnHandle(void* t) override;

};

#endif
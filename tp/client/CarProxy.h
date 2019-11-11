#ifndef _CARPROXY_H_
#define _CARPROXY_H_
#include <string>

class CarProxy {
  private:
    void sendMethod(std::string method);

  public:
    CarProxy();
    void GasOn();
    void GasOff();
    void BreakOn();
    void BreakOff();
    void SteerRight();
    void SteerLeft();
    void SteerCenter();
};

#endif

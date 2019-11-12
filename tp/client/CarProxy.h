#ifndef _CARPROXY_H_
#define _CARPROXY_H_
#include <string>
#include <vector>
#include "../common/blockingqueue.h"

class CarProxy {
  private:
    BlockingQueue<std::string>& outqueue;
    float x;
    float y;
    float angle;
    float size_x;
    float size_y;
    bool dead;
    int id;
    std::mutex m;
    
    void sendMethod(std::string method);

  public:
    CarProxy(BlockingQueue<std::string>& outqueue, float x, float y, float angle, float size_x, float size_y, int id);
    std::vector<float> GetPosition();
    std::vector<float> GetSize();
    void update(float x, float y, float angle, float size_x, float size_y, bool dead);
    int GetId();
    bool isDead();
    void GasOn();
    void GasOff();
    void BreakOn();
    void BreakOff();
    void SteerRight();
    void SteerLeft();
    void SteerCenter();
};

#endif

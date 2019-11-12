#ifndef _MODIFIERPROXY_H_
#define _MODIFIERPROXY_H_
#include <vector>

class ModifierProxy {
  
  private:
    float x;
    float y;
    float size_x;
    float size_y;
    
  public:
    ModifierProxy(float x, float y, float size_x, float size_y);
    std::vector<float> GetPosition();
    std::vector<float> GetSize();

};

#endif
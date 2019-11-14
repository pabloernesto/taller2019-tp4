#ifndef _MODIFIERPROXY_H_
#define _MODIFIERPROXY_H_
#include <vector>
#include <string>

class ModifierProxy {
  
  private:
    float x;
    float y;
    float size_x;
    float size_y;
    std::string type;
    
  public:
    ModifierProxy(float x, float y, float size_x, float size_y, std::string type);
    std::vector<float> GetPosition();
    std::vector<float> GetSize();
    std::string getType();

};

#endif
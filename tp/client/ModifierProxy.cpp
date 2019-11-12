#include "ModifierProxy.h"


ModifierProxy::ModifierProxy(float x, float y, float size_x, float size_y, std::string type) :
            x(x), y(y), size_x(size_x), size_y(size_y), type(type){}

std::vector<float> ModifierProxy::GetPosition(){
  std::vector<float> v;
  v.push_back(this->x);
  v.push_back(this->y);
  return v;
}

std::vector<float> ModifierProxy::GetSize(){
  std::vector<float> v;
  v.push_back(this->size_x);
  v.push_back(this->size_y);
  return v;
}

std::string ModifierProxy::getType(){
  return this->type;
}


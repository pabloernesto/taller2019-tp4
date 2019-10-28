#include "Point.h" 
#define SPEED 2

Point::Point(int x, int y) :  x(x), y(y), speed(SPEED){}

void Point::moveUp(){
  this->y += this->speed;
}

void Point::moveDown(){
  this->y -= this->speed;
}

void Point::moveRight(){
  this->x += this->speed;
}

void Point::moveLeft(){
  this->x -= this->speed;
}

std::vector<int> Point::getPosition(){
  std::vector<int> r;
  r.push_back(this->x);
  r.push_back(this->y);
  return r;
}

/*
    size_t getX(){
      return this->x;
    }

    size_t getY(){
      return this->y;
    }
Supongamos que esto no lo tengo por ahora...
*/

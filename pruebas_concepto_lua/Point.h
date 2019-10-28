#ifndef _POINT_H_
#define _POINT_H_
#include <string>
#include <vector>

class Point{
  private:
    int x;
    int y;
    size_t speed;

  public:
    Point(int x, int y);
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    std::vector<int> getPosition();
};

#endif

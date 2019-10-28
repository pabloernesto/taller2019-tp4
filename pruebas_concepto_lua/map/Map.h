#ifndef _MAP_H_
#define _MAP_H_
#include <vector>
#include "Point.h"

class Map{

  private:
    std::vector<Point> map;
    size_t width;
    size_t height;
    size_t findPoint(size_t x, size_t y);
    bool isValidPos(int x, int y);

  public:
    Map(size_t w, size_t h);
    void addPoint(size_t x, size_t y);
    void moveUpPoint(size_t x, size_t y);
    void moveDownPoint(size_t x, size_t y);
    void moveRightPoint(size_t x, size_t y);
    void moveLeftPoint(size_t x, size_t y);
    std::vector<std::vector<int>> getPositions();
    // Alguna especie de getter para saber donde estan los puntos?
    ~Map();

};

#endif

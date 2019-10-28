#include <iostream>
#include <fstream>
#include <vector>
// #include "Map.h"
#include "Point.h"
#include "ai.h"
// #define MAX_X 20
// #define MAX_Y 20

int main(int argc, char** argv){
  Point p(0,0);
  // map.addPoint(0,0);
  Ai ai(p);
  ai.run();
  return 0;
}
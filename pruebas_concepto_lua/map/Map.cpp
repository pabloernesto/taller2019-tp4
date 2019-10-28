#include "Map.h"
#include <unordered_map>
#include <tuple>

Map::Map(size_t w, size_t h) : width(w), height(h){}

void Map::addPoint(size_t x, size_t y){
  if (x > this->width || y > this->height){
    // exception
  }
  this->map.push_back(Point(x, y));
}

void Map::moveUpPoint(size_t x, size_t y){
  std::vector<int> old_pos = this->map[this->findPoint(x,y)].getPosition(); 
  this->map[this->findPoint(x,y)].moveUp();
  std::vector<int> new_pos = this->map[this->findPoint(x,y)].getPosition();
  if (!this->isValidPos(new_pos[0], new_pos[1])){
    this->map[this->findPoint(new_pos[0], new_pos[1])] = Point(old_pos[0], old_pos[1]);
    // Que pasa si hay dos en el mismo lugar?
  }

}

bool Map::isValidPos(int x, int y){
  return (x < 0) || (x >= this->width) || (y < 0) || (y >= this->height);
}

void Map::moveDownPoint(size_t x, size_t y){
  std::vector<int> old_pos = this->map[this->findPoint(x,y)].getPosition(); 
  this->map[this->findPoint(x,y)].moveDown();
  std::vector<int> new_pos = this->map[this->findPoint(x,y)].getPosition();
  if (!this->isValidPos(new_pos[0], new_pos[1])){
    this->map[this->findPoint(new_pos[0], new_pos[1])] = Point(old_pos[0], old_pos[1]);
    // Que pasa si hay dos en el mismo lugar?
  }
}

void Map::moveLeftPoint(size_t x, size_t y){
  std::vector<int> old_pos = this->map[this->findPoint(x,y)].getPosition(); 
  this->map[this->findPoint(x,y)].moveLeft();
  std::vector<int> new_pos = this->map[this->findPoint(x,y)].getPosition();
  if (!this->isValidPos(new_pos[0], new_pos[1])){
    this->map[this->findPoint(new_pos[0], new_pos[1])] = Point(old_pos[0], old_pos[1]);
    // Que pasa si hay dos en el mismo lugar?
  }
}

void Map::moveRightPoint(size_t x, size_t y){
  std::vector<int> old_pos = this->map[this->findPoint(x,y)].getPosition(); 
  this->map[this->findPoint(x,y)].moveRight();
    // Que pasa si hay dos en el mismo lugar?
    // Excepcion?
  std::vector<int> new_pos = this->map[this->findPoint(x,y)].getPosition();
  if (!this->isValidPos(new_pos[0], new_pos[1])){
    this->map[this->findPoint(new_pos[0], new_pos[1])] = Point(old_pos[0], old_pos[1]);
  }
}

std::vector<std::vector<int>> Map::getPositions(){
  std::vector<std::vector<int>> ret;
  for (auto it = this->map.begin(); it != this->map.end(); it++){
    ret.push_back(it->getPosition());
  }
  return ret;
}

Map::~Map(){}
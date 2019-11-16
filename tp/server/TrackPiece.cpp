#include "TrackPiece.h"
#include <iostream>
#include <unistd.h>

TrackPiece::TrackPiece(float x, float y, int track_type,
  std::vector<float> size)
  :  x(x), y(y), size(size), track_type(track_type)
{}

const bool TrackPiece::isCarOverMe(Car& car){
  float x_min = this->x - (this->size[0]/2);
  float x_max = this->x + (this->size[0]/2);
  float y_min = this->y - (this->size[1]/2);
  float y_max = this->y + (this->size[1]/2);
  b2Vec2 car_pos = car.GetPosition();
  // It considers the car as a point.
  return ((car_pos.x >= x_min) &&
          (car_pos.x <= x_max) &&
          (car_pos.y >= y_min) &&
          (car_pos.y <= y_max));
}

const std::vector<float> TrackPiece::GetPosition(){
  std::vector<float> vec;
  vec.push_back(this->x);
  vec.push_back(this->y);
  return vec;
}

const std::vector<float> TrackPiece::GetSize(){
  return this->size;
}

const int TrackPiece::getTrackType(){
  return this->track_type;
}
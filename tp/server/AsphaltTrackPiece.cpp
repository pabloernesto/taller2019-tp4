#include "AsphaltTrackPiece.h"
#include <iostream>

AsphaltTrackPiece::AsphaltTrackPiece(float x, float y, int track_type, std::vector<float> size)
                                               : TrackPiece(x,y, track_type, size){}

const bool AsphaltTrackPiece::isCarOverMe(Car& car){
  return TrackPiece::isCarOverMe(car);
}

const std::vector<float> AsphaltTrackPiece::GetPosition(){
  return TrackPiece::GetPosition ();
}


const std::vector<float> AsphaltTrackPiece::GetSize(){
  return TrackPiece::GetSize();
}

void AsphaltTrackPiece::updateCarCounter(Car& car){
  car.setCounter(0);
}

const int AsphaltTrackPiece::getTrackType(){
  return TrackPiece::getTrackType();
}
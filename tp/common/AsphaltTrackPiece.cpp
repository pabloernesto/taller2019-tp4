#include "AsphaltTrackPiece.h"

AsphaltTrackPiece::AsphaltTrackPiece(float x, float y, std::vector<size_t> size)
                                               : TrackPiece(x,y, size){}

const bool AsphaltTrackPiece::isCarOverMe(Car& car){
  return TrackPiece::isCarOverMe(car);
}

const std::vector<float> AsphaltTrackPiece::GetPosition(){
  return TrackPiece::GetPosition ();
}


const std::vector<size_t> AsphaltTrackPiece::GetSize(){
  return TrackPiece::GetSize();
}

void AsphaltTrackPiece::updateCarCounter(Car& car){
  car.setCounter(0);
}
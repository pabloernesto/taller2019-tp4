#include "GrassTrackPiece.h"

GrassTrackPiece::GrassTrackPiece(float x, float y, int track_type, std::vector<size_t> size) : 
                                                      TrackPiece(x,y, track_type, size){}

const bool GrassTrackPiece::isCarOverMe(Car& car){
  return TrackPiece::isCarOverMe(car);
}

const std::vector<float> GrassTrackPiece::GetPosition(){
  return TrackPiece::GetPosition ();
}


const std::vector<size_t> GrassTrackPiece::GetSize(){
  return TrackPiece::GetSize();
}

void GrassTrackPiece::updateCarCounter(Car& car){
  car.updateCounter(1);
}

const int GrassTrackPiece::getTrackType(){
  return TrackPiece::getTrackType();
}
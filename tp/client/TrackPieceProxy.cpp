#include "TrackPieceProxy.h"

TrackPieceProxy::TrackPieceProxy(int track_type, float x, float y, float size_x, float size_y) :
                  track_type(track_type), x(x), y(y), size_x(size_x), size_y(size_y){}

std::vector<float> TrackPieceProxy::GetPosition(){
  std::vector<float> v;
  v.push_back(this->x);
  v.push_back(this->y);
  return v;
}

std::vector<float> TrackPieceProxy::GetSize(){
  std::vector<float> v;
  v.push_back(this->size_x);
  v.push_back(this->size_y);
  return v;
}

int TrackPieceProxy::getTrackType(){
  return this->track_type;
}
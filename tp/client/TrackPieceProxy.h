#ifndef _TRACKPIECEPROXY_H_
#define _TRACKPIECEPROXY_H_
#include <vector>


class TrackPieceProxy {
  private:
    int track_type;
    float x;
    float y;
    float size_x;
    float size_y;


  public:
    TrackPieceProxy(int track_type, float x, float y, float size_x, float size_y);
    std::vector<float> GetPosition();
    std::vector<float> GetSize();
    int getTrackType();

};



#endif

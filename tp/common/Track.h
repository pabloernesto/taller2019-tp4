#ifndef TRACK_H_
#define TRACK_H_

#include "TrackPiece.h"
#include "TrackPiece.h"
#include <string>
#include <vector>
#include <memory>   // unique_ptr
// #include <Box2D/Box2D.h>
#include "Car.h"

class TrackPiece;
class Car;

enum trackTypes {
  HORIZONTAL,
  VERTICAL,
  GIRO_ARRIBADER,
  GIRO_ABAJODER,
  GIRO_ARRIBAIZQ,
  GIRO_ABAJOIZQ,
  PASTO
};

class Track{
private:
  static const std::vector<float> PIECE_SIZE;
  size_t num_rows;
  size_t num_cols;
  std::vector<std::vector<int>> blocks;
  std::vector<std::unique_ptr<TrackPiece>> tracks;
  std::string tracks_s;
  
public:
  Track(std::string race_specs);
  void updateCarCounter(Car& car);
  std::vector<std::unique_ptr<TrackPiece>>& getTrackPieces();
  std::vector<int> GetPositionOfClosestAsphalt(b2Vec2& position);
  std::string getTrackPiecesString();
};

#endif
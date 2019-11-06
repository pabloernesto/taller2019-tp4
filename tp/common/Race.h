#ifndef RACE_H_
#define RACE_H_

#include <Box2D/Box2D.h>
#include "Car.h"
#include "Modifier.h"
#include "Track.h"
#include <vector>
#include <memory>   // unique_ptr
#include "ContactListener.h"
#include "Posta.h"
#include "ModifierFactory.h"

class Race {
  b2World world;
  std::vector<std::unique_ptr<Car>> cars;
  std::vector<std::unique_ptr<Posta>> postas;
  std::vector<std::unique_ptr<Modifier>> modifiers;
  ModifierFactory modif_factory;

  Track track;
  ContactListener listener;
  size_t modifiers_reset;

public:
  Race(std::string track);
  void Step();
  Car& AddCar(float x, float y);
  void AddPosta(float x, float y, int id, float32 angle);
  std::vector<std::unique_ptr<Car>>& GetCars();
  Track& GetTrack();
  std::vector<std::unique_ptr<TrackPiece>>& getTrackPieces();

  Race();

private:
  void placeModifiers();
  void placeRandomModifier(float x, float y);
};

#endif    // RACE_H_

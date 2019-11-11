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
  int laps;
  bool ended;
  Car* winnerCar;

public:
  Race(std::string track, int laps);
  void Step();
  Car& AddCar(float x, float y, int id);
  Car& AddNewCarToRace();
  void AddPosta(float x, float y, int id, float32 angle);
  std::vector<std::unique_ptr<Car>>& GetCars();
  Track& GetTrack();
  std::vector<std::unique_ptr<TrackPiece>>& getTrackPieces();
  std::vector<std::unique_ptr<Modifier>>& getModifiers();
  int GetAmountOfPostas();
  int GetLaps();
  void SetWinner(Car* car);
  bool Ended();
  int GetIdWinnerCar();
  Race();

private:
  void placeModifiers();
  void placeRandomModifier(float x, float y);
  void removeUsedModifiers();
};

#endif    // RACE_H_

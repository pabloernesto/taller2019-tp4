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
#include "RaceModInterface.h"
#include <string>

class Race : public RaceModInterface {
  b2World world;
  std::vector<std::unique_ptr<Car>> cars;
  std::unique_ptr<std::vector<std::unique_ptr<Posta>>> postas;
  std::vector<std::unique_ptr<Modifier>> modifiers;
  ModifierFactory modif_factory;

  Track track;
  ContactListener listener;
  size_t modifiers_reset;
  int laps;
  bool ended;
  Car* winnerCar;
  b2Vec2 modif_size;

public:
  Race(std::string track, int laps, std::vector<std::unique_ptr<Posta>>* postas);
  void Step();
  Car& AddCar(float x, float y, int id);
  Car& AddNewCarToRace();
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

  // RaceModInterface
  // Modifiers
  virtual void placeRandomModifier(float x, float y) override; //This one is used in internal methods
  virtual void placeStoneModifier(float x, float y) override;
  virtual void placeBoostModifier(float x, float y) override;
  virtual void placeHealthModifier(float x, float y) override;
  virtual void removeModifiers() override;
  virtual void removeStoneModifiers() override;
  virtual void removeBoostModifiers() override;
  virtual void removeHealthModifiers() override;

private:
  void placeModifier(float x, float y, int num);
  void removeModifiersByType(std::string type);
  void placeModifiers();
  void removeUsedModifiers();
};

#endif    // RACE_H_

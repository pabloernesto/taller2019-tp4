#include "RaceFabric.h"
#include <string>
#include <vector>
#include <math.h>

RaceFabric::RaceFabric(){}

Race* RaceFabric::makeRace1(){
  std::string track = "6 9 666662004204661661163005661166666661162004661305663005";
  std::vector<std::unique_ptr<Posta>>* postas = new std::vector<std::unique_ptr<Posta>>();
  postas->emplace_back(new Posta(0, {5,-20}, 0));
  postas->emplace_back(new Posta(1, {55,-20}, 0));
  postas->emplace_back(new Posta(2, {80,-5}, -M_PI/2));
  postas->emplace_back(new Posta(3, {55,-50}, 0));
  postas->emplace_back(new Posta(4, {5,-50}, 0));

  return new Race(track, 1, postas);
}
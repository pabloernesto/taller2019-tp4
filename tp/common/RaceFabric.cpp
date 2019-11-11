#include "RaceFabric.h"

RaceFabric::RaceFabric(){}

Race* RaceFabric::makeRace1(){
  std::string track = "6 9 666662004204661661163005661166666661162004661305663005";
  std::vector<std::unique_ptr<Posta>> postas;
  postas.emplace_back(new Posta(0, {5,-20}, 0));
  postas.emplace_back(new Posta(0, {55,-20}, 1));
  postas.emplace_back(new Posta(0, {80,-5}, 2));
  postas.emplace_back(new Posta(0, {55,-50}, 3));
  postas.emplace_back(new Posta(0, {5,-50}, 4));

	return new Race(track, 3, postas);
}
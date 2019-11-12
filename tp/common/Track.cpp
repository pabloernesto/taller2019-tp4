#include "Track.h"
#include "string.h"
#include <vector>
#include <string>
#include <memory>   // unique_ptr
#include "GrassTrackPiece.h"
#include "AsphaltTrackPiece.h"
#include <iostream>

const std::vector<float> Track::PIECE_SIZE(10, 10);

// Format for race_specs is "d d dd..." where the first digit is the number
// of rows, the second is the number of columns, and the rest is -left to right,
// top to bottom- the code of the track block
Track::Track(std::string race_specs){
  std::vector<std::string> parameters = split(race_specs);
  this->num_rows = stoi(parameters[0]);
  this->num_cols = stoi(parameters[1]);
  this->tracks_s = race_specs;

  size_t block_counter = 0; 
  for (size_t j = 0; j < this->num_rows; j++){
    std::vector<int> row;

    // Populate the row
    for (size_t i = 0; i < this->num_cols; i++){
      row.push_back(parameters[2][block_counter] - '0');

      // Calculate the position of the center of the block
      float x = (0.5 + i) * PIECE_SIZE[0];
      float y = -(0.5 + j) * PIECE_SIZE[1];

      if (row[i] == PASTO) {
        this->tracks.emplace_back(
          new GrassTrackPiece(x, y, row[i], this->PIECE_SIZE));
      } else {
        this->tracks.emplace_back(
          new AsphaltTrackPiece(x, y, row[i], this->PIECE_SIZE));
      }
      block_counter++; 
    }

    // Push it in to the block matrix
    this->blocks.push_back(row);
  }   
}


void Track::updateCarCounter(Car& car){
  for (auto it = this->tracks.begin(); it != this->tracks.end(); it++){
    if ((*it)->isCarOverMe(car)){
      (*it)->updateCarCounter(car);
      // std::cout << "Track piece finished updating car counter! Now i end loop\n";
      break;
    }
  }
  // std::cout << "Checked for tracks\n";
}

std::vector<std::unique_ptr<TrackPiece>>& Track::getTrackPieces(){
  return this->tracks;
}

std::string Track::getTrackPiecesString(){
  return this->tracks_s;
}
#include "Track.h"
#include "image.h"
#include "string.h"
#include <vector>
#include <string>
#include <memory>   // unique_ptr
#include "MKStoPixel.h"
#include "GrassTrackPiece.h"
#include "AsphaltTrackPiece.h"
#include <iostream>
/*
void Track::initialiceTrackPieces(b2World& world,std::vector<int> &blocks){
  int contador = 0;
  for(int y = 0; y < this->width; ++y){
    for(int x = 0; x < this->height; ++x){
      this->tracks.emplace_back();
      auto&& size = this->tracks.at(x).GetSize();
      b2Vec2 where = {(float) (x+0.5)*size.x, (float) (y+0.5)*size.y };
      this->tracks.back().Place(world, where);
      contador++;
    }
  }
}

Track::Track(uint16_t height, uint16_t width, std::vector<int> blocks)
  : height(height), width(width), blocks(blocks), tracks()
{}

Track::Track(std::string event, b2World& world){
  //"H W B"
  std::vector<std::string> parametros = split(event);
  this->height = stoi(parametros[0]);
  this->width = stoi(parametros[1]);
  for(int i = 0; i < parametros[2].size(); ++i){
    int block = stoi((parametros[2]).substr(i,1));
    this->blocks.push_back(block);
  }
  this->initialiceTrackPieces(world, this->blocks);
}

std::string Track::ToStr() {
  std::string event = std::to_string(this->height) + " " + 
                      std::to_string(this->width) + " ";
  for(int i = 0; i < this->blocks.size(); ++i){
    event = event + std::to_string(this->blocks.at(i));
  }
  return event;
}

void Track::render(SDL_Window* w, SDL_Renderer* r, Camara& camara){
  auto& tracks = TrackImages(w, r);
  for (int i = 0; i < this->blocks.size(); ++i){
    int block = this->blocks.at(i);
    auto&& size = this->tracks.at(i).GetSize();
    camara.renderMe(this->tracks.at(i).GetPosition(), b2Vec2(size.x, size.y), *tracks[block], 0);
  }
}*/

const std::vector<float> Track::PIECE_SIZE(10, 10);

// Format for race_specs is "d d dd..." where the first digit is the number
// of rows, the second is the number of columns, and the rest is -left to right,
// top to bottom- the code of the track block
Track::Track(std::string race_specs){
  std::vector<std::string> parameters = split(race_specs);
  this->num_rows = stoi(parameters[0]);
  this->num_cols = stoi(parameters[1]);

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
      // std::cout << "There's a car over me!\n";
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

/*
std::vector<std::unique_ptr<Image>>& Track::TrackImages(
  SDL_Window* w, SDL_Renderer* r)
{
  static std::vector<std::unique_ptr<Image>> track_images;
  if (track_images.size() != 0) return track_images;

  track_images.emplace_back(new Image("../client/Imagenes/horizontal.bmp", w, r));
  track_images.emplace_back(new Image("../client/Imagenes/vertical.bmp", w, r));
  track_images.emplace_back(new Image("../client/Imagenes/giro_arribader.bmp", w, r));
  track_images.emplace_back(new Image("../client/Imagenes/giro_abajoder.bmp", w, r));
  track_images.emplace_back(new Image("../client/Imagenes/giro_arribaizq.bmp", w, r));
  track_images.emplace_back(new Image("../client/Imagenes/giro_abajoizq.bmp", w, r));
  track_images.emplace_back(new Image("../client/Imagenes/pasto.bmp", w, r));
  return track_images;
}*/
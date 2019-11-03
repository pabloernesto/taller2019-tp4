#include "Track.h"
#include "image.h"
#include "string.h"
#include <vector>
#include <string>
#include <memory>   // unique_ptr
#include "MKStoPixel.h"
#include "GrassTrackPiece.h"
#include "AsphaltTrackPiece.h"
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

const std::vector<size_t> Track::PIECE_SIZE(3, 3);


Track::Track(std::string race_specs){
  //"R C B"
  std::vector<std::string> parameters = split(race_specs);
  this->num_rows = stoi(parameters[0]);
  this->num_cols = stoi(parameters[1]);
  size_t block_counter = 0; 
  float block_x = 0;
  float block_y = 0;
  for (size_t j = 0; j < this->num_rows; j++){
    std::vector<int> row;
    for (size_t i = 0; i < this->num_cols; i++){
      // this->blocks[j].emplace_back(parameters[2][block_counter] - '0');
      row.push_back(parameters[2][block_counter] - '0');
      // this->blocks[j][i] = (parameters[2][block_counter] - '0');
      // if (this->blocks[j][i] == PASTO){
      if (row[i] == PASTO){
        this->tracks.emplace_back(new GrassTrackPiece(block_x, block_y, row[i], this->PIECE_SIZE));
      } else {
        this->tracks.emplace_back(new AsphaltTrackPiece(block_x, block_y, row[i], this->PIECE_SIZE));
      }
      block_x += (this->PIECE_SIZE[0]) / 2;
      block_counter++; 
    }
    this->blocks.push_back(row);
    block_y = (this->PIECE_SIZE[1]) / 2;
    block_x = 0;
  }   
}


void Track::updateCarCounter(Car& car){
  for (auto it = this->tracks.begin(); it != this->tracks.end(); it++){
    if ((*it)->isCarOverMe(car)){
      (*it)->updateCarCounter(car);
      break;
    }
  }
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
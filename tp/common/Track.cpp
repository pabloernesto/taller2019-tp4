#include "Track.h"
#include "image.h"
#include "string.h"
#include <vector>
#include <string>
#include <memory>   // unique_ptr
#include "MKStoPixel.h"

void Track::initialiceTrackPieces(b2World& world,std::vector<int> &blocks){
  int contador = 0;
  for(int y = 0; y < this->width; ++y){
    for(int x = 0; x < this->height; ++x){
      this->tracks.emplace_back();
      auto&& size = MKStoPixelTransform(this->tracks.at(x).GetSize());
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

void Track::render(SDL_Window* w, SDL_Renderer* r, SDL_Rect& camara){
  auto& tracks = TrackImages(w, r);
  for (int i = 0; i < this->blocks.size(); ++i){
    int x = this->tracks.at(i).GetPosition().x;
    int y = this->tracks.at(i).GetPosition().y;
    //Solo renderiza lo que se encuentra dentro de la camara
    //if ((x - WIDTHBLOCK/2) < camara.w && (x + WIDTHBLOCK/2) > camara.x &&
      //(y - HEIGHTBLOCK/2) < camara.h && (y + HEIGHTBLOCK/2) > camara.y){
      int block = this->blocks.at(i);
      auto&& size = MKStoPixelTransform(this->tracks.at(i).GetSize());
      SDL_Rect where = { x - size.x/2 - camara.x, 
                        y - size.y/2 + camara.y, 
                        size.x, size.y };
      tracks.at(block)->render(&where, 0);
    //}
  }
}

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
}
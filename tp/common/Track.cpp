#include "Track.h"
#include "image.h"
#include "string.h"
#include <map>
#include <string>

#define HEIGHTBLOCK 200
#define WIDTHBLOCK 200

std::map<int,Image*> Track::tracks(SDL_Window* &w, SDL_Renderer* &r){
  std::map<int,Image*> tracks;
    //{0, Imagen("../Imagenes/...",w,r)},
    //{1, Imagen("",w,r)},
  tracks[2] = new Image("../client/Imagenes/giro_arribader.bmp",w,r);
  tracks[3] = new Image("../client/Imagenes/giro_abajoder.bmp",w,r);
  tracks[4] = new Image("../client/Imagenes/giro_arribaizq.bmp",w,r);
  tracks[5] = new Image("../client/Imagenes/giro_abajoizq.bmp",w,r);
    //{6, Imagen("../Imagenes/",w,r)}
  
  return tracks;
}

Track::Track(uint16_t height, uint16_t width, std::vector<int> blocks): 
    height(height), width(width), blocks(blocks){
}

Track::Track(std::string event){
  //"H W B"
  std::vector<std::string> parametros = split(event);
  this->height = stoi(parametros[0]);
  this->width = stoi(parametros[1]);
  for(int i = 0; i < parametros[2].size(); ++i){
    int block = stoi((parametros[2]).substr(i,1));
    this->blocks.push_back(block);
  }
}

std::string Track::ToStr() {
  std::string event = std::to_string(this->height) + " " + 
                      std::to_string(this->width) + " ";
  for(int i = 0; i < this->blocks.size(); ++i){
    event = event + std::to_string(this->blocks.at(i));
  }
  return event;
}

void Track::render(SDL_Window* &w, SDL_Renderer* &r){
  std::map<int,Image*> tracks = this->tracks(w,r);
  int contador = 0;
  for(int y = 0; y < this->width; ++y){
    for(int x = 0; x < this->height; ++x){
      int block = this->blocks.at(contador);
      tracks.at(block)->render(x*WIDTHBLOCK, y*HEIGHTBLOCK, HEIGHTBLOCK, WIDTHBLOCK);
      contador++;
    }
  }
}
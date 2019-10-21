#include "Track.h"
#include "image.h"
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

Track::Track(uint16_t height, uint16_t width, std::vector<int> &blocks): 
    height(height), width(width), blocks(blocks){
 }

/*Track::Track(std::string event){
	//sscanf(event.c_str(), "H: %d W: %d B: %hhu", &this->height, 
    //&this->width, &this->blocks);
}*/

std::string Track::ToStr() {
  /*std::string event = "H: " + std::to_string(this->height)
    + " W: " + std::to_string(this->width)
    + " B: ";
    for(int i = 0; i < (this->blocks).size(); ++i){
      std::string bloque = std::to_string(this->blocks.at(i));
      event.append(bloque);
    }*/
    return "";
}

void Track::render(SDL_Window* &w, SDL_Renderer* &r){
  std::map<int,Image*> tracks = this->tracks(w,r);
  /*tracks.at(2)->render(0, 0, HEIGHTBLOCK, WIDTHBLOCK);
  tracks.at(4)->render(200, 0, 200, 200);
  tracks.at(3)->render(0, 200, 200, 200);
  tracks.at(5)->render(200, 200, 200, 200);*/

  int contador = 0;
  for(int y = 0; y < this->width; ++y){
    for(int x = 0; x < this->height; ++x){
      int block = this->blocks.at(contador);
      tracks.at(block)->render(x*WIDTHBLOCK, y*HEIGHTBLOCK, HEIGHTBLOCK, WIDTHBLOCK);
      contador++;
    }
  }
}
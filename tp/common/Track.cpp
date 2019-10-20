#include "Track.h"
#include "image.h"
#include <map>
#include <string>

std::map<int,Image> Track::tracks(SDL_Window* w, SDL_Renderer* r){
  std::map<int,Image> tracks = {
    {0, Imagen("",w,r)},
    {1, Imagen("",w,r)},
    {2, Imagen("",w,r)},
    {3, Imagen("",w,r)},
    {4, Imagen("",w,r)},
    {5, Imagen("",w,r)},
    {6, Imagen("",w,r)}
  }
}

Track::Track(uint16_t height, uint16_t width, std::vector<int> blocks): 
    height(height), width(width), blocks(blocks){
 }

Track::Track(std::string event){
	//sscanf(event.c_str(), "H: %d W: %d B: %hhu", &this->height, 
    //&this->width, &this->blocks);
}

std::string Track::ToStr() {
  /*std::string event = "H: " + std::to_string(this->height)
    + " W: " + std::to_string(this->width)
    + " B: ";
    for(int i = 0; i < (this->blocks).size(); ++i){
      std::string bloque = std::to_string(this->blocks.at(i));
      event.append(bloque);
    }*/
}

void Track::render(SDL_Window* w, SDL_Renderer* r){
  for(int i = 0; i < this->blocks.size(); ++i){

  }
}
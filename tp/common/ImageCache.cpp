#include "ImageCache.h"

ImageCache::ImageCache(SDL_Window* w, SDL_Renderer* r) {
  this->images["Imagenes/Micro-Machines.bmp"] = std::unique_ptr<Image>(new Image("Imagenes/Micro-Machines.bmp", w, r));
  this->images["Imagenes/giro_abajoder.bmp"] = std::unique_ptr<Image>(new Image("Imagenes/giro_abajoder.bmp", w, r));
  this->images["Imagenes/giro_abajoizq.bmp"] = std::unique_ptr<Image>(new Image("Imagenes/giro_abajoizq.bmp", w, r));
  this->images["Imagenes/giro_arribader.bmp"] = std::unique_ptr<Image>(new Image("Imagenes/giro_arribader.bmp", w, r));
  this->images["Imagenes/giro_arribaizq.bmp"] = std::unique_ptr<Image>(new Image("Imagenes/giro_arribaizq.bmp", w, r));
  this->images["Imagenes/horizontal.bmp"] = std::unique_ptr<Image>(new Image("Imagenes/horizontal.bmp", w, r));
  this->images["Imagenes/pasto.bmp"] = std::unique_ptr<Image>(new Image("Imagenes/pasto.bmp", w, r));
  this->images["Imagenes/pitstop_car_1.bmp"] = std::unique_ptr<Image>(new Image("Imagenes/pitstop_car_1.bmp", w, r));
  this->images["Imagenes/vertical.bmp"] = std::unique_ptr<Image>(new Image("Imagenes/vertical.bmp", w, r));
}

Image& ImageCache::getImage(std::string path) {
  return *(images.at(path));
}

ImageCache::~ImageCache() {}

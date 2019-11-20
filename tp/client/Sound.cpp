#include "Sound.h"
#include <iostream>

Sound::Sound(std::string file) : sound(Mix_LoadWAV(file.c_str())), channel(-1){}

Sound::~Sound(){
  Mix_FreeChunk(sound);
}

void Sound::Play(){
  if (channel == -1){
    channel = Mix_PlayChannel(-1, sound, 0);
  } else if (Mix_Playing(channel) == 0) {
    Mix_PlayChannel(channel, sound, 0);
  }
}

void Sound::SetVolume(int volume){
  if (sound){
    Mix_VolumeChunk(sound, volume);
  } else {
    std::cerr << "Sound: failed to load sound\n";
  }
}
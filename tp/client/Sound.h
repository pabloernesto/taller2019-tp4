#ifndef SOUND_H_
#define SOUND_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class Sound {
  Mix_Chunk* sound;
  int channel;

public:
  Sound(std::string file);
  ~Sound();

  void Play();
  void SetVolume(int volume);
};

#endif
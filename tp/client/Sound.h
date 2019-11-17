#ifndef SOUND_H_
#define SOUND_H_
#include <SDL2/SDL.h>
#include <string>

class Sound {
private:
  static Uint32 wav_length;
	static Uint8 *wav_buffer;
	static SDL_AudioSpec wav_spec;


public:
  Sound(char* path);
  void my_audio_callback(void *userdata, Uint8 *stream, int len);
};

#endif

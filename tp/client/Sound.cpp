#include "Sound.h"

Sound::Sound(char* path) {
  SDL_LoadWAV(path, &wav_spec, &wav_buffer, &wav_length);
  wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;
  SDL_OpenAudio(&wav_spec, NULL);
}

void Sound::my_audio_callback(void *userdata, Uint8 *stream, int len) {
	
	if (audio_len ==0)
		return;
	
	len = ( len > audio_len ? audio_len : len );
	//SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another
	
	audio_pos += len;
	audio_len -= len;
}
#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h> // Uncomment if SDL_mixer is available
#include <string>

class AudioPlayer {
public:
    AudioPlayer() 
    { 
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); 
    }
    ~AudioPlayer() 
    { 
        Mix_CloseAudio(); 
    }
    void play(const std::string& filename) {
        Mix_Music* music = Mix_LoadMUS(filename.c_str());
        if (music) Mix_PlayMusic(music, 1);
        // Stub: Print message
        SDL_Log("Audio playback is not implemented. Add SDL_mixer for full functionality.");
    }
};

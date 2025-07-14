#include "cub_bns.h"

void run_sound_file(const char *file)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 *wav_buffer;

    if (SDL_LoadWAV(file, &wav_spec, &wav_buffer, &wav_length) == NULL)
    {
        fprintf(stderr, "Could not load %s: %s\n", file, SDL_GetError());
        SDL_Quit();
        return;
    }

    if (SDL_OpenAudio(&wav_spec, NULL) < 0)
    {
        fprintf(stderr, "SDL_OpenAudio Error: %s\n", SDL_GetError());
        SDL_FreeWAV(wav_buffer);
        SDL_Quit();
        return;
    }

    SDL_PauseAudio(0); // start playing
    SDL_QueueAudio(1, wav_buffer, wav_length);

    // Wait until audio finishes
    SDL_Delay(wav_length / (wav_spec.freq * wav_spec.channels / 2) * 1000);

    SDL_CloseAudio();
    SDL_FreeWAV(wav_buffer);
    SDL_Quit();
}

int main(void)
{
    run_sound_file("bonus/audio/gunshot.wav"); 
    run_sound_file("bonus/audio/machine-gun.wav"); 

    return 0;
}
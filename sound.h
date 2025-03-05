#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED



#include <SDL.h>
#include <SDL_mixer.h>



namespace sound {
    Mix_Music *preparing_for_battle;
    Mix_Music *battle_loop;
    Mix_Chunk *click_button;
    Mix_Chunk *sell_tower;
    Mix_Chunk *shooting1;
    Mix_Chunk *shooting2;
    Mix_Chunk *place_tower;
    Mix_Chunk *explode;

    Mix_Music *load_music(const char* path) {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        return gMusic;
    }

    void play(Mix_Music *gMusic) {
        if (gMusic == nullptr) return;
        if (Mix_PlayingMusic() == 0) Mix_PlayMusic(gMusic, -1);
        else if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
    }

    Mix_Chunk* load_sound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        return gChunk;
    }

    void play(Mix_Chunk* gChunk) {
        if (gChunk != nullptr) Mix_PlayChannel(-1, gChunk, 0);
    }

    void stop_music() {
        Mix_HaltMusic();
    }

    void pause_music() {
        Mix_PauseMusic();
    }

    void log_error_and_exit(const char *message, const char *error) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", message, error);
        SDL_Quit();
    }

    void init() {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) log_error_and_exit("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        preparing_for_battle = load_music("sounds/preparing for battle.mp3");
        battle_loop = load_music("sounds/battle loop.mp3");
        click_button = load_sound("sounds/click button.mp3");
        sell_tower = load_sound("sounds/sell tower.mp3");
        shooting1 = load_sound("sounds/shooting1.mp3");
        shooting2 = load_sound("sounds/shooting2.mp3");
        place_tower = load_sound("sounds/place tower.mp3");
        explode = load_sound("sounds/explode.mp3");
    }

    void quit() {
        Mix_Quit();
    }
};



#endif // SOUND_H_INCLUDED

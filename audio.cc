//
// Created by Tufa Manon on 2023/2/1.
//

#include "audio.h"
Audio::Audio() {
  move_chunk = Mix_LoadWAV("assets/move_.ogg");
  back_music = Mix_LoadMUS("assets/back.mp3");
}
void Audio::Play_Move() const {
  Mix_PlayChannel(-1, move_chunk, 0);
}
void Audio::Play_Back() const {
  Mix_PlayMusic(back_music, -1);
}

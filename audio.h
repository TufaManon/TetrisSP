//
// Created by Tufa Manon on 2023/2/1.
//

#ifndef TETRIS_AUDIO_H_
#define TETRIS_AUDIO_H_
#include <SDL_mixer.h>
class Audio {
 private:
  Audio();

 public:
  Audio(const Audio &) = delete;
  Audio(const Audio &&) = delete;
  Audio &operator=(const Audio &) = delete;
  static Audio &GetInstance() {
    static Audio s;
    return s;
  }
  void Play_Move() const;
  void Play_Back() const;
  Mix_Chunk *move_chunk = nullptr;
  Mix_Chunk *hard_down_chunk_ = nullptr;
  Mix_Music *back_music = nullptr;
};

#endif//TETRIS_AUDIO_H_

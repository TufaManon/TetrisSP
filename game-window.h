//
// Created by Tufa Manon on 2023/1/26.
//

#ifndef TETRIS_GAME_WINDOW_H_
#define TETRIS_GAME_WINDOW_H_
#include <SDL.h>

class GameWindow {
 public:
  GameWindow(int w, int h);
  ~GameWindow();
  void Present() const;
  void Clear() const;
  SDL_Window *window_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;
  [[nodiscard]] int GetW() const;
  [[nodiscard]] int GetH() const;

 private:
  int w_,h_;
};

#endif//TETRIS_GAME_WINDOW_H_

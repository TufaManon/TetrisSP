//
// Created by Tufa Manon on 2023/1/26.
//

#include "game-window.h"
void GameWindow::Present() const {
  SDL_RenderPresent(renderer_);
}
GameWindow::GameWindow(int w, int h) : w_(w), h_(h) {
  SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, &window_, &renderer_);
}
void GameWindow::Clear() const {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
}
GameWindow::~GameWindow() {
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
}
int GameWindow::GetW() const {
  return w_;
}
int GameWindow::GetH() const {
  return h_;
}

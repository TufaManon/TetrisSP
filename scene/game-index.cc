//
// Created by Tufa Manon on 2023/1/26.
//

#include "game-index.h"
#include "the-game.h"
void GameIndex::Update(uint64_t delta) {
  Scene::Update(delta);
}
GameIndex::GameIndex(GameWindow *game_window) : Scene(game_window), button_(graphics_->CreateButton()) {
  button_->coord.x = game_window->GetW() / 2;
  button_->coord.y = game_window->GetH() / 2;
}
void GameIndex::HandleEvent(SDL_Event &event) {
  Scene::HandleEvent(event);
  if (event.type == SDL_MOUSEBUTTONDOWN) {

    int start_x = button_->coord.x;
    int start_y = button_->coord.y;
    int end_x = start_x + button_->w;
    int end_y = start_y + button_->h;
    int mouse_x = event.button.x;
    int mouse_y = event.button.y;
    if (mouse_x >= start_x && mouse_x <= end_x && mouse_y >= start_y && mouse_y <= end_y) {
      next_scene_ = new TheGame(game_window_);
    }
  }
}

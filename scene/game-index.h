//
// Created by Tufa Manon on 2023/1/26.
//

#ifndef TETRIS_SCENE_GAME_INDEX_H_
#define TETRIS_SCENE_GAME_INDEX_H_
#include "scene.h"
class GameIndex : public Scene {
 public:
  explicit GameIndex(GameWindow *game_window);
  void Update(uint64_t delta) override;
  void HandleEvent(SDL_Event &event) override;

 private:
  Button *button_;
};

#endif//TETRIS_SCENE_GAME_INDEX_H_

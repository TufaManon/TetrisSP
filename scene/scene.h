
#ifndef TETRIS_GAME_INDEX_H_
#include "cinttypes"
#include "game-window.h"
#include "graphics.h"
#include "loop-node.h"
#define TETRIS_GAME_INDEX_H_
class Scene : public LoopNode {
 public:
  explicit Scene(GameWindow *game_window);
  ~Scene() override;
  void Update(uint64_t delta) override;
  virtual void HandleEvent(SDL_Event &event){};
  Scene *GetNextScene();

 protected:
  Scene *next_scene_ = nullptr;
  Graphics *graphics_ = nullptr;
  GameWindow *game_window_;
};
#endif
#ifndef  TETRIS_SCENE_THE_GAME_H_
#define  TETRIS_SCENE_THE_GAME_H_
#include "scene.h"
#include "matrix.h"
#include "tetris-actuator.h"
#include "tetris-operator.h"
#include "audio.h"
class TheGame : public Scene{
 public:
  explicit TheGame(GameWindow *game_window);
  ~TheGame() override;
  void Update(uint64_t delta) override;
  void HandleEvent(SDL_Event &event) override;
 private:
  ScoreBoard *score;
  ScoreBoard *time_stamp;
  ScoreBoard *lines;
 TetrisActuator actuator_;
  Matrix* main_matrix;
  bool left_button_down = false;
  bool right_button_down = false;
  bool soft_down_button_down = false;
  bool hard_down_button_down = false;
  bool l_rotate_button_down = false;
  bool r_rotate_button_down = false;
  bool hold_button_down = false;
  uint64_t das = 167;
  uint64_t arr = 33;
  uint64_t timer = 0;
  bool is_das = true;
  Vec2 transform_ = Vec2(1,0);
};

#endif//TETRIS_SCENE_THE_GAME_H_

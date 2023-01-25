//  Copyright [2023] [Tufa Manon]
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

//
// Created by Tufa Manon on 2023/1/23.
//

#ifndef TETRISSP_GAME_SRC_SERVER_TETRIS_ENGINE_H_
#define TETRISSP_GAME_SRC_SERVER_TETRIS_ENGINE_H_
#include <cinttypes>
#include <list>
#include <array>
#include <vector>
#include <utils/point.h>
#include <functional>
#include "response/response.h"
#include "tetrimino/mino.h"
#include "tetrimino/tetrimino.h"
#include "tetrimino/generator.h"
#include "srs.h"

namespace tetris_sp::game::server {

class TetrisEngine {
 public:
  struct Configurable {
    uint64_t falling_interval;
  };
  enum Phase {
    GENERATION_PHASE,
    FALLING_PHASE,
    LOCK_PHASE,
    PATTERN_PHASE,
    ITERATE_PHASE,
    ANIMATE_PHASE,
    ELIMINATE_PHASE,
    COMPLETION_PHASE
  };
  explicit TetrisEngine(tetrimino::Generator *generator);
  ~TetrisEngine();
  void Update();
  bool Move(bool right);
  bool Rotate(bool clockwise);
  bool HardDrop();
  bool Hold();
  response::Response GeyMatrixRenderResponse();
  Configurable configurable_{1000};
 private:
  // phases
  void Generation();
  void Falling();
  void Lock();
  void Pattern();
  void Iterate();
  void Animate();
  void Eliminate();
  void Completion();
  void GameOver();
  // utils
  void EachMino(const std::function<void(tetrimino::Mino *mino, int x, int y)> &fn);
  void EachMino(const std::function<void(tetrimino::Mino *mino, int x, int y)> &fn,
                const std::function<bool(tetrimino::Mino *mino)> &filter);
  std::vector<int> GetFullLineNum();
  void ClearLine();
  bool PositionCheck(const std::array<utils::Point, 4> &pos);
  static std::array<utils::Point, 4> GetMinosAbsolutePos(const tetrimino::Tetrimino &target);
  static std::array<utils::Point, 4> GetMinosAbsolutePos(const std::array<utils::Point, 4> &mino_pos,
                                                         const utils::Point &tetrimino_pos);
  std::array<utils::Point, 4> GetTetriminoProjection(const tetrimino::Tetrimino &target, int *i);
  static std::array<utils::Point, 4> GetTetriminoProjection(const tetrimino::Tetrimino &tetrimino_1, int i);
  tetrimino::Generator *generator_;
  Phase phase_{GENERATION_PHASE};
  uint64_t timer_1_{0};
  uint64_t current_tick_{SDL_GetTicks64()};
  uint64_t lock_phase_record_timer_1_{0};
  uint8_t lock_phase_reset_counter_{0};
  utils::Point lock_phase_record_pos_{0, 0};
  tetrimino::Orientation lock_phase_record_ori_{};
  tetrimino::Tetrimino *activity_tetrimino_{nullptr};
  tetrimino::Tetrimino *held_tetrimino_{nullptr};
  SRS srs_{};
  tetrimino::Mino *lock_map_[22][10]{nullptr};
  std::list<tetrimino::Tetrimino *> next_queue_{};
  std::vector<int> marked_lines_{};
  bool is_hard_drop_{false};
  bool stop_count_time_{false};
  bool is_hold_act{false};
  bool cen_hold{true};
};

} // server

#endif //TETRISSP_GAME_SRC_SERVER_TETRIS_ENGINE_H_

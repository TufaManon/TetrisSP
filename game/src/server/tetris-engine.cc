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
#include <map>
#include <SDL.h>
#include "tetris-engine.h"
#include "tetrimino/tetrimino.h"

namespace tetris_sp::game::server {
namespace {
std::map<tetrimino::Type, tetrimino::Color> kColorTypeMap = {
    {tetrimino::O, tetrimino::YELLOW},
    {tetrimino::I, tetrimino::LIGHT_BLUE},
    {tetrimino::T, tetrimino::VIOLET},
    {tetrimino::L, tetrimino::ORANGE},
    {tetrimino::J, tetrimino::BLUE},
    {tetrimino::S, tetrimino::GREEN},
    {tetrimino::Z, tetrimino::RED}
};

const int MINO_COORD_POOL[7][8] = {
    {-1, 0, 0, 0, 1, 0, 2, 0},
    {-1, -1, -1, 0, 0, 0, 1, 0},
    {-1, 0, 0, 0, 1, 0, 1, -1},
    {0, -1, 0, 0, 1, -1, 1, 0},
    {-1, 0, 0, 0, 0, -1, 1, -1},
    {-1, 0, 0, -1, 0, 0, 1, 0},
    {-1, -1, 0, -1, 0, 0, 1, 0}
};

tetrimino::Tetrimino *TetriminoFactory(tetrimino::Type type) {
  auto set_mino_from_coord_pool = [type](int index) -> tetrimino::Tetrimino * {
    auto *target = new tetrimino::Tetrimino();
    for (int i = 0; i < 4; i++) {
      target->mino_relative_position[i].x = MINO_COORD_POOL[index][i * 2];
      target->mino_relative_position[i].y = MINO_COORD_POOL[index][i * 2 + 1];
      target->type = type;
    }
    return target;
  };

  switch (type) {
    case tetrimino::I: return set_mino_from_coord_pool(0);
    case tetrimino::J:return set_mino_from_coord_pool(1);
    case tetrimino::L:return set_mino_from_coord_pool(2);
    case tetrimino::O:return set_mino_from_coord_pool(3);
    case tetrimino::S:return set_mino_from_coord_pool(4);
    case tetrimino::T:return set_mino_from_coord_pool(5);
    case tetrimino::Z:return set_mino_from_coord_pool(6);
    default:break;
  }
  return nullptr;
}
}
void TetrisEngine::Generation() {
  if (timer_1_ >= 200) {
    if (is_hold_act) {
      std::swap(activity_tetrimino_, held_tetrimino_);
      is_hold_act = false;
    } else if (activity_tetrimino_ != nullptr) {
      delete activity_tetrimino_;
      activity_tetrimino_ = nullptr;
    }
    if (activity_tetrimino_ == nullptr) {
      tetrimino::Tetrimino *generated = TetriminoFactory(generator_->GetType()); //TODO generate a tetrimino
      activity_tetrimino_ = next_queue_.front();
      next_queue_.pop_front();
      next_queue_.push_back(generated);
    }
    activity_tetrimino_->pos.x = 4;
    activity_tetrimino_->pos.y = 1;
    if (!PositionCheck(GetTetriminoProjection(*activity_tetrimino_, 1))) {
      //TODO End The Game
    } else {
      activity_tetrimino_->pos.y++;
    }
    phase_ = FALLING_PHASE;
    timer_1_ = 0;
  }
}
void TetrisEngine::Falling() {
  if (!PositionCheck(GetTetriminoProjection(*activity_tetrimino_, 1))) {
    phase_ = LOCK_PHASE;
    lock_phase_record_pos_ = activity_tetrimino_->pos;
    lock_phase_record_ori_ = activity_tetrimino_->ori;
    timer_1_ = 0;
  } else if (timer_1_ >= configurable_.falling_interval) {
    activity_tetrimino_->pos.y++;
    timer_1_ = 0;
  }
}
void TetrisEngine::Lock() {
  // Using the Super Rotation System, rotating a Tetrimino often causes the y-coordinate of the
  //Tetrimino to increase, i.e., it “lifts” off the Surface it landed on. The Lock-Down Timer does not
  //reset in this case, but it does stop counting down until the Tetrimino lands again on a Surface
  if (lock_phase_record_timer_1_ != 0) {
    timer_1_ = lock_phase_record_timer_1_;
    lock_phase_record_timer_1_ = 0;
  }

  if (lock_phase_record_pos_.y > activity_tetrimino_->pos.y) {
    lock_phase_record_timer_1_ = timer_1_;
    phase_ = FALLING_PHASE;
    lock_phase_reset_counter_ = 0;
    lock_phase_record_pos_ = activity_tetrimino_->pos;
    lock_phase_record_ori_ = activity_tetrimino_->ori;

    timer_1_ = 0;
  } else if (lock_phase_record_pos_ != activity_tetrimino_->pos || lock_phase_record_ori_ != activity_tetrimino_->ori) {
    //If Moving or rotation a Tetrimino causes it to fall again. it re-enters the Falling Phase.
    if (PositionCheck(GetTetriminoProjection(*activity_tetrimino_, 1))) {
      lock_phase_reset_counter_ = 0;
      phase_ = FALLING_PHASE;
      timer_1_ = 0;
    } else {
      //When lands the a surface with a lower y-coordinate will reset the timer;
      timer_1_ = 0;
      lock_phase_reset_counter_++;
    }
    lock_phase_record_pos_ = activity_tetrimino_->pos;
    lock_phase_record_ori_ = activity_tetrimino_->ori;
  }
  if (timer_1_ >= 500 || lock_phase_reset_counter_ >= 15 || is_hard_drop_) {
    lock_phase_reset_counter_ = 0;
    for (const auto &[x, y] : activity_tetrimino_->mino_relative_position) {
      auto *mino = new tetrimino::Mino();
      mino->color = kColorTypeMap[activity_tetrimino_->type];
      mino->is_blinking = false;
      mino->is_flash_once = true;
      mino->x = activity_tetrimino_->pos.x + x;
      mino->y = activity_tetrimino_->pos.y + y;
      lock_map_[activity_tetrimino_->pos.y + y]
      [activity_tetrimino_->pos.x + x] = mino;
    }
    // Once the Tetrimino is fully Locked Down,it enters the Pattern Phase.
    phase_ = PATTERN_PHASE;
    timer_1_ = 0;
    is_hard_drop_ = false;
  }
}
void TetrisEngine::Pattern() {
  marked_lines_ = GetFullLineNum();
  phase_ = ITERATE_PHASE;
  timer_1_ = 0;
}
void TetrisEngine::Iterate() {
  phase_ = ANIMATE_PHASE;
  timer_1_ = 0;
}
void TetrisEngine::Animate() {
  phase_ = ELIMINATE_PHASE;
  timer_1_ = 0;
}
void TetrisEngine::Eliminate() {
  if (!marked_lines_.empty())
    ClearLine();
  phase_ = COMPLETION_PHASE;
  timer_1_ = 0;
}
void TetrisEngine::Completion() {
  phase_ = GENERATION_PHASE;
  timer_1_ = 0;
}

void TetrisEngine::EachMino(
    const std::function<void(tetrimino::Mino *mino, int x, int y)
    > &fn) {
  for (
      int i = 0;
      i < 22; i++)
    for (
        int j = 0;
        j < 10; j++)
      fn(lock_map_[i][j], j, i
      );
}

void TetrisEngine::EachMino(const std::function<void(tetrimino::Mino *mino, int x, int y)
> &fn,
                            const std::function<bool(tetrimino::Mino *mino)> &filter
) {
  for (
      int i = 0;
      i < 22; i++)
    for (
        int j = 0;
        j < 10; j++)
      if (
          filter(lock_map_[i][j])
          )
        fn(lock_map_[i][j], j, i
        );
}

std::vector<int> TetrisEngine::GetFullLineNum() {
  auto check = [this](int y) -> bool {
    bool res = true;
    for (int x = 0; x < 10; x++) {
      res &= lock_map_[y][x] != nullptr;
    }
    return res;
  };
  std::vector<int> rows;
  for (int y = 21; y >= 0; y--) {
    if (check(y)) {
      rows.push_back(y);
    }
  }
  return rows;
}

TetrisEngine::TetrisEngine(tetrimino::Generator *generator) : generator_(generator) {
  for (int i = 0; i < 6; ++i)
    next_queue_.push_back(TetriminoFactory(generator_->GetType()));
}
void TetrisEngine::Update() {
  switch (phase_) {
    case GENERATION_PHASE:Generation();
      break;
    case FALLING_PHASE:Falling();
      break;
    case LOCK_PHASE:Lock();
      break;
    case PATTERN_PHASE:Pattern();
      break;
    case ITERATE_PHASE:Iterate();
      break;
    case ANIMATE_PHASE:Animate();
      break;
    case ELIMINATE_PHASE:Eliminate();
      break;
    case COMPLETION_PHASE:Completion();
      break;
  }

  Uint64 ticks_64 = SDL_GetTicks64();
  timer_1_ += ticks_64 - current_tick_;
  current_tick_ = ticks_64;
}
bool TetrisEngine::Move(bool right) {
  if (phase_ != FALLING_PHASE && phase_ != LOCK_PHASE) return false;
  std::array<utils::Point, 4> absolute_pos = GetMinosAbsolutePos(*activity_tetrimino_);
  for (auto &item : absolute_pos) {
    item.x += right ? 1 : -1;
  }
  if (PositionCheck((absolute_pos))) {
    activity_tetrimino_->pos.x += right ? 1 : -1;
    return true;
  }
  return false;
}
void TetrisEngine::ClearLine() {
  for (const auto &item : marked_lines_) {
    for (int i1 = 0; i1 < 10; ++i1) {
      delete lock_map_[item][i1];
    }
  }
  int i = 0;
  while (i < marked_lines_.size()) {
    int end = -1;
    if (i < marked_lines_.size() - 1)
      end = marked_lines_[i + 1] + 1;
    for (int col = marked_lines_[i] + i; col - 1 - i > end; col--) {
      for (int x = 0; x < 10; x++) {
        lock_map_[col][x] = lock_map_[col - 1 - i][x];
        if (lock_map_[col][x] != nullptr)
          lock_map_[col][x]->y = col;
      }
    }
    if (end == -1) {
      for (int col = end + 1 + i; col >= 0; col--) {
        for (int x = 0; x < 10; x++) {
          lock_map_[col][x] = nullptr;
        }
      }
    }
    i++;
  }
  for (int col = 0; col < marked_lines_.size(); col++) {
    for (int x = 0; x < 10; x++) {
      lock_map_[col][x] = nullptr;
    }
  }
  marked_lines_.clear();
}
bool TetrisEngine::PositionCheck(const std::array<utils::Point, 4> &pos) {
  bool res = true;
  for (const auto &item : pos) {
    res &= item.y < 22 && item.x < 10 && item.y >= 0 && item.x >= 0 && lock_map_[item.y][item.x] == nullptr;
  }
  return res;
}
std::array<utils::Point, 4> TetrisEngine::GetMinosAbsolutePos(const tetrimino::Tetrimino &target) {
  std::array<utils::Point, 4> res = target.mino_relative_position;
  for (auto &item : res) {
    item.x += target.pos.x;
    item.y += target.pos.y;
  }
  return res;
}
bool TetrisEngine::Rotate(bool clockwise) {
  if (phase_ != FALLING_PHASE && phase_ != LOCK_PHASE) return false;
  auto srs_res = srs_(*activity_tetrimino_, clockwise);
  std::array<utils::Point, 4> abs_rotated_mino_pos = srs_res.rotated_mino_pos;
  for (int i = 0; i < 5; ++i) {
    auto of = srs_res.offsets[i];
    int j = 0;
    for (auto &item : abs_rotated_mino_pos) {
      item = srs_res.rotated_mino_pos[j] + activity_tetrimino_->pos + of;
      j++;
    }
    if (PositionCheck(abs_rotated_mino_pos)) {
      activity_tetrimino_->pos += of;
      activity_tetrimino_->mino_relative_position = srs_res.rotated_mino_pos;
      activity_tetrimino_->ori = srs_res.next_orien;
      return true;
    }
  }
  return false;
}
bool TetrisEngine::HardDrop() {
  if (phase_ != FALLING_PHASE && phase_ != LOCK_PHASE) return false;
  int i;
  GetTetriminoProjection(*activity_tetrimino_, &i);
  activity_tetrimino_->pos.y += i;
  is_hard_drop_ = true;
  lock_phase_record_pos_ = activity_tetrimino_->pos;
  lock_phase_record_ori_ = activity_tetrimino_->ori;
  phase_ = LOCK_PHASE;
  timer_1_ = 0;
  return true;
}
bool TetrisEngine::Hold() {
  if (phase_ != FALLING_PHASE && phase_ != LOCK_PHASE) return false;
  if (can_hold) {
    is_hold_act = true;
    can_hold = false;
    return true;
  }
  return false;
}
void TetrisEngine::GameOver() {

}
std::array<utils::Point, 4> TetrisEngine::GetTetriminoProjection(const tetrimino::Tetrimino &target, int *i) {
  int min = 22;
  for (const auto &item : target.mino_relative_position) {
    int drop_counter = -1;
    utils::Point point = item + target.pos;
    while (point.y < 22 && point.y >= 0 && lock_map_[point.y][point.x] == nullptr) {
      point.y++;
      drop_counter++;
    };
    if (min > drop_counter) min = drop_counter;
  }
  if (i != nullptr) *i = min;
  auto pos = target.pos;
  pos.y += min;
  return GetMinosAbsolutePos(target.mino_relative_position, pos);
}
std::array<utils::Point, 4> TetrisEngine::GetTetriminoProjection(const tetrimino::Tetrimino &tetrimino_1, int i) {
  auto tmp = tetrimino_1.pos;
  tmp.y += i;
  return GetMinosAbsolutePos(tetrimino_1.mino_relative_position, tmp);
}
std::array<utils::Point, 4> TetrisEngine::GetMinosAbsolutePos(const std::array<utils::Point, 4> &mino_pos,
                                                              const utils::Point &tetrimino_pos) {
  std::array<utils::Point, 4> res = mino_pos;
  for (auto &item : res) {
    item.x += tetrimino_pos.x;
    item.y += tetrimino_pos.y;
  }
  return res;
}
response::Response TetrisEngine::GeyMatrixRenderResponse() {
  response::Response resp{};
  resp.matrix_render_response.type = response::MATRIX_RENDER_RESPONSE;
  resp.matrix_render_response.activity_tetrimino_ = activity_tetrimino_;
  resp.matrix_render_response.held_tetrimino_ = held_tetrimino_;
  resp.matrix_render_response.lock_map_ = lock_map_;
  resp.matrix_render_response.next_queue_ = &next_queue_;
  int i = -1;
  if (activity_tetrimino_ != nullptr)
    GetTetriminoProjection(*activity_tetrimino_, &i);
  resp.matrix_render_response.ghost_off = i;
  return resp;
}

TetrisEngine::~TetrisEngine() {
  delete generator_;
  EachMino([](tetrimino::Mino *mino, int x, int y) -> void {
    delete mino;
  });
  for (auto &item : next_queue_) {
    delete item;
  }
  delete held_tetrimino_;
  delete activity_tetrimino_;
}
} // server
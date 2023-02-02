//
// Created by Tufa Manon on 2023/1/28.
//

#include "tetris-actuator.h"
namespace {
}
void TetrisActuatorState::CalibrationTime() { current_time_ = SDL_GetTicks64(); }
TetrisActuatorState *TetrisActuatorState::Handle(TetrisActuator &context) {
  auto time = SDL_GetTicks64();
  timer_ += time - current_time_;
  current_time_ = time;
  return nullptr;
}
void TetrisActuator::SetState(TetrisActuatorState *state) {
  delete state_;
  state_ = state;
}
void TetrisActuator::Request(uint64_t delta) {
  if (state_) {
    playing_time_ += std::chrono::milliseconds(delta);
    auto state = state_->Handle(*this);
    if (state != state_) {
      delete state_;
      state_ = state;
    }
  }
  matrix_->phase_ = GetStateCode();
}
TetrisActuator::TetrisActuator(Matrix *matrix) : matrix_(matrix), state_(nullptr), graphics_(nullptr), generator_(), playing_time_(0) {
  if (matrix != nullptr)
    for (int i = 0; i < 6; ++i) {
      matrix->next_.push_back(new Tetrimino(generator_.GetType()));
    }
}
int TetrisActuator::GetStateCode() const {
  if (state_) return state_->code_;
  return 0;
}
TetrisActuator::TetrisActuator() : TetrisActuator(nullptr) {
}
TetrisActuatorState *Generation::Handle(TetrisActuator &context) {
  TetrisActuatorState::Handle(context);
  if (timer_ >= 200) {
    if (hold_) {
      std::swap(context.matrix_->active_, context.matrix_->held_);
      context.hold_flag = true;
    } else if (context.matrix_->active_ != nullptr) {
      context.matrix_->active_ = nullptr;
    }
    if (context.matrix_->active_ == nullptr) {
      auto tetrimino = new Tetrimino(context.generator_.GetType());
      context.matrix_->active_ = context.matrix_->next_.front();
      context.matrix_->next_.pop_front();
      context.matrix_->next_.push_back(tetrimino);
      if (!context.matrix_->IsLandsOnTheSurface(*context.matrix_->active_)) {
        context.matrix_->active_->pos_.y++;
      } else {
        //TODO Game Over Phase
      }
      return new Falling();
    }
  }
  return this;
}
Generation::Generation(bool hold) : hold_(hold) {
  code_ = 1;
}
Generation::~Generation() = default;
Falling::Falling() {
  code_ = 2;
}
TetrisActuatorState *Falling::Handle(TetrisActuator &context) {
  TetrisActuatorState::Handle(context);
  context.matrix_->ghost_->pos_ = context.matrix_->active_->pos_;
  context.matrix_->ghost_->type_ = context.matrix_->active_->type_;
  context.matrix_->ghost_->mino_relative_pos_ = context.matrix_->active_->mino_relative_pos_;
  while (!context.matrix_->IsLandsOnTheSurface(*context.matrix_->ghost_)) {
    context.matrix_->ghost_->pos_.y++;
  }
  if (context.matrix_->IsLandsOnTheSurface(*context.matrix_->active_)) {
    return new Lock(context.matrix_->active_->pos_, context.matrix_->active_->ori_, false);
  } else if (timer_ >= context.falling_interval) {
    context.matrix_->active_->pos_.y++;
    timer_ = 0;
  }
  return this;
}
Falling::~Falling() = default;
TetrisActuatorState *Lock::Handle(TetrisActuator &context) {
  TetrisActuatorState::Handle(context);
  if (context.timer_store.find(kLock_phase_record_timer_name) != context.timer_store.end()) {
    if (context.timer_store[kLock_phase_record_timer_name] != 0) {
      timer_ = context.timer_store[kLock_phase_record_timer_name];
      context.timer_store[kLock_phase_record_timer_name] = 0;
    }
  }
  if (pos_at_entry_.y > context.matrix_->active_->pos_.y) {
    context.timer_store[kLock_phase_record_timer_name] = timer_;
    return new Falling();
  } else if (pos_at_entry_ != context.matrix_->active_->pos_ || ori_at_entry_ != context.matrix_->active_->ori_) {
    if (context.matrix_->IsLandsOnTheSurface(*context.matrix_->active_)) {
      timer_ = 0;
      reset_counter++;
    } else {
      return new Falling();
    }
    pos_at_entry_ = context.matrix_->active_->pos_;
    ori_at_entry_ = context.matrix_->active_->ori_;
  }
  if (timer_ >= 500 || reset_counter >= 15 || hard_drop_) {
    context.matrix_->Solidify();
    context.matrix_->active_ = nullptr;
    context.hold_flag = false;
    return new Pattern();
  }
  return this;
}
Lock::Lock(Vec2 pos_at_entry, Orientation ori_at_entry, bool hard_drop) : pos_at_entry_(pos_at_entry), ori_at_entry_(ori_at_entry), hard_drop_(hard_drop) {
  code_ = 3;
}
Lock::~Lock() = default;
TetrisActuatorState *Pattern::Handle(TetrisActuator &context) {
  TetrisActuatorState::Handle(context);
  context.marked_lines = GetFullLinesIndex(*context.matrix_);
  context.line_counter += context.marked_lines.size();
  if (context.operation_code_ == 1 && context.t_spin_) {
    if (context.t_spin_min_) {
      //TODO t spin
      SDL_Log("t spin min");
    }
    SDL_Log("t spin");
  }
  context.operation_code_ = 0;
  context.t_spin_ = context.t_spin_min_ = false;
  return new Animate();
}
std::vector<int> Pattern::GetFullLinesIndex(Matrix &matrix) {
  std::vector<int> rows;
  int counter = 0;
  for (auto it = matrix.data_.begin(); it != matrix.data_.end(); it++) {
    bool res = true;
    for (const auto &mino : **it) {
      res &= mino != nullptr;
    }
    if (res) {
      rows.push_back(counter);
    }
    counter++;
  }
  return rows;
}
Pattern::~Pattern() = default;
TetrisActuatorState *Animate::Handle(TetrisActuator &context) {
  TetrisActuatorState::Handle(context);
  if (!context.marked_lines.empty()) {
    for (const auto &index : context.marked_lines) {
      context.matrix_->DeleteRow(index);
    }
    context.marked_lines.clear();
  }
  return new Eliminate();
}
Animate::~Animate() = default;
TetrisActuatorState *Eliminate::Handle(TetrisActuator &context) {
  TetrisActuatorState::Handle(context);
  return new Completion();
}
Eliminate::~Eliminate() = default;
TetrisActuatorState *Completion::Handle(TetrisActuator &context) {
  TetrisActuatorState::Handle(context);
  return new Generation(false);
}
Completion::~Completion() = default;

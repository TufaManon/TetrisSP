//
// Created by Tufa Manon on 2023/1/28.
//

#ifndef TETRIS_SCENE_TETRIS_ACTUATOR_H_
#define TETRIS_SCENE_TETRIS_ACTUATOR_H_
#include "generator.h"
#include "graphics.h"
#include "matrix.h"
#include <chrono>
#include <cinttypes>
#include <vector>
class TetrisActuator;
class TetrisActuatorState {
 public:
  virtual TetrisActuatorState *Handle(TetrisActuator &context);
  virtual ~TetrisActuatorState() = default;
  ;
  void CalibrationTime();
  int code_ = 0;
  uint64_t timer_ = 0;

 private:
  uint64_t current_time_ = SDL_GetTicks64();
};

class TetrisActuator {
 public:
  explicit TetrisActuator(Matrix *matrix);
  explicit TetrisActuator();
  void Request(uint64_t delta);
  void SetState(TetrisActuatorState *state);
  int GetStateCode() const;
  TetrisActuatorState *state_;
  Generator generator_;
  Matrix *matrix_;
  Graphics *graphics_;
  std::map<std::string, uint64_t> timer_store;
  uint64_t falling_interval = 500;
  std::vector<int> marked_lines;
  bool hold_flag = false;
  int line_counter = 0;
  bool back_to_back_ = false;
  int level = 1;
  bool t_spin_ = false;
  bool t_spin_min_ = false;
  int operation_code_ = 0;
  std::chrono::milliseconds playing_time_;
};

class Generation : public TetrisActuatorState {
 public:
  explicit Generation(bool hold);
  TetrisActuatorState *Handle(TetrisActuator &context) override;
  ~Generation() override;

 private:
  bool hold_;
};
class Falling : public TetrisActuatorState {
 public:
  Falling();
  TetrisActuatorState *Handle(TetrisActuator &context) override;
  ~Falling() override;
};

class Lock : public TetrisActuatorState {
 public:
  Lock(Vec2 pos_at_entry, Orientation ori_at_entry, bool hard_drop);
  TetrisActuatorState *Handle(TetrisActuator &context) override;
  ~Lock() override;
  bool hard_drop_;
  Vec2 pos_at_entry_;
  Orientation ori_at_entry_;
  int reset_counter = 0;
  const std::string kLock_phase_record_timer_name = "lock phase record timer";
};

class Pattern : public TetrisActuatorState {
 public:
  Pattern() { code_ = 4; };
  TetrisActuatorState *Handle(TetrisActuator &context) override;
  ~Pattern() override;
  static std::vector<int> GetFullLinesIndex(Matrix &matrix);
};

class Animate : public TetrisActuatorState {
 public:
  Animate() { code_ = 5; }
  TetrisActuatorState *Handle(TetrisActuator &context) override;
  ~Animate() override;
};

class Eliminate : public TetrisActuatorState {
 public:
  Eliminate() { code_ = 6; }
  TetrisActuatorState *Handle(TetrisActuator &context) override;
  ~Eliminate() override;
};
class Completion : public TetrisActuatorState {
 public:
  Completion() { code_ = 7; };
  TetrisActuatorState *Handle(TetrisActuator &context) override;
  ~Completion() override;
};
#endif//TETRIS_SCENE_TETRIS_ACTUATOR_H_

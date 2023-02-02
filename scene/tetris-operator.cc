//
// Created by Tufa Manon on 2023/1/28.
//

#include "tetris-operator.h"
#include "audio.h"
const std::array<std::array<Vec2, 5>, 4> SRS::J_L_S_T_Z_OFFSET_DATA = {
    std::array<Vec2, 5>{Vec2(0, 0), Vec2(0, 0), Vec2(0, 0), Vec2(0, 0),
                        Vec2(0, 0)},
    std::array<Vec2, 5>{Vec2(0, 0), Vec2(1, 0), Vec2(1, 1), Vec2(0, -2),
                        Vec2(1, -2)},
    std::array<Vec2, 5>{Vec2(0, 0), Vec2(0, 0), Vec2(0, 0), Vec2(0, 0),
                        Vec2(0, 0)},
    std::array<Vec2, 5>{Vec2(0, 0), Vec2(-1, 0), Vec2(-1, 1), Vec2(0, -2),
                        Vec2(-1, -2)},
};
const std::array<std::array<Vec2, 5>, 4> SRS::I_OFFSET_DATA = {
    std::array<Vec2, 5>{Vec2(0, 0), Vec2(-1, 0), Vec2(2, 0), Vec2(-1, 0),
                        Vec2(2, 0)},
    std::array<Vec2, 5>{Vec2(-1, 0), Vec2(0, 0), Vec2(0, 0), Vec2(0, -1),
                        Vec2(0, 2)},
    std::array<Vec2, 5>{Vec2(-1, -1), Vec2(+1, -1), Vec2(-2, -1), Vec2(1, 0),
                        Vec2(-2, 0)},
    std::array<Vec2, 5>{Vec2(0, -1), Vec2(0, -1), Vec2(0, -1), Vec2(0, 1),
                        Vec2(0, -2)},
};
const std::array<std::array<Vec2, 5>, 4> SRS::O_OFFSET_DATA = {
    std::array<Vec2, 5>{Vec2(0, 0), Vec2(0, 0), Vec2(0, 0), Vec2(0, 0),
                        Vec2(0, 0)},
    std::array<Vec2, 5>{Vec2(0, 1), Vec2(0, 1), Vec2(0, 1), Vec2(0, 1),
                        Vec2(0, 1)},
    std::array<Vec2, 5>{Vec2(-1, 1), Vec2(-1, 1), Vec2(-1, 1), Vec2(-1, 1),
                        Vec2(-1, 1)},
    std::array<Vec2, 5>{Vec2(-1, 0), Vec2(-1, -0), Vec2(-1, 0), Vec2(-1, 0),
                        Vec2(-1, 0)},
};
std::array<Vec2, 5> SRS::GetOffSet(TetriminoType type,
                                   Orientation ori_1,
                                   Orientation ori_2) {
  std::array<Vec2, 5> f, s;
  if (type == I) {
    f = I_OFFSET_DATA[ori_1];
    s = I_OFFSET_DATA[ori_2];
  } else if (type == O) {
    f = O_OFFSET_DATA[ori_1];
    s = O_OFFSET_DATA[ori_2];
  } else {
    f = J_L_S_T_Z_OFFSET_DATA[ori_1];
    s = J_L_S_T_Z_OFFSET_DATA[ori_2];
  }
  return std::array<Vec2, 5>{f[0] - s[0], f[1] - s[1], f[2] - s[2], f[3] - s[3], f[4] - s[4]};
}
SRS::ResultType SRS::Get(const Tetrimino &target, bool clockwise) {
  int cos = 0, sin, m_sin;
  auto pos = target.mino_relative_pos_;
  if (!clockwise) {
    sin = -1;
    m_sin = 1;
  } else {
    sin = 1;
    m_sin = -1;
  }
  std::array<Vec2, 4> rotated_mino_pos{};
  for (int i = 0; i < 4; ++i) {
    rotated_mino_pos.at(i).x = cos * pos[i].x + m_sin * pos[i].y;
    rotated_mino_pos.at(i).y = sin * pos[i].x + cos * pos[i].y;
  }
  auto ori = clockwise ? target.ori_ >> 1 : target.ori_ << 1;
  auto offset = GetOffSet(target.type_, target.ori_, ori);
  return ResultType{rotated_mino_pos, offset, ori};
}

bool Move(TetrisActuator &actuator, Vec2 transform) {
  if (actuator.GetStateCode() != 2 && actuator.GetStateCode() != 3) return false;
  auto matrix = actuator.matrix_;
  matrix->active_->pos_ = matrix->active_->pos_ + transform;
  if (matrix->IsEmbedsInObs(*matrix->active_)) {
    matrix->active_->pos_ = matrix->active_->pos_ - transform;
    return false;
  }
  actuator.operation_code_ = 2;
  Audio::GetInstance().Play_Move();
  return true;
}
bool HardDrop(TetrisActuator &actuator) {
  if (actuator.GetStateCode() != 2 && actuator.GetStateCode() != 3) return false;
  while (!actuator.matrix_->IsLandsOnTheSurface(*actuator.matrix_->active_)) {
    actuator.matrix_->active_->pos_.y++;
  }
  actuator.SetState(new Lock(actuator.matrix_->active_->pos_, actuator.matrix_->active_->ori_, true));
  return true;
}
bool Rotate(TetrisActuator &actuator, bool clockwise) {
  if (actuator.GetStateCode() != 2 && actuator.GetStateCode() != 3) return false;
  auto srs_res = SRS::Get(*actuator.matrix_->active_, clockwise);
  std::swap(actuator.matrix_->active_->mino_relative_pos_, srs_res.rotated_mino_pos);
  for (int i = 0; i < 5; ++i) {
    actuator.matrix_->active_->pos_ = actuator.matrix_->active_->pos_ + srs_res.offsets.at(i);
    if (!actuator.matrix_->IsEmbedsInObs(*actuator.matrix_->active_)) {
      actuator.matrix_->active_->ori_ = srs_res.next_ori;
      actuator.operation_code_ = 1;
      int state = actuator.matrix_->CheckTSpin();
      if (state != 0) {
        actuator.t_spin_ = true;
        if (i == 4) actuator.t_spin_min_ = false;
        else if (state == 3)
          actuator.t_spin_min_ = true;
      }
      return true;
    }
    actuator.matrix_->active_->pos_ = actuator.matrix_->active_->pos_ - srs_res.offsets.at(i);
  }
  std::swap(actuator.matrix_->active_->mino_relative_pos_, srs_res.rotated_mino_pos);
  return false;
}
bool Hold(TetrisActuator &actuator) {
  if (actuator.GetStateCode() != 2 && actuator.GetStateCode() != 3) return false;
  if (!actuator.hold_flag) {
    actuator.hold_flag = true;
    actuator.SetState(new Generation(true));
    return true;
  }
  return false;
}

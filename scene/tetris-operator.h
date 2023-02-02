//
// Created by Tufa Manon on 2023/1/28.
//

#ifndef TETRIS_SCENE_TETRIS_OPERATOR_H_
#define TETRIS_SCENE_TETRIS_OPERATOR_H_
#include "matrix.h"
#include "tetris-actuator.h"
#include "tty.h"
class SRS {
 public:
  struct ResultType {
    std::array<Vec2, 4> rotated_mino_pos{};
    std::array<Vec2, 5> offsets{};
    Orientation next_ori{};
  };
  static std::array<Vec2, 5> GetOffSet(TetriminoType type,
                                       Orientation ori_1,
                                       Orientation ori_2);
  static ResultType Get(const Tetrimino &tetrimino, bool clockwise);

 private:
  static const std::array<std::array<Vec2, 5>, 4> J_L_S_T_Z_OFFSET_DATA;
  static const std::array<std::array<Vec2, 5>, 4> I_OFFSET_DATA;
  static const std::array<std::array<Vec2, 5>, 4> O_OFFSET_DATA;
};
bool Move(TetrisActuator &actuator, Vec2 transform);
bool HardDrop(TetrisActuator &actuator);
bool Rotate(TetrisActuator &actuator , bool right);
bool Hold(TetrisActuator &actuator);
#endif//TETRIS_SCENE_TETRIS_OPERATOR_H_

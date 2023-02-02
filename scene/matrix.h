//
// Created by Tufa Manon on 2023/1/27.
//

#ifndef TETRIS_SCENE_MATRIX_H_
#define TETRIS_SCENE_MATRIX_H_
#include "tty.h"
#include <array>
#include <list>
#include <map>
#include <string>
enum TetriminoType {
  O,
  I,
  T,
  L,
  J,
  S,
  Z
};

enum Orientation {
  NORTH,
  SOUTH,
  EAST,
  WEST
};
inline Orientation operator>>(const Orientation &state, int i) {
  auto c = (int) state + i;
  return c >= 0 ? (Orientation) (c % 4) : (Orientation) (4 + (c % 4));
}

inline Orientation operator<<(const Orientation &state, int i) {
  auto c = (int) state - i;
  return c >= 0 ? (Orientation) (c % 4) : (Orientation) (4 + (c % 4));
}
class Tetrimino;

using Mino = Tetrimino;

class Tetrimino {
 public:
  explicit Tetrimino(TetriminoType type);
  TetriminoType type_;
  Orientation ori_;
  int mino_point_counter_ = 4;
  std::array<Vec2,4> mino_relative_pos_;
  Vec2 pos_;
  static const int kMino_pos_pool_[7][8];
};

class Matrix {
 public:
  Matrix();
  ~Matrix();
  void DeleteRow(int row_index);
  bool IsLandsOnTheSurface(Tetrimino &tetrimino);
  bool IsEmbedsInObs(Tetrimino &tetrimino);
  int CheckTSpin();
  using Row = std::array<Mino *, 10>;
  std::list<Row *> data_;
  Tetrimino *active_;
  Tetrimino *held_;
  Tetrimino *ghost_;
  std::list<Tetrimino *> next_;
  int cell_size_ = 36;
  Vec2 coord;
  int phase_;
  int id = 0;
  void Solidify();
};
#endif//TETRIS_SCENE_MATRIX_H_
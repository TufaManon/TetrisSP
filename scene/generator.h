//
// Created by Tufa Manon on 2023/1/29.
//

#ifndef TETRIS_SCENE_GENERATOR_H_
#define TETRIS_SCENE_GENERATOR_H_
#include "matrix.h"
class Generator {
 public:
  explicit Generator();
  TetriminoType GetType();
  void Shuffle();
  int top;
  TetriminoType types_[7];
};

#endif//TETRIS_SCENE_GENERATOR_H_

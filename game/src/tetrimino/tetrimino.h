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
// Created by Tufa Manon on 2023/1/22.
//

#ifndef TETRISSP_GAME_SRC_TETRIMINO_TETRIMINO_H_
#define TETRISSP_GAME_SRC_TETRIMINO_TETRIMINO_H_
#include <array>
#include "utils/point.h"

namespace tetris_sp::game::tetrimino {
enum Type {
  O, I, T, L, J, S, Z
};

enum Orientation {
  FACE_UP,
  FACE_RIGHT,
  FACE_DOWN,
  FACE_LEFT,
};

inline Orientation operator>>(const Orientation &state, int i) {
  auto c = (int) state + i;
  return c >= 0 ? (Orientation) (c % 4) : (Orientation) (4 + (c % 4));
}

inline Orientation operator<<(const Orientation &state, int i) {
  auto c = (int) state - i;
  return c >= 0 ? (Orientation) (c % 4) : (Orientation) (4 + (c % 4));
}
struct Tetrimino {
  std::array<utils::Point, 4> mino_relative_position;
  utils::Point pos;
  Type type;
  Orientation ori;
};
} // tetrimino

#endif  // TETRISSP_GAME_SRC_TETRIMINO_TETRIMINO_H_
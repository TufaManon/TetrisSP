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

#ifndef TETRISSP_GAME_SRC_TETRIMINO_MINO_H_
#define TETRISSP_GAME_SRC_TETRIMINO_MINO_H_

namespace tetris_sp::game::tetrimino {
enum Color {
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  LIGHT_BLUE,
  BLUE,
  VIOLET,
};

struct Mino {
  int x, y;
  Color color;
  bool is_ghost;
  bool is_blinking;
  bool is_flash_once;
};

} // tetrimino

#endif //TETRISSP_GAME_SRC_TETRIMINO_MINO_H_
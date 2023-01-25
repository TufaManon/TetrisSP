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

#ifndef TETRISSP_GAME_SRC_SERVER_SRS_H_
#define TETRISSP_GAME_SRC_SERVER_SRS_H_
#include <array>
#include <utils/point.h>
#include "tetrimino/tetrimino.h"
namespace tetris_sp::game::server {

class SRS {
 public:
  struct ResultType {
    std::array<utils::Point, 4> rotated_mino_pos;
    std::array<tetris_sp::game::utils::Point, 5> offsets;
    tetrimino::Orientation next_orien;
  };
  static std::array<utils::Point, 5> GetOffSet(tetrimino::Type type,
                                               tetrimino::Orientation ori_1,
                                               tetrimino::Orientation ori_2);
  ResultType operator()(const tetrimino::Tetrimino &target, bool clockwise) const;
 private:
  static const std::array<std::array<utils::Point, 5>, 4> J_L_S_T_Z_OFFSET_DATA;
  static const std::array<std::array<utils::Point, 5>, 4> I_OFFSET_DATA;
  static const std::array<std::array<utils::Point, 5>, 4> O_OFFSET_DATA;
};

} // server

#endif //TETRISSP_GAME_SRC_SERVER_SRS_H_

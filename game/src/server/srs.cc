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

#include "srs.h"

namespace tetris_sp::game::server {
const std::array<std::array<utils::Point, 5>, 4> SRS::J_L_S_T_Z_OFFSET_DATA = {
    std::array<utils::Point, 5>{utils::Point(0, 0), utils::Point(0, 0), utils::Point(0, 0), utils::Point(0, 0),
                                utils::Point(0, 0)},
    std::array<utils::Point, 5>{utils::Point(0, 0), utils::Point(1, 0), utils::Point(1, 1), utils::Point(0, -2),
                                utils::Point(1, -2)},
    std::array<utils::Point, 5>{utils::Point(0, 0), utils::Point(0, 0), utils::Point(0, 0), utils::Point(0, 0),
                                utils::Point(0, 0)},
    std::array<utils::Point, 5>{utils::Point(0, 0), utils::Point(-1, 0), utils::Point(-1, 1), utils::Point(0, -2),
                                utils::Point(-1, -2)},
};
const std::array<std::array<utils::Point, 5>, 4> SRS::I_OFFSET_DATA = {
    std::array<utils::Point, 5>{utils::Point(0, 0), utils::Point(-1, 0), utils::Point(2, 0), utils::Point(-1, 0),
                                utils::Point(2, 0)},
    std::array<utils::Point, 5>{utils::Point(-1, 0), utils::Point(0, 0), utils::Point(0, 0), utils::Point(0, -1),
                                utils::Point(0, 2)},
    std::array<utils::Point, 5>{utils::Point(-1, -1), utils::Point(+1, -1), utils::Point(-2, -1), utils::Point(1, 0),
                                utils::Point(-2, 0)},
    std::array<utils::Point, 5>{utils::Point(0, -1), utils::Point(0, -1), utils::Point(0, -1), utils::Point(0, 1),
                                utils::Point(0, -2)},
};
const std::array<std::array<utils::Point, 5>, 4> SRS::O_OFFSET_DATA = {
    std::array<utils::Point, 5>{utils::Point(0, 0), utils::Point(0, 0), utils::Point(0, 0), utils::Point(0, 0),
                                utils::Point(0, 0)},
    std::array<utils::Point, 5>{utils::Point(0, 1), utils::Point(0, 1), utils::Point(0, 1), utils::Point(0, 1),
                                utils::Point(0, 1)},
    std::array<utils::Point, 5>{utils::Point(-1, 1), utils::Point(-1, 1), utils::Point(-1, 1), utils::Point(-1, 1),
                                utils::Point(-1, 1)},
    std::array<utils::Point, 5>{utils::Point(-1, 0), utils::Point(-1, -0), utils::Point(-1, 0), utils::Point(-1, 0),
                                utils::Point(-1, 0)},
};
std::array<utils::Point, 5> SRS::GetOffSet(tetrimino::Type type,
                                           tetrimino::Orientation ori_1,
                                           tetrimino::Orientation ori_2) {
  std::array<tetris_sp::game::utils::Point, 5> f, s;
  if (type == tetrimino::I) {
    f = I_OFFSET_DATA[ori_1];
    s = I_OFFSET_DATA[ori_2];
  } else if (type == tetrimino::O) {
    f = O_OFFSET_DATA[ori_1];
    s = O_OFFSET_DATA[ori_2];
  } else {
    f = J_L_S_T_Z_OFFSET_DATA[ori_1];
    s = J_L_S_T_Z_OFFSET_DATA[ori_2];
  }
  return std::array<utils::Point, 5>{f[0] - s[0], f[1] - s[1], f[2] - s[2], f[3] - s[3], f[4] - s[4]};

}
SRS::ResultType SRS::operator()(const tetrimino::Tetrimino &target, bool clockwise) const {
  int cos = 0, sin, m_sin;
  auto pos = target.mino_relative_position;
  if (!clockwise) {
    sin = -1;
    m_sin = 1;
  } else {
    sin = 1;
    m_sin = -1;
  }
  std::array<utils::Point, 4> rotated_mino_pos{};
  for (int i = 0; i < 4; ++i) {
    rotated_mino_pos.at(i).x = cos * pos.at(i).x + m_sin * pos.at(i).y;
    rotated_mino_pos.at(i).y = sin * pos.at(i).x + cos * pos.at(i).y;
  }
  auto ori = clockwise ? target.ori >> 1 : target.ori << 1;
  auto offset = GetOffSet(target.type, target.ori, ori);
  return ResultType{rotated_mino_pos, offset, ori};
}
} // server
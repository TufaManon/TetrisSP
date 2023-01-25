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

#ifndef TETRISSP_GAME_SRC_UTILS_POINT_H_
#define TETRISSP_GAME_SRC_UTILS_POINT_H_
#include <ostream>
namespace tetris_sp::game::utils {
class Point {
 public:
  Point() = default;
  Point(int x, int y);
  int x, y;
  bool operator==(const Point &rhs) const;
  bool operator!=(const Point &rhs) const;
  bool operator<(const Point &rhs) const;
  bool operator>(const Point &rhs) const;
  bool operator<=(const Point &rhs) const;
  bool operator>=(const Point &rhs) const;
  friend std::ostream &operator<<(std::ostream &os, const Point &point);
  Point operator-(const Point &rhs) const;
  const Point &operator-=(const Point &rhs);
  Point operator+(const Point &rhs) const;
  const Point &operator+=(const Point &rhs);
};

}

#endif //TETRISSP_GAME_SRC_UTILS_POINT_H_
